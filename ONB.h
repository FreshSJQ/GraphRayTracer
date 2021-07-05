#ifndef RAYTRACER_ONB_H
#define RAYTRACER_ONB_H

#include "Vec3.h"

class ONB {
public:
    Vec3 axis[3];

    ONB() {}

    ONB(Vec3& n, Vec3& i) {buildFrom(n, i);}

    Vec3 operator[](int i) const { return axis[i]; }

    Vec3 u() const { return axis[0]; }

    Vec3 v() const { return axis[1]; }

    Vec3 w() const { return axis[2]; }

    Vec3 local(double a, double b, double c) const { return a * u() + b * v() + c * w(); }

    Vec3 local(const Vec3 &a) const {
        return a.x() * u() + a.y() * v() + a.z() * w();
    }

    void buildFromW(const Vec3 &n) {
        axis[2] = unit_vector(n);
        Vec3 a;
        if (fabs(w().x()) > 0.9)
            a = Vec3(0, 1, 0);
        else a = Vec3(1, 0, 0);

        axis[1] = unit_vector(cross(w(), a));
        axis[0] = cross(w(), v());
    }

    void buildFrom(Vec3& v) {
        axis[2] = v;
        bool useY = abs(axis[2].x()) > 0.9;
        if(useY) axis[1] = Vec3(0, 1, 0);
        else axis[1] = Vec3(1, 0, 0);

        axis[1] = cross(axis[1], axis[2]).Normalize();
        axis[0] = cross(axis[1], axis[2]);
    }

    void buildFrom(Vec3& n, Vec3& i) {
        double cosine = abs(dot(n, i));

        if(cosine > 0.9999999) buildFrom(n);
        else {
            axis[2] = n;
            axis[0] = cross(i, n).Normalize();
            axis[1] = cross(axis[2], axis[0]);
        }
    }
};

#endif //RAYTRACER_ONB_H
