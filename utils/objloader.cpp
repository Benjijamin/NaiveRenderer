#include <objloader.h>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <iostream>

void loadOBJ(Mesh &mesh, const char* path)
{
    mesh.clear();

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

            mesh.vertIndices.push_back(vertIndex[0]);
            mesh.vertIndices.push_back(vertIndex[1]);
            mesh.vertIndices.push_back(vertIndex[2]);
            mesh.uvIndices.push_back(uvIndex[0]);
            mesh.uvIndices.push_back(uvIndex[1]);
            mesh.uvIndices.push_back(uvIndex[2]);
            mesh.normalIndices.push_back(normalIndex[0]);
            mesh.normalIndices.push_back(normalIndex[1]);
            mesh.normalIndices.push_back(normalIndex[2]);
        }
    }

    for (size_t i = 0; i < mesh.vertIndices.size(); i++)
    {
        mesh.vertIndices[i]--;
        Vec3f vert = temp_verts[mesh.vertIndices[i]];
        mesh.indexedVerts.push_back(vert);
    }
    
    for (size_t i = 0; i < mesh.uvIndices.size(); i++)
    {
        mesh.uvIndices[i]--;
        Vec2f uv = temp_uvs[mesh.uvIndices[i]];
        mesh.indexedUvs.push_back(uv);
    }

    for (size_t i = 0; i < mesh.normalIndices.size(); i++)
    {
        mesh.normalIndices[i]--;
        Vec3f normal = temp_normals[mesh.normalIndices[i]];
        mesh.indexedNormals.push_back(normal);
    }
}
