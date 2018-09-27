// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	PulleyBlock.h
// Description	:	PulleyBlock header file

#pragma once
#include "Utilities.h"
#include "Entity.h"

class StoneBlock;
class PulleyBlock
{
public:
	PulleyBlock(b2Vec2 _position0, b2Vec2 _position1);
	~PulleyBlock();

	void Update(float _deltaTime);
	void SetBlockOnePosition(b2Vec2 _position);
	void SetBlockTwoPosition(b2Vec2 _position);
	void SetBlockOneRotation(float _rotation);
	void SetBlockTwoRotation(float _rotation);

	std::shared_ptr<StoneBlock> GetBlockOne();
	std::shared_ptr<StoneBlock> GetBlockTwo();

private:	
	bool m_bMovementDirection;	
	// Two blocks used in joint
	std::shared_ptr<StoneBlock> m_blockOne;
	std::shared_ptr<StoneBlock> m_blockTwo;
};