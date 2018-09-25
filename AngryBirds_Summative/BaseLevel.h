#pragma once
#include "Utilities.h"

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
	std::vector<std::shared_ptr<Entity>> m_EntityVec;

	// Other Entities	
	std::shared_ptr<Sprite> m_Background;
	std::shared_ptr<Camera> m_Camera;
};

