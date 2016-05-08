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

#include <OVR_CAPI_GL.h>

#include "OpenGL.h"
#include "Scene.h"

using namespace std;
//using namespace OVR;

Debug debug;

OpenGL opengl;
Scene scene;

ovrHmd HMD;
ovrGraphicsLuid luid;
GLFWwindow * window;
void draw() {

	double           ftiming = ovr_GetPredictedDisplayTime(HMD, 0);

	ovrTrackingState hmdState = ovr_GetTrackingState(HMD, ftiming, ovrTrue);


	glClearColor(1.0, 1.0, 0.0, 0.0);

	scene.render_scene(&opengl);
}

void setupVR() {

	ovrResult result = ovr_Create(&HMD, &luid);
	ovrHmdDesc hmdDesc = ovr_GetHmdDesc(HMD);
	ovrSizei windowSize = { hmdDesc.Resolution.w / 2, hmdDesc.Resolution.h / 2 };
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
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(int argc, char* argv[]){
	//OVR::System::Init();

	ovrResult result = ovr_Initialize(nullptr);
	//VALIDATE(OVR_SUCCESS(result), "Failed to initialize libOVR.");
	if (!OVR_SUCCESS(result)) {
		exit(1);
	}

	debug.init(debug.VERBOSE);

	//glutInit(&argc, argv);
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Now setup glfw stuff
	window = glfwCreateWindow(1000, 1000, "4D VR", NULL, NULL); //glfwGetPrimaryMonitor() for first NULL for full screen
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key_callback);
	opengl.init(1000, 1000); //sets up openGL


	setupVR(); //start up oculus rift and head tracking

	//glutDisplayFunc(draw);
	//glutReshapeFunc(reshape);
	mainLoop();
	//glutMainLoop();

	ovr_Destroy(HMD);
	ovr_Shutdown();
	//OVR::System::Destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

	//return 0;
}