#pragma once

#include "GameComponent.h"
#include "Vertex.h"
#include "Buffer.h"

class Model : GameComponent
{
public:
	std::vector<VERTEX4D> verts4D;
	std::vector<VERTEX> verts2;
	Buffer *vertexBuffer;

	std::vector<GLushort> indices;
	Buffer *indiciesBuffer;
	bool autoRotate = false;
	Buffer *modelBuffer;

	Model();
	~Model();

	bool init_from_obj_file(const wchar_t *filename);
};
