#ifndef GRAPH_TEXTURE_H
#define GRAPH_TEXTURE_H

#include "Vec3.h"
#include "PerlinNoise.h"

class Texture {
public:
    Vec3 color;
    virtual Vec3 Value(double u, double v, const Vec3 &p) const = 0;
};

class ConstantTexture : public Texture {
public:
    Vec3 color;

    ConstantTexture() = default;

    ConstantTexture(Vec3 c) : color(c) {}

    Vec3 Value(double u, double v, const Vec3 &p) const override {
        return color;
    };
};

class CheckerTexture : public Texture {
public:
    Texture *odd;
    Texture *even;

    CheckerTexture() {}

    CheckerTexture(Texture *t0, Texture *t1) : even(t0), odd(t1) {}

    Vec3 Value(double u, double v, const Vec3 &p) const override {
        double sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
        if (sines < 0)
            return odd->Value(u, v, p);
        else
            return even->Value(u, v, p);
    }
};

class NoiseTexture : public Texture {
public:
    PerlinNoise noise;
    double scale;

    NoiseTexture(double sc) : scale(sc) {}

    Vec3 Value(double u, double v, const Vec3 &p) const override {
//        return Vec3(1, 1, 1) * noise.noise(scale * p);
        return Vec3(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p)));
    }
};

class ImageTexture : public Texture {
public:
    vector<vector<Vec3>> imageData;
    int width, height;

    ImageTexture() {}

    ImageTexture(unsigned char *pixels, int A, int B) : width(A), height(B) {
        imageData.resize(height);
        for(int i = height - 1; i >= 0; i--) {
            imageData[i].resize(width);
            for(int j = 0; j < width; j++) {
                double r = int(pixels[3 * j + 3 * width * i]) / 255.0;
                double g = int(pixels[3 * j + 3 * width * i + 1]) / 255.0;
                double b = int(pixels[3 * j + 3 * width * i + 2]) / 255.0;
                imageData[i][j] = Vec3(r, g, b);
            }
        }
    }

    Vec3 Value(double u, double v, const Vec3 &p) const override {
        int i = u * width;
        int j = (1 - v) * height - 0.001;

        if (i < 0) i = 0;
        if (j < 0) j = 0;
        if (i > width - 1) i = width - 1;
        if (j > height - 1) j = height - 1;
        return imageData[j][i];
    }
};

#endif //GRAPH_TEXTURE_H
