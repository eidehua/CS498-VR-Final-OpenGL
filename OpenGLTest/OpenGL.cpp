#include "OpenGL.h"

/**
* Standard Constructor
* @param GameWindow (to render to)
**/
OpenGL::OpenGL(){
}

/**
* Destory method
**/
OpenGL::~OpenGL(){
	//this->release(0);
}


/**
* Initialized everything related to DirectX (shaders, render texture, depth)
* @param bool (true if it succeeded)
**/
bool OpenGL::init(int window_width, int window_height){
/*
	if (!init_viewport(window_width, window_height))
		debug.write("DirectX11:init:Failed to init viewport");
*/
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		//Problem: glewInit failed, something is seriously wrong.
		debug.write("glewInit failed, aborting.");
		debug.write(err);
		exit(1);
	}

	set_settings();

	if (!init_shaders())
		debug.write("DirectX11:init:Failed to init shaders");

	return true;
}

/**
* Init the view port (on the window)
* @param bool (true if it succeeded)
**/
bool OpenGL::init_viewport(int window_width, int window_height){
	/*glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	//We want to make a GL 3.3 context
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_CORE_PROFILE);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(600, 600);
	__glutCreateWindowWithExit("GL 3.3 Test", NULL);*/


	return true;
}

bool OpenGL::init_shaders()
{
	if (LoadShader("Shader1.vert", "Shader1.frag", false, false, true, ShaderProgram, VertexShader, FragmentShader) == -1)
	{
		debug.write("failed to load shaders");
		exit(1);
	}
	else
	{
		GLenum error = glGetError();
		ProjectionModelviewMatrix_Loc = glGetUniformLocation(ShaderProgram, "ProjectionModelviewMatrix");
	}

	return true;
}

/**
* Settings for global rendering options
**/
void OpenGL::set_settings(){
	GLenum error = glGetError();

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(TRUE);
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFFFFFFFF);
	glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glFrontFace(GL_CCW);
	//glCullFace(GL_BACK);
	//glEnable(GL_CULL_FACE);
	glClearColor(1.0, 0.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DITHER);


	 error = glGetError();

	if (error != 0) {
		debug.write("Failed to init settings s");
		debug.write(error);
	}

	//glActiveTexture(GL_TEXTURE0);
}

/**
* Settings for global rendering options
**/
void OpenGL::set_background(float bgcolor[4]){
	glClearColor(bgcolor[0], bgcolor[1], bgcolor[2], bgcolor[3]);
}

/**
* Reset depth buffer
**/
void OpenGL::clear_bits(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

/**
* Swap the rendering targets
**/
void OpenGL::update_swapchain() {
	glutSwapBuffers();
}

/**
* Used to release all related DirectX resources
**/
void OpenGL::release(int value){
	glDetachShader(this->ShaderProgram, this->VertexShader);
	glDetachShader(this->ShaderProgram, this->FragmentShader);
	glDeleteProgram(this->ShaderProgram);
	delete this;
}

/**
* Updates the resources for a scene (World and object matrix)
* @param Transform (of model to render)
* @param Camera in the scene
**/
void OpenGL::update_resources(Transform *transform, Camera *camera)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)4 / (float)3, 0.1f, 100.0f);

	glm::mat4 View = glm::lookAt(
		camera->position,
		camera->look_at,
		camera->up
		);

	glm::mat4 Model = glm::mat4(1.0f);
	glm::scale(Model, transform->scale);
	glm::rotate(Model, transform->rotation.x, vec3(1, 0, 0));
	glm::rotate(Model, transform->rotation.y, vec3(0, 1, 0));
	glm::rotate(Model, transform->rotation.z, vec3(0, 0, 1));
	glm::translate(Model, transform->position);
	glm::mat4 mvp = Projection * View * Model;

	glUseProgram(this->ShaderProgram);
	glUniformMatrix4fv(ProjectionModelviewMatrix_Loc, 1, FALSE, &mvp[0][0]);
}

/**
* Tell DirectX to render the model givenm
* @param init'ed model
**/
void OpenGL::render_model(Model *model)
{
	glBindVertexArray(model->modelBuffer->buffer);
	glDrawRangeElements(GL_TRIANGLES, 0, 3, model->indices.size(), GL_UNSIGNED_SHORT, NULL);
}