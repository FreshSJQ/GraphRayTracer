#include "RayTracer.h"

RayTracer::RayTracer() {
    srand(time(nullptr));
    nx = 960;
    ny = 540;
    ns = 200;
    Vec3 lookfrom(0, 300, 500);
    Vec3 lookat(0, 0, -300);
    double dist_to_focus = 10;
    camera = Camera(lookfrom, lookat, Vec3(0, 1, 0), 40, double(nx) / double(ny), dist_to_focus);
}

Vec3 RayTracer::color(const Ray &r, Hitable *scene, int depth) {
    HitRecord rec;
    if (scene->hit(r, 0.001, FLT_MAX, rec)) {
        Ray scattered;
        Vec3 attenuation;
        Vec3 emitted = rec.mat_ptr->Emitted(rec.u, rec.v, rec.p);
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return emitted + attenuation * color(scattered, scene, depth + 1);
        } else {
            return emitted;
        }
    } else {
        Vec3 unit_direction = unit_vector(r.getDirection());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
    }
}

void RayTracer::BuildScene() {
//    auto material1 = new DiffuseLight(new ConstantTexture(Vec3(7, 7, 7)));
//    auto material3 = new DiffuseLight(new ConstantTexture(Vec3(1, 0, 0)));

    auto WallMat = new Lambertian(new ConstantTexture(Vec3(0.5, 0.5, 0.5)));

    auto RabbitMat = new Lambertian(new ConstantTexture(Vec3(0.65, 0.13, 0.13)));
    auto DiscobolusMat = new Lambertian(new ConstantTexture(Vec3(1, 1, 1)));

    auto SphereMetMat1 = new Metal(new ConstantTexture(Vec3(0, 1, 0)), 10);
    auto SphereMetMat2 = new Metal(new ConstantTexture(Vec3(0, 0, 1)), 0.5);
    auto SphereMetMat3 = new Metal(new ConstantTexture(Vec3(1, 0, 1)), 0.5);
    auto SphereMetMat4 = new Metal(new ConstantTexture(Vec3(1, 0.95, 0)), 0);

    auto SphereDieMat1 = new Dielectric(1.5);
    auto SphereDieMat2 = new Dielectric(0.8);

    auto SphereLamMat1 = new Lambertian(new ConstantTexture(Vec3(0.7, 0.5, 0.1)));
    auto SphereLamMat2 = new Lambertian(new ConstantTexture(Vec3(0.3, 0.6, 1.0)));
    auto SphereLamMat3 = new Lambertian(new ConstantTexture(Vec3(0.3, 1, 0.5)));

    auto CylinderMat1 = new Lambertian(new ConstantTexture(Vec3(1.0, 1.0, 0)));
    auto CylinderMat2 = new Lambertian(new ConstantTexture(Vec3(1.0, 0.0, 1.0)));


    vector<Hitable *> list;

    list.push_back(new RECTXZ(-300, 300, -300, 300, 0, WallMat));
    list.push_back(new RECTXY(-300, 300, 0, 500, -300, WallMat));
    list.push_back(new RECTYZ(0, 500, -300, 300, 300, WallMat));
    list.push_back(new RECTYZ(0, 500, -300, 300, -300, WallMat));

    list.push_back(new Sphere(Vec3(100, 50, 100), 50, SphereMetMat2));
    list.push_back(new Sphere(Vec3(-150, 20, 0), 20, SphereMetMat3));
    list.push_back(new Sphere(Vec3(-100, 25, 80), 25, SphereLamMat1));
    list.push_back(new Sphere(Vec3(-200, 40, 40), 40, SphereDieMat1));
    list.push_back(new Sphere(Vec3(-200, 30, -40), 30, SphereLamMat2));
    list.push_back(new Sphere(Vec3(-100, 50, -100), 50, SphereMetMat1));
    list.push_back(new Sphere(Vec3(190, 30, -100), 30, SphereLamMat3));
    list.push_back(new Sphere(Vec3(100, 50, -70), 50, SphereDieMat2));
    list.push_back(new Sphere(Vec3(-200, 200, -70), 70, SphereMetMat4));

    list.push_back(new Cylinder(Vec3(0, 0, 0), 50, 50, CylinderMat1));
    list.push_back(new Cylinder(Vec3(240, 0, 0), 40, 200, CylinderMat2));

    ObjLoader loader1;
    loader1.Load("./src/rabbit.obj", 500, Vec3(0, 0, 100), RabbitMat);
    list.insert(list.end(), loader1.triangles.begin(), loader1.triangles.end());
    ObjLoader loader2;
    loader2.Load("./src/Discobolus.obj", 0.115, Vec3(0, 50, 0), DiscobolusMat);
    list.insert(list.end(), loader2.triangles.begin(), loader2.triangles.end());

    world = new BVHNode(list.begin(), list.end(), list.size());
}

void RayTracer::StartRayTracing() {
    ofstream fout("./output/temp1.ppm");
    fout << "P3\n" << nx << " " << ny << "\n255\n";
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
