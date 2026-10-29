// copyright 2026 swaroop.
#pragma once

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>

#include "vec3.hpp"
#include "interval.hpp"


const double PI = 3.14159265358979323846;

inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.f;
}

inline double randomDouble() {
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*randomDouble();
}


#endif
