// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	RopeBlock.h
// Description	:	RopeBlock header file

#pragma once
#include "Utilities.h"
#include "Entity.h"

class WoodBlock;
class RopeBlock : public Entity
{
public:
	RopeBlock();
	~RopeBlock();

	// Virtual Functions
	void Render();
	void Update(float _DeltaTick);
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_STONEBLOCK; }
	b2Body* GetBody() { return m_body; }

	void SetBlockOnePosition(b2Vec2 _position);
	void SetBlockTwoPosition(b2Vec2 _position);
	void SetBlockOneRotation(float _rotation);
	void SetBlockTwoRotation(float _rotation);
	void SetPosition(b2Vec2 _position);
	void SetRotation(float _angle);

	std::shared_ptr<WoodBlock> GetBlockOne();
	std::shared_ptr<WoodBlock> GetBlockTwo();


private:
	// Two blocks used by joint
	std::shared_ptr<WoodBlock> m_blockOne;
	std::shared_ptr<WoodBlock> m_blockTwo;	
};

