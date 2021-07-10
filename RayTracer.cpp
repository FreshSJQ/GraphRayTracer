#include "RayTracer.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

RayTracer::RayTracer() {
    srand(time(nullptr));
    nx = 384;
    ny = 384;
    ns = 384;
    Vec3 lookfrom(13, 2, 3);
    Vec3 lookat(0, 0, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.0;
    double vfov = 20.0;
//    Vec3 lookfrom(278, 278, -800);
//    Vec3 lookat(278, 278, 0);
//    double dist_to_focus = 10.0;
//    double aperture = 0.0;
//    double vfov = 40.0;

    camera = Camera(lookfrom, lookat, Vec3(0, 1, 0), vfov, double(nx) / double(ny), aperture, dist_to_focus, 0.0, 1.0);
}

Vec3 RayTracer::color(const Ray &r, Hitable *scene, int depth) {
    HitRecord hrec;
    if (scene->hit(r, 0.001, FLT_MAX, hrec)) {
        ScatterRecord srec;
        Vec3 emitted = hrec.mat_ptr->Emitted(r, hrec, hrec.u, hrec.v, hrec.p);
        if (depth < 50 && hrec.mat_ptr->scatter(r, hrec, srec)) {
            if(srec.isSpecular) {
                delete srec.pdf_ptr;
                return srec.attenuation * color(srec.specularRay, world, depth + 1);
            }
            HitablePDF pLight(light_shape, hrec.p);
            MixturePDF p(&pLight, srec.pdf_ptr);
            Ray scattered = Ray(hrec.p, p.generate(&srec), r.time());
            double pdf_val = p.value(scattered.getDirection());
            delete srec.pdf_ptr;
            if(pdf_val == 0) pdf_val = 1;
            return emitted + srec.attenuation * hrec.mat_ptr->scateringPDF(r, hrec, scattered) *
                color(scattered, scene, depth + 1) /  pdf_val;
        } else {
            return emitted;
        }
    } else {
        return Vec3(0, 0, 0);
    }
}


void RayTracer::BuildScene() {
    vector<Hitable *> list;
    Material *white = new Lambertian(new ConstantTexture(Vec3(0.73, 0.73, 0.73)));
    Material *light = new DiffuseLight(new ConstantTexture(Vec3(15, 15, 15)));
    Material *red = new Lambertian(new ConstantTexture(Vec3(0.65, 0.05, 0.05)));
    Material *microfacet = new Microfacet(new ConstantTexture(Vec3(0.65, 0.05, 0.05)), 10,
                                          new ConstantTexture(Vec3(0.05, 0.05, 0.65)));
    double exponent = 200. * randNum01();
    Material *phong = new AnisotropicPhong(100, 100,
                                           new ConstantTexture(Vec3(0.65, 0.05, 0.05)),
                                           new ConstantTexture(Vec3(0.7, 0.7, 0.7)));

    list.push_back(new RECTXZ(7, 8, 1, 2, 4, light));
    light_shape = new RECTXZ(7, 8, 1, 2, 4, nullptr);
    list.push_back(new Sphere(Vec3(0, -1000, 0), 1000, white));
    list.push_back(new Sphere(Vec3(5, 1, 1), 1.0, phong));

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
