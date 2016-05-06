#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "OpenGL.h"
#include "Scene.h"

using namespace std;

Debug debug;

OpenGL opengl;
Scene scene;

void draw() {
	scene.render_scene(&opengl);
}

int main(int argc, char* argv[])
{
	debug.init(debug.VERBOSE);
	glutInit(&argc, argv);

	opengl.init(1000, 1000);

	glutDisplayFunc(draw);
	//glutReshapeFunc(reshape);

	glutMainLoop();
	return 0;
}