#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Model.h"
#include "Debug.h"

#include <glm/vec3.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

bool init_model_from_obj(const wchar_t *filename, Model *model);