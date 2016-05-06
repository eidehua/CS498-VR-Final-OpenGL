#pragma once

#include <Eigen/Dense>

using Eigen::Vector3f;

class Camera
{
public:
	//Constructors
	Camera();
	Camera(Vector3f pos, Vector3f look_at, Vector3f up);
	
	//Attributes
	Vector3f position;
	Vector3f look_at;
	Vector3f up;
};