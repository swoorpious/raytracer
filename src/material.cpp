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
    vec3 reflected = reflect(r_in.getDirection(), rec.normal);
    reflected = unit_vector(reflected) + fuzz * random_unit_vector();
    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return true;
}

bool Glass::scatter(
    const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
) const {
    attenuation = color(1.0, 1.0, 1.0);
    double ri = rec.isFrontFace ? 1.f / refractiveIndex : refractiveIndex;

    vec3 unitDirection = unit_vector(r_in.getDirection());
    double cos = std::fmin(dot(-unitDirection, rec.normal), 1.0);
    double sin = std::sqrt(1.f - cos * cos);
    vec3 direction;
    if (ri * sin > 1.f || reflectance(cos, ri) > randomDouble())
        direction = reflect(unitDirection, rec.normal);
    else
        direction = refract(unitDirection, rec.normal, ri);

    scattered = ray(rec.p, direction);
    return true;
}
