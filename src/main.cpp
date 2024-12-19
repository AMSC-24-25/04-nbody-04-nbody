#include "nbody.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using namespace nbody;
#define DIM 2

int main() {
    std::ofstream outFile("output.csv", std::ios::trunc);  
    if (!outFile.is_open()) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura: output.csv");
    }

    Particle<double, DIM> p1({0.0, 0.0}, {0.0, 0.0}, 200000000000000000.0);
    Particle<double, DIM> p2({10.0, 0.0}, {0.0, 0.0}, 10000000.0);
    Particle<double, DIM> p3({0.0, 10.0}, {0.0, 0.0}, 90000.0);
    Particle<double, DIM> p4({0.0, 30.0}, {0.0, 0.0}, 90000000.0);

    nbody::Nbody<double, DIM> nbody;

    nbody.addParticle(p1);
    nbody.addParticle(p2);
    nbody.addParticle(p3);
    nbody.addParticle(p4);

    nbody.setDt(1.0);

    for (int i = 0; i < 1000; ++i) {
        nbody.update();
        nbody.exportToCsv("output.csv");
    }

    return 0;
}