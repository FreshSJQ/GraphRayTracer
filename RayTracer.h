#ifndef RAYTRACER_RAYTRACER_H
#define RAYTRACER_RAYTRACER_H

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
#include "FlipNormals.h"
#include "Translate.h"
#include "RotateY.h"
#include "Box.h"
#include "PDF.h"

using namespace std;

class RayTracer {
    int nx, ny, ns;
    Camera camera;
    BVHNode *world;
    vector<vector<double>> results;
    Hitable* light_shape;
public:
    RayTracer();
    Vec3 color(const Ray &r, Hitable *world, int depth);
    void BuildScene();
    void StartRayTracing();
};

#endif //RAYTRACER_RAYTRACER_H
