#include <cmath>
#include <vec3.h>
#include <camera.cpp>
#include <tri.h>
#include <ppm.h>
#include <objloader.h>

void renderScene(const int WIDTH, const int HEIGHT)
{
    Camera cam(WIDTH, HEIGHT);

    cam.translate(-2, 0, -10);

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

    OBJModel cube;
    cube.loadOBJ("models/cube.obj");
    std::vector<Tri> cubeTris = cube.toTris();

    tris.insert(tris.end(), cubeTris.begin(), cubeTris.end());

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
                        depthBuffer[j * WIDTH + i] = z;
                        imageBuffer[j * WIDTH + i] = Vec3i(w.x * 255, w.y * 255, w.z * 255);
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