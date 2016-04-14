#pragma once

#include <cml>

typedef cml::vector3f Vector3;
typedef cml::vector4f Vector4;

class Camera
{
public:
	//Constructors
	Camera();
	Camera(Vector3 pos, Vector3 look_at, Vector3 up);
	
	//Attributes
	Vector3 position;
	Vector3 look_at;
	Vector3 up;
};
