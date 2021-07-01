#ifndef RAYTRACER_HITABLE_H
#define RAYTRACER_HITABLE_H

#pragma once

#include "Ray.h"
#include "Material.h"
#include "AxisAlignedBoundingBox.h"

class Hitable {
public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
    virtual bool bounding_box(AxisAlignedBoundingBox& box) const = 0;
    virtual double pdfValue(const Vec3& o, const Vec3& v) const {return 0.0;}
    virtual Vec3 random(const Vec3& o) const {return Vec3(1, 0, 0);}
};

#endif //RAYTRACER_HITABLE_H
