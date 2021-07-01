#include "RayTracer.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

RayTracer::RayTracer() {
    srand(time(nullptr));
    nx = 400;
    ny = 400;
    ns = 200;
//    Vec3 lookfrom(13, 2, 3);
//    Vec3 lookat(0, 0, 0);
//    double dist_to_focus = 10.0;
//    double aperture = 0.0;
//    double vfov = 20.0
    Vec3 lookfrom(278, 278, -800);
    Vec3 lookat(278, 278, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.0;
    double vfov = 40.0;

    camera = Camera(lookfrom, lookat, Vec3(0, 1, 0), vfov, double(nx) / double(ny), aperture, dist_to_focus, 0.0, 1.0);
}

Vec3 RayTracer::color(const Ray &r, Hitable *scene, int depth) {
    HitRecord rec;
    if (scene->hit(r, 0.001, FLT_MAX, rec)) {
        Ray scattered;
        Vec3 attenuation;
        Vec3 emitted = rec.mat_ptr->Emitted(r, rec, rec.u, rec.v, rec.p);
        double pdf_val;
        Vec3 albedo;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, albedo, scattered, pdf_val)) {
//            Hitable *light_shape = new RECTXZ(213, 343, 227, 332, 554, 0);
            Hitable* light_shape = new Disk(Vec3(278, 554, 278), 100, 0);
            HitablePDF p0(light_shape, rec.p);
            CosinePDF p1(rec.normal);
            MixturePDF p(&p0, &p1);
            scattered = Ray(rec.p, p.generate(), r.time());
            pdf_val = p.value(scattered.getDirection());
            if(pdf_val == 0) {
                pdf_val = 1;
            }
            delete light_shape;
//            Hitable *light_shape = new RECTXZ(213, 343, 227, 332, 554, 0);
//            HitablePDF p(light_shape, rec.p);
//            scattered = Ray(rec.p, p.generate(), r.time());
//            pdf_val = p.value(scattered.getDirection());
            return emitted + albedo * rec.mat_ptr->scateringPDF(r, rec, scattered) * color(scattered, scene, depth + 1) /  pdf_val;
        } else {
            return emitted;
        }
    } else {
        return Vec3(0, 0, 0);
    }
}


void RayTracer::BuildScene() {
    vector<Hitable *> list;
    Material *red = new Lambertian(new ConstantTexture(Vec3(0.65, 0.05, 0.05)));
    Material *white = new Lambertian(new ConstantTexture(Vec3(0.73, 0.73, 0.73)));
    Material *green = new Lambertian(new ConstantTexture(Vec3(0.12, 0.45, 0.15)));
    Material *light = new DiffuseLight(new ConstantTexture(Vec3(15, 15, 15)));

    list.push_back(new FlipNormals(new RECTYZ(0, 555, 0, 555, 555, green)));
    list.push_back(new RECTYZ(0, 555, 0, 555, 0, red));
//    list.push_back(new RECTXZ(213, 343, 227, 332, 554, light));
//    list.push_back(new RECTXZ(213, 343, 227, 332, 100, red));
    list.push_back(new Disk(Vec3(278, 554, 278), 100, light));
//    list.push_back(new RECTXZ(213, 343, 227, 332, 100, light));
    list.push_back(new FlipNormals(new RECTXZ(0, 555, 0, 555, 555, white)));
    list.push_back(new RECTXZ(0, 555, 0, 555, 0, white));
    list.push_back(new FlipNormals(new RECTXY(0, 555, 0, 555, 555, white)));

//    list.push_back(new Translate(new RotateY(
//            new Box(Vec3(0, 0, 0), Vec3(165, 165, 165), white), -18), Vec3(130, 0, 65)));
//    list.push_back(new Translate(new RotateY(
//            new Box(Vec3(0, 0, 0), Vec3(165, 330, 168), white), 15), Vec3(265, 0, 295)));
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
                double u = (double(i) + randNum01()) / double(nx);
                double v = (double(j) + randNum01()) / double(ny);
                Ray r = camera.get_ray(u, v);
                col += de_nan(color(r, world, 0));
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
