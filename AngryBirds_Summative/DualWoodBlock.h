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
	std::shared_ptr<WoodBlock> m_blockOne;
	std::shared_ptr<WoodBlock> m_blockTwo;	
};

