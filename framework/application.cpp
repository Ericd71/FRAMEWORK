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

float fov = 45;
float near_plane = 0.01;
float far_plane = 100;
bool nearplane = false; //true for near, false for far
bool perspective = true; // true for perspective, false for ortographic

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
    
    camera = new Camera();
    camera->LookAt(Vector3(0,0,1), Vector3(0,0,0), Vector3::UP);
    
    //Loading Anna
    anna.mesh.LoadOBJ("meshes/anna.obj");
    

    //Loading Lee
    lee.mesh.LoadOBJ("meshes/lee.obj");

    
    if (cleo.mesh.LoadOBJ("meshes/cleo.obj")) {
         //We load cleo's mesh
    } else printf("Error loading Cleo");
    
    texture_lee =  new Image();
    
    texture_anna =  new Image();
    
    texture_cleo =  new Image();
    
    bool tex_a = texture_anna->LoadTGA("textures/anna_color_specular.tga",true);
    bool tex_l = texture_lee->LoadTGA("textures/lee_color_specular.tga", true);
    bool tex_c = texture_cleo->LoadTGA("textures/cleo_color_specular.tga", true);



    //Now we set how the camera looks
    camera->SetPerspective(fov, float(framebuffer.width) / framebuffer.height, near_plane, far_plane);
    camera->eye.Set(0, 0, 1);// Where is the camera
    camera->center.Set(0, 0, 0); // Where is it pointing
    camera->up.Set(0, 1, 0); // The up pointing up
    camera->UpdateViewMatrix();
    
}

bool case1 = false;
bool case2 = false;


// Render one frame
void Application::Render(void)
{
	// ...
    // Testing different functions
    framebuffer.DrawBlack(0, 0, framebuffer.width, framebuffer.height);
    zBuffer.Fill(100.0);
    
    //framebuffer.DrawTriangleInterpolated(Vector3(100, 100, 5), Vector3(300, 350, 20), Vector3(630, 300, 10), Color::RED, Color::CYAN, Color::YELLOW);
    if (case1) {
        anna.Render(&framebuffer, camera, Color::RED, &zBuffer, texture_anna);
        //lee.Render(&framebuffer, camera, Color::GREEN, &zBuffer, texture_lee);
        //cleo.Render(&framebuffer, camera, Color::BLUE, &zBuffer, texture_cleo);
    }
    if (case2) {
        anna.Render(&framebuffer, camera, Color::RED, &zBuffer, texture_anna);
        //lee.Render(&framebuffer, camera, Color::GREEN, &zBuffer, texture_lee);
        //cleo.Render(&framebuffer, camera, Color::BLUE, &zBuffer, texture_cleo);
    }
        
    // Send the framebuffer to the screen
	framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    anna.Render(&framebuffer, camera, Color::RED, &zBuffer, texture_anna);
    if (case2) {
        this->anna.Update(seconds_elapsed, 1);
        this->lee.Update(seconds_elapsed, 2);
        this->cleo.Update(seconds_elapsed, 3);
    }
    
    camera->UpdateViewMatrix();
    camera->UpdateProjectionMatrix();
    
    
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
            if (!case1) case1 = true; else case1 = false;
            printf("Draw single entity!");
            break;
        case SDLK_2:
            if (!case2) case2 = true; else case2 = false;
            printf("Draw multiple animated entities!");
            
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
        case SDLK_f:
            if (nearplane) nearplane = false; // set farplane
            printf("Set current property to camera far");
            break;
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
        case SDLK_c:
            printf("Toggle (activate/deactivate) between PLAIN COLOR/INTERPOLATED vertex colors");
            //Could do with all 3 Entities
            if (anna.mode == Entity::eRenderMode::COLOR) anna.mode = Entity::eRenderMode::TRIANGLES_INTERPOLATED;
            else anna.mode = Entity::eRenderMode::COLOR;
            break;
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
