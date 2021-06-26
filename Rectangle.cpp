#include "Rectangle.h"

bool RECTXY::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    double t = (k - r.getOrigin().z()) / r.getDirection().z();
    if (t < t_min || t > t_max)
        return false;
    double x = r.getOrigin().x() + t * r.getDirection().x();
    double y = r.getOrigin().y() + t * r.getDirection().y();
    if(x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.mat_ptr = mat_ptr;
    rec.p = r.point_at_parameter(t);
    rec.normal = Vec3(0, 0, 1);
    return true;
}

bool RECTXZ::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    double t = (k - r.getOrigin().y()) / r.getDirection().y();
    if (t < t_min || t > t_max)
        return false;
    double x = r.getOrigin().x() + t * r.getDirection().x();
    double z = r.getOrigin().z() + t * r.getDirection().z();
    if(x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.mat_ptr = mat_ptr;
    rec.p = r.point_at_parameter(t);
    rec.normal = Vec3(0, 1, 0);
    return true;
}

bool RECTYZ::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    double t = (k - r.getOrigin().x()) / r.getDirection().x();
    if (t < t_min || t > t_max)
        return false;
    double y = r.getOrigin().y() + t * r.getDirection().y();
    double z = r.getOrigin().z() + t * r.getDirection().z();
    if(y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.mat_ptr = mat_ptr;
    rec.p = r.point_at_parameter(t);
    rec.normal = Vec3(1, 0, 0);
    return true;
}
