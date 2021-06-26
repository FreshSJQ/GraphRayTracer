#ifndef RAYTRACER_PERLINNOISE_H
#define RAYTRACER_PERLINNOISE_H

#include "Vec3.h"
#include "Utils.h"

double perlinInterp(Vec3 c[2][2][2], double u, double v, double w);

double perlin_generate(Vec3 c[2][2][2], double u, double v, double w);

static Vec3* perlinGenerate();

void permute(int *p, int n);

static int* perlinGeneratePerm();

class PerlinNoise {
public:
    static double *randDouble;
    static Vec3 *ranVec;
    static int *perm_x;
    static int *perm_y;
    static int *perm_z;

    double noise(const Vec3& p) const {
        double u = p.x() - floor(p.x());
        double v = p.y() - floor(p.y());
        double w = p.z() - floor(p.z());
//        int i = int(4 * p.x()) & 255;
//        int j = int(4 * p.y()) & 255;
//        int k = int(4 * p.z()) & 255;
//        return randDouble[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
        int i = floor(p.x());
        int j = floor(p.y());
        int k = floor(p.z());
        Vec3 c[2][2][2];
        for(int di = 0; di < 2; di++) {
            for(int dj = 0; dj < 2; dj++) {
                for(int dk = 0; dk < 2; dk++)
                    c[di][dj][dk] = ranVec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^ perm_z[(k + dk) & 255]];
            }
        }
        return perlinInterp(c, u, v, w);
    }

    double turb(const Vec3& p, int depth = 7) const {
        double accum = 0;
        Vec3 temp = p;
        double weight = 1.0;
        for(int i = 0; i < depth; i++) {
            accum += weight * noise(temp);
            weight *= 0.5;
            temp *= 2;
        }
        return fabs(accum);
    }
};

#endif //RAYTRACER_PERLINNOISE_H
