#include "entity.h"
#include "camera.h"
#include "image.h"

Entity::Entity(){
//    this->mesh = new Mesh;
    this->modelMat = Matrix44();
}

Entity::Entity(Mesh* mesh, Vector3 translation, Vector3 rotational, Vector3 scale, float angle){
//    this->mesh = mesh;
//    model_matrix
}

Entity::Entity(Mesh mesh, Matrix44 model) {
//    this->mesh = new Mesh;
    this->modelMat = Matrix44();
}


Vector3 coord;
//Defining negZ as false
bool negZ = false;
// Storing x,y coordinates of the 3 vertices of the triangle
Vector2 triangle[3];
float x, y;



void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
    //Get vertices
    std::vector<Vector3> vertices = this->mesh.GetVertices();
    
    for (int row = 0; row < vertices.size(); row += 3) { //Iterating to get 3 points for each vertex
        for (int i = 0; i < 3 && !negZ; i++) { //With this for loop we will store the three coordinates of each line of the mesh file
            coord = vertices[row + i]; //We save the coordinate vector xyz
            coord = this->modelMat * coord; //We multiply the model matrix with our 3D coordinate system so as to go from Local space to work with the world space
            coord = camera->ProjectVector(coord, negZ); //World to View space transformation
            //Clip to Screen transformation
            x = (coord.x + 1) * framebuffer->width / 2.0;
            y = (coord.y + 1) * framebuffer->height / 2.0;
            triangle[i].set(x, y); //Since at this point we are working in 2D we will store x,y coordinates in our previously created 2D vector
        }

        //Now as long as our coordinates z is not negative we will draw a line between each point so as to form the triangle
        if (!negZ) {
            framebuffer->DrawLineDDA(triangle[0].x, triangle[0].y, triangle[1].x, triangle[1].y, c); //From 0 to 1
            framebuffer->DrawLineDDA(triangle[0].x, triangle[0].y, triangle[2].x, triangle[2].y, c); //From 0 to 2
            framebuffer->DrawLineDDA(triangle[2].x, triangle[2].y, triangle[1].x, triangle[1].y, c); //From 2 to 1
        }
    }
}


void Entity::Update(float seconds_elapsed) {
    
}
