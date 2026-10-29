// copyright 2026 swaroop.

#ifndef INTERVAL_HPP
#define INTERVAL_HPP
#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

struct IntervalF {
    double min, max;

    double size() const { return max - min; }

    bool contains(double x) const {
        return min <= x && x <= max;
    }

    bool surrounds(double x) const {
        return min < x && x < max;
    }

    // uses the min, max variables defined above
    double clamp(double x) const {
        if (x <= min) return min;
        if (x >= max) return max;
        return x;
    }

    IntervalF() : min(infinity), max(-infinity) {}
    IntervalF(double min, double max) : min(min), max(max) {}

    static IntervalF Zero() { return {0, 0}; }
    static IntervalF Empty() { return {infinity, -infinity}; }
    static IntervalF Universe() { return {-infinity, infinity}; }
};


#endif //INTERVAL_HPP
