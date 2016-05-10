#pragma once

#include <vector>
#include <string>

#include "GL/CAPI_GLE.h"

class Buffer
{
public:
	GLuint buffer;

	Buffer();
	~Buffer();
};
