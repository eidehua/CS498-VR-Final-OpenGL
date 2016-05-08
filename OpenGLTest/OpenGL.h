#pragma once
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

#include "load_file.h"

#include "Debug.h"
#include "Camera.h"
#include "Model.h"
#include "Transfrom.h"

#include "Buffer.h"

extern Debug debug;

class OpenGL
{
public:
	GLuint ShaderProgram;
	GLuint VertexShader;
	GLuint FragmentShader;

	//Constructors
	OpenGL();
	~OpenGL();

	//Initialize DirectX11
	bool init(int window_width, int window_height);

	void set_settings();
	void set_background(float bgcolor[4]);
	void clear_depth();
	void update_swapchain();
	void release(int value);

	void update_resources(Transform *transform, Camera camera);
	void render_model(Model *model);

	template <typename T>
	bool init_buffer(Buffer *buffer, const std::vector<T>& data, int type)
	{
		glGenBuffers(1, buffer->buffer);
		glBindBuffer(type, buffer->buffer);
		glBufferData(type, data.size() * sizeof(T), data, GL_STATIC_DRAW);

		return true;
	}

	//Functions
	bool init_viewport(int window_width, int window_height);
	bool init_shaders();
};