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
}

Application::~Application()
{
}

void Application::Init(void)
{
	std::cout << "Initiating app..." << std::endl;
    
    float fov = 45;
    float near_plane = 0.01;
    float far_plane = 100;
    
    camera = new Camera();
    camera->LookAt(Vector3(0,0,1), Vector3(0,0,0), Vector3::UP);

    
    
    //Loading Anna
    entity.mesh.LoadOBJ("meshes/anna.obj");
    

    //Loading Lee
    entity2.mesh.LoadOBJ("meshes/lee.obj");
    entity2.modelMat.Translate(0, -0.3, 0); //Translate matrix
    
    
    //model.Translate(20, 0, 0); //Translate matrix
    
    if (entity3.mesh.LoadOBJ("meshes/cleo.obj")) {
         //We load cleo's mesh
    } else printf("Error loading Cleo");

    //model.SetIdentity(); //We set the identity matrix
    //model.Translate(0.3, -0.3, 0); //Translate matrix

    //Now we set how the camera looks
    camera->SetPerspective(fov, float(framebuffer.width) / framebuffer.height, near_plane, far_plane);
    camera->eye.Set(0, 0, 1);// Where is the camera
    camera->center.Set(0, 0, 0); // Where is it pointing
    camera->up.Set(0, 1, 0); // The up pointing up
    camera->UpdateViewMatrix();
    
}

bool case1 = false;
bool case2 = false;


bool nearplane = false; //1 for near, 2 for far

float near_plane;
float far_plane;



// Render one frame
void Application::Render(void)
{
	// ...
    // Testing different functions
    framebuffer.DrawBlack(0, 0, framebuffer.width, framebuffer.height);
    if (case1) entity.Render(&framebuffer, camera, Color::CYAN);
    if (case2) {
        entity.Render(&framebuffer, camera, Color::CYAN);
        entity2.Render(&framebuffer, camera, Color::YELLOW);
        entity3.Render(&framebuffer, camera, Color::RED);
    }
    
    
    
    
    
    
    
    
    // Send the framebuffer to the screen
	framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed)
{
    if (case2) {
        this->entity.Update(seconds_elapsed, 1);
        this->entity2.Update(seconds_elapsed, 2);
        this->entity3.Update(seconds_elapsed, 3);
    }
    
}

//int pointcount = 0;
//Vector2 points[3];
//
//Vector2 center;
//float radius;
//
//bool fillShapes = false;
//
//Color color;
//
//bool paint = false;
//
//bool eraser = false;
//
//Vector2 final_point;

void Application::OnMouseButtonDown( SDL_MouseButtonEvent event )
{
    if (event.button == SDL_BUTTON_LEFT) {
        
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
            printf("Set Ortographic camera mode");
            //camera->SetOrthographic(<#float left#>, <#float right#>, <#float top#>, <#float bottom#>, <#float near_plane#>, <#float far_plane#>);
            break;
        case SDLK_p:
            printf("Set Perspective camera mode");
            //camera->SetPerspective(<#float fov#>, <#float aspect#>, <#float near_plane#>, <#float far_plane#>);
            break;
        case SDLK_n:
            if (!nearplane) nearplane = true; else nearplane = false;
            printf("Set current property to camera near");
        case SDLK_f:
            if (nearplane) nearplane = false; else nearplane = true;
            printf("Set current property to camera far");
        case SDLK_g: //Should be SDLK_PLUS
            if (nearplane) near_plane += 0.01; else far_plane += 1;
            printf("Increase CURRENT PROPERTY");
            break;
        case SDLK_MINUS:
            if (nearplane) near_plane -= 0.01; else far_plane -= 1;
            printf("Decrease CURRENT PROPERTY");
            break;
    }
}



void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
        
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event) {
    if (event.button == SDL_BUTTON_LEFT) {
        
    }
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}
