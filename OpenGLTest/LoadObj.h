#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Model.h"
#include <Eigen/Dense>

bool init_model_from_obj(const wchar_t *filename, Model *model);