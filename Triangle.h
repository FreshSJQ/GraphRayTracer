#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#pragma once

#include "Vec3.h"
#include <vector>
#include <cmath>
#include "Material.h"
#include "Hitable.h"

class Triangle : public Hitable {
    double area;
    Material *mat_ptr;
    Vec3 normal;
    Vec3 edge1;
    Vec3 edge2;
public:
    Vec3 A, B, C;

    Triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c, Material *m);

    bool hit(const Ray &r, double tmin, double tmax, HitRecord &rec) const override;

    bool bounding_box(AxisAlignedBoundingBox &box) const override;

    Vec3 getNormal(const HitRecord &rec) const {
        return normal;
    }

    void Scale(double scale);

    void Translate(const Vec3 &t);
};

#endif //RAYTRACER_TRIANGLE_H
