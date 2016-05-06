#include "Buffer.h"

/**
* Default Constrcuter
* @param Vector (data to put into the buffer)
**/
Buffer::Buffer()
{
}

/**
* Destroyer
* - Must release the buffer before releasing the memory
**/
Buffer::~Buffer()
{
	if (this->buffer != NULL)
		glDeleteBuffers(1, this->buffer);
}
