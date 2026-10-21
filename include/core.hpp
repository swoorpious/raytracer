// copyright 2026 swaroop.
#pragma once

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include <stdio.h>
#include <cmath>
#include <limits>
#include <memory>
#include <vector>

#include "vec3.hpp"


const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.14159265358979323846;

inline double degreesToRadians(double degrees) {
    return degrees * PI / 180.f;
}

#endif
