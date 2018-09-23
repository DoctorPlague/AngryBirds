#pragma once
#include "Entity.h"
class StoneBlock :
	public Entity
{
public:
	StoneBlock();
	~StoneBlock();

	// Virtual Functions
	void Render();
	void Update(float _DeltaTick);
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_STONEBLOCK; }
	b2Body* GetBody() { return m_body; }

	void SetPosition(b2Vec2 _position);
	void SetRotation(float _angle);
};

