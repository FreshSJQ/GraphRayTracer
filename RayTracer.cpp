#include "RayTracer.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

RayTracer::RayTracer() {
    srand(time(nullptr));
    nx = 200;
    ny = 100;
    ns = 100;
    Vec3 lookfrom(13, 2, 3);
    Vec3 lookat(0, 0, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.0;

    camera = Camera(lookfrom, lookat, Vec3(0, 1, 0), 20, double(nx) / double(ny), aperture, dist_to_focus, 0.0, 1.0);
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
    vector<Hitable *> list;
    Texture *checker = new CheckerTexture(new ConstantTexture(Vec3(0.2, 0.3, 0.1)),
                                          new ConstantTexture(Vec3(0.9, 0.9, 0.9)));
    list.push_back(new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(checker)));
    int i = 1;
    for(int a = -10; a < 10; a++) {
        for(int b = -10; b < 10; b++) {
            double choosMat = randNum01();
            Vec3 center(a + 0.9 * randNum01(), 0.2, b + 0.9 * randNum01());
            if((center - Vec3(4, 0.2, 0)).length() > 0.9) {
                if(choosMat < 0.8) {
                    list.push_back(new MovingSphere(center, center + Vec3(0, 0.5 * randNum01(), 0), 0.0, 1.0, 0.2, new Lambertian(
                            new ConstantTexture(
                                    Vec3(randNum01() * randNum01(), randNum01() * randNum01(), randNum01() * randNum01())))));
                } else if(choosMat < 0.95) {
                    list.push_back(new Sphere(center, 0.2,
                                              new Metal(new ConstantTexture(Vec3(0.5 * (1 + randNum01()), 0.5 * (1 + randNum01()), 0.5 * (1 + randNum01()))), 0.5 * randNum01())));
                } else {
                    list.push_back(new Sphere(center, 0.2, new Dielectric(1.5)));
                }
            }
        }
    }
    list.push_back(new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5)));
    list.push_back(new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(new ConstantTexture(Vec3(0.4, 0.2, 0.1)))));
    list.push_back(new Sphere(Vec3(5, 2, 1), 2.0, new Metal(new ConstantTexture(Vec3(0.7, 0.6, 0.5)), 0.0)));
    world = new BVHNode(list.begin(), list.end(), list.size());
}

void RayTracer::StartRayTracing() {
    ofstream fout("../output/sjq.ppm");
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
