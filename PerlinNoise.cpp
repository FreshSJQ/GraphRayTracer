#include "PerlinNoise.h"

static double *perlin_generate() {
    double * p = new double[256];
    for(int i = 0; i < 256; i++)
        p[i] = randNum01();
    return p;
}

static Vec3 *perlinGenerate() {
    Vec3 *p = new Vec3[256];
    for (int i = 0; i < 256; i++)
        p[i] = unit_vector(Vec3(-1 + 2 * randNum01(), -1 + 2 * randNum01(), -1 + 2 * randNum01()));
    return p;
}

void permute(int *p, int n) {
    for (int i = n - 1; i > 0; i--) {
        int target = int(randNum01() * (i + 1));
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
    return;
}

static int *perlinGeneratePerm() {
    int *p = new int[256];
    for (int i = 0; i < 256; i++)
        p[i] = i;
    permute(p, 256);
    return p;
}

double perlinInterp(Vec3 c[2][2][2], double u, double v, double w) {
    double uu = u * u * (3 - 2 * u);
    double vv = v * v * (3 - 2 * v);
    double ww = w * w * (3 - 2 * w);
    double accum = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                Vec3 weightV(u - i, v - j, w - k);
                accum += (i * uu + (1 - i) * (1 - uu)) *
                         (j * vv + (1 - j) * (1 - vv)) *
                         (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weightV);
            }
        }
    }
    return accum;
}

double *PerlinNoise::randDouble = perlin_generate();
Vec3 *PerlinNoise::ranVec = perlinGenerate();
int *PerlinNoise::perm_x = perlinGeneratePerm();
int *PerlinNoise::perm_y = perlinGeneratePerm();
int *PerlinNoise::perm_z = perlinGeneratePerm();
