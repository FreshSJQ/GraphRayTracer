#ifndef GRAPH_AXISALIGNEDBOUNDINGBOX_H
#define GRAPH_AXISALIGNEDBOUNDINGBOX_H

#include "Vec3.h"
#include "Ray.h"

inline double ffmin(double a, double b) {return a < b ? a : b;}
inline double ffmax(double a, double b) {return a > b ? a : b;}

class AxisAlignedBoundingBox {
public:
    AxisAlignedBoundingBox() =default;
    AxisAlignedBoundingBox(const Vec3& a, const Vec3& b) { _min = a; _max = b;}

    Vec3 min() const {return _min;}
    Vec3 max() const {return _max;}

    bool hit(const Ray& r, double tmin, double tmax) const;
    Vec3 _min;
    Vec3 _max;
};

AxisAlignedBoundingBox surrounding_box(AxisAlignedBoundingBox box0, AxisAlignedBoundingBox box1);

#endif //GRAPH_AXISALIGNEDBOUNDINGBOX_H
