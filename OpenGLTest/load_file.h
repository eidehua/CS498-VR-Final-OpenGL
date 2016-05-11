#pragma once

#include "GL/CAPI_GLE.h"
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Debug.h"

using namespace std;

extern Debug debug;

std::string loadFile(const char *fname);

void printShaderInfoLog(GLint shader);

int LoadShader(const char *pfilePath_vs, const char *pfilePath_fs, bool bindTexCoord0, bool bindNormal, bool bindColor, GLuint &shaderProgram, GLuint &vertexShader, GLuint &fragmentShader);