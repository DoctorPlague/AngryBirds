// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	SlingShot.h
// Description	:	SlingShot header file

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
	void Update(float _DeltaTick);
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_SLINGSHOT; }
	b2Body* GetBody() { return m_body; }

	// Not Virtual Functions
	void SetPosition(b2Vec2 _position);
	bool GetLoaded();
	void SetLoaded(bool _loaded);
	glm::vec2 GetDrawOrigin();
	glm::vec2 GetReleasePosition();
	void SetDrawOrigin(glm::vec2 _mouseXY);
	void SetReleasePosition(glm::vec2 _mouseXY);


private:	
	bool m_loaded;
	glm::vec2 m_drawOrigin; 
	glm::vec2 m_releasePosition;
	float m_shotStrength;
};

