#pragma once

#include <glm/vec3.hpp> // glm::vec3

#include "OpenGL.h"
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"

using glm::vec3;

class Scene{
public:
	Camera camera;

	Scene();
	Scene(const wchar_t *filename);
	~Scene();

	//Update and Render
	void update_scene();
	void render_scene(OpenGL *opengl);

	//Add/Delete GameObjects from Scene
	int add_game_object(GameObject *game_object);
	GameObject * get_game_object(int pos);
	bool delete_game_object(int pos);

private:

	float bgcolor[4];

	std::vector<GameObject *> game_objects;
};
