#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#pragma once

#include "Utils.h"
#include "Vec3.h"
#include "Ray.h"
#include "Texture.h"
#include "ONB.h"

class Material;

class PDF;

struct HitRecord {
    double t;
    Vec3 p;
    Vec3 normal;
    Material *mat_ptr;
    double u;
    double v;
};

struct ScatterRecord {
    Ray specularRay;
    bool isSpecular;
    Vec3 attenuation;
    PDF *pdf_ptr;
};

class Material {
public:
    virtual bool scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const = 0;

    virtual double scateringPDF(const Ray &r_in, const HitRecord &rec, const Ray &scattered) const {
        return false;
    }

    virtual Vec3 Emitted(const Ray& r_in, const HitRecord& rec, double u, double v, const Vec3 &p) const {
        return Vec3(0, 0, 0);
    }
};

class Lambertian : public Material {
public:
    Texture *albedo;

    Lambertian(Texture *a) : albedo(a) {}

    double scateringPDF(const Ray &r_in, const HitRecord &rec, const Ray &scattered) const override {
        double cosine = dot(rec.normal, unit_vector(scattered.getDirection()));
        if (cosine < 0) cosine = 0;
        return cosine / PI;
    }

    bool scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const override;
};

class Metal : public Material {
    Texture *albedo;
    double fuzz;
public:
    Metal(Texture *a, double f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

    bool scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const override;
};

class Microfacet : public Material {
    Texture *albedo;
    double roughness;

public:
    Microfacet(Texture *a, double r):albedo(a), roughness(r){}

    bool scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const override;
};

class Dielectric : public Material {
    double ref_idx;
public:
    Dielectric(double ri) : ref_idx(ri) {}

    bool scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const override;
};

class DiffuseLight : public Material {
public:
    Texture *emit;

    DiffuseLight(Texture *a) : emit(a) {}

    bool scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const override {
        return false;
    }

    Vec3 Emitted(const Ray& r_in, const HitRecord& rec, double u, double v, const Vec3 &p) const override {
        if(dot(rec.normal, r_in.getDirection()) > 0.0)
            return emit->Value(u, v, p);
        else return Vec3(0, 0, 0);
    }
};



#endif //RAYTRACER_MATERIAL_H
