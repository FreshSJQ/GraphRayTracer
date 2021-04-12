#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#pragma once
#include "Vec3.h"

double randNum01();

Vec3 random_in_unit_sphere();

Vec3 reflect(const Vec3& v, const Vec3& n);

bool refract(const Vec3& v, const Vec3& n, double ni_over_nt, Vec3& refracted);

double schlick(double cosine, double ref_idx);

#endif //GRAPH_UTILS_H
