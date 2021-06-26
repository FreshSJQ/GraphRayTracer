#include "Box.h"

Box::Box(const Vec3 &p0, const Vec3 &p1, Material *ptr) {
    pmin = p0;
    pmax = p1;
    vector<Hitable *> list;
    list.push_back(new RECTXY(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    list.push_back(new FlipNormals(new RECTXY(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr)));
    list.push_back(new RECTXZ(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    list.push_back(new FlipNormals(new RECTXZ(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr)));
    list.push_back(new RECTYZ(p0.y(), p1.y(), p0.z(),p1.z(), p1.x(), ptr));
    list.push_back(new FlipNormals(new RECTYZ(p0.y(), p1.y(), p0.z(),p1.z(), p0.x(), ptr)));
    list_ptr = new BVHNode(list.begin(), list.end(), list.size());
}

bool Box::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    return list_ptr->hit(r, t_min, t_max, rec);
}
