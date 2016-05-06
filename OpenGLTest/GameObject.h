#pragma once
#include <vector>
#include <string>
#include <Eigen/Dense>

#include "GameComponent.h"
#include "Transfrom.h"

using Eigen::Vector3f;
using Eigen::Vector4f;

class GameObject
{
public:
	//Constructors
	GameObject();
	GameObject(Vector4f pos, Vector4f rot, Vector4f scale);
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
