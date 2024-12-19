# N-Body Simulation

This project implements an N-body gravitational simulation in C++, with both serial and parallel (OpenMP) versions. The simulation calculates the gravitational interactions between multiple particles in a 2D or 3D space.

## Overview

The N-body problem simulates the motion of particles under gravitational forces. Each particle is affected by the gravitational pull of all other particles in the system, following Newton's law of universal gravitation:

F = G * (m1 * m2) / r^2

where:
- F is the gravitational force between two particles
- G is the gravitational constant (6.67430e-11 m³/kg·s²)
- m1, m2 are the masses of the particles
- r is the distance between the particles

## Features

- 2D particle simulation with gravitational interactions
- Both serial and parallel (OpenMP) implementations
- CSV output for position and velocity data
- Python-based animation visualization
- Template-based implementation for different numeric types

## Prerequisites

- C++ compiler with C++20 support
- CMake (>= 3.20)
- OpenMP
- Python 3 with PIL (Python Imaging Library) for visualization

## Building the Project

```bash
mkdir build
cd build
cmake ..
make
```

## Running the Simulation

1. Run the simulation:
```bash
./bin/nbody
```

2. Visualize the results:
```bash
python ../animate.py output.csv animation.gif 
```

## Project Structure

- `nbody.hpp` - Main header file containing the serial implementation
- `nbody_parallel.hpp` - Header file containing the OpenMP parallel implementation
- `main.cpp` - Example usage and simulation setup
- `animate.py` - Python script for generating visualization
- `CMakeLists.txt` - CMake build configuration

## Implementation Details

### Data Structures

The project uses two main classes:

1. `Particle`: Represents a single particle with:
   - Position (2D - 3D array)
   - Velocity (2D - 3D array)
   - Mass (scalar)

2. `Nbody`: Main simulation class with:
   - Vector of particles
   - Force calculations
   - Time integration
   - CSV export functionality

### Algorithms

The simulation uses:
- Direct summation method for force calculations
- Euler integration for updating positions and velocities
- OpenMP parallelization for force calculations in the parallel version

### Parallelization

The parallel version uses OpenMP to:
- Parallelize the force calculations between particles
- Use thread-local storage for intermediate force calculations
- Reduce false sharing by using appropriate data structures

## Example Usage

```cpp
// Create particles
Particle<double, 2> p1({0.0, 0.0}, {0.0, 0.0}, 5.0e10);  // Central body
Particle<double, 2> p2({20.0, 0.0}, {0.0, 0.8}, 1.0e10); // Orbiting body

// Initialize simulation
nbody::Nbody<double, 2> simulation;
simulation.addParticle(p1);
simulation.addParticle(p2);
simulation.setDt(1.0);

// Run simulation
while (currentTime < simulationTime) {
    simulation.update();
    simulation.exportToCsv("output.csv");
    currentTime += dt;
}
```

## Visualization

The included Python script `animate.py` creates an animated GIF from the simulation output:
- Coloured dots to represent the different particles
- The animation shows the evolution of the system over time

## Credits

- Lorenzo Esposito
- Francesco Grassi
- Giorgio Venezia

Group 04 of HPC.