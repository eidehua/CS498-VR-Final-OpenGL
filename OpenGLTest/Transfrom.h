#pragma once

#include <Eigen/Dense>

#include "GameComponent.h"

using Eigen::Vector3f;
using Eigen::Vector4f;

class Transform : GameComponent
{
	public:
		//Constructors
		Transform();
		Transform(float p_x, float p_y, float p_z, float p_w, float r_x, float r_y, float r_z, float r_w, float s_x, float s_y, float s_z, float s_w);
		Transform(Vector4f pos, Vector4f rot, Vector4f scale);

		//Helper Functions
		void copy(Transform transform);
		
		//Operator Overload
		bool operator==(const Transform& transform) const;

		//Transform attributes
		//No need to be private because it doesn't need getters and setters yet?
		Vector4f position;
		Vector4f rotation;
		Vector4f scale;
};
