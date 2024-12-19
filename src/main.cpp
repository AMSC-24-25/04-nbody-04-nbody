// #include "nbody.hpp"
#include "nbody_parallel.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace nbody;
#define DIM 2

int main() {
    std::string fileName="output.csv";
    std::ofstream outFile(fileName, std::ios::trunc);  
    if (!outFile.is_open()) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura: output.csv");
    }

    Particle<double, DIM> p1({5.0, 5.0}, {0.0, 0.0}, 5.0e10);        // Massive central body
    Particle<double, DIM> p2({10.0, 10.0}, {0.0, 0.8}, 1.0e10);      // Orbiting body 1
    Particle<double, DIM> p3({10.0, 5.0}, {-0.7, 0.0}, 1.0e10);     // Orbiting body 2
    Particle<double, DIM> p4({0.0, 10.0}, {0.5, -0.5}, 5.0e9);   // Diagonal trajectory

    nbody::Nbody<double, DIM> nbody;
    double time_step=1.0;

    nbody.addParticle(p1);
    nbody.addParticle(p2);
    nbody.addParticle(p3);
    nbody.addParticle(p4);

    nbody.setDt(time_step);

    auto start = std::chrono::high_resolution_clock::now();
    
    double currentTime = 0.0;
    double simulationTime = 100.0;  // 10 seconds
    while (currentTime < simulationTime) {
        nbody.update();
        nbody.exportToCsv(fileName);
        currentTime +=time_step;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Execution time: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}