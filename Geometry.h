#ifndef RAYTRACER_GEOMETRY_H
#define RAYTRACER_GEOMETRY_H

#pragma once

#include "Hitable.h"

class Sphere : public Hitable {
    Vec3 center;
    double radius;
    Material* mat_ptr;
public:
    Sphere() {}
    Sphere(Vec3 cen, double r, Material* m) : center(cen), radius(r), mat_ptr(m){
    };
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool bounding_box(AxisAlignedBoundingBox& box) const {
        box = AxisAlignedBoundingBox(center - Vec3(radius, radius, radius), center + Vec3(radius, radius, radius));
        return true;
    }
};

class Disk: public Hitable {
    Vec3 center;
    double radius;
    Material* mat_ptr;
    double height;
    double x0, x1, z0, z1, k;
public:
    Disk() {}
    Disk(Vec3 cen, double r, Material* m) : center(cen), radius(r), height(cen.y()), mat_ptr(m){
        x0 = center.x() - radius;
        x1 = center.x() + radius;
        z0 = center.x() - radius;
        z1 = center.x() + radius;
        k = height;
    }
    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;
    bool bounding_box(AxisAlignedBoundingBox& box) const override {
        box = AxisAlignedBoundingBox(Vec3(center.x() - radius, height - 0.001, center.z() - radius),
                                     Vec3(center.x() + radius, height + 0.001, center.z() + radius));
        return true;
    }
    double pdfValue(const Vec3& o, const Vec3& v) const override {
        HitRecord hrec;
        if(this->hit(Ray(o, v), 0.001, DBL_MAX, hrec)) {
            double area = radius * radius * PI;
//            double area = (x1 - x0) * (z1 - z0);
            double distance_squared = hrec.t * hrec.t * v.squared_length();
            double cosine = fabs(dot(v, hrec.normal) / v.length());
            return distance_squared / (cosine * area);
        }
        else return 0;
    }

    Vec3 random(const Vec3& o) const override {
        Vec3 p = random_in_unit_disk();
        p[2] = p[1];
        p[1] = 0;
        Vec3 randomPoint = radius * p + center;
        return randomPoint - o;
//        Vec3 randomPoint = Vec3(x0 + randNum01() * (x1 - x0), k, z0 + randNum01() * (z1 - z0));
//        return randomPoint - o;
    }
};

class Cylinder : public Hitable {
    Vec3 center;
    double radius;
    double height;
    Material* mat_ptr;
public:
    Cylinder() {}

    Cylinder(Vec3 cen, double r, double h, Material* m) : center(cen), radius(r), height(h), mat_ptr(m){
    };

    virtual bool hit(const Ray &r, double tmin, double tmax, HitRecord &rec) const;
    virtual bool bounding_box(AxisAlignedBoundingBox& box) const {
        box = AxisAlignedBoundingBox(center - Vec3(radius, 0, radius), center + Vec3(radius, height, radius));
        return true;
    }
};

class MovingSphere : public Hitable {
public:
    Vec3 center0, center1;
    double time0, time1;
    double radius;
    Material* mat_ptr;
    MovingSphere() {}
    MovingSphere(Vec3 cen0, Vec3 cen1, double t0, double t1, double r, Material *m) :
            center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {}
    virtual bool hit(const Ray &r, double tmin, double tmax, HitRecord &rec) const {
        Vec3 oc = r.getOrigin() - center(r.time());
        double a = dot(r.getDirection(), r.getDirection());
        double b = dot(oc, r.getDirection());
        double c = dot(oc, oc) - radius * radius;
        double discriminant = b * b - a * c;
        if (discriminant > 0) {
            double temp = (-b - sqrt(discriminant)) / a;
            if (temp < tmax && temp > tmin) {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center(r.time())) / radius;
                rec.mat_ptr = mat_ptr;
                get_sphere_uv(rec.normal, rec.u, rec.v);
                return true;
            }
            temp = (-b + sqrt(discriminant)) / a;
            if (temp < tmax && temp > tmin) {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center(r.time())) / radius;
                rec.mat_ptr = mat_ptr;
                get_sphere_uv(rec.normal, rec.u, rec.v);
                return true;
            }
        }
        return false;
    }
    Vec3 center(double time) const {
        return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
    }
    bool bounding_box(AxisAlignedBoundingBox& box) const {
        box = AxisAlignedBoundingBox(center(time0) - Vec3(radius, radius, radius), center(time1) + Vec3(radius, radius, radius));
        return true;
    }
};

#endif //RAYTRACER_GEOMETRY_H
