#ifndef COLOR_H
#define COLOR_H

#include <core.hpp>


using color = vec3;

inline void writeColor(std::ostream& out, const color& pixelColor) {
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    int ir = int(255.999f * r);
    int ig = int(255.999f * g);
    int ib = int(255.999f * b);

    out << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif