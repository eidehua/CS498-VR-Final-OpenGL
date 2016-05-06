#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

class Buffer
{
public:
	GLuint *buffer;

	Buffer();
	~Buffer();
};
