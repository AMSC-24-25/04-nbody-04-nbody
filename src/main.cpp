#include "nbody.hpp"
#include <vector>
#include <iostream>

using namespace nbody;

int main(){

    Particle<double, 3> p1({0.0, 0.0, 10.0}, {0.0, 0.0, 0.0}, 200000000000000000.0);
    Particle<double, 3> p2({10.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 10000000.0);
    Particle<double, 3> p3({0.0, 10.0, 0.0}, {0.0, 0.0, 0.0}, 90000.0);
    Particle<double, 3> p4({0.0, 30.0, 0.0}, {0.0, 0.0, 0.0}, 90000000.0);

    nbody::Nbody<double, 3> nbody;

    nbody.addParticle(p1);
    nbody.addParticle(p2);
    nbody.addParticle(p3);
    nbody.addParticle(p4);

    nbody.setDt(1.0);

    for(int i = 0; i < 1000; i++ ){
        nbody.update();
        std::cout << nbody.particles[0].position[0] << " " << nbody.particles[0].position[1] << " " << nbody.particles[0].position[2] << std::endl;
        std::cout << nbody.particles[1].position[0] << " " << nbody.particles[1].position[1] << " " << nbody.particles[1].position[2] << std::endl;
        std::cout << nbody.particles[2].position[0] << " " << nbody.particles[2].position[1] << " " << nbody.particles[2].position[2] << std::endl;
        std::cout << nbody.particles[3].position[0] << " " << nbody.particles[3].position[1] << " " << nbody.particles[3].position[2] << std::endl;
        std::cout << std::endl;
    }

    return 0;
}