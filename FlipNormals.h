#ifndef RAYTRACER_FLIPNORMALS_H
#define RAYTRACER_FLIPNORMALS_H

#include "Hitable.h"

class FlipNormals: public Hitable {
public:
    Hitable *ptr;
    FlipNormals(Hitable *p) : ptr(p){}
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override {
        if(ptr->hit(r, t_min, t_max, rec)) {
            rec.normal = -rec.normal;
            return true;
        } else return false;
    }
    bool bounding_box(AxisAlignedBoundingBox& box) const override {
        return ptr->bounding_box(box);
    }
};

#endif //RAYTRACER_FLIPNORMALS_H
