#include "Geometry.h"

bool Sphere::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Vec3 oc = r.getOrigin() - center;
    double a = dot(r.getDirection(), r.getDirection());
    double b = dot(oc, r.getDirection());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - a * c;
    if (discriminant > 0) {
        double temp = (-b - sqrt(b * b - a * c)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(b * b - a * c)) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

bool Cylinder::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Vec3 oc = r.getOrigin() - center;
    double a = r.getDirection().z() * r.getDirection().z() + r.getDirection().x() * r.getDirection().x();
    double b = oc.z() * r.getDirection().z() + oc.x() * r.getDirection().x();
    double c = oc.z() * oc.z() + oc.x() * oc.x() - radius * radius;
    double discriminant = b * b - a * c;
    if (discriminant > 0) {
        double temp = (-b - sqrt(b * b - a * c)) / a;
        double y = r.point_at_parameter(temp).y() + center.y();

        if (temp < t_max && temp > t_min && y <= height && y >= 0) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }

        double oy = r.getOrigin().y();
        double dy = r.getDirection().y();
        if(center.y() + height != oy) {
            temp = (center.y() + height - oy) / dy;
            Vec3 point = r.point_at_parameter(temp);
            double value = (point.z() - center.z()) * (point.z() - center.z()) +
                           (point.x() - center.x()) * (point.x() - center.x());
            if (temp < t_max && temp > t_min && value <= radius * radius) {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = Vec3(0, 1, 0);
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }

        temp = (-b + sqrt(b * b - a * c)) / a;
        y = r.point_at_parameter(temp).y() + center.y();
        if (temp < t_max && temp > t_min && y <= height && y >= 0) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
//            double ypoint = rec.p.y();
            rec.normal = (rec.p - center) / radius;
            rec.mat_ptr = mat_ptr;
//            rec.normal[1] = ypoint;
            return true;
        }
    }
    return false;
}