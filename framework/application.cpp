#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h"
#include "camera.h"
#include "entity.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);
    this->zBuffer.Resize(w, h);
}

Application::~Application()
{
}

Mesh quad;
Shader *shader;
Texture *texture;

float fov = 45;
float near_plane = 0.01;
float far_plane = 100;
bool nearplane = false; //true for near, false for far
bool perspective = true; // true for perspective, false for ortographic
float option;
//Drawing formulas
bool Ex1 = false;
bool _a = false;
bool _b = false;
bool _c = false;
bool _d = false;
bool _e = false;
bool _f = false;
//Simple image filters
bool Ex2 = false;
//Image transformations
bool Ex3 = false;
//Render 3D mesh using GPU
bool Ex4 = false;



void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
    
    quad.CreateQuad();
    shader = Shader::Get("shaders/quad.vs", "shaders/quad.fs");
    texture = Texture::Get("images/fruits.png");
    
    
    
}

bool case1 = false;
bool case2 = false;


// Render one frame
void Application::Render(void)
{
    shader->Enable();
    //glEnable(GL_DEPTH);
    
    if (Ex1) {
        if (_a) option = 1.1;
        else if (_b) option = 1.2;
        else if (_c) option = 1.3;
        else if (_d) option = 1.4;
        else if (_e) option = 1.5;
        else if (_f) option = 1.6;
    } else if (Ex2) {
        if (_a) option = 2.1;
        else if (_b) option = 2.2;
        else if (_c) option = 2.3;
        else if (_d) option = 2.4;
        else if (_e) option = 2.5;
        else if (_f) option = 2.6;
    } else if (Ex3) {
        if (_a) option = 3.1;
        else if (_b) option = 3.2;
        
    } else if (Ex4) {
        
    }
    
    
    shader->SetFloat("u_option", option); //Setting the option variable as the u_option variable for the shader
    shader->SetFloat("u_time", time); //Assign value of time
    shader->SetTexture("u_texture", texture); // I will assign a texture to the given image to be able to be used in the shaders
    shader->SetUniform2("u_aspect", float(this->window_width), float(this->window_height)); //assigns aspect ratio by taking into account the width and height
    quad.Render();
    //glDisable(GL_DEPTH);
    shader->Disable();
}

// Called after render
void Application::Update(float seconds_elapsed)
{
//    anna.Render(&framebuffer, camera, Color::RED, &zBuffer, texture_anna);
//    if (case2) {
//        this->anna.Update(seconds_elapsed, 1);
//        this->lee.Update(seconds_elapsed, 2);
//        this->cleo.Update(seconds_elapsed, 3);
//    }
//    
//    camera->UpdateViewMatrix();
//    camera->UpdateProjectionMatrix();
    
    
}

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
    
    if (event.button == SDL_BUTTON_LEFT) { // Should be button right
        
    }
}



