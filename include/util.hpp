// copyright 2026 swaroop.

#ifndef UTIL_H
#define UTIL_H

#include <cstdlib>
#include <random>

const double PI = 3.14159265358979323846;

inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.f;
}

inline double randomDouble() {
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    static std::mt19937 generator;
    return dist(generator);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*randomDouble();
}


#endif //UTIL_H
