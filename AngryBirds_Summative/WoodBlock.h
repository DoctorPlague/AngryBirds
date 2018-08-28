#pragma once
#include "Entity.h"
class WoodBlock :
	public Entity
{
public:
	WoodBlock();
	~WoodBlock();

	// Virtual Functions
	void Render();
	void Update();
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }



	void SetPosition(b2Vec2 _position);
	void SetRotation(float _angle);
};
