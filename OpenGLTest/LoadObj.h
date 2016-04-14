#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Model.h"
#include "SimpleMath.h"

using namespace DirectX::SimpleMath;

bool init_model_from_obj(const wchar_t *filename, Model *model);