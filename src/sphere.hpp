// copyright 2026 swaroop.

#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.hpp"


double hitSphere(const point3& center, double rad, const ray& r);

class Sphere : public Hittable {
public:
    Sphere(const point3& center, double radius) :
        center(center), radius(radius) {}

    virtual bool hits(const ray& r, double t_min, double t_max, HitRecord& rec) const override;

private:
    point3 center;
    double radius;
};

#endif //SPHERE_H
