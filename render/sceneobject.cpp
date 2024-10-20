#include <sceneObject.h>

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