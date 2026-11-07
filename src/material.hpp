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
    Metal(const color& albedo, double fuzz) :
        albedo(albedo), fuzz(fuzz < 1.f ? fuzz : 1.f) {}

    virtual ~Metal() = default;

    virtual bool scatter(
        const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
    ) const override;

private:
    color albedo;
    double fuzz;
};


class Glass : public Material {
public:
    Glass(double refractiveIndex) :
        refractiveIndex(refractiveIndex) {}

    virtual ~Glass() = default;

    static double reflectance(double cos, double ri) {
        double r0 = std::pow((1-ri)/(1+ri), 2.0);
        return r0 + (1-r0) * std::pow(1-cos, 5.0) ;
    }

    virtual bool scatter(
        const ray& r_in, const HitRecord& rec, color& attenuation, ray& scattered
    ) const override;

private:
    double refractiveIndex;
};

#endif //MATERIAL_H
