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
	/*
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		//Problem: glewInit failed, something is seriously wrong.
		debug.write("glewInit failed, aborting.");
		debug.write(err);
		exit(1);
	}
	*/

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
		From_loc = glGetUniformLocation(ShaderProgram, "From");
		Wa_loc = glGetUniformLocation(ShaderProgram, "Wa");
		Wb_loc = glGetUniformLocation(ShaderProgram, "Wb");
		Wc_loc = glGetUniformLocation(ShaderProgram, "Wc");
		Wd_loc = glGetUniformLocation(ShaderProgram, "Wd");
	}

	return true;
}

/**
* Settings for global rendering options
**/
void OpenGL::set_settings(){
	GLenum error = glGetError();

	glShadeModel(GL_SMOOTH);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	glDisable(GL_CULL_FACE); //need to disable because it is enabled in the sample code somewhere
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

glm::vec4 *Cross4(glm::vec4 *result, glm::vec4 U, glm::vec4 V, glm::vec4 W)
{
	double A, B, C, D, E, F;       // Intermediate Values

								   // Calculate intermediate values.

	A = (V[0] * W[1]) - (V[1] * W[0]);
	B = (V[0] * W[2]) - (V[2] * W[0]);
	C = (V[0] * W[3]) - (V[3] * W[0]);
	D = (V[1] * W[2]) - (V[2] * W[1]);
	E = (V[1] * W[3]) - (V[3] * W[1]);
	F = (V[2] * W[3]) - (V[3] * W[2]);

	// Calculate the result-vector components.

	(*result)[0] = (U[1] * F) - (U[2] * E) + (U[3] * D);
	(*result)[1] = -(U[0] * F) + (U[2] * C) - (U[3] * B);
	(*result)[2] = (U[0] * E) - (U[1] * C) + (U[3] * A);
	(*result)[3] = -(U[0] * D) + (U[1] * B) - (U[2] * A);

	return result;
}

void  Calc4Matrix(
	glm::vec4 *Wa,
	glm::vec4 *Wb,
	glm::vec4 *Wc,
	glm::vec4 *Wd)
{
	glm::vec4  From(0.0f,0.0f,0.0f,4.0f),  To(0.0f,0.0f,0.0f,0.0f);    // 4D From and To Points
	glm::vec4 Up(0.0f,1.0f,0.0f,0.0f), Over(0.0f,0.0f,1.0f,0.0f);    // 4D Up and Over Vectors
	double norm;    // Vector Norm

					// Get the normalized Wd column-vector.

	*Wd = To - From; 	//VecSub(Wd, To, From);
	norm = glm::length(*Wd); // norm = Norm4(*Wd);
	if (norm == 0)
		debug.write(L"To point and From point are the same.");

	(*Wd) *= (1 / norm);//VecScale(Wd, 1 / norm);

	// Calculate the normalized Wa column-vector.

	Cross4(Wa, Up, Over, *Wd);
	norm = glm::length(*Wa); // norm = Norm4(Wa);
	if (norm == 0)
		debug.write("Invalid Up vector.");
	(*Wa) *= (1 / norm); //VecScale(Wa, 1 / norm);

	// Calculate the normalized Wb column-vector.

	Cross4(Wb, Over, *Wd, *Wa);
	norm = glm::length(*Wb); //norm = Norm4(Wb);
	if (norm == 0)
		debug.write("Invalid Over vector.");
	(*Wb) *= (1 / norm);  //VecScale(Wb, 1 / norm);

	// Calculate the Wc column-vector.

	Cross4(Wc, *Wd, *Wa, *Wb);
}
/**
* Updates the resources for a scene (World and object matrix)
* @param Transform (of model to render)
* @param Camera in the scene
**/
void OpenGL::update_resources(Model * model, Transform *transform, Camera *camera,  glm::mat4 view, glm::mat4 proj)
{
	glm::vec4  From(0.0f, 0.0f, 0.0f, 4.0f);
	glm::vec4  Wa, Wb, Wc, Wd; // 4D Transformation Matrix Column Vectors
	Calc4Matrix(&Wa, &Wb, &Wc, &Wd);

	//PROJECT perspective
	double  S, T;    // Divisor Values
	glm::vec4 V;      // Scratch Vector

	T = 1 / tan(45.0 / 2.0);

	for (int i = 0; i < model->verts4D.size(); ++i) {
		V = glm::vec4(model->verts4D[i].x, model->verts4D[i].y, model->verts4D[i].z, model->verts4D[i].w) - From;//VecSub(V, VertList[i].Position, From);

		S = T / glm::dot(V, Wd);

		debug.write(S * glm::dot(V, Wa));
		debug.write(S * glm::dot(V, Wb));
		debug.write(S * glm::dot(V, Wc));
	}

	glUniform4fv(From_loc, 1, &From[0]);
	glUniform4fv(Wa_loc, 1, &Wa[0]);
	glUniform4fv(Wb_loc, 1, &Wb[0]);
	glUniform4fv(Wc_loc, 1, &Wc[0]);
	glUniform4fv(Wd_loc, 1, &Wd[0]);

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
	glm::mat4 mvp = proj * view * Model;

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