#include "RayTracer.h"

int main() {
    RayTracer rayTracer;
    rayTracer.BuildScene();
    rayTracer.StartRayTracing();
//    int N = 1000000;
//    double sum = 0.0;
//    for (int i = 0; i < N; i++) {
//        Vec3 v = random_cosin_direction();
//        sum += v.z() * v.z() * v.z() / (v.z() / PI);
//    }
//    cout<<sum<<endl;
//    cout << "PI/2 = " << PI / 2 << endl;
//    cout << "Estimate = " << sum / N << endl;
//    int N = 1000000;
//    double sum = 0.0;
//    for (int i = 0; i < N; i++) {
//        double r1 = randNum01();
//        double r2 = randNum01();
//        double x = cos(2 * PI * r1) * 2 * sqrt(r2 * (1 - r2));
//        double y = sin(2 * PI * r1) * 2 * sqrt(r2 * (1 - r2));
//        double z = 1 - r2;
//        sum += z * z * z / (1.0 / (2.0 * PI));
//    }
//    cout << "PI / 2 = " << PI / 2 << endl;
//    cout << "Estimate = " << sum / N << endl;
    return 0;
}
