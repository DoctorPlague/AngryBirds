// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	BaseLevel.h
// Description	:	BaseLevel header file

#pragma once
#include "Utilities.h"

class TextLabel;
class Entity;
class Sprite;
class Camera;
class BaseLevel
{
public:
	BaseLevel();
	~BaseLevel();

	// Mouse Picking
	bool CheckMousePicking(glm::vec2 _position, float _radius);

protected:
	glm::vec2 m_mousePos;

	// Contains all entities, for rendering and updating purposes
	std::vector<std::shared_ptr<Entity>> m_entityVec;
	std::vector<std::shared_ptr<TextLabel>> m_textLabels;

	// Other Entities	
	std::shared_ptr<Sprite> m_background;
	std::shared_ptr<Camera> m_camera;
};

