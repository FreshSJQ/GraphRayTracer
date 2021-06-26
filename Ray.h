#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#pragma once

#include "Vec3.h"

class Ray {
    Vec3 origin;
    Vec3 direction;
    double _time;
public:
    Ray() {}

    Ray(const Vec3 &o, const Vec3 &t, double ti = 0.0) : origin(o), direction(t), _time(ti) {}

    Vec3 getOrigin() const { return this->origin; }

    Vec3 getDirection() const { return this->direction; }

    double time() const {return this->_time;}

    Vec3 point_at_parameter(double t) const { return origin + t * direction; }
};

#endif //RAYTRACER_RAY_H
