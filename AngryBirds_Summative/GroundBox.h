#pragma once
#include "Entity.h"
#include "Utilities.h"

class Sprite;
class GroundBox :
	public Entity
{
public:
	GroundBox();
	~GroundBox();

	// Virtual Functions
	void Render();
	void Update();


	void SetPosition(b2Vec2 _position);	
	void Initialize();

private:
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationAxis;	

	// Physics
	b2BodyDef m_bodyDef;
	b2Body* m_body;
};

