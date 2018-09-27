// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	BaseLevel.cpp
// Description	:	BaseLevel c++ file

#include "BaseLevel.h"

BaseLevel::BaseLevel()
{
}


BaseLevel::~BaseLevel()
{
}

bool BaseLevel::CheckMousePicking(glm::vec2 _position, float _radius)
{
	if (glm::distance(_position, m_mousePos) <= _radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
