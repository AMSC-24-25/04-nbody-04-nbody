#include "nbody.hpp"
#include <vector>
#include <iostream>

using namespace nbody;

int main(){

    Particle<double, 3> p1({0.0, 0.0, 10.0}, {0.0, 0.0, 0.0}, 1.0);
    Particle<double, 3> p2({10.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);
    Particle<double, 3> p3({0.0, 10.0, 0.0}, {0.0, 0.0, 0.0}, 1.0);

    nbody::Nbody<double, 3> nbody;

    nbody.addParticle(p1);
    nbody.addParticle(p2);
    nbody.addParticle(p3);

    for(int i = 0; i < 10; i++ ){
        nbody.update();
        std::cout << nbody.particles[0].position[0] << " " << nbody.particles[0].position[1] << " " << nbody.particles[0].position[2] << std::endl;
        std::cout << nbody.particles[1].position[0] << " " << nbody.particles[1].position[1] << " " << nbody.particles[1].position[2] << std::endl;
        std::cout << nbody.particles[2].position[0] << " " << nbody.particles[2].position[1] << " " << nbody.particles[2].position[2] << std::endl;
        std::cout << std::endl;
    }

    return 0;
}