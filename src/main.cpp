#include "nbody.hpp"
// #include "nbody_parallel.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace nbody;
#define DIM 2

int main() {
    std::string fileName="output.csv";
    // std::string fileName="output_parallel.csv";
    std::ofstream outFile(fileName, std::ios::trunc);  
    if (!outFile.is_open()) {
        throw std::runtime_error("Impossibile aprire il file per la scrittura: output.csv");
    }

    // Create a system with 1000 particles
    nbody::Nbody<double, DIM> nbody;
    double time_step = 1.0;
    
    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> pos_dist(-10.0, 10.0);  // Position distribution
    std::uniform_real_distribution<> vel_dist(-0.5, 0.5);    // Velocity distribution
    std::uniform_real_distribution<> mass_dist(0.1, 1.0);    // Mass distribution

    // Generate 1000 particles with random positions, velocities, and masses
    for (int i = 0; i < 400; ++i) {
        std::array<double, DIM> position;
        std::array<double, DIM> velocity;
        
        // Generate random position and velocity components
        for (int d = 0; d < DIM; ++d) {
            position[d] = pos_dist(gen);
            velocity[d] = vel_dist(gen);
        }
        
        double mass = mass_dist(gen);
        Particle<double, DIM> p(position, velocity, mass);
        nbody.addParticle(p);
    }

    nbody.setDt(time_step);

    auto start = std::chrono::high_resolution_clock::now();
    
    double currentTime = 0.0;
    double simulationTime = 1000.0;
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