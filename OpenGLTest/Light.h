#pragma once

#include <cml>

typedef cml::vector3f Vector3;
typedef cml::vector4f Vector4;

struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
  Vector4 dir;
	Vector4 pos;
	float range;
	Vector3 att;
	Vector4 ambient;
	Vector4 diffuse;
};
