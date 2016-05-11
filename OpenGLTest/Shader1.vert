//[VERTEX SHADER]
#version 330

in vec4 InVertex;
in vec4 InColor;

smooth out vec4 Color;

uniform mat4 ProjectionModelviewMatrix;
uniform vec4 From;
uniform vec4 Wa;
uniform vec4 Wb;
uniform vec4 Wc;
uniform vec4 Wd;


void main()
{
	float S, T;
	vec4 V, newV;

	T = 1 / tan(45.0 / 2.0);

	V = InVertex - From;
	S = T /  dot(V, Wd);

	newV = vec4(S * dot(V, Wa), S * dot(V, Wb), S * dot(V, Wc), 1.0);

	gl_Position = ProjectionModelviewMatrix * newV;
	Color = InColor;
}