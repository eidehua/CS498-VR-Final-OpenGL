#include "stdafx.h"
#include "LoadObj.h"

/**
* Load the vertex and normal information from a obj file
* - Clears current information from model
* - Currently only supports objs that have one mesh and ignore material of mesh (must be set up somewhere else
* - Currently loads face based normals
* @param filename (name of obj file)
* @param Model (model to load information);
* @return bool (if file exists)
**/
bool init_model_from_obj(const wchar_t *filename, Model *model){
	// Is the model init'd?
	if (model == NULL)
		return false;

	std::ifstream obj_file(L"models/wolf.obj");

	//Check if file exists
	if (!obj_file) {
		return false;
	}
	
	std::vector<Vector2> vertex_texture;
	std::vector<Vector3> vertex_normal;

	float x, y, z;
	int a, b, c, d, e, f, g, h, i;
	std::string line;

	while (getline(obj_file, line)){
		// Found new vertex
		if (line[0] == 'v' && line[1] == ' '){
			sscanf_s(&line[0], "v %f %f %f", &x, &y, &z);
			model->verts.push_back({ x, y, z  * -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f });
		}
		// Found new texture mapping coord
		else if (line[0] == 'v' && line[1] == 't'){
			sscanf_s(&line[0], "vt %f %f", &x, &y);
			vertex_texture.push_back({ x, 1.0f - y });
		}
		// Found new normal
		else if (line[0] == 'v' && line[1] == 'n'){
			sscanf_s(&line[0], "vn %f %f %f", &x, &y, &z);
			vertex_normal.push_back({ x, y, z * -1.0f });
		}
		// Found new face
		else if (line[0] == 'f'){
			sscanf_s(&line[0], "f %d/%d/%d %d/%d/%d %d/%d/%d", &a, &d, &g, &b, &e, &h, &c, &f, &i);
			model->indices.push_back((a - 1));

			model->verts[(a - 1)].tU = vertex_texture[(d - 1)].x;
			model->verts[(a - 1)].tV = vertex_texture[(d - 1)].y;

			model->verts[(a - 1)].nX = vertex_normal[(g - 1)].x;
			model->verts[(a - 1)].nY = vertex_normal[(g - 1)].y;
			model->verts[(a - 1)].nZ = vertex_normal[(g - 1)].z;

			model->indices.push_back((c - 1));

			model->verts[(c - 1)].tU = vertex_texture[(f - 1)].x;
			model->verts[(c - 1)].tV = vertex_texture[(f - 1)].y;

			model->verts[(c - 1)].nX = vertex_normal[(i - 1)].x;
			model->verts[(c - 1)].nY = vertex_normal[(i - 1)].y;
			model->verts[(c - 1)].nZ = vertex_normal[(i - 1)].z;

			model->indices.push_back((b - 1));

			model->verts[(b - 1)].tU = vertex_texture[(e - 1)].x;
			model->verts[(b - 1)].tV = vertex_texture[(e - 1)].y;

			model->verts[(b - 1)].nX = vertex_normal[(h - 1)].x;
			model->verts[(b - 1)].nY = vertex_normal[(h - 1)].y;
			model->verts[(b - 1)].nZ = vertex_normal[(h - 1)].z;
		}
	}
	return true;
}