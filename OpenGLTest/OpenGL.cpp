#include "OpenGL.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
using Eigen::Matrix4d;
 

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
		//ProjectionModelviewMatrix_Loc = glGetUniformLocation(ShaderProgram, "ProjectionModelviewMatrix");
	}

	return true;
}

/**
* Settings for global rendering options
**/
void OpenGL::set_settings(){
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFFFFFFFF);
	glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClearDepth(1.0);
	glClearStencil(0);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DITHER);
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
void OpenGL::clear_depth(){
	glClearDepth(1.0);
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
void OpenGL::update_resources(Transform *transform, Camera camera)
{
	/*Matrix4d position = Matrix::CreateTranslation(transform->position);
	Matrix4d rotation = Matrix::CreateRotationX(transform->rotation.x) * Matrix::CreateRotationY(transform->rotation.y) * Matrix::CreateRotationZ(transform->rotation.z);
	Matrix4d scale = Matrix::CreateScale(transform->scale);

	Matrix World = scale * rotation * position;
	Matrix WVP = World * Matrix::CreateLookAt(camera.position, camera.look_at, camera.up) * this->projection;

	this->cbPerObj.World = World;
	this->cbPerObj.WVP = WVP;
	this->devcon->UpdateSubresource(this->cbPerObjectBuffer, 0, NULL, &this->cbPerObj, 0, 0);
	this->devcon->VSSetConstantBuffers(0, 1, &this->cbPerObjectBuffer);*/
}

/**
* Tell DirectX to render the model givenm
* @param init'ed model
**/
void OpenGL::render_model(Model *model)
{
	/*UINT stride = sizeof(VERTEX);
	UINT offset = 0;

	this->devcon->IASetVertexBuffers(0, 1, &(model->vertexBuffer->buffer), &stride, &offset);
	this->devcon->IASetIndexBuffer(model->indiciesBuffer->buffer, DXGI_FORMAT_R32_UINT, 0);
	this->devcon->PSSetShaderResources(0, 1, &this->default_texture->texture);
	this->devcon->PSSetSamplers(0, 1, &this->default_texture->SamplerState);
	this->devcon->DrawIndexed(model->indices.size(), 0, 0);*/
}