// copyright 2026 swaroop.

#include "material.hpp"


bool Lambertian::scatter(
    const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
) const {
    vec3 direction = rec.normal + random_unit_vector(); // random new ray bounce direction
    if (direction.near_zero())
        direction = rec.normal;
    scattered = ray(rec.p, direction);
    attenuation = albedo;
    return true;
}

bool Metal::scatter(
    const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
) const {
    vec3 direction = reflect(r_in.getDirection(), rec.normal);
    scattered = ray(rec.p, direction);
    attenuation = albedo;
    return true;
}
