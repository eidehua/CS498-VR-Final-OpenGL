#pragma once

#include <cml>

#include "GameComponent.h"

typedef cml::vector3f Vector3;
typedef cml::vector4f Vector4;

class Transform : GameComponent
{
	public:
		//Constructors
		Transform();
		Transform(float p_x, float p_y, float p_z, float p_w, float r_x, float r_y, float r_z, float r_w, float s_x, float s_y, float s_z, float s_w);
		Transform(Vector4 pos, Vector4 rot, Vector4 scale);

		//Helper Functions
		void copy(Transform transform);
		
		//Operator Overload
		bool operator==(const Transform& transform) const;

		//Transform attributes
		//No need to be private because it doesn't need getters and setters yet?
		Vector4 position;
		Vector4 rotation;
		Vector4 scale;
};
