#pragma once
#include "mesh.h"
#include "camera.h"
#include "image.h"


class Entity {
private:
    
public:
    Mesh mesh;
    Matrix44 modelMat;
    
    //Constructors
    Entity(Mesh mesh, Matrix44 model);
    //Entity(Mesh mesh);
    Entity();
    Entity(Mesh* mesh, Vector3 translation, Vector3 rotational, Vector3 scale, float angle);
    
    enum class eRenderMode {
        COLOR,
        TEXTURES,
        OCCLUSIONS,
        TRIANGLES_INTERPOLATED
    };
    
    eRenderMode mode;

    void Render(Image* framebuffer, Camera* camera, const Color& c, FloatImage* zBuffer, Image* texture);
    void Update(float seconds_elapsed, int option);
    
};
