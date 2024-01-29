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
    camera->LookAt(Vector3(0,0,1), Vector3(0,0,0), Vector3(0,1,0));
    camera->SetPerspective(45, framebuffer.width / (float)framebuffer.height, 1.0, 100);
    
    
    //Loading Anna
    mesh.LoadOBJ("meshes/anna.obj");
    
    model.SetIdentity(); //Setting identity matrix
    model.Translate(0, -0.3, 0); //Translate matrix
    //entity.setModelMat(modelMat);
    //entity.setMesh(&mesh);
    
    mesh2.LoadOBJ("meshes/lee.obj");
    
    model.SetIdentity();
    model.Translate(-0.5, -0.3, 0); //Translate matrix
    //entity2.setModelMat(modelMat); //We set the Model Matrix
    //entity2.setMesh(&mesh2); //We set the mesh
    
    if (mesh3.LoadOBJ("meshes/cleo.obj")) {
         //We load cleo's mesh
    } else printf("Error loading Cleo");

    model.SetIdentity(); //We set the identity matrix
    model.Translate(0.3, -0.3, 0); //Translate matrix
    //entity3.setModelMat(modelMat); //We set the Model Matrix
    //entity3.setMesh(&mesh3); //We set the mesh

    //Now we set how the camera looks
    camera->SetPerspective(fov, float(framebuffer.width) / framebuffer.height, near_plane, far_plane);
    camera->eye.Set(0, 0, 1);// Where is the camera
    camera->center.Set(0, 0, 0); // Where is it pointing
    camera->up.Set(0, 1, 0); // The up pointing up
    camera->UpdateViewMatrix();
    
    
}

// Render one frame
void Application::Render(void)
{
	// ...
    // Testing different functions
    entity.Render(&framebuffer, camera, Color::CYAN);
    entity2.Render(&framebuffer, camera, Color::YELLOW);
    entity3.Render(&framebuffer, camera, Color::YELLOW);
    
    
    
    // Send the framebuffer to the screen
	framebuffer.Render();
}

// Called after render
void Application::Update(float seconds_elapsed)
{
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
            printf("Draw single entity!");
            break;
        case SDLK_2:
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
        case SDLK_PLUS:
            printf("Increase CURRENT PROPERTY");
            break;
        case SDLK_MINUS:
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
