#include <sceneObject.h>
#include <math.h>

SceneObject::SceneObject() {}
SceneObject::SceneObject(const SceneObject &other) : transform(other.transform) {}

void SceneObject::translate(float x, float y, float z)
{
    transform[3][0] += x;
    transform[3][1] += y;
    transform[3][2] += z;
}

void SceneObject::setScale(float x, float y, float z)
{
    transform[0][0] = x;
    transform[1][1] = y;
    transform[2][2] = z;
}

void SceneObject::rotate(float xDeg, float yDeg, float zDeg)
{
    float xRad = xDeg * M_PI / 180;
    float yRad = yDeg * M_PI / 180;
    float zRad = zDeg * M_PI / 180;

    float cosX = cos(xRad);
    float sinX = sin(xRad);
    float cosY = cos(yRad);
    float sinY = sin(yRad);
    float cosZ = cos(zRad);
    float sinZ = sin(zRad);

    //Not too sure what convoluted wizardry is going on here, thank you wikipedia

    std::cout << "rotating object" 
        << " x: " << xDeg << "(" << xRad << " rad)"
        << " y: " << yDeg << "(" << yRad << " rad)"
        << " z: " << zDeg << "(" << zRad << " rad)" << std::endl;

    Matrix4f rotX;
    rotX[0][0] = 1;     rotX[0][1] = 0;     rotX[0][2] = 0;     rotX[0][3] = 0;
    rotX[1][0] = 0;     rotX[1][1] = cosX;  rotX[1][2] = -sinX; rotX[1][3] = 0;
    rotX[2][0] = 0;     rotX[2][1] = sinX;  rotX[2][2] = cosX;  rotX[2][3] = 0;
    rotX[3][0] = 0;     rotX[3][1] = 0;     rotX[3][2] = 0;     rotX[3][3] = 1;

    Matrix4f rotY;
    rotY[0][0] = cosY;  rotY[0][1] = 0;     rotY[0][2] = sinY;  rotY[0][3] = 0;
    rotY[1][0] = 0;     rotY[1][1] = 1;     rotY[1][2] = 0;     rotY[1][3] = 0;
    rotY[2][0] = -sinY; rotY[2][1] = 0;     rotY[2][2] = cosY;  rotY[2][3] = 0;
    rotY[3][0] = 0;     rotY[3][1] = 0;     rotY[3][2] = 0;     rotY[3][3] = 1;

    Matrix4f rotZ;
    rotZ[0][0] = cosZ;  rotZ[0][1] = -sinZ; rotZ[0][2] = 0;     rotZ[0][3] = 0;
    rotZ[1][0] = sinZ;  rotZ[1][1] = cosZ;  rotZ[1][2] = 0;     rotZ[1][3] = 0;
    rotZ[2][0] = 0;     rotZ[2][1] = 0;     rotZ[2][2] = 1;     rotZ[2][3] = 0;
    rotZ[3][0] = 0;     rotZ[3][1] = 0;     rotZ[3][2] = 0;     rotZ[3][3] = 1;

    Matrix4f rotation = rotX * rotY * rotZ;

    std::cout << "rotation " << std::endl;

    std::cout << "before transform " << transform << std::endl;

    transform = transform * rotation; 

    std::cout << "after transform " << transform << std::endl;
}