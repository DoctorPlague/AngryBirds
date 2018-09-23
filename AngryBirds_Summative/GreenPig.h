#pragma once
#include "Entity.h"
class GreenPig :
	public Entity
{
public:
	GreenPig();
	~GreenPig();

	// Virtual Functions
	void Render();
	void Update(float _DeltaTick);
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_GREENPIG; }
	b2Body* GetBody() { return m_body; }

	void SetPosition(b2Vec2 _position);
	void SetRotation(float _angle);
	void SetAlive(bool _bool);
	bool GetAlive() const;
	void startContact() { m_numContacts++; }
	void endContact() { m_numContacts--; }

private:
	bool m_alive;
	int m_numContacts;
};

