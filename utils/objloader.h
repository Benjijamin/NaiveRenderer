#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <vec3.h>
#include <cstdint>

class OBJModel
{
    public:
        std::vector<Vec3f> indexedVerts;
        std::vector<Vec3f> verts;
        std::vector<uint32_t> vertIndices;
        std::vector<Vec2f> indexedUvs;
        std::vector<Vec2f> uvs;
        std::vector<uint32_t> uvIndices;
        std::vector<Vec3f> indexedNormals;
        std::vector<Vec3f> normals;
        std::vector<uint32_t> normalIndices;

        void loadOBJ(const char* path);
    private:
};

#endif