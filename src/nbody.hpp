#define G 6.67430e-11
#include <vector>
#include <cmath>

template<typename T, int DIM>
class Particle {
public:
    std::vector<T> position;
    std::vector<T> velocity;
    T mass;

    void update(const std::vector<T>& pos, const std::vector<T>& vel) {
        this->position = pos;
        this->velocity = vel;
    }
};

template<typename T, int DIM>
class Nbody {
public:
    std::vector<std::vector<T>> forces;
    std::vector<Particle<T, DIM>> particles;
    T dt;

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
};