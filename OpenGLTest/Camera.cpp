#include "Camera.h"

using Eigen::Vector3f;

/**
* Standard Constructor, 0.0'd attributes
**/
Camera::Camera(){

}

/**
* Constructor set by vec3's
* @param Vector3 (position)
* @param Vector3 (look_at)
* @param Vector3 (up)
**/
Camera::Camera(Vector3f pos, Vector3f look_at, Vector3f up){
	this->position = pos;
	this->look_at = look_at;
	this->up = up;
}
