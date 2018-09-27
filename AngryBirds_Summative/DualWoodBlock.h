// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	DualWoodBlock.h
// Description	:	DualwoodBlock header file

#pragma once
#include "Utilities.h"

class WoodBlock;
class DualWoodBlock
{
public:
	DualWoodBlock();
	~DualWoodBlock();

	void SetBlockOnePosition(b2Vec2 _position);
	void SetBlockTwoPosition(b2Vec2 _position);
	void SetBlockOneRotation(float _rotation);
	void SetBlockTwoRotation(float _rotation);

	std::shared_ptr<WoodBlock> GetBlockOne();
	std::shared_ptr<WoodBlock> GetBlockTwo();	

private:
	// The two blocks that are connected by joint
	std::shared_ptr<WoodBlock> m_blockOne;
	std::shared_ptr<WoodBlock> m_blockTwo;	
};

