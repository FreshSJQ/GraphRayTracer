#include "BVHNode.h"

BVHNode::BVHNode(vector<Hitable*>::iterator start, vector<Hitable*>::iterator end, int n) {
    int axis = int(3 * randNum01());
    if (axis == 0)
        sort(start, end, [](const auto &o1, const auto &o2) {
            AxisAlignedBoundingBox box_left, box_right;
            o1->bounding_box(box_left);
            o2->bounding_box(box_right);
            return box_left.min().x() < box_right.min().x();
        });
    else if (axis == 1)
        sort(start, end, [](const auto &o1, const auto &o2) {
            AxisAlignedBoundingBox box_left, box_right;
            o1->bounding_box(box_left);
            o2->bounding_box(box_right);
            return box_left.min().y() < box_right.min().y();
        });
    else
        sort(start, end, [](const auto &o1, const auto &o2) {
            AxisAlignedBoundingBox box_left, box_right;
            o1->bounding_box(box_left);
            o2->bounding_box(box_right);
            return box_left.min().z() < box_right.min().z();
        });
    if(n == 1) {
        left = right = *start;
    } else if(n == 2) {
        left = *start;
        right = *(start + 1);
    } else {
        left = new BVHNode(start, start + n / 2, n / 2);
        right = new BVHNode(start + n / 2, end, n - n / 2);
    }
    AxisAlignedBoundingBox box_left, box_right;
    if(!left->bounding_box(box_left) || !right->bounding_box(box_right))
        cerr<<"error"<<endl;
    box = surrounding_box(box_left, box_right);
}

bool BVHNode::bounding_box(AxisAlignedBoundingBox &box) const {
    box = this->box;
    return true;
}

bool BVHNode::hit(const Ray &r, double tmin, double tmax, HitRecord &rec) const {
    if (box.hit(r, tmin, tmax)) {
        HitRecord left_rec, right_rec;
        bool hit_left = left->hit(r, tmin, tmax, left_rec);
        bool hit_right = right->hit(r, tmin, tmax, right_rec);
        if (hit_left && hit_right) {
            if (left_rec.t < right_rec.t)
                rec = left_rec;
            else
                rec = right_rec;
            return true;
        } else if (hit_left) {

            rec = left_rec;
            return true;
        } else if (hit_right) {

            rec = right_rec;
            return true;
        } else return false;
    } else return false;
}
