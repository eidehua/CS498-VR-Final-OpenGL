#include "Scene.h"

typedef cml::vector3f Vector3;
typedef cml::vector4f Vector4;

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
	this->camera.position = Vector4(20.0, 20.0, 20.0);
	this->camera.up = Vector3(0.0, 0.0, 1.0);
	this->light.pos = Vector3(14.0f, 10.0f, 14.0f);
	this->light.dir = Vector3(0.0f, -1.0f, 0.0f);
	this->light.range = 50.0f;
	this->light.att = Vector3(0.0f, 0.2f, 0.0f);
	this->light.ambient = Vector4(0.2f, 0.2f, 0.2f, 1.0f);
	this->light.diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
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
void Scene::render_scene(DX11 *directx)
{
	directx->set_background(Scene::bgcolor);
	directx->clear_depth();

	directx->update_light(this->light);

	for (std::vector<GameObject *>::iterator it = this->game_objects.begin(); it != this->game_objects.end(); ++it)
	{
		Model *game_model = (Model *) (*it)->get_game_component(GameComponent::MODEL);
		if ((*it)->get_game_component(GameComponent::MODEL) != NULL){
			directx->update_resources((Transform *) (*it)->get_game_component(GameComponent::TRANSFORM), this->camera);
			directx->render_model(game_model);
		}
	}

	directx->update_swapchain();
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
