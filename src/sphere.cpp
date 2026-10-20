// copyright 2026 swaroop.
#include "sphere.hpp"

bool Sphere::hits(const ray& r, double t_min, double t_max, HitRecord& rec) const {
    vec3 oc = center - r.getOrigin();
    double a = r.getDirection().length_squared();
    double h = dot(r.getDirection(), oc);
    double c = oc.length_squared() - radius*radius;

    double discriminant = h*h - a*c;
    if (discriminant < 0)
        return false;

    double sqrtd = std::sqrt(discriminant);

    double root = (h - sqrtd) / a;
    if (root <= t_min || t_max <= root) {
        root = (h + sqrtd) / a;
        if (root <= t_min || t_max <= root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 normal = (rec.p - center) / radius;
    rec.setOutwardNormal(r, normal);

    return true;
}