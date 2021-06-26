#ifndef RAYTRACER_BOX_H
#define RAYTRACER_BOX_H

#include "Hitable.h"
#include "BVHNode.h"
#include "Rectangle.h"
#include "FlipNormals.h"

class Box: public Hitable {
public:
    Vec3 pmin, pmax;
    BVHNode *list_ptr;
    Box(){}
    Box(const Vec3 &p0, const Vec3 &p1, Material *ptr);
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool bounding_box(AxisAlignedBoundingBox& box) const override {
        box = AxisAlignedBoundingBox(pmin, pmax);
        return true;
    }
};

#endif //RAYTRACER_BOX_H
