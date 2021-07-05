#ifndef RAYTRACER_PDF_H
#define RAYTRACER_PDF_H

#include "Hitable.h"

class PDF {
public:
    virtual double value(const Vec3& direction) const = 0;
    virtual Vec3 generate() const = 0;
};

class CosinePDF: public PDF {
    ONB uvw;
public:
    CosinePDF(const Vec3& w) {uvw.buildFromW(w);}
    double value(const Vec3& direction) const override {
        double cosine = dot(unit_vector(direction), uvw.w());
        if(cosine > 0)
            return cosine / PI;
        else
            return 0;
    };
    Vec3 generate() const override {
        return uvw.local(random_cosin_direction());
    };
};

class HitablePDF: public PDF {
    Vec3 o;
    Hitable *ptr;
public:
    HitablePDF(Hitable *p, const Vec3& origin) : ptr(p), o(origin){}
    double value(const Vec3& direction) const override {
        return ptr->pdfValue(o, direction);
    }
    Vec3 generate() const override {
        return ptr->random(o);
    }
};

class MixturePDF: public PDF {
    PDF *p[2];
public:
    MixturePDF(PDF* p0, PDF* p1) {p[0] = p0; p[1] = p1;}
    double value(const Vec3& direction) const override {
        return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
    }

    Vec3 generate() const override {
        if(randNum01() < 0.5)
            return p[0]->generate();
        else return p[1]->generate();
    }
};

class MicrofacetPDF : public PDF {
    ONB onb;
public:
    MicrofacetPDF(Vec3& inc, Vec3& norm):onb(norm, inc){}

};

#endif //RAYTRACER_PDF_H
