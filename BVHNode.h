#ifndef GRAPH_BVHNODE_H
#define GRAPH_BVHNODE_H

#include "Hitable.h"
#include <vector>
#include <algorithm>

class BVHNode : public Hitable {
public:
    BVHNode():left(nullptr), right(nullptr){}
    BVHNode(vector<Hitable*>::iterator start, vector<Hitable*>::iterator end, int n);
    bool hit(const Ray& r, double tmin, double tmax, HitRecord& rec) const override;
    bool bounding_box(AxisAlignedBoundingBox& box) const override;
    Hitable *left;
    Hitable *right;
    AxisAlignedBoundingBox box;
};

#endif //GRAPH_BVHNODE_H
