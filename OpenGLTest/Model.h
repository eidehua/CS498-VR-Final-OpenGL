#pragma once

#include "GameComponent.h"
#include "Vertex.h"
#include "Buffer.h"

class Model : GameComponent
{
public:
	std::vector<VERTEX> verts;
	Buffer *vertexBuffer;

	std::vector<GLushort> indices;
	Buffer *indiciesBuffer;

	Buffer *modelBuffer;

	Model();
	~Model();

	bool init_from_obj_file(const wchar_t *filename);
};
