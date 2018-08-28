#pragma once
#include "Entity.h"
#include "Utilities.h"

class Sprite;
class SlingShot : public Entity
{
public:
	SlingShot();
	~SlingShot();

	// Virtual Functions
	void Render();
	void Update();
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }

	void SetPosition(b2Vec2 _position);
	

private:	
	
};

