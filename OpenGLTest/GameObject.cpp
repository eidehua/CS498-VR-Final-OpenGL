#include "GameObject.h"

/**
* Standard Constructor, 0.0'd transform
**/
GameObject::GameObject()
{
	Transform *transform = new Transform();
	this->add_game_component((GameComponent *)transform);
}

/**
* Constructor set by Vec3's
* @param Vector3 (position)
* @param Vector3 (rotation)
* @param Vector3 (scale)
**/
GameObject::GameObject(vec3 pos, vec3 rot, vec3 scale)
{
	Transform *transform = new Transform(pos, rot, scale);
	this->add_game_component((GameComponent *) transform);
}

/**
* Constructor set by transform
* @param Transform
**/
GameObject::GameObject(Transform transform)
{
	Transform *new_transform = new Transform();
	(*new_transform).copy(transform);
	this->add_game_component((GameComponent *) new_transform);
}

/**
* Used to add a game object
* @param GameComponent *(Pointer to Gamecomponent to add)
* @return bool (true if is actually gets added)
**/
bool GameObject::add_game_component(GameComponent *game_component)
{
	if (game_component == NULL)
		return false;
	if (game_component->get_can_doubles() && this->has_game_component(game_component->get_type()))
		return false;
	this->game_components.push_back(game_component);
	return true;
}

/**
* Returns the first game component with that type
* @param int (type of component)
* @return GameComponent *
**/
GameComponent *GameObject::get_game_component(int type)
{
	for (std::vector<GameComponent *>::iterator it = this->game_components.begin(); it != this->game_components.end(); ++it)
		if ((*it)->get_type() == type)
			return (GameComponent *) (*it);
		return NULL;
}

/**
* Returns a vector of game components that the game object has
* @return vector<GameComponent *>
**/
std::vector<GameComponent *> GameObject::get_game_components(){
	return this->game_components;
}

/**
* Determine if the game object has a game component of that type
* @param type
* @return bool
**/
bool GameObject::has_game_component(int type)
{
	for (std::vector<GameComponent *>::iterator it = this->game_components.begin(); it != this->game_components.end(); ++it)
		if ((*it)->get_type() == type)
			return true;
	return false;
}

/**
* Remove the game comp at a given position
* @param num (pos of game component)
* @return bool
**/
bool GameObject::delete_game_component(int pos)
{
	if (0 < pos && pos <= this->game_components.size()){
		delete this->game_components[pos];

		this->game_components.erase(this->game_components.begin() + pos);
		return true;
	}
	return false;
}