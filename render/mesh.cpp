#include <mesh.h>
#include <iostream>

Mesh::Mesh() {}

std::string Mesh::info()
{
    return "t " + std::to_string(transform[3][0]) + " " + std::to_string(transform[3][1]) + " " + std::to_string(transform[3][2]) + "\n"
    + "iv " + std::to_string(indexedVerts.size()) + " in " + std::to_string(indexedNormals.size()) + " iu " + std::to_string(indexedUvs.size());
}

std::string Mesh::deepInfo()
{
    std::string s = info() + "\n";
    s += "indexed Verts : \n"; 
    for (size_t i = 0; i < indexedVerts.size(); i++)
    {
        s += "Vec3: " + std::to_string(indexedVerts[i].x)
            + " " + std::to_string(indexedVerts[i].y)
            + " " + std::to_string(indexedVerts[i].z) + "\n";
    }
    
    s += "indexed Normals : \n"; 
    for (size_t i = 0; i < indexedNormals.size(); i++)
    {
        s += "Vec3: " + std::to_string(indexedNormals[i].x)
            + " " + std::to_string(indexedNormals[i].y)
            + " " + std::to_string(indexedNormals[i].z) + "\n";
    }
    
    s += "indexed Uvs : \n"; 
    for (size_t i = 0; i < indexedUvs.size(); i++)
    {
        s += "Vec2: " + std::to_string(indexedUvs[i].x)
            + " " + std::to_string(indexedUvs[i].y) + "\n";
    }

    s += "end of mesh";
    
    return s;
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
    indexedVerts.clear();
    vertIndices.clear();
    indexedUvs.clear();
    uvIndices.clear();
    indexedNormals.clear();
    normalIndices.clear();
}