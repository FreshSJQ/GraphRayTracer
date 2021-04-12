#include "AxisAlignedBoundingBox.h"

AxisAlignedBoundingBox surrounding_box(AxisAlignedBoundingBox box0, AxisAlignedBoundingBox box1) {
    Vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));
    Vec3 big(fmax(box0.max().x(), box1.max().x()),
             fmax(box0.max().y(), box1.max().y()),
             fmax(box0.max().z(), box1.max().z()));
    return AxisAlignedBoundingBox(small, big);
}

bool AxisAlignedBoundingBox::hit(const Ray &r, double tmin, double tmax) const {
    for (int a = 0; a < 3; a++) {
        double invD = 1.0f / r.getDirection()[a];
        double t0 = (min()[a] - r.getOrigin()[a]) * invD;
        double t1 = (max()[a] - r.getOrigin()[a]) * invD;
        if (invD < 0.0f)
            swap(t0, t1);
        tmin = ffmax(t0, tmin);
        tmax = ffmin(t1, tmax);
        if (tmax <= tmin) return false;
    }
    return true;
}
