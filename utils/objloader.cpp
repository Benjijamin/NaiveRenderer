#include <objloader.h>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <iostream>

void OBJModel::loadOBJ(const char* path)
{
    verts.clear();
    vertIndices.clear();
    uvs.clear();
    uvIndices.clear();
    normals.clear();
    normalIndices.clear();

    std::vector<Vec3f> temp_verts;
    std::vector<Vec2f> temp_uvs;
    std::vector<Vec3f> temp_normals;

    std::cout << "opening " << path << std::endl;

    FILE* file = fopen(path, "r");

    if(file == NULL)
    {
        std::cout << "failed to open file" << std::endl;
        exit(0);
    }

    while(true)
    {
        char header[256];

        int res = fscanf(file, "%s", header);

        if(res == EOF)
        {
            fclose(file);
            break;
        }

        if(strcmp(header, "v") == 0)
        {
            Vec3f vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_verts.push_back(vertex);
        }
        else if(strcmp(header, "vt") == 0)
        {
            Vec2f uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if(strcmp(header, "vn") == 0)
        {
            Vec3f normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if(strcmp(header, "f") == 0)
        {
            uint32_t vertIndex[3] = {100, 100 ,100}, uvIndex[3] = {100, 100 ,100}, normalIndex[3] = {100, 100 ,100};
            int match = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                &vertIndex[0], &uvIndex[0], &normalIndex[0],
                &vertIndex[1], &uvIndex[1], &normalIndex[1],
                &vertIndex[2], &uvIndex[2], &normalIndex[2]);

            if(match != 9)
            {
                std::cout << "OBJ must have only vertex, uv and normal attributes" << std::endl;
                exit(0);
            }

            vertIndices.push_back(vertIndex[0]);
            vertIndices.push_back(vertIndex[1]);
            vertIndices.push_back(vertIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    for (size_t i = 0; i < vertIndices.size(); i++)
    {
        vertIndices[i]--;
        Vec3f vert = temp_verts[vertIndices[i]];
        indexedVerts.push_back(vert);
    }
    
    for (size_t i = 0; i < uvIndices.size(); i++)
    {
        uvIndices[i]--;
        Vec2f uv = temp_uvs[uvIndices[i]];
        indexedUvs.push_back(uv);
    }

    for (size_t i = 0; i < normalIndices.size(); i++)
    {
        normalIndices[i]--;
        Vec3f normal = temp_normals[normalIndices[i]];
        indexedNormals.push_back(normal);
    }
}

std::vector<Tri> OBJModel::toTris()
{
    std::vector<Tri> tris;
    for (size_t i = 0; i < indexedVerts.size(); i+=3)
    {
        Tri tri;
        tri[0].position = indexedVerts[i + 0];
        tri[0].normal = indexedNormals[i + 0];
        tri[0].texCoord = indexedUvs[i + 0];
        
        tri[1].position = indexedVerts[i + 1];
        tri[1].normal = indexedNormals[i + 1];
        tri[1].texCoord = indexedUvs[i + 1];
        
        tri[2].position = indexedVerts[i + 2];
        tri[2].normal = indexedNormals[i + 2];
        tri[2].texCoord = indexedUvs[i + 2];

        tris.push_back(tri);
    }

    return tris;
}