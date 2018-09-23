#pragma once
#include "Utilities.h"
#include "Entity.h"

class StoneBlock;
class PulleyBlock
{
public:
	PulleyBlock(b2Vec2 _position0, b2Vec2 _position1);
	~PulleyBlock();

	void Update();
	void SetBlockOnePosition(b2Vec2 _position);
	void SetBlockTwoPosition(b2Vec2 _position);
	void SetBlockOneRotation(float _rotation);
	void SetBlockTwoRotation(float _rotation);

	std::shared_ptr<StoneBlock> GetBlockOne();
	std::shared_ptr<StoneBlock> GetBlockTwo();

private:
	bool m_bMovementDirection;
	std::shared_ptr<StoneBlock> m_blockOne;
	std::shared_ptr<StoneBlock> m_blockTwo;
};