cmake_minimum_required(VERSION 3.20)
project(nbody)

# Imposta il livello di ottimizzazione e il supporto per C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")

# Aggiungi l'eseguibile
add_executable(nbody main.cpp)