#pragma once
#include "Entity.h"
class GlassBlock :
	public Entity
{
public:
	GlassBlock();
	~GlassBlock();

	// Virtual Functions
	void Render();
	void Update(float _DeltaTick);
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_GLASSBLOCK; }
	b2Body* GetBody() { return m_body; }

	void SetPosition(b2Vec2 _position);
	void SetRotation(float _angle);
	int GetDestroyed() const { return m_bDestroyed; }
	void SetDestroyed(bool _bool) { m_bDestroyed = _bool; }

private:
	bool m_bDestroyed;
};

