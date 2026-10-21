// copyright 2026 swaroop.

#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtcore.hpp"

struct HitRecord {
    point3 p;
    vec3 normal;
    double t;
    bool isFrontFace;
    
    void setOutwardNormal(const ray& r, const vec3 outNormal) {
        isFrontFace = dot(r.getDirection(), outNormal) < 0;
        normal = isFrontFace ? outNormal : -outNormal;
    }
};


class Hittable {
public:
    ~Hittable() = default;
    virtual bool hits(const ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};


class HittableList : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;
    
    HittableList() { objects.reserve(32); }
    ~HittableList() { clear(); }
    
    void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }
    
    virtual bool hits(const ray& r, double t_min, double t_max, HitRecord& rec) const override {
        HitRecord temp;
        bool hitAnyAtAll = false;
        double closestSoFar = t_max;
        
        for(const auto& object : objects) {
            if(object->hits(r, t_min, closestSoFar, temp)) {
                hitAnyAtAll = true;
                closestSoFar = temp.t;
                rec = temp;
            }
        }
        
        return hitAnyAtAll;
    }
};

#endif //HITTABLE_H
