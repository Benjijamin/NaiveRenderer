#include <ppm.h>
#include <sstream>

void PpmWriter::print(const Vec3i *imageBuffer) const
{
    std::ofstream file;
    file.open("output.ppm");

    file << "P3\n" << w << ' ' << h << "\n255\n";

    for (int j = 0; j < h; j++)
    {
        for(int i = 0; i < w; i++)
        {
            file << imageBuffer[j * w + i].x << 
            ' ' << imageBuffer[j * w + i].y << 
            ' ' << imageBuffer[j * w + i].z << '\n';
        }
    }

    file.close();
}

void readPpm(const std::string &fileName, std::vector<unsigned char> &imageBuffer, int &width, int &height)
{
    std::ifstream file(fileName);

    if(!file)
    {
        std::cerr << "cannot open file" << std::endl;
        exit(0);
    }

    std::string l;

    std::getline(file, l);
    if(l != "P3")
    {
        std::cerr << "file is not a p3" << std::endl;
        exit(0);
    }

    std::getline(file, l);
    std::istringstream resolution(l);
    resolution >> width >> height;

    std::getline(file, l);
    int maxColor;
    std::istringstream maxC(l);
    maxC >> maxColor;

    if(maxColor != 255)
    {
        std::cerr << "max color is not 255" << std::endl;
        exit(0);
    }

    imageBuffer.reserve(width * height * 3);

    int r,g,b;
    for(int i = 0; i < width * height; i++)
    {
        file >> r >> g >> b;

        imageBuffer[i * 3] = static_cast<unsigned char>(r);
        imageBuffer[i * 3 + 1] = static_cast<unsigned char>(g);
        imageBuffer[i * 3 + 2] = static_cast<unsigned char>(b);
    }
}