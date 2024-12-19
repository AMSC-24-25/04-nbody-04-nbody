#ifndef NBODY_HPP
#define NBODY_HPP

#include <array>
#include <vector>
#include <cmath>
#include <fstream>
#include <stdexcept>
#include <string>

#define G 1.0

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

        void addParticle(const Particle<T, DIM>& p) {
            particles.push_back(p);
            forces.push_back(std::array<T, DIM>{});  // Initialize forces to zero
        }

        void setDt(T d) {
            dt = d;
        }

        void update() {
            // Reset forces to zero
            for (auto& force : forces) {
                force.fill(0.0);
            }

            // Compute gravitational forces
            for (size_t i = 0; i < particles.size(); i++) {
                for (size_t j = i + 1; j < particles.size(); j++) {
                    T distance = 0.0;
                    std::array<T, DIM> r_ij{};  // Vector from i to j

                    // Calculate vector from particle i to j
                    for (int k = 0; k < DIM; k++) {
                        r_ij[k] = particles[j].position[k] - particles[i].position[k];
                        distance += r_ij[k] * r_ij[k];
                    }
                    distance = std::sqrt(distance);

                    if (distance > 0) {
                        // Calculate magnitude of gravitational force
                        T force_magnitude = G * particles[i].mass * particles[j].mass / 
                                         (distance * distance);

                        // Apply force components
                        for (int k = 0; k < DIM; k++) {
                            // Force direction is along r_ij
                            T force_component = -force_magnitude * r_ij[k] / distance;
                            forces[i][k] -= force_component;  // Force on i points toward j
                            forces[j][k] += force_component;  // Force on j points toward i
                        }
                    }
                }
            }

            // Update positions and velocities using Euler integration
            for (size_t i = 0; i < particles.size(); i++) {
                // First update velocity using F = ma
                for (int k = 0; k < DIM; k++) {
                    particles[i].velocity[k] += (forces[i][k] / particles[i].mass) * dt;
                }
                
                // Then update position using new velocity
                for (int k = 0; k < DIM; k++) {
                    particles[i].position[k] += particles[i].velocity[k] * dt;
                }
            }
        }

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