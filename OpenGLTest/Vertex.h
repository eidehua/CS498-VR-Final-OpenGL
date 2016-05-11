#pragma once

struct VERTEX
{
	float	x, y, z;
	unsigned int	color;
	float	padding[4];
};

struct VERTEX4D
{
	float	x, y, z, w;
	unsigned int	color;
	float	padding[3];
};

/*struct VERTEX {
	float pX, pY, pZ, pW;
	unsigned int color;
	float nX, nY, nZ, nW;
};*/