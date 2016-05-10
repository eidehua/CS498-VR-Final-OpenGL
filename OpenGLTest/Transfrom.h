#pragma once

#include <glm/vec3.hpp> // glm::vec3

#include "GameComponent.h"

using glm::vec3;

class Transform : GameComponent
{
	public:
		//Constructors
		Transform();
		Transform(float p_x, float p_y, float p_z, float p_w, float r_x, float r_y, float r_z, float r_w, float s_x, float s_y, float s_z, float s_w);
		Transform(vec3 pos, vec3 rot, vec3 scale);

		//Helper Functions
		void copy(Transform transform);
		
		//Operator Overload
		bool operator==(const Transform& transform) const;

		//Transform attributes
		//No need to be private because it doesn't need getters and setters yet?
		vec3 position;
		vec3 rotation;
		vec3 scale;
};
