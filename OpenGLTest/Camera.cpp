#include "Camera.h"

typedef cml::vector3f Vector3;
typedef cml::vector4f Vector4;

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
Camera::Camera(Vector3 pos, Vector3 look_at, Vector3 up){
	this->position = pos;
	this->look_at = look_at;
	this->up = up;
}
