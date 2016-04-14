#pragma once

#include <cml>

#include "GameObject.h"

class Scene{
public:
	Scene();
	Scene(const wchar_t *filename);
	~Scene();

	//Update and Render
	void update_scene();
	void render_scene(DX11 *directx);

	//Add/Delete GameObjects from Scene
	int add_game_object(GameObject *game_object);
	GameObject * get_game_object(int pos);
	bool delete_game_object(int pos);

private:
	Camera camera;
	Light light;

	FLOAT bgcolor[4];

	std::vector<GameObject *> game_objects;
};
