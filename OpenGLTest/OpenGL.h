#pragma once

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#include "GL/CAPI_GLE.h"
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
	int From_loc;
	int Wa_loc;
	int Wb_loc;
	int Wc_loc;
	int Wd_loc;

	float w_pos = 4.0f;
	float w_move = -.005f;

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

	void update_resources(Model * model, Transform *transform, Camera *camera, glm::mat4 view, glm::mat4 proj, glm::vec4 To);
	void render_model(Model *model);

	template <typename T>
	bool init_buffer(Buffer *buffer, vector<T> &data, unsigned int type, unsigned int buffer_type)
	{
		GLenum error = glGetError();

		glGenBuffers(1, &buffer->buffer);
		glBindBuffer(type, buffer->buffer);
		glBufferData(type, data.size() * sizeof(T), &data[0], buffer_type);

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
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX4D), BUFFER_OFFSET(0));
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VERTEX4D), BUFFER_OFFSET(sizeof(float) * 4));
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