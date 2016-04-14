#pragma once

#include <vector>
#include <string>

#include <gl/freeglut.h>

class Buffer
{
public:
	GLuint *buffer;

	Buffer();
	~Buffer();
};
