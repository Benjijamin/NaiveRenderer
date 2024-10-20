#include <mesh.h>
#include <iostream>

Mesh::Mesh() {}
Mesh::Mesh(const Mesh& other) : SceneObject(other), indexedVerts(other.indexedVerts), indexedNormals(other.indexedNormals), indexedUvs(other.indexedUvs),
    vertIndices(other.vertIndices), normalIndices(other.normalIndices), uvIndices(other.uvIndices), 
    verts(other.verts), normals(other.normals), uvs(other.uvs) {}

std::string Mesh::info()
{
    return "t " + std::to_string(transform[3][0]) + " " + std::to_string(transform[3][1]) + " " + std::to_string(transform[3][2]) + "\n"
    + "iv " + std::to_string(indexedVerts.size()) + " in " + std::to_string(indexedNormals.size()) + " iu " + std::to_string(indexedUvs.size());
}

void Mesh::toTris(std::vector<Tri> &tris)
{
    std::vector<Vec3f> wsVerts = indexedVerts;

    for (size_t i = 0; i < wsVerts.size(); i++)
    {
        Vec3f vertWorldSpace;

        transform.multVecMatrix(wsVerts[i], vertWorldSpace);

        wsVerts[i] = vertWorldSpace;
    }

    //TODO: WS NORMALS

    for (size_t i = 0; i < indexedVerts.size(); i+=3)
    {
        Tri tri;
        tri[0].position = wsVerts[i + 0];
        tri[0].normal = indexedNormals[i + 0];
        tri[0].texCoord = indexedUvs[i + 0];
        
        tri[1].position = wsVerts[i + 1];
        tri[1].normal = indexedNormals[i + 1];
        tri[1].texCoord = indexedUvs[i + 1];
        
        tri[2].position = wsVerts[i + 2];
        tri[2].normal = indexedNormals[i + 2];
        tri[2].texCoord = indexedUvs[i + 2];

        tris.push_back(tri);
    }
}

void Mesh::clear()
{
    verts.clear();
    vertIndices.clear();
    uvs.clear();
    uvIndices.clear();
    normals.clear();
    normalIndices.clear();
}