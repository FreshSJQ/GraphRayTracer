#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#pragma once

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class Vec3 {
public:
    Vec3() {}

    Vec3(double e0, double e1, double e2) {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    inline double x() const { return e[0]; }

    inline double y() const { return e[1]; }

    inline double z() const { return e[2]; }

    inline double r() const { return e[0]; }

    inline double g() const { return e[1]; }

    inline double b() const { return e[2]; }

    inline const Vec3 &operator+() const { return *this; }

    inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }

    inline double operator[](int i) const { return e[i]; }

    inline double &operator[](int i) { return e[i]; }

    inline Vec3 &operator+=(const Vec3 &v2);

    inline Vec3 &operator-=(const Vec3 &v2);

    inline Vec3 &operator*=(const Vec3 &v2);

    inline Vec3 &operator/=(const Vec3 &v2);

    inline Vec3 &operator*=(const double t);

    inline Vec3 &operator/=(const double t);

    inline Vec3 &operator+=(const double t);

    inline double length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    inline double squared_length() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline bool isEmitted() {
        return e[0] > 1.0 || e[1] > 1.0 || e[2] > 1.0;
    }

    inline void make_unit_vector();

    inline Vec3 Normalize() const;

    double e[3];
};

inline istream &operator>>(istream &is, Vec3 &t) {
    is >> t.e[0] >> t.e[1] >> t.e[2];
    return is;
}

inline ostream &operator<<(ostream &os, const Vec3 &t) {
    os << t.e[0] << " "<< t.e[1] <<" "<< t.e[2];
    return os;
}

inline void Vec3::make_unit_vector() {
    double k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
    return Vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vec3 operator/(Vec3 v, double t) {
    return Vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline double dot(const Vec3& v1, const Vec3 &v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
    return Vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
                (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
                (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}

inline Vec3 &Vec3::operator+=(const Vec3 &v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline Vec3 &Vec3::operator*=(const Vec3 &v) {
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline Vec3 &Vec3::operator/=(const Vec3 &v) {
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline Vec3 &Vec3::operator-=(const Vec3 &v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline Vec3 &Vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline Vec3 &Vec3::operator/=(const double t) {
    double k = 1.0 / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

Vec3 Vec3::Normalize() const {
    double len = length();
    if(len != 0) return *this / len;
    return *this;
}

Vec3 &Vec3::operator+=(const double t) {
    e[0] += t;
    e[1] += t;
    e[2] += t;
    return *this;
}

inline Vec3 unit_vector(Vec3 v) {
    return v / v.length();
}

inline Vec3 de_nan(const Vec3& c) {
    Vec3 temp = c;
    if(temp[0] != temp[0]) temp[0] = 0;
    if(temp[1] != temp[1]) temp[1] = 0;
    if(temp[2] != temp[2]) temp[2] = 0;
    return temp;
}

#endif //RAYTRACER_VEC3_H
