#include <tuple>
#include "Triangle.h"

Triangle::Triangle(const Vec3 &a, const Vec3 &b, const Vec3 &c, Material *m): A(a), B(b), C(c), mat_ptr(m) {
    Init();
}

void Triangle::Init() {
    edge1 = B - A;
    edge2 = C - A;
    normal = cross(edge1, edge2);
    area = normal.length() * 0.5;
    normal = normal.Normalize();
}

bool Triangle::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    const Vec3 pvec = cross(r.getDirection(), edge2);
    const double det = dot(pvec, edge1);

    if (abs(det) < 1E-15) return false;

    const double invdet = 1. / det;

    const Vec3 tvec = r.getOrigin() - A;

    const double u = dot(pvec, tvec) * invdet;
    if (u < 0 || u > 1) return false;

    const Vec3 qvec = cross(tvec, edge1);
    const double v = dot(qvec, r.getDirection()) * invdet;

    if (v < 0 || u + v > 1.) return false;

    const double t = dot(qvec, edge2) * invdet;

    if (t < t_min || t > t_max) return false;

    rec.t = t;
    rec.p = r.getOrigin() + t * r.getDirection();
    rec.mat_ptr = mat_ptr;
    rec.normal = getNormal(rec);

    return true;
}

bool Triangle::bounding_box(AxisAlignedBoundingBox &box) const {
    Vec3 minv(min(min(A.x(), B.x()), C.x()), min(min(A.y(), B.y()), C.y()), min(min(A.z(), B.z()), C.z()));
    Vec3 maxv(max(max(A.x(), B.x()), C.x()), max(max(A.y(), B.y()), C.y()), max(max(A.z(), B.z()), C.z()));

    Vec3 dif = maxv - minv;
    if (dif.x() < 1E-5) maxv[0] += 1E-5;
    if (dif.y() < 1E-5) maxv[1] += 1E-5;
    if (dif.z() < 1E-5) maxv[2] += 1E-5;

    box = AxisAlignedBoundingBox(minv, maxv);
    return true;
}

void Triangle::Scale(double scale) {
    A *= scale;
    B *= scale;
    C *= scale;
    edge1 *= scale;
    edge2 *= scale;

    area *= scale * scale;
}

void Triangle::Translate(const Vec3 &t) {
    A += t;
    B += t;
    C += t;
}

