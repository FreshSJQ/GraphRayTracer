#include "RotateY.h"

RotateY::RotateY(Hitable *p, double angle): ptr(p){
    double radians = (PI / 180.) * angle;
    sinTheta = sin(radians);
    cosTheta = cos(radians);
    hasBox = ptr->bounding_box(bbox);
    Vec3 min(DBL_MAX, DBL_MAX, DBL_MAX);
    Vec3 max(-DBL_MAX, -DBL_MAX, -DBL_MAX);
    for(int i = 0; i < 2; i++) {
        for(int j = 0;j < 2; j++) {
            for(int k = 0; k < 2 ; k++) {
                double x = i * bbox.max().x() + (1 - i) * bbox.min().x();
                double y = j * bbox.max().y() + (1 - j) * bbox.min().y();
                double z = k * bbox.max().z() + (1 - k) * bbox.min().z();
                double newx = cosTheta * x + sinTheta * z;
                double newz = -sinTheta * x + cosTheta * z;
                Vec3 tester(newx, y, newz);
                for(int c = 0; c < 3; c++) {
                    if(tester[c] > max[c])
                        max[c] = tester[c];
                    if(tester[c] < min[c])
                        min[c] = tester[c];
                }
            }
        }
    }
    bbox = AxisAlignedBoundingBox(min, max);
}

bool RotateY::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    Vec3 origin = r.getOrigin();
    Vec3 direction = r.getDirection();
    origin[0] = cosTheta * r.getOrigin()[0] - sinTheta * r.getOrigin()[2];
    origin[2] = sinTheta * r.getOrigin()[0] + cosTheta * r.getOrigin()[2];
    direction[0] = cosTheta * r.getDirection()[0] - sinTheta * r.getDirection()[2];
    direction[2] = sinTheta * r.getDirection()[0] + cosTheta * r.getDirection()[2];
    Ray rotatedRay(origin, direction, r.time());
    if(ptr->hit(rotatedRay, t_min, t_max, rec)) {
        Vec3 p = rec.p;
        Vec3 normal = rec.normal;
        p[0] = cosTheta * rec.p[0] + sinTheta * rec.p[2];
        p[2] = -sinTheta * rec.p[0] + cosTheta * rec.p[2];
        normal[0] = cosTheta * rec.normal[0] + sinTheta * rec.normal[2];
        normal[2] = -sinTheta * rec.normal[0] + cosTheta * rec.normal[2];
        rec.p = p;
        rec.normal = normal;
        return true;
    } else return false;
}

bool RotateY::bounding_box(AxisAlignedBoundingBox& box) const {
    box = bbox;
    return hasBox;
}
