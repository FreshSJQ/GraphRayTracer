#ifndef GRAPH_RAYTRACER_H
#define GRAPH_RAYTRACER_H

#pragma once

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "Vec3.h"
#include "Camera.h"
#include "Hitable.h"
#include "Geometry.h"
#include "Triangle.h"
#include "ObjLoader.h"
#include "BVHNode.h"
#include "Rectangle.h"

using namespace std;

class RayTracer {
    int nx, ny, ns;
    Camera camera;
    BVHNode *world;
    vector<vector<double>> results;
public:
    RayTracer();
    Vec3 color(const Ray &r, Hitable *world, int depth);
    void BuildScene();
    void StartRayTracing();
};

#endif //GRAPH_RAYTRACER_H
