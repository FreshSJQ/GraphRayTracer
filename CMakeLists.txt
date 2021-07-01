cmake_minimum_required(VERSION 3.17)
project(RayTracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(RayTracer main.cpp RayTracer.h RayTracer.cpp Vec3.h Camera.h Hitable.h Geometry.h Triangle.h ObjLoader.h BVHNode.h Rectangle.h Ray.h Utils.h Utils.cpp Triangle.cpp AxisAlignedBoundingBox.h AxisAlignedBoundingBox.cpp BVHNode.cpp Geometry.cpp Material.h Material.cpp ObjLoader.cpp Rectangle.cpp Texture.h PerlinNoise.h PerlinNoise.cpp RotateY.h RotateY.cpp Translate.h Translate.cpp FlipNormals.h Box.h Box.cpp ONB.h PDF.h)