#ifndef RAYTRACER_GEOMETRY_H
#define RAYTRACER_GEOMETRY_H

#pragma once

#include "Hitable.h"

class Sphere : public Hitable {
    Vec3 center;
    double radius;
    Material* mat_ptr;
public:
    Sphere() {}
    Sphere(Vec3 cen, double r, Material* m) : center(cen), radius(r), mat_ptr(m){
    };
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool bounding_box(AxisAlignedBoundingBox& box) const {
        box = AxisAlignedBoundingBox(center - Vec3(radius, radius, radius), center + Vec3(radius, radius, radius));
        return true;
    }
};

class Cylinder : public Hitable {
    Vec3 center;
    double radius;
    double height;
    Material* mat_ptr;
public:
    Cylinder() {}

    Cylinder(Vec3 cen, double r, double h, Material* m) : center(cen), radius(r), height(h), mat_ptr(m){
    };

    virtual bool hit(const Ray &r, double tmin, double tmax, HitRecord &rec) const;
    virtual bool bounding_box(AxisAlignedBoundingBox& box) const {
        box = AxisAlignedBoundingBox(center - Vec3(radius, 0, radius), center + Vec3(radius, height, radius));
        return true;
    }
};

#endif //RAYTRACER_GEOMETRY_H
