#include "Material.h"

bool Lambertian::scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation, Ray &scattered, double& pdf) const {
//    Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
//    scattered = Ray(rec.p, target - rec.p, r_in.time());
//    attenuation = albedo->Value(rec.u, rec.v, rec.p);
//    return true;
    Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    scattered = Ray(rec.p, unit_vector(target-rec.p), r_in.time());
    attenuation = albedo->Value(rec.u, rec.v, rec.p);
    pdf = dot(rec.normal, scattered.getDirection()) / PI;
    return true;
}

bool Metal::scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation, Ray &scattered, double& pdf) const {
    Vec3 reflected = reflect(unit_vector(r_in.getDirection()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo->Value(0, 0, rec.p);
    return (dot(scattered.getDirection(), rec.normal) > 0);
}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &rec, Vec3 &attenuation, Ray &scattered, double& pdf) const {
    Vec3 outward_normal;
    Vec3 reflected = reflect(r_in.getDirection(), rec.normal);
    double ni_over_nt;
    attenuation = Vec3(1.0, 1.0, 1.0);
    Vec3 refracted;
    double reflect_prob;
    double cosine;
    if (dot(r_in.getDirection(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.getDirection(), rec.normal) / r_in.getDirection().length();
    }
    else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.getDirection(), rec.normal) / r_in.getDirection().length();
    }
    if (refract(r_in.getDirection(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    }
    else {
        scattered = Ray(rec.p, reflected);
        reflect_prob = 1.0;
    }
    if (randNum01() < reflect_prob) {
        scattered = Ray(rec.p, reflected);
    }
    else {
        scattered = Ray(rec.p, refracted);
    }
    return true;
}
