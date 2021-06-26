#ifndef RAYTRACER_ROTATEY_H
#define RAYTRACER_ROTATEY_H

#include "Hitable.h"

class RotateY : public Hitable {
public:
    Hitable *ptr;
    double sinTheta;
    double cosTheta;
    bool hasBox;
    AxisAlignedBoundingBox bbox;
    RotateY(Hitable *p, double angle);
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool bounding_box(AxisAlignedBoundingBox& box) const override;
};

#endif //RAYTRACER_ROTATEY_H
