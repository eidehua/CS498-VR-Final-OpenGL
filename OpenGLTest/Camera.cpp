#include "Camera.h"

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
Camera::Camera(vec3 pos, vec3 look_at, vec3 up){
	this->position = pos;
	this->look_at = look_at;
	this->up = up;
}
