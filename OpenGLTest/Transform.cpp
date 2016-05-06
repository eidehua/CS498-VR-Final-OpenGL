#include "Transfrom.h"

using Eigen::Vector3f;
using Eigen::Vector4f;

/**
* Standard Constructor, 0.0'd attributes
**/
Transform::Transform()
: GameComponent(GameComponent::TRANSFORM, false)
{
	this->scale = Vector4f(1, 1, 1, 1);
}

/**
* Constructor set by floats
* @param float x9 (order goes postion, rotation, scale, and x, y ,z, w).
**/
Transform::Transform(float p_x, float p_y, float p_z, float p_w, float r_x, float r_y, float r_z, float r_w, float s_x, float s_y, float s_z, float s_w)
: GameComponent(GameComponent::TRANSFORM, false)
{
	this->position = Vector4f(p_x, p_y, p_z, p_w);
	this->rotation = Vector4f(r_x, r_y, r_z, r_w);
	this->scale = Vector4f(s_x, s_y, s_z, s_w);
}

/**
* Constructor set by vec4's
* @param Vector4 (position)
* @param Vector4 (rotation)
* @param Vector4 (scale)
**/
Transform::Transform(Vector4f pos, Vector4f rot, Vector4f scale)
: GameComponent(GameComponent::TRANSFORM, false)
{
	this->position = pos;
	this->rotation = rot;
	this->scale = scale;
}

/**
* Copy the pos, rot, scale, from another transform
* @param Transform (to be copied)
**/
void Transform::copy(Transform transform)
{
	this->position = transform.position;
	this->rotation = transform.rotation;
	this->scale = transform.scale;
}

/**
* Overloader equality operator
**/
bool Transform::operator==(const Transform& transform) const
{
	return this->position == transform.position &&
		this->rotation == transform.rotation &&
		this->scale == transform.scale;
}
