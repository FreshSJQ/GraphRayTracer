#include "Utils.h"

double randNum01() {
    return rand() / double(RAND_MAX);
}

Vec3 random_in_unit_sphere() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(randNum01(), randNum01(), randNum01()) - Vec3(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

Vec3 random_in_unit_disk() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(randNum01(), randNum01(), 0) - Vec3(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}

Vec3 random_on_unit_sphere() {
    Vec3 p;
    do {
        p = 2.0 * Vec3(randNum01(), randNum01(), randNum01()) - Vec3(1, 1, 1);
    } while (dot(p, p) >= 1.0);
    return unit_vector(p);
}

Vec3 reflect(const Vec3 &v, const Vec3 &n) {
    return v - 2 * dot(v, n) * n;
}

bool refract(const Vec3 &v, const Vec3 &n, double ni_over_nt, Vec3 &refracted) {
    Vec3 uv = unit_vector(v);
    double dt = dot(uv, n);
    double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    } else return false;
}

double schlick(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

void get_sphere_uv(const Vec3 &p, double &u, double &v) {
    double phi = atan2(p.z(), p.x());
    double theta = asin(p.y());
    u = 1 - (phi + PI) / (2 * PI);
    v = (theta + PI / 2) / PI;
}

Vec3 random_cosin_direction() {
    double r1 = randNum01();
    double r2 = randNum01();
    double z = sqrt(1 - r2);
    double phi = 2 * PI * r1;
    double x = cos(phi) * 2 * sqrt(r2);
    double y = sin(phi) * 2 * sqrt(r2);
    return Vec3(x, y, z);
}
