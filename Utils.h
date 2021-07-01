#ifndef RAYTRACER_UTILS_H
#define RAYTRACER_UTILS_H

#pragma once
#include "Vec3.h"
#include <vector>

#define PI 3.14159265358979323846

double randNum01();

Vec3 random_in_unit_sphere();

Vec3 random_in_unit_disk();

Vec3 random_on_unit_sphere();

Vec3 reflect(const Vec3& v, const Vec3& n);

bool refract(const Vec3& v, const Vec3& n, double ni_over_nt, Vec3& refracted);

double schlick(double cosine, double ref_idx);

void get_sphere_uv(const Vec3& p, double& u, double& v);

Vec3 random_cosin_direction();

#endif //RAYTRACER_UTILS_H
