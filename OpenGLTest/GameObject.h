#pragma once
#include <vector>
#include <string>
#include <glm/vec3.hpp> // glm::vec3

#include "GameComponent.h"
#include "Transfrom.h"

using glm::vec3;

class GameObject
{
public:
	//Constructors
	GameObject();
	GameObject(vec3 pos, vec3 rot, vec3 scale);
	GameObject(Transform transform);

	//Get and Setters
	void set_name(wchar_t *name){ this->name = name; }
	wchar_t * get_name(){ return this->name; }

	//Game Component control functions
	bool add_game_component(GameComponent *game_component);
	GameComponent *get_game_component(int type);
	std::vector<GameComponent *> get_game_components();
	bool has_game_component(int type);
	bool delete_game_component(int pos);

private:
	//Game Object Basic attributes
	wchar_t *name = L"GameObject";

	std::vector<GameComponent *> game_components;
};
