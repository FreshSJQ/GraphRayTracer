#ifndef GRAPH_HITABLE_H
#define GRAPH_HITABLE_H

#pragma once

#include "Ray.h"
#include "Material.h"
#include "AxisAlignedBoundingBox.h"

class Hitable {
public:
    virtual bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const = 0;
    virtual bool bounding_box(AxisAlignedBoundingBox& box) const = 0;
};

#endif //GRAPH_HITABLE_H