//keyboard press event
void Application::OnKeyPressed( SDL_KeyboardEvent event )
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
    switch(event.keysym.sym) {
        case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
        case SDLK_1:
            Ex1 = true; Ex2 = false; Ex3 = false; Ex4 = false;
            break;
        case SDLK_2:
            Ex1 = false; Ex2 = true; Ex3 = false; Ex4 = false;
            break;
        case SDLK_3:
            Ex1 = false; Ex2 = false; Ex3 = true; Ex4 = false;
            break;
        case SDLK_4:
            Ex1 = false; Ex2 = false; Ex3 = false; Ex4 = true;
            break;
        case SDLK_a: 
            _a = true; _b = false; _c = false; _d = false; _e = false; _f = false;
            break;
        case SDLK_b:
            _a = false; _b = true; _c = false; _d = false; _e = false; _f = false;
            break;
        case SDLK_c:
            _a = false; _b = false; _c = true; _d = false; _e = false; _f = false;
            break;
        case SDLK_d:
            _a = false; _b = false; _c = false; _d = true; _e = false; _f = false;
            break;
        case SDLK_e:
            _a = false; _b = false; _c = false; _d = false; _e = true; _f = false;
            break;
        case SDLK_f:
            _a = false; _b = false; _c = false; _d = false; _e = false; _f = true;
            break;
        case SDLK_o:
            if (perspective) perspective = false; //Set ortographic
            //framebuffer.Fill(Color::BLACK);
            //camera->SetOrthographic(-0.5, 0.7, 0.6, -0.2, near_plane, far_plane); //Set orthographic type
            camera->type = Camera::ORTHOGRAPHIC;
            //entity.Render(&framebuffer, camera, Color::PURPLE);
            //entity2.Render(&framebuffer, camera, Color::PURPLE);
            //entity3.Render(&framebuffer, camera, Color::PURPLE);
            printf("Set Ortographic camera mode");
            break;
        case SDLK_p:
            if (!perspective) perspective = true;
            //framebuffer.Fill(Color::BLACK);
            //camera->SetPerspective(fov, float(framebuffer.width) / framebuffer.height, near_plane, far_plane); //Set perspective type
            camera->type = Camera::PERSPECTIVE;
            //entity.Render(&framebuffer, camera, Color::YELLOW);
            //entity2.Render(&framebuffer, camera, Color::YELLOW);
            //entity3.Render(&framebuffer, camera, Color::YELLOW);
            printf("Set Perspective camera mode");
            break;
        case SDLK_n:
            if (!nearplane) nearplane = true; // set nearplane
            printf("Set current property to camera near");
            break;
//        case SDLK_f:
//            if (nearplane) nearplane = false; // set farplane
//            printf("Set current property to camera far");
//            break;
        case SDLK_PLUS: //Should be SDLK_PLUS
            if (perspective){ //Perspective
                if (nearplane) near_plane += .1; else if (!nearplane) far_plane += 5;
                camera->SetPerspective(fov, float(framebuffer.width) / framebuffer.height, near_plane, far_plane);
            }
            
            else if (!perspective) { //Orthographic
                if (nearplane) near_plane += .1; else if (!nearplane) far_plane += 5;
                camera->SetOrthographic(0.5, 0.2, 0.7, 0.3, near_plane, far_plane);
            }
            
            printf("Increase CURRENT PROPERTY");
            break;
        case SDLK_MINUS:
            if (perspective){
                if (nearplane) near_plane -= .1; else if (!nearplane) far_plane -= 5;
                camera->SetPerspective(fov, float(framebuffer.width) / framebuffer.height, near_plane, far_plane);
            }
            
            else if (!perspective) {
                if (nearplane) near_plane -= .1; else if (!nearplane) far_plane -= 5;
                camera->SetOrthographic(0.5, 0.2, 0.7, 0.3, near_plane, far_plane);
            }
            printf("Decrease CURRENT PROPERTY");
            break;
            
            // COLOR - TRIANGLES 3.1
            // TRIANGLES-INTERPOLATED - 3.2
            // OCCLUSIONS - Z-BUFFER, 3.3
            // TEXTURES - 3.4
//        case SDLK_c:
//            printf("Toggle (activate/deactivate) between PLAIN COLOR/INTERPOLATED vertex colors");
//            //Could do with all 3 Entities
//            if (anna.mode == Entity::eRenderMode::COLOR) anna.mode = Entity::eRenderMode::TRIANGLES_INTERPOLATED;
//            else anna.mode = Entity::eRenderMode::COLOR;
//            break;
        case SDLK_z:
            printf("Toggle between OCCLUSIONS and NO OCCLUSIONS");
            if (anna.mode == Entity::eRenderMode::OCCLUSIONS) anna.mode = Entity::eRenderMode::TRIANGLES_INTERPOLATED;
            else anna.mode = Entity::eRenderMode::OCCLUSIONS;
            break;
        case SDLK_t:
            printf("Toggle between USE MESH TEXTURE and USE PLAIN COLOR colors");
            if (anna.mode == Entity::eRenderMode::TEXTURES) anna.mode = Entity::eRenderMode::COLOR;
            else anna.mode = Entity::eRenderMode::TEXTURES;
            break;
    }
}



void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
        
	}
}

float xMouse;
float yMouse;

void Application::OnMouseMove(SDL_MouseButtonEvent event) {
    if (event.button == SDL_BUTTON_LEFT) { //Eye (camera orbit)
        camera->Orbit(-mouse_delta.x * 0.01, Vector3::UP);
        camera->Orbit(-mouse_delta.y * 0.01, Vector3::RIGHT);
//        xMouse = event.x;
//        xMouse = xMouse / framebuffer.width; //We normalize the x
//        yMouse = event.y;
//        yMouse = yMouse / framebuffer.height; //We normalize the y
//        camera->eye.Set(xMouse, yMouse, 1); //Set where is the camera
//        camera->UpdateViewMatrix(); //And update the matrix
    }
    if (event.button == SDL_BUTTON_RIGHT) { //Center
        xMouse = event.x;
        xMouse = xMouse / framebuffer.width; //We normalize the x
        yMouse = event.y;
        yMouse = yMouse / framebuffer.height; //We normalize the y
        camera->center.Set(xMouse, yMouse, 0);
        camera->UpdateViewMatrix(); //And update the matrix
    }
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;
    camera->Zoom(dy < 0 ? 1.1 : 0.9);
	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}
