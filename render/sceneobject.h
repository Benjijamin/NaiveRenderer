#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <matrix.h>

class SceneObject
{
    protected:
        Matrix4f transform;

    public:
        SceneObject();
        SceneObject(const SceneObject &other);

        void translate(float x, float y, float z);
        void setScale(float x, float y, float z);
        void rotate(float xRad, float yRad, float zRad);

    private:
};

#endif