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
