#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#pragma once

#include "Ray.h"
#include "Utils.h"

class Camera {
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double time0, time1;
    double lens_radius;
public:
    Camera() = default;

    Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect, double aperture, double focus_dist,
           double t0, double t1) {
        time0 = t0;
        time1 = t1;
        lens_radius = aperture / 2;
        double theta = vfov * PI / 180;
        double half_height = tan(theta / 2);
        double half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    Ray get_ray(double s, double t) {
        Vec3 rd = lens_radius * random_in_unit_disk();
        Vec3 offset = u * rd.x() + v * rd.y();
        double time = time0 + randNum01() * (time1 - time0);
        return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
    }
};

#endif //RAYTRACER_CAMERA_H
