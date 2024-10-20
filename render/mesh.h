#ifndef MESH_H
#define MESH_H

#include <vector>
#include <vec3.h>
#include <tri.h>
#include <cstdint>
#include <sceneObject.h>

class Mesh : public SceneObject
{
    public:
        Mesh();
        Mesh(const Mesh &other);

        std::vector<Vec3f> indexedVerts;
        std::vector<Vec3f> verts;
        std::vector<uint32_t> vertIndices;
        std::vector<Vec2f> indexedUvs;
        std::vector<Vec2f> uvs;
        std::vector<uint32_t> uvIndices;
        std::vector<Vec3f> indexedNormals;
        std::vector<Vec3f> normals;
        std::vector<uint32_t> normalIndices;

        void clear();
        void toTris(std::vector<Tri> &tris);

        std::string info();
    private:
};

#endif