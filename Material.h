#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#pragma once

#include "Utils.h"
#include "Vec3.h"
#include "Ray.h"
#include "Texture.h"
class Material;

struct HitRecord {
    double t;
    Vec3 p;
    Vec3 normal;
    Material* mat_ptr;
    double u;
    double v;
};

class Material {
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const = 0;
    virtual Vec3 Emitted(double u, double v, const Vec3& p) const{
        return Vec3(0, 0, 0);
    }
};

class Lambertian : public Material {
public:
    Texture* albedo;
    Lambertian(Texture *a) : albedo(a) {}
    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;
};

class Metal : public Material {
    Texture* albedo;
    double fuzz;
public:
    Metal(Texture *a, double f) : albedo(a) {if(f < 1) fuzz = f; else fuzz = 1;}
    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;
};


class Dielectric :public Material {
    double ref_idx;
public:
    Dielectric(double ri) :ref_idx(ri) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override;
};

class DiffuseLight:public Material {
public:
    Texture *emit;
    DiffuseLight(Texture *a) : emit(a){}
    bool scatter(const Ray& r_in, const HitRecord& rec, Vec3& attenuation, Ray& scattered) const override {
        return false;
    }

    Vec3 Emitted(double u, double v, const Vec3& p) const override{
        return emit->Value(u, v, p);
    }
};

#endif //RAYTRACER_MATERIAL_H
