#ifndef GRAPH_RAYTRACER_H
#define GRAPH_RAYTRACER_H

#pragma once

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <iostream>
#include <cstdlib>
#include <fstream>

#include "Vec3.h"
#include "Camera.h"
#include "Hitable.h"
#include "Geometry.h"
#include "Triangle.h"
#include "ObjLoader.h"
#include "BVHNode.h"
#include "Rectangle.h"
#include "Light.h"

using namespace std;

class RayTracer {
    int nx, ny, ns;
    Camera camera;
    BVHNode *world;
    vector<vector<double>> results;
    PointLight pointLight;
public:
    RayTracer();
    Vec3 color(const Ray &r, Hitable *world, int depth);
    void RandomScene();
    void BuildScene();
    void StartRayTracing();
};

#endif //GRAPH_RAYTRACER_H
