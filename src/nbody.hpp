#define G 6.67430e-11
#ifndef NBODY_HPP
#define NBODY_HPP

#include <array>
#include <vector>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <string>

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

    template <typename T, int DIM>
    class Nbody {
    public:
        std::vector<std::array<T, DIM>> forces;
        std::vector<Particle<T, DIM>> particles;
        T dt;

        // Add a particle to the simulation
        void addParticle(const Particle<T, DIM>& p) {
            particles.push_back(p);
            forces.push_back(std::array<T, DIM>{});  // Initialize forces to zero
        }

        // Set the time step
        void setDt(T d) {
            dt = d;
        }

        // Update the positions and velocities of particles
        void update() {
            // Reset forces to zero
            for (auto& force : forces) {
                force.fill(0.0);
            }

            // Compute gravitational forces
            for (size_t i = 0; i < particles.size(); i++) {
                for (size_t j = i + 1; j < particles.size(); j++) {
                    T distance = 0.0;
                    std::array<T, DIM> diff{};

                    for (int k = 0; k < DIM; k++) {
                        diff[k] = particles[j].position[k] - particles[i].position[k];
                        distance += diff[k] * diff[k];
                    }
                    distance = std::sqrt(distance);

                    if (distance > 0) {
                        for (int k = 0; k < DIM; k++) {
                            T force = G * particles[i].mass * particles[j].mass * diff[k] / (distance * distance * distance);
                            forces[i][k] += force;
                            forces[j][k] -= force;
                        }
                    }
                }
            }

            // Update positions and velocities
            for (size_t i = 0; i < particles.size(); i++) {
                for (int k = 0; k < DIM; k++) {
                    particles[i].velocity[k] += forces[i][k] * dt / particles[i].mass;
                    particles[i].position[k] += particles[i].velocity[k] * dt;
                }
            }
        }

        // Export current simulation state to CSV
        void exportToCsv(const std::string& filename) {
            std::ofstream outFile(filename, std::ios::app);
            if (!outFile.is_open()) {
                throw std::runtime_error("Unable to open file for writing: " + filename);
            }

            static bool firstCall = true;

            if (firstCall) {
                outFile << particles.size() << " " << dt << "\n";
                firstCall = false;
            }

            for (const auto& particle : particles) {
                for (int k = 0; k < DIM; k++) {
                    outFile << particle.position[k] << " ";
                }
                outFile << "\n";
            }
            outFile << std::endl;
        }
    };

} // namespace nbody

#endif // NBODY_HPP
