#ifndef RAYTRACER_PDF_H
#define RAYTRACER_PDF_H

#include "Hitable.h"

class PDF {
public:
    virtual double value(const Vec3 &direction) const = 0;

    virtual Vec3 generate(ScatterRecord* srec) const = 0;
};

class CosinePDF : public PDF {
    ONB uvw;
public:
    CosinePDF(const Vec3 &w) { uvw.buildFromW(w); }

    double value(const Vec3 &direction) const override {
        double cosine = dot(unit_vector(direction), uvw.w());
        if (cosine > 0)
            return cosine / PI;
        else
            return 0;
    };

    Vec3 generate(ScatterRecord* srec) const override {
        return uvw.local(random_cosin_direction());
    };
};

class HitablePDF : public PDF {
    Vec3 o;
    Hitable *ptr;
public:
    HitablePDF(Hitable *p, const Vec3 &origin) : ptr(p), o(origin) {}

    double value(const Vec3 &direction) const override {
        return ptr->pdfValue(o, direction);
    }

    Vec3 generate(ScatterRecord* srec) const override {
        return ptr->random(o);
    }
};

class MixturePDF : public PDF {
    PDF *p[2];
public:
    MixturePDF(PDF *p0, PDF *p1) {
        p[0] = p0;
        p[1] = p1;
    }

    double value(const Vec3 &direction) const override {
        return 0.5 * p[0]->value(direction) + 0.5 * p[1]->value(direction);
    }

    Vec3 generate(ScatterRecord* srec) const override {
        if (randNum01() < 0.5)
            return p[0]->generate(srec);
        else return p[1]->generate(srec);
    }
};



class MicrofacetPDF : public PDF {
    ONB uvw;
    Vec3 incident, normal;
    double roughness;

    Vec3 FresnelSchlick(Vec3 f0, double LdotH) const {
        return f0 + (Vec3(1., 1., 1.) - f0) * pow(1. - LdotH, 5.);
    }

    double Distribution(double NdotH) const {
        double alpha2 = roughness * roughness;
        double d = NdotH * NdotH * (alpha2 - 1) + 1;
        return alpha2 / (d * d * PI);
    }

    double schlickMasking(double NdotL, double NdotV) const {
        double k = (roughness + 1) * (roughness + 1) / 8;
        double gl = NdotL * (NdotL * (1 - k) + k);
        double gv = NdotV * (NdotV * (1 - k) + k);
        return gl * gv;
    }

public:
    MicrofacetPDF(Vec3 inc, Vec3 norm, double r) :
            incident(inc), normal(norm), uvw(norm, inc), roughness(r) {}

    double value(const Vec3 &direction) const override {
        Vec3 H = (uvw.w() + incident).Normalize();
        double NdotH = dot(normal, H);
        double HdotV = dot(H, uvw.w());
        double D = Distribution(NdotH);
        return D * NdotH / (4 * HdotV);
//        double cosine = dot(unit_vector(direction), uvw.w());
//        if (cosine > 0)
//            return cosine / PI;
//        else
//            return 0;

    }

    Vec3 generate(ScatterRecord* srec) const override {
        Vec3 H = (uvw.w() + incident).Normalize();
        double NdotL = dot(normal, incident);
        double NdotH = dot(normal, H);
        double LdotH = dot(incident, H);
        double NdotV = dot(normal, uvw.w());

        double D = Distribution(NdotH);
        double G = schlickMasking(NdotL, NdotV);
        Vec3 F = FresnelSchlick(srec->specularColor, LdotH);

//        srec->attenuation =  D * G * F / (4 * NdotV);
        return uvw.local(random_cosin_direction());
//        return uvw.w();
    }

};

class AnisotropicPhongPDF : public PDF {
    double nu, nv;
    double prefactor1, prefactor2;
    Vec3 incident;
    ONB onb;
public:
    AnisotropicPhongPDF(Vec3 inc, Vec3 norm, double u, double v):
        incident(inc), onb(norm, inc), nu(u), nv(v){
        prefactor1 = sqrt((nu + 1.) / (nv + 1.));
        prefactor2 = sqrt((nu + 1.) * (nv + 1.)) / (2. * PI);
    }

    double value(const Vec3 &direction) const override {
        double cosine = dot(unit_vector(direction), onb.w());
        if (cosine > 0)
            return cosine / PI;
        else
            return 0;
    }

    Vec3 getSpecularReflected(Vec3 incident, Vec3 h, double kh) const {
        return incident + 2. * kh *h;
    }

    double getSpecularPDH(Vec3 h, double kh, double cos2, double sin2) const {
        return getHPDH(h, cos2, sin2) / (4. * kh);
    }

    double getHPDH(Vec3 h, double cos2, double sin2) const {
        double nh = dot(h, onb.w());
        return prefactor2 * pow(nh, nu * cos2 + nv * sin2);
    }

    Vec3 generate(ScatterRecord* srec) const override {
        double xi = randNum01();

        double phase = 0;
        bool flip = false;


        if (xi < 0.25)
        {
            xi *= 4;
        }
        else if (xi < 0.5)
        {
            xi = 1. - 4. * (0.5 - xi);
            phase = PI;
            flip = true;
        }
        else if (xi < 0.75)
        {
            xi = 1. - 4. * (0.75 - xi);
            phase = PI;
        }
        else
        {
            xi = 1. - 4. * (1. - xi);
            phase = 2. * PI;
            flip = true;
        }


        double phi = atan(prefactor1 * tan(2 * PI * xi));
        if (flip)
            phi = phase - phi;
        else
            phi += phase;

        const double c = cos(phi);
        const double s = sin(phi);
        const double c2 = c * c;
        const double s2 = 1. - c2;

        xi = randNum01();

        phase = 0;
        flip = false;

        if (xi < 0.25)
        {
            xi *= 4;
        }
        else if (xi < 0.5)
        {
            xi = 1. - 4. * (0.5 - xi);
            phase = PI;
            flip = true;
        }
        else if (xi < 0.75)
        {
            xi = 1. - 4. * (0.75 - xi);
            phase = PI;
        }
        else
        {
            xi = 1. - 4. * (1. - xi);
            phase = 2. * PI;
            flip = true;
        }


        double theta = acos(pow(1. - xi, 1. / (nu * c2 + nv * s2 + 1.)));
        if (flip)
            theta = phase - theta;
        else
            theta += phase;

        double st = sin(theta);
        double ct = cos(theta);

        double cos2 = ct * ct;
        double sin2 = st * st;

        Vec3 h = onb.local(Vec3(st * c, st * s, ct));

        double kh = -dot(incident, h);
        double specularProbability = getSpecularPDH(h, kh, cos2, sin2);
        double weight = 1. + specularProbability;

        double diffuseProbability = 1. / weight;


        if (randNum01() < diffuseProbability)
        {
            srec->attenuation = srec->diffuseColor;
            return onb.local(random_cosin_direction());
        }

        srec->attenuation = srec->specularColor;
        return getSpecularReflected(incident, h, kh);
    }
};

#endif //RAYTRACER_PDF_H
