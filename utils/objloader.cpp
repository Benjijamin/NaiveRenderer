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
            break;
        }

        if(strcmp(header, "v") == 0)
        {
            Vec3f vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_verts.push_back(vertex);

            std::cout << "vertex " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
        }
        else if(strcmp(header, "vt") == 0)
        {
            Vec2f uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
            
            std::cout << "uv " << uv.x << " " << uv.y << std::endl;
        }
        else if(strcmp(header, "vn") == 0)
        {
            Vec3f normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
            
            std::cout << "normal " << normal.x << " " << normal.y << " " << normal.z << std::endl;
        }
        else if(strcmp(header, "f"))
        {
            uint32_t vertIndex[3], uvIndex[3], normalIndex[3];
            int match = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                vertIndex[0], uvIndex[0], normalIndex[0],
                vertIndex[1], uvIndex[1], normalIndex[1],
                vertIndex[2], uvIndex[2], normalIndex[2]);

            std::cout << "face " 
                << vertIndex[0] << "/" << uvIndex[0] << "/" << normalIndex[0] << " "
                << vertIndex[1] << "/" << uvIndex[1] << "/" << normalIndex[1] << " "
                << vertIndex[2] << "/" << uvIndex[2] << "/" << normalIndex[2] << std::endl;

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