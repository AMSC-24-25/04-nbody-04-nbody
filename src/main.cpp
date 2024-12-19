#include "nbody.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "json.hpp"

using namespace nbody;

int main() {
    const std::string filename = "output.json";
    nlohmann::json jsonOutput = nlohmann::json::array(); 

    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        try {
            inFile >> jsonOutput;
            if (!jsonOutput.is_array()) {
                jsonOutput = nlohmann::json::array(); 
            }
        } catch (...) {
            jsonOutput = nlohmann::json::array(); 
        }
    }

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

    for (int i = 0; i < 1000; ++i) {
        nbody.update();
        nbody.exportToCsv("output.csv");
    }

    return 0;
}