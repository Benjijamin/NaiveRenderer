#include <tri.h>
#include <iostream>

Tri::Tri() {}
Tri::Tri(Vertex v1, Vertex v2, Vertex v3)
{
    vertex[0] = v1;
    vertex[1] = v2;
    vertex[2] = v3;
}

const Vertex Tri::operator [] (int i) const { return vertex[i]; }
Vertex& Tri::operator [] (int i) { return vertex[i]; } 

bool Tri::isPointInTri(const Vec2f &p) const
{
    float e1 = edge(p, vertex[1].position.xy(), vertex[2].position.xy());
    float e2 = edge(p, vertex[2].position.xy(), vertex[0].position.xy());
    float e3 = edge(p, vertex[0].position.xy(), vertex[1].position.xy());

    bool neg = (e1 < 0) || (e2 < 0) || (e3 < 0);
    bool pos = (e1 > 0) || (e2 > 0) || (e3 > 0);

    return !( neg && pos );
}

float edge(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3)
{
    return (p3.x - p1.x) * (p2.y - p1.y) - (p3.y - p1.y) * (p2.x - p1.x);
}

bool isPointInTri(const Vec2f &p, const Vec2f &v1, const Vec2f &v2, const Vec2f &v3)
{
    float e1 = edge(p, v2, v3);
    float e2 = edge(p, v3, v1);
    float e3 = edge(p, v1, v2);

    bool neg = (e1 < 0) || (e2 < 0) || (e3 < 0);
    bool pos = (e1 > 0) || (e2 > 0) || (e3 > 0);

    return !( neg && pos );
}

Vec3f barycentricPoint(const Vec2f &p, const Vec2f &v1, const Vec2f &v2, const Vec2f &v3)
{
    float e1 = edge(p, v2, v3);
    float e2 = edge(p, v3, v1);
    float e3 = edge(p, v1, v2);

    float area = edge(v1,v2,v3);
    float w1 = e1 / area;
    float w2 = e2 / area;
    float w3 = e3 / area;

    return Vec3f(w1,w2,w3);
}