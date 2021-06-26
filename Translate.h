#ifndef RAYTRACER_TRANSLATE_H
#define RAYTRACER_TRANSLATE_H

#include "Hitable.h"

class Translate : public Hitable {
public:
    Hitable *ptr;
    Vec3 offset;
    Translate(Hitable *p, const Vec3& displacement) : ptr(p), offset(displacement) {}
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool bounding_box(AxisAlignedBoundingBox& box) const override;
};

#endif //RAYTRACER_TRANSLATE_H
