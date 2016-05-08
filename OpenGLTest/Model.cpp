#include "LoadObj.h"
#include "model.h"

/**
* Default Constructor
**/
Model::Model()
: GameComponent(GameComponent::MODEL, true)
{
	this->indiciesBuffer = new Buffer();
	this->vertexBuffer = new Buffer();
	this->modelBuffer = new Buffer();
}

/**
* Destoryer
**/
Model::~Model()
{
	delete this->indiciesBuffer;
	delete this->vertexBuffer;
	delete this->modelBuffer;
}

/**
* Loads vertex information from a .obj file
* @param string (filename of obj)
* @return bool (true if success)
**/
bool Model::init_from_obj_file(const wchar_t *filename)
{
	return init_model_from_obj(filename, this);
}
