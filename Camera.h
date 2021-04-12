#ifndef GRAPH_CAMERA_H
#define GRAPH_CAMERA_H

#pragma once

#include "Ray.h"
#include "Utils.h"

#define PI 3.14159265358979323846

class Camera {
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
public:
    Camera() = default;

    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect, double focus_dist) {
        double theta = vfov * PI / 180;
        double half_height = tan(theta / 2);
        double half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical =2 * half_height * focus_dist * v;
    }
    Ray get_ray(double s, double t) {
        return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
    }
};

#endif //GRAPH_CAMERA_H
