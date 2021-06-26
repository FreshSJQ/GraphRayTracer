#include "Translate.h"

bool Translate::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Ray movedRay(r.getOrigin() - offset, r.getDirection(), r.time());
    if(ptr->hit(movedRay, t_min, t_max, rec)) {
        rec.p += offset;
        return true;
    }
    else return false;
}

bool Translate::bounding_box(AxisAlignedBoundingBox& box) const {
    if(ptr->bounding_box(box)) {
        box = AxisAlignedBoundingBox(box.min() + offset, box.max() + offset);
        return true;
    }
    return false;
}