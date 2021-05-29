#include "RayTracer.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

RayTracer::RayTracer() {
    pointLight = PointLight(Vec3(7, 7, 7), Vec3(200, 400, 500));
    srand(time(nullptr));
    nx = 200;
    ny = 100;
    ns = 100;
    Vec3 lookfrom(13, 2, 3);
    Vec3 lookat(0, 0, 0);
    double dist_to_focus = 10;
    camera = Camera(lookfrom, lookat, Vec3(0, 1, 0), 40, double(nx) / double(ny), dist_to_focus);
}

Vec3 RayTracer::color(const Ray &r, Hitable *scene, int depth) {
    HitRecord rec;
    if (scene->hit(r, 0.001, FLT_MAX, rec)) {
//        if(depth == 0 && pointLight.intersect(rec, scene)) {
//            return Vec3(0, 0, 0);
//        }
        Ray scattered;
        Vec3 attenuation;
        Vec3 emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.p);
//        if(emitted.isEmitted()) {
//            if (dot(rec.normal, r.getDirection()) < 0) return emitted;
//            return Vec3(0, 0, 0); // no emission from the back!
//        }
//        Vec3 emitted = pointLight.intensity;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return emitted + attenuation * color(scattered, scene, depth + 1);
        } else {
            return emitted;
        }
    } else {
        Vec3 unit_direction = unit_vector(r.getDirection());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
//        return Vec3(0, 0, 0);
    }
}


void RayTracer::BuildScene() {
    RandomScene();
////    auto material1 = new DiffuseLight(new ConstantTexture(Vec3(4, 4, 4)));
////    auto material3 = new DiffuseLight(new ConstantTexture(Vec3(1, 0, 0)));
//
//    auto WallMat = new Lambertian(new ConstantTexture(Vec3(0.5, 0.5, 0.5)));
////
////    auto RabbitMat = new Lambertian(new ConstantTexture(Vec3(0.65, 0.13, 0.13)));
////    auto DiscobolusMat = new Lambertian(new ConstantTexture(Vec3(1, 1, 1)));
////
//    auto SphereMetMat1 = new Metal(new ConstantTexture(Vec3(0, 1, 0)), 10);
////    auto SphereMetMat2 = new Metal(new ConstantTexture(Vec3(0, 0, 1)), 0.5);
////    auto SphereMetMat3 = new Metal(new ConstantTexture(Vec3(1, 0, 1)), 0.5);
////    auto SphereMetMat4 = new Metal(new ConstantTexture(Vec3(1, 0.95, 0)), 0);
////
////    auto SphereDieMat1 = new Dielectric(1.5);
////    auto SphereDieMat2 = new Dielectric(0.8);
////
////    auto SphereLamMat1 = new Lambertian(new ConstantTexture(Vec3(0.7, 0.5, 0.1)));
////    auto SphereLamMat2 = new Lambertian(new ConstantTexture(Vec3(0.3, 0.6, 1.0)));
////    auto SphereLamMat3 = new Lambertian(new ConstantTexture(Vec3(0.3, 1, 0.5)));
////
////    auto CylinderMat1 = new Lambertian(new ConstantTexture(Vec3(1.0, 1.0, 0)));
////    auto CylinderMat2 = new Lambertian(new ConstantTexture(Vec3(1.0, 0.0, 1.0)));
////
////
//    vector<Hitable *> list;
////
//    list.push_back(new RECTXZ(-300, 300, -300, 300, 0, WallMat));
//////    list.push_back(new RECTXZ(-300, 300, -300, 300, 500, WallMat));
//    list.push_back(new RECTXY(-300, 300, 0, 500, -300, WallMat));
//////    list.push_back(new RECTXY(-300, 300, 0, 500, 500, WallMat));
//    list.push_back(new RECTYZ(0, 500, -300, 300, 300, WallMat));
//    list.push_back(new RECTYZ(0, 500, -300, 300, -300, WallMat));
//
//    Texture *checker = new CheckerTexture(new ConstantTexture(Vec3(0.2, 0.3, 0.1)),
//                                          new ConstantTexture(Vec3(0.9, 0.9, 0.9)));
//    list.push_back(new Sphere(Vec3(0, 150, 0), 150, new Lambertian(checker)));
//////
//////    list.push_back(new RECTXZ(-100, 100, -100, 100, 500, material1));
//////
////    list.push_back(new Sphere(Vec3(100, 50, 100), 50, SphereMetMat2));
////    list.push_back(new Sphere(Vec3(-150, 20, 0), 20, SphereMetMat3));
////    list.push_back(new Sphere(Vec3(-100, 25, 80), 25, SphereLamMat1));
////    list.push_back(new Sphere(Vec3(-200, 40, 40), 40, SphereDieMat1));
////    list.push_back(new Sphere(Vec3(-200, 30, -40), 30, SphereLamMat2));
////    list.push_back(new Sphere(Vec3(-100, 50, -100), 50, SphereMetMat1));
////    list.push_back(new Sphere(Vec3(190, 30, -100), 30, SphereLamMat3));
////    list.push_back(new Sphere(Vec3(100, 50, -70), 50, SphereDieMat2));
////    list.push_back(new Sphere(Vec3(-200, 200, -70), 70, SphereMetMat4));
//////
////    list.push_back(new Cylinder(Vec3(0, 0, 0), 50, 50, CylinderMat1));
////    list.push_back(new Cylinder(Vec3(240, 0, 0), 40, 200, CylinderMat2));
//
////    ObjLoader loader1;
////    loader1.Load("./src/rabbit.obj", 500, Vec3(0, 0, 100), RabbitMat);
////    list.insert(list.end(), loader1.triangles.begin(), loader1.triangles.end());
////    ObjLoader loader2;
////    loader2.Load("./src/Discobolus.obj", 0.115, Vec3(0, 50, 0), DiscobolusMat);
////    list.insert(list.end(), loader2.triangles.begin(), loader2.triangles.end());
//
////    world = new BVHNode(list.begin(), list.end(), list.size());
//    world = new BVHNode(list.begin(), list.end(), list.size());
}

void RayTracer::StartRayTracing() {
    ofstream fout("./output/sjq.ppm");
    fout << "P3\n" << nx << " " << ny << "\n255\n";
//    int width, height, nn;
//    unsigned char *tex_data = stbi_load("./src/earthmap.jpg", &width, &height, &nn, 0);
//    Texture *mat = new ImageTexture(tex_data, width, height);
//    for (int j = ny - 1; j >= 0; j--) {
//        cout << j << endl;
//        for (int i = 0; i < nx; i++) {
//            Vec3 col = mat->Value(double(i) / nx,double(j) / ny, Vec3(0, 0, 0));
//            int ir = int(col.x() * 255.99);
//            int ig = int(col.y() * 255.99);
//            int ib = int(col.z() * 255.99);
////            cout<<ir<<" "<<ig<<" "<<ib<<endl;
//            fout << ir << " " << ig << " " << ib << "\n";
//        }
//    }
    for (int j = ny - 1; j >= 0; j--) {
        cout << j << endl;
        for (int i = 0; i < nx; i++) {
            Vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                double u = double(i + randNum01()) / double(nx);
                double v = double(j + randNum01()) / double(ny);
                Ray r = camera.get_ray(u, v);
                col += color(r, world, 0);
            }

            col /= double(ns);
            col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            fout << ir << " " << ig << " " << ib << "\n";
        }
    }
}

void RayTracer::RandomScene() {
    vector<Hitable *> list;
    Texture *pertext = new NoiseTexture(5);
    list.push_back(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(pertext)));
//    list.push_back((new Sphere(Vec3(5, 2, 1), 2.0, new Lambertian(pertext))));
    int width, height, nn;
    unsigned char *tex_data = stbi_load("./src/earthmap.jpg", &width, &height, &nn, 0);
    Material *mat = new Lambertian(new ImageTexture(tex_data, width, height));
    Material *light = new Lambertian(new ConstantTexture(Vec3(15, 15, 15)));
    list.push_back(new Sphere(Vec3(6, 2, 4), 1.0, mat));
    list.push_back(new Sphere(Vec3(5, 2, 1), 2.0, mat));
//    Texture *checker = new CheckerTexture(new ConstantTexture(Vec3(0.2, 0.3, 0.1)),
//                                          new ConstantTexture(Vec3(0.9, 0.9, 0.9)));
//    list.push_back(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(checker)));
//    int i = 1;
//    for(int a = -10; a < 10; a++) {
//        for(int b = -10; b < 10; b++) {
//            double choosMat = randNum01();
//            Vec3 center(a + 0.9 * randNum01(), 0.2, b + 0.9 * randNum01());
//            if((center - Vec3(4, 0.2, 0)).length() > 0.9) {
//                if(choosMat < 0.8) {
//                    list.push_back(new Sphere(center, 0.2, new Lambertian(
//                            new ConstantTexture(
//                                    Vec3(randNum01() * randNum01(), randNum01() * randNum01(), randNum01() * randNum01())))));
//                } else if(choosMat < 0.95) {
//                    list.push_back(new Sphere(center, 0.2,
//                                              new Metal(new ConstantTexture(Vec3(0.5 * (1 + randNum01()), 0.5 * (1 + randNum01()), 0.5 * (1 + randNum01()))), 0.5 * randNum01())));
//                } else {
//                    list.push_back(new Sphere(center, 0.2, new Dielectric(1.5)));
//                }
//            }
//        }
//    }
//    list.push_back(new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5)));
//    list.push_back(new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(new ConstantTexture(Vec3(0.4, 0.2, 0.1)))));
//    list.push_back(new Sphere(Vec3(5, 2, 1), 2.0, new Metal(new ConstantTexture(Vec3(0.7, 0.6, 0.5)), 0.0)));
    world = new BVHNode(list.begin(), list.end(), list.size());
}
