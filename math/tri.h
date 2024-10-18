#ifndef TRI_H
#define TRI_H

#include <vec2.h>
#include <vec3.h>
#include <structs.h>

class Tri
{
    public:
        Tri();
        Tri(Vertex v1, Vertex v2, Vertex v3);

        bool isPointInTri(const Vec2f &p) const;
        
        const Vertex operator [] (int i) const;
        Vertex& operator [] (int i);

    private:
        Vertex vertex[3];
};

float edge(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3);
bool isPointInTri(const Vec2f &p, const Vec2f &v1, const Vec2f &v2, const Vec2f &v3);
Vec3f barycentricPoint(const Vec2f &p, const Vec2f &v1, const Vec2f &v2, const Vec2f &v3);

#endif