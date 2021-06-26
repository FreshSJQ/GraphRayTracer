#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#pragma once

#include "Vec3.h"

class Ray {
    Vec3 origin;
    Vec3 direction;
public:
    Ray() {}

    Ray(const Vec3 &o, const Vec3 &t) : origin(o), direction(t) {}

    Vec3 getOrigin() const { return this->origin; }

    Vec3 getDirection() const { return this->direction; }

    Vec3 point_at_parameter(double t) const { return origin + t * direction; }
};

#endif //RAYTRACER_RAY_H
