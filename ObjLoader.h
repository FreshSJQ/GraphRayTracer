#ifndef RAYTRACER_OBJLOADER_H
#define RAYTRACER_OBJLOADER_H

#pragma once

#include <vector>
#include <tuple>
#include "Triangle.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "Material.h"

class ObjLoader {
    // 加载Obj文件
public:
    typedef vector<tuple<int, int, int>> TrianglePoint;
    vector<Triangle*> triangles;
    double miny;
    Vec3 centerCoord;

    ObjLoader() = default;

    void Load(const string &name, double scale, const Vec3& tran, Material* mat_ptr);

};

#endif //RAYTRACER_OBJLOADER_H
