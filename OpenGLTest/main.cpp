#if defined(_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define OVR_OS_WIN32
#elif defined(__APPLE__)
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#define OVR_OS_MAC
#elif defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#define OVR_OS_LINUX
#endif


#include <GL/glew.h>
//#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "OpenGL.h"
#include "Scene.h"
#include "Vertex.h"

// http://www.codeproject.com/Articles/26949/Xbox-Controller-Input-in-C-with-XInput
#include "CXBOXController.h"
#include <iostream>

/*
XINPUT_GAMEPAD_DPAD_UP          0x00000001
XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
XINPUT_GAMEPAD_START            0x00000010
XINPUT_GAMEPAD_BACK             0x00000020
XINPUT_GAMEPAD_LEFT_THUMB       0x00000040
XINPUT_GAMEPAD_RIGHT_THUMB      0x00000080
XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
XINPUT_GAMEPAD_A                0x1000
XINPUT_GAMEPAD_B                0x2000
XINPUT_GAMEPAD_X                0x4000
XINPUT_GAMEPAD_Y                0x8000




typedef struct _XINPUT_GAMEPAD {
WORD wButtons;
BYTE bLeftTrigger;
BYTE bRightTrigger;
SHORT sThumbLX;
SHORT sThumbLY;
SHORT sThumbRX;
SHORT sThumbRY;
} XINPUT_GAMEPAD, *PXINPUT_GAMEPAD;
*/

#define BUFFER_OFFSET(i) ((void*)(i))

using namespace std;
//using namespace OVR;

Debug debug;

OpenGL opengl;
Scene scene;

CXBOXController* Player1;

GLFWwindow * window;

void draw() {

	glClearColor(1.0, 1.0, 0.0, 0.0);
	scene.render_scene(&opengl);
}

void mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height); //sets width and height
		glViewport(0, 0, width, height);

		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

static void error_callback(int error, const char* description){
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_W) {
		scene.camera.position.x -= 1.0;
	}
	if (key == GLFW_KEY_S) {
		scene.camera.position.x += 1.0;
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[]){

	debug.init(debug.VERBOSE);

	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Now setup glfw stuff
	window = glfwCreateWindow(800, 600, "4D VR", NULL, NULL); //glfwGetPrimaryMonitor() for first NULL for full screen
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);

	Player1 = new CXBOXController(1); //setup player controller
	opengl.init(1600, 700); //sets up openGL

	/*GameObject *room = new GameObject(vec3(0,0,0), vec3(0,0,0), vec3(3,3,2));
	Model *room_model = new Model();
	room_model->init_from_obj_file(L"box_blue.obj");
	room->add_game_component((GameComponent *)room_model);
	opengl.init_buffer(room_model->vertexBuffer, room_model->verts, GL_ARRAY_BUFFER);
	opengl.init_buffer(room_model->indiciesBuffer, room_model->indices, GL_ELEMENT_ARRAY_BUFFER);
	opengl.bind_vertex_indices(room_model);
	scene.add_game_object(room);*/

	GameObject *box = new GameObject(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	Model *box_model = new Model();
	box_model->init_from_obj_file(L"box_red.obj");
	box->add_game_component((GameComponent *)box_model);
	opengl.init_buffer(box_model->vertexBuffer, box_model->verts, GL_ARRAY_BUFFER);
	opengl.init_buffer(box_model->indiciesBuffer, box_model->indices, GL_ELEMENT_ARRAY_BUFFER);
	opengl.bind_vertex_indices(box_model);
	scene.add_game_object(box);
	
	mainLoop();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	/*while (true)
	{
		if (Player1->IsConnected())
		{	
			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_B)
			{
				Player1->Vibrate(0, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X)
			{
				Player1->Vibrate(65535, 65535);
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_Y)
			{
				Player1->Vibrate();
			}

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
			{
				break;
			}
		}
		else
		{
			std::cout << "\n\tERROR! PLAYER 1 - XBOX 360 Controller Not Found!\n";
			std::cout << "Press Any Key To Exit.";
			std::cin.get();
			break;
		}
	}*/
}