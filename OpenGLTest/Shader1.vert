//[VERTEX SHADER]
#version 330

in vec3 InVertex;
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
	

	gl_Position = ProjectionModelviewMatrix * vec4(InVertex,1.0);
	Color = InColor;
}