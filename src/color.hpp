#ifndef COLOR_H
#define COLOR_H

#include <core.hpp>
#include <fstream>


inline double linearToGamma(double x) {
    if (x > 0) 
        return std::sqrt(x);
    return 0.f;
}

inline void writeColor(std::ofstream& out, const color& pixelColor) {
    double r = pixelColor.x();
    double g = pixelColor.y();
    double b = pixelColor.z();

    r = linearToGamma(r);
    g = linearToGamma(g);
    b = linearToGamma(b);

    static const IntervalF intensity(0.0f, 0.999f);
    int ir = int(256 * intensity.clamp(r));
    int ig = int(256 * intensity.clamp(g));
    int ib = int(256 * intensity.clamp(b));

    out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif