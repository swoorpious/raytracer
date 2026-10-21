// copyright 2026 swaroop.

#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <core.hpp>

struct IntervalF {
    double min, max;

    double size() { return max - min; }

    bool contains(double x) {
        return min <= x && x <= max;
    }

    bool surrounds(double x) {
        return min < x && x < max;
    }

    IntervalF() : min(infinity), max(-infinity) {}
    IntervalF(double min, double max) : min(min), max(max) {}

    static Zero() { return {0, 0}; }
    static Empty() { return {infinity, -infinity}; }
    static Universe() { return {-infinity, infinity}; }
};


#endif //INTERVAL_HPP
