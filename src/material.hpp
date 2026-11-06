// copyright 2026 swaroop.

#ifndef MATERIAL_H
#define MATERIAL_H
#include "rtcore.hpp"
#include "hittable/hit_record.hpp"

class ray;

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(
        const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
    ) const {
        return false;
    }
};

class Lambertian : public Material {
public:
    Lambertian(const color& albedo) : albedo(albedo) {}
    virtual ~Lambertian() = default;

    virtual bool scatter(
        const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
    ) const override;

private:
    color albedo;
};


class Metal : public Material {
public:
    Metal(const color& albedo) : albedo(albedo) {}
    virtual ~Metal() = default;

    virtual bool scatter(
        const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
    ) const override;

private:
    color albedo;
};

#endif //MATERIAL_H
