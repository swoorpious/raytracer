#ifndef COLOR_H
#define COLOR_H

#include <core.hpp>
#include <fstream>


inline void writeColor(std::ofstream& out, const color& pixelColor) {
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    static const IntervalF intensity(0.0f, 0.999f);
    int ir = int(256 * intensity.clamp(r));
    int ig = int(256 * intensity.clamp(g));
    int ib = int(256 * intensity.clamp(b));

    out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif