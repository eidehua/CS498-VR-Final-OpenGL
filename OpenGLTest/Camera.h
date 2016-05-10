#pragma once

#include <glm/vec3.hpp> // glm::vec3

using glm::vec3;

class Camera
{
public:
	//Constructors
	Camera();
	Camera(vec3 pos, vec3 look_at, vec3 up);
	
	//Attributes
	vec3 position;
	vec3 look_at;
	vec3 up;
};