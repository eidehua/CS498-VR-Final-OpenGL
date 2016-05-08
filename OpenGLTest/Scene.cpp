#include "Scene.h"

using Eigen::Vector3f;
using Eigen::Vector4f;

/**
* Default constructor
* Background color is Blue
**/
Scene::Scene()
{
	this->bgcolor[0] = 0.0;
	this->bgcolor[1] = 0.0;
	this->bgcolor[2] = 1.0;
	this->bgcolor[3] = 1.0;
	this->camera.position = Vector3f(20.0, 20.0, 20.0);
	this->camera.up = Vector3f(0.0, 0.0, 1.0);
}

/**
* Constructor that will be used to load scene information from a file
**/
Scene::Scene(const wchar_t *filename)
{

}

/**
* Scene Destructor
**/
Scene::~Scene()
{

}

/**
* Updates all the objects in a scene
**/
void Scene::update_scene()
{

}

/**
* Render Scene
* - Goes through each game object and renders the model if it exists
* @param DX11 (Directx object)
**/
void Scene::render_scene(OpenGL *opengl)
{
	opengl->clear_bits();

	for (std::vector<GameObject *>::iterator it = this->game_objects.begin(); it != this->game_objects.end(); ++it)
	{
		Model *game_model = (Model *) (*it)->get_game_component(GameComponent::MODEL);
		if ((*it)->get_game_component(GameComponent::MODEL) != NULL){
			opengl->update_resources((Transform *) (*it)->get_game_component(GameComponent::TRANSFORM), &this->camera);
			opengl->render_model(game_model);
		}
	}

	//opengl->update_swapchain();
}

/**
* Add a game object to the scene
* @param GameObject
**/
int Scene::add_game_object(GameObject *game_object)
{
	if (game_object == NULL)
		return -1;

	this->game_objects.push_back(game_object);
	return this->game_objects.size() - 1;
}

/**
* Get the gameobject at current position
* @param int
* @return GameObject
**/
GameObject * Scene::get_game_object(int pos)
{
	if (0 <= pos && pos < this->game_objects.size())
		return this->game_objects[pos];
	return NULL;
}

/**
* Delete game object at certain position
* @param int
* @return bool (if success)
**/
bool Scene::delete_game_object(int pos)
{
	if (pos >= this->game_objects.size())
		return false;
	delete this->game_objects[pos];

	this->game_objects.erase(this->game_objects.begin() + pos);
	return true;
}
