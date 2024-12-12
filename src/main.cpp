#include "nbody.hpp"

int main(){
    Particle p1, p2, p3;

    p1.update({0.0, 0.0, 1.0}, {0.0, 100.0, 0.0});
    p2.update({1.0, 0.0, 0.0}, {0.0, 0.0, 0.0});
    p3.update({0.0, 1.0, 0.0}, {0.0, 0.0, 0.0});

    return 0;
}