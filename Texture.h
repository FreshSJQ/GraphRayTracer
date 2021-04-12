#ifndef GRAPH_TEXTURE_H
#define GRAPH_TEXTURE_H

#include "Vec3.h"

class Texture {
public:
    virtual Vec3 Value(double u, double v, const Vec3& p) const = 0;
};

class ConstantTexture : public Texture{
public:
    Vec3 color;
    ConstantTexture()=default;
    ConstantTexture(Vec3 c):color(c){}
    Vec3 Value(double u, double v, const Vec3& p) const override {
        return color;
    };
};

#endif //GRAPH_TEXTURE_H
