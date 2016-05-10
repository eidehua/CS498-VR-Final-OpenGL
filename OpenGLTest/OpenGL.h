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

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "load_file.h"

#include "Math.h"
#include "Debug.h"
#include "Camera.h"
#include "Model.h"
#include "Transfrom.h"

#include "Buffer.h"

#define BUFFER_OFFSET(i) ((void*)(i))

extern Debug debug;

class OpenGL
{
public:
	GLuint ShaderProgram;
	GLuint VertexShader;
	GLuint FragmentShader;
	int ProjectionModelviewMatrix_Loc;

	//Constructors
	OpenGL();
	~OpenGL();

	//Initialize DirectX11
	bool init(int window_width, int window_height);

	void set_settings();
	void set_background(float bgcolor[4]);
	void clear_bits();
	void update_swapchain();
	void release(int value);

	void update_resources(Transform *transform, Camera *camera);
	void render_model(Model *model);

	template <typename T>
	bool init_buffer(Buffer *buffer, vector<T> &data, unsigned int type)
	{
		GLenum error = glGetError();

		glGenBuffers(1, &buffer->buffer);
		glBindBuffer(type, buffer->buffer);
		glBufferData(type, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);

		error = glGetError();
		if (error != 0) {
			debug.write("Failed to init buffer");
			debug.write(error);
		}

		glBindBuffer(type, 0);

		error = glGetError();
		if (error != 0) {
			debug.write("Failed to bind buffer");
			debug.write(error);
		}

		return true;
	}

	bool bind_vertex_indices(Model *model) {
		GLenum error = glGetError();

		glGenVertexArrays(1, &model->modelBuffer->buffer);
		glBindVertexArray(model->modelBuffer->buffer);

		glBindBuffer(GL_ARRAY_BUFFER, model->vertexBuffer->buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX), BUFFER_OFFSET(0));
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VERTEX), BUFFER_OFFSET(sizeof(float) * 3));
		glEnableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		//Bind the IBO for the VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indiciesBuffer->buffer);

		error = glGetError();
		if (error != 0) {
			debug.write("Failed to bind buffers");
			debug.write(error);
			return false;
		}

		return true;
	}

	//Functions
	bool init_viewport(int window_width, int window_height);
	bool init_shaders();
};