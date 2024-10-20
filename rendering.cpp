#include <cmath>
#include <vec3.h>
#include <camera.cpp>
#include <tri.h>
#include <ppm.h>
#include <objloader.h>
#include <memory>

void sceneSetup(Camera &cam, std::vector<Mesh> &meshes)
{
    cam.translate(0, 0, -10);

    Mesh& cube = meshes.emplace_back();
    loadOBJ(cube, "models/cube.obj");

    cube.translate(0,0,-1);
}

void renderScene(const int WIDTH, const int HEIGHT)
{
    Camera cam(WIDTH, HEIGHT);
    std::vector<Mesh> meshes;

    sceneSetup(cam, meshes);

    Vec3i *imageBuffer = new Vec3i[WIDTH * HEIGHT];
    float *depthBuffer = new float[WIDTH * HEIGHT];

    for(int j = 0; j < HEIGHT; j++)
    {
        for(int i = 0; i < WIDTH; i++)
        {
            depthBuffer[j * WIDTH + i] = INFINITY;
        }
    }

    std::vector<Tri> tris;
    for(Mesh mesh : meshes)
    {
        mesh.toTris(tris);
    }

    for(Tri tri : tris)
    {
        Vec2f bbmin = INFINITY, bbmax = -INFINITY;
        Vec3f vProj[3];

        //Tri bounding box
        for(int i = 0; i < 3; i++)
        {
            vProj[i] = cam.worldToScreen(tri[i].position);

            if(vProj[i].x < bbmin.x) { bbmin.x = vProj[i].x; }
            if(vProj[i].y < bbmin.y) { bbmin.y = vProj[i].y; }
            if(vProj[i].x > bbmax.x) { bbmax.x = vProj[i].x; }
            if(vProj[i].y > bbmax.y) { bbmax.y = vProj[i].y; }

            vProj[i].z = 1 / vProj[i].z;
        }

        int xmin = std::max(0, std::min(WIDTH - 1, (int)bbmin.x));
        int ymin = std::max(0, std::min(HEIGHT - 1, (int)bbmin.y));
        int xmax = std::max(0, std::min(WIDTH - 1, (int)bbmax.x));
        int ymax = std::max(0, std::min(HEIGHT - 1, (int)bbmax.y));

        for(int j = ymin; j <= ymax; j++)
        {
            for(int i = xmin; i <= xmax; i++)
            {
                if(isPointInTri(Vec2f(i,j), vProj[0].xy(), vProj[1].xy(), vProj[2].xy()))
                {
                    Vec3f w = barycentricPoint(Vec2f(i,j), vProj[0].xy(), vProj[1].xy(), vProj[2].xy());

                    float z = 1 / (w.x * vProj[0].z + w.y * vProj[1].z + w.z * vProj[2].z);

                    if(z < depthBuffer[j * WIDTH + i])
                    {
                        Vec3f cameraSpaceCoord = Vec3f(w.x * vProj[0].x + w.y * vProj[1].x + w.z * vProj[2].x,
                                                       w.x * vProj[0].y + w.y * vProj[1].y + w.z * vProj[2].y,
                                                       w.x * vProj[0].z + w.y * vProj[1].z + w.z * vProj[2].z);

                        depthBuffer[j * WIDTH + i] = z;
                        imageBuffer[j * WIDTH + i] = Vec3i(cameraSpaceCoord.x * 255, cameraSpaceCoord.y * 255, cameraSpaceCoord.z * 255);
                    }
                }
            }
        }
    }

    //print final image
    PpmWriter printer = PpmWriter(WIDTH, HEIGHT);
    printer.print(imageBuffer);
    printf("image printed to output.ppm\n");
}