#include "ObjLoader.h"

void ObjLoader::Load(const string &name, double scale, const Vec3& tran, Material* mat_ptr) {
    ifstream infile(name);
    string line;
    vector<Vec3> vertices;
    centerCoord = Vec3(0, 0, 0);
    TrianglePoint trianglePoints;
    while (getline(infile, line)) {
        switch (line[0]) {
            case 'v': {
                line = line.substr(2);
                Vec3 vertex;
                istringstream st(line);
                st >> vertex;
                vertices.emplace_back(vertex);
                centerCoord += vertex;
                break;
            }
            case 'f': {
                line = line.substr(2);
                istringstream st(line);
                int iv1, iv2, iv3;
                st >> iv1 >> iv2 >> iv3;
                trianglePoints.emplace_back(make_tuple(iv1 - 1, iv2 - 1, iv3 - 1));
            }
            default: {
                break;
            }
        }
    }
    infile.close();

    centerCoord /= vertices.size();
    for (auto &vertex : vertices) {
        vertex -= centerCoord;
    }
    auto material = mat_ptr;
    miny = 500;
    for (const auto &tri : trianglePoints) {
        const int indexv1 = get<0>(tri);
        const int indexv2 = get<1>(tri);
        const int indexv3 = get<2>(tri);
        auto triangle = new Triangle(vertices[indexv1], vertices[indexv2], vertices[indexv3], material);
        triangle->Scale(scale);
        miny = min(miny, min(min(triangle->A.y(), triangle->B.y()), triangle->C.y()));
        triangles.emplace_back(triangle);
    }

    for(auto i : triangles) {
        i->Translate(tran + Vec3(0, -miny, 0));
    }
}



