// copyright 2026 swaroop.

#ifndef HIT_RECORD_H
#define HIT_RECORD_H
#include "rtcore.hpp"

class Material;

struct HitRecord {
    point3 p;
    vec3 normal;
    double t;
    bool isFrontFace;
    std::shared_ptr<Material> mat;
    
    void setOutwardNormal(const ray& r, const vec3 outNormal) {
        isFrontFace = dot(r.getDirection(), outNormal) < 0;
        normal = isFrontFace ? outNormal : -outNormal;
    }
};


#endif
