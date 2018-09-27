// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	WoodBlock.h
// Description	:	WoodBlock header file

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
	void Update(float _DeltaTick);
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_WOODBLOCK; }
	b2Body* GetBody() { return m_body; }

	void SetPosition(b2Vec2 _position);
	void SetRotation(float _angle);
	
};

