#define G 6.67430e-11
#ifndef NBODY_HPP
#define NBODY_HPP

#include <array>
#include <vector>
#include <cmath>
#include <fstream>
#include <exception>
#include "json.hpp"

namespace nbody {

    template <typename T, int D>
    class Particle {
    public:
        std::array<T, D> position;
        std::array<T, D> velocity;
        T mass;

        Particle(const std::array<T, D>& pos, const std::array<T, D>& vel, T m)
            : position(pos), velocity(vel), mass(m) {}
    };

    template<typename T, int DIM>
    class Nbody {
    public:
        std::vector<std::vector<T>> forces;
        std::vector<Particle<T, DIM>> particles;
        T dt;

        void addParticle(const Particle<T, DIM>& p) {
            particles.push_back(p);
            forces.push_back(std::vector<T>(DIM, 0.0));
        }

        void setDt(T d) {
            dt = d;
        }

        void update() {
            T distance = 0.0;
            std::vector<T> diff(DIM, 0.0);

            for (int q = 0; q < forces.size(); q++) {
                forces[q] = std::vector<T>(DIM, 0.0);
            }

            for (int i = 0; i < particles.size(); i++) {
                for (int j = i + 1; j < particles.size(); j++) {
                    for (int k = 0; k < DIM; k++) {
                        diff[k] = particles[i].position[k] - particles[j].position[k];
                    }

                    distance = 0.0;
                    for (int k = 0; k < DIM; k++) {
                        distance += diff[k] * diff[k];
                    }
                    distance = std::sqrt(distance);

                    for (int k = 0; k < DIM; k++) {
                        T force = G * particles[i].mass * particles[j].mass * diff[k] / std::pow(distance, 3);
                        forces[i][k] += force;
                        forces[j][k] -= force;
                    }
                }
            }

            for (int i = 0; i < particles.size(); i++) {
                for (int k = 0; k < DIM; k++) {
                    particles[i].position[k] += particles[i].velocity[k] * dt;
                    particles[i].velocity[k] += forces[i][k] * dt / particles[i].mass;
                }
            }
        }

        void exportToCsv(const std::string& filename) {
            std::ofstream outFile;

            bool fileExists = std::ifstream(filename).good();
            outFile.open(filename, std::ios::app);
            if (!outFile.is_open()) {
                throw std::runtime_error("Impossibile aprire il file per la scrittura: " + filename);
            }

            if (!fileExists) {
                outFile << "step,particle_id,mass";
                for (int k = 0; k < DIM; ++k) {
                    outFile << ",position_" << k;
                    outFile << ",velocity_" << k;
                }
                outFile << "\n";
            }

            static int step = 0;
            for (size_t i = 0; i < particles.size(); ++i) {
                outFile << step << "," << i << "," << particles[i].mass;
                for (int k = 0; k < DIM; ++k) {
                    outFile << "," << particles[i].position[k];
                }
                for (int k = 0; k < DIM; ++k) {
                    outFile << "," << particles[i].velocity[k];
                }
                outFile << "\n";
            }
            ++step;
        }
    };
}

#endif