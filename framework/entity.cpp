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

// Storing x,y coordinates of the 3 vertices of the triangle
Vector2 triangle[3];
float x, y;

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c, FloatImage* zBuffer, Image* texture) {
    //Get vertices and UVs
    const std::vector<Vector3>& vertices = this->mesh.GetVertices();
    const std::vector<Vector2>& uvs = this->mesh.GetUVs();
    // For frustum properties for the triangle
    bool negZ = false;
    
    // Iterating every 3 because we are looking for triangles
    for (int row = 0; row < this->mesh.GetVertices().size(); row += 3) {
        
        //From model space to world space
        Vector4 vertex = Vector4(vertices[row].x, vertices[row].y, vertices[row].z, 1);
        Vector4 vertex_world = this->modelMat * vertex;
        // Using this variable to define know whether we are in the frustum or not
        bool negZ_0;
        //From world space to clip space
        Vector3 vertex_clip = camera->ProjectVector(vertex_world.GetVector3(), negZ_0);
        //Lastly, converting the vertex from clip space to the screen/framebuffer
        Vector3 vertex_screen = Vector3(((vertex_clip.x + 1) / 2) * (framebuffer->width - 1), ((vertex_clip.y + 1) / 2) * (framebuffer->height - 1), vertex_clip.z);
        
        //All the above iteratively for all 3 vertices, no need to comment all of it once again
        Vector4 vertex_1 = Vector4(vertices[row + 1].x, vertices[row + 1].y, vertices[row + 1].z, 1);
        Vector4 vertex_world_1 = this->modelMat * vertex_1;
        bool negZ_1;
        Vector3 vertex_clip_1 = camera->ProjectVector(vertex_world_1.GetVector3(), negZ_1);
        Vector3 vertex_screen_1 = Vector3(((vertex_clip_1.x + 1) / 2) * (framebuffer->width - 1), ((vertex_clip_1.y + 1) / 2) * (framebuffer->height - 1), vertex_clip_1.z);
        
        Vector4 vertex_2 = Vector4(vertices[row + 2].x, vertices[row + 2].y, vertices[row + 2].z, 1);
        Vector4 vertex_world_2 = this->modelMat * vertex_2;
        bool negZ_2;
        Vector3 vertex_clip_2 = camera->ProjectVector(vertex_world_2.GetVector3(), negZ_2);
        Vector3 vertex_screen_2 = Vector3(((vertex_clip_2.x + 1) / 2) * (framebuffer->width - 1), ((vertex_clip_2.y + 1) / 2) * (framebuffer->height - 1), vertex_clip_2.z);
        
        
        // Making sure they are inside the frustum
        if (negZ_0 == false || negZ_1 == false || negZ_2 == false) {
            //Depending on the mode we do one thing or the other by using the rendermode structure given by the document
            if (mode == Entity::eRenderMode::COLOR) {
                for (int i = 0; i < 3 && !negZ; i++) {
                    coord = vertices[row + i]; //We save the coordinate vector xyz
                    coord = this->modelMat * coord; //We multiply the model matrix with our 3D coordinate system so as to go from Local space to world space
                    coord = camera->ProjectVector(coord, negZ); //World to View space transformation
                    //Clip to Screen transformation
                    x = (coord.x + 1) * framebuffer->width / 2.0;
                    y = (coord.y + 1) * framebuffer->height / 2.0;
                    triangle[i].set(x, y); //Since at this point we are working in 2D we will store x,y coordinates in our previously created 2D vector
                    
                    //Now as long as our coordinates z is not negative we will draw a line between each point so as to form the triangle
                    //Had to comment this because if not it was drawing random lines, DrawTriangle function already does the work
//                    if (!negZ) {
//                        framebuffer->DrawLineDDA(triangle[0].x, triangle[0].y, triangle[1].x, triangle[1].y, c); //From 0 to 1
//                        framebuffer->DrawLineDDA(triangle[0].x, triangle[0].y, triangle[2].x, triangle[2].y, c); //From 0 to 2
//                        framebuffer->DrawLineDDA(triangle[2].x, triangle[2].y, triangle[1].x, triangle[1].y, c); //From 2 to 1
//                    }
                }
                framebuffer->DrawTriangle(Vector2(triangle[0].x, triangle[0].y), Vector2(triangle[1].x, triangle[1].y), Vector2(triangle[2].x, triangle[2].y), c, 1, c);
            } else if (mode == Entity::eRenderMode::TRIANGLES_INTERPOLATED) {
                framebuffer->DrawTriangleInterpolated(vertex_screen, vertex_screen_1, vertex_screen_2, Color::RED, Color::GREEN, Color::BLUE);
            } else if (mode == Entity::eRenderMode::OCCLUSIONS) {
                framebuffer->DrawTriangleInterpolated(vertex_screen, vertex_screen_1, vertex_screen_2, Color::RED, Color::GREEN, Color::BLUE, zBuffer);
            } else if (mode == Entity::eRenderMode::TEXTURES) {
                framebuffer->DrawTriangleInterpolated(vertex_screen, vertex_screen_1, vertex_screen_2, Color::RED, Color::GREEN, Color::BLUE, zBuffer, texture, uvs[row], uvs[row+1], uvs[row+2]);
            }
        }
    }
}


void Entity::Update(float seconds_elapsed, int option) {
    if (option == 1) this->modelMat.Rotate(0.1, Vector3(0,1,0));
    if (option == 2) this->modelMat.Translate(0, 0.003, 0);
    if (option == 3) {
        this->modelMat.m[0] += 0.02;
        this->modelMat.m[5] += 0.02;
        this->modelMat.m[10] += 0.02;
    }
}
