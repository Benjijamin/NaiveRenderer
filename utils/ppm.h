#ifndef PPM_H
#define PPM_H

#include <iostream>
#include <fstream>
#include <vector>
#include <vec3.h>

class PpmWriter
{
    public:
        PpmWriter(int width, int height) : w(width), h(height){}
        int w,h;

        void print(const Vec3i *imageBuffer) const;
};

void readPpm(const std::string &fileName, std::vector<unsigned char> &imageBuffer, int &width, int &height);

#endif