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
    
    
    
    void Render(Image* framebuffer, Camera* camera, const Color& c);
    void Update(float seconds_elapsed);
    
};
