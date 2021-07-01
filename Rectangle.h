#ifndef RAYTRACER_RECTANGLE_H
#define RAYTRACER_RECTANGLE_H

#include "Hitable.h"

class RECTXY : public Hitable {
public:
    double x0, x1, y0, y1, k;
    Material *mat_ptr;

    RECTXY() {}

    RECTXY(double x_0, double x_1, double y_0, double y_1, double kt, Material *mat) :
            x0(x_0), x1(x_1), y0(y_0), y1(y_1), k(kt), mat_ptr(mat) {}

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    bool bounding_box(AxisAlignedBoundingBox &box) const override{
        box = AxisAlignedBoundingBox(Vec3(x0, y0, k - 0.0001), Vec3(x1, y1, k + 0.0001));
        return true;
    }

};

class RECTXZ : public Hitable {
public:
    double x0, x1, z0, z1, k;
    Material *mat_ptr;

    RECTXZ() {}

    RECTXZ(double x_0, double x_1, double z_0, double z_1, double kt, Material *mat) :
            x0(x_0), x1(x_1), z0(z_0), z1(z_1), k(kt), mat_ptr(mat) {}

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    bool bounding_box(AxisAlignedBoundingBox &box) const override{
        box = AxisAlignedBoundingBox(Vec3(x0, k - 0.0001, z0), Vec3(x1, k + 0.0001, z1));
        return true;
    }

    double pdfValue(const Vec3& o, const Vec3& v) const override {
        HitRecord hrec;
        if(this->hit(Ray(o, v), 0.001, DBL_MAX, hrec)) {
            double area = (x1 - x0) * (z1 - z0);
            double distance_squared = hrec.t * hrec.t * v.squared_length();
            double cosine = fabs(dot(v, hrec.normal) / v.length());
            return distance_squared / (cosine * area);
        }
        else return 0;
    }

    Vec3 random(const Vec3& o) const override {
        Vec3 randomPoint = Vec3(x0 + randNum01() * (x1 - x0), k, z0 + randNum01() * (z1 - z0));
        return randomPoint - o;
    }

};

class RECTYZ : public Hitable {
public:
    double y0, y1, z0, z1, k;
    Material *mat_ptr;

    RECTYZ() {}

    RECTYZ(double y_0, double y_1, double z_0, double z_1, double kt, Material *mat) :
            y0(y_0), y1(y_1), z0(z_0), z1(z_1), k(kt), mat_ptr(mat) {}

    bool hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

    bool bounding_box(AxisAlignedBoundingBox &box) const override{
        box = AxisAlignedBoundingBox(Vec3(k - 0.0001, y0, z0), Vec3(k + 0.0001, y1, z1));
        return true;
    }

};

#endif //RAYTRACER_RECTANGLE_H
