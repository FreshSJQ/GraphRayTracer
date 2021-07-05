#include "Material.h"
#include "PDF.h"

bool Lambertian::scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const {
    srec.isSpecular = false;
    srec.attenuation = albedo->Value(hrec.u, hrec.v, hrec.p);
    srec.pdf_ptr = new CosinePDF(hrec.normal);
    return true;
}

bool Metal::scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const {
    Vec3 reflected = reflect(unit_vector(r_in.getDirection()), hrec.normal);
    srec.specularRay = Ray(hrec.p, reflected + fuzz * random_in_unit_sphere());
    srec.attenuation = albedo->Value(0, 0, hrec.p);
    srec.isSpecular = true;
    srec.pdf_ptr = nullptr;
    return true;
}

bool Microfacet::scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const {
//    double alpha = pow(roughness, 2.);
//    double F, D, G;
//
//    double alphaSqr = alpha * alpha;
//    double NdotH = dot(hrec.normal, )
//    double denom =
    return true;
}

bool Dielectric::scatter(const Ray &r_in, const HitRecord &hrec, ScatterRecord &srec) const {
    Vec3 outward_normal;
    Vec3 reflected = reflect(r_in.getDirection(), hrec.normal);
    double ni_over_nt;
    srec.attenuation = Vec3(1.0, 1.0, 1.0);
    Vec3 refracted;
    double reflect_prob;
    double cosine;
    if (dot(r_in.getDirection(), hrec.normal) > 0) {
        outward_normal = -hrec.normal;
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot(r_in.getDirection(), hrec.normal) / r_in.getDirection().length();
    }
    else {
        outward_normal = hrec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.getDirection(), hrec.normal) / r_in.getDirection().length();
    }
    if (refract(r_in.getDirection(), outward_normal, ni_over_nt, refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    }
    else {
        srec.specularRay = Ray(hrec.p, reflected);
        reflect_prob = 1.0;
    }
    if (randNum01() < reflect_prob) {
        srec.specularRay = Ray(hrec.p, reflected);
    }
    else {
        srec.specularRay = Ray(hrec.p, refracted);
    }
    return true;
}
