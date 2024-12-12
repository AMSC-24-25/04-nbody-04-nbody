#define DIM 3
#define G 6.67430e-11
#include <vector>
#include <cmath>

class Particle{
    public:
        std::vector<double> position;
        std::vector<double> velocity;
        double mass;

        void update(std::vector<double> pos, std::vector<double> vel){
            this->position = pos;
            this->velocity = vel;
        }
};

class Nbody{
    public:
        std::vector<std::vector<double>> forces;
        std::vector<Particle> particles;
        double dt;

        void update(){

            double distance = 0.0;
            double x_diff=0.0, y_diff=0.0, z_diff=0.0;

            for(int q = 0; q < forces.size(); q++){
                forces[q] = std::vector<double>(DIM, 0.0);
            }
            
            for(int i = 0; i < particles.size(); i++){
                for(int j = i + 1; j < particles.size(); j++){
                    x_diff = particles[i].position[0] - particles[j].position[0];
                    y_diff = particles[i].position[1] - particles[j].position[1];
                    z_diff = particles[i].position[2] - particles[j].position[2];

                    distance = sqrt(x_diff*x_diff + y_diff*y_diff + z_diff*z_diff);

                    
                    forces[i][0] += G * particles[i].mass * particles[j].mass * x_diff / pow(distance, 3);
                    forces[i][1] += G * particles[i].mass * particles[j].mass * y_diff / pow(distance, 3);
                    forces[i][2] += G * particles[i].mass * particles[j].mass * z_diff / pow(distance, 3);

                    forces[j][0] -= G * particles[i].mass * particles[j].mass * x_diff / pow(distance, 3);
                    forces[j][1] -= G * particles[i].mass * particles[j].mass * y_diff / pow(distance, 3);
                    forces[j][2] -= G * particles[i].mass * particles[j].mass * z_diff / pow(distance, 3);

                }
            }

            for(int i = 0; i < particles.size(); i++){
                for(int k = 0; k < DIM; k++){;
                    particles[i].position[k] += particles[i].velocity[k] * dt;
                    particles[i].velocity[k] += forces[i][k] * dt / particles[i].mass;
                }
            }
        }
}