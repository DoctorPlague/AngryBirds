// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	Utilities.h
// Description	:	Utilities header file

#pragma once
const int ki_SCREENWIDTH = 1600;
const int ki_SCREENHEIGHT = 900;
const float kf_NORMALX = static_cast<float>(ki_SCREENHEIGHT) / static_cast<float>(ki_SCREENWIDTH);

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\soil\SOIL.h"
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glm\gtc\type_ptr.hpp"
#include "Dependencies\Box2D\Box2D.h"
#include <memory>
#include <vector>
#include <iostream>

static float ConvertToRadian(float _degree)
{
	return _degree * b2_pi / 180.0f;
}

