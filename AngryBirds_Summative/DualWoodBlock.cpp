#include "DualWoodBlock.h"
#include "WoodBlock.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"

DualWoodBlock::DualWoodBlock()
{
	m_blockOne = std::make_shared<WoodBlock>();
	m_blockTwo = std::make_shared<WoodBlock>();	

	b2RevoluteJointDef jointDef;

	// Define Joint Definition 
	jointDef.bodyA = m_blockOne->GetBody();
	jointDef.bodyB = m_blockTwo->GetBody();
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(1, 0);
	jointDef.localAnchorB.Set(-1, 0);
	jointDef.referenceAngle = 0.0f;

	// Create Joint
	(b2RevoluteJoint*)Physics::GetInstance()->GetWorld()->CreateJoint(&jointDef);
}

DualWoodBlock::~DualWoodBlock()
{
	
}

void DualWoodBlock::SetBlockOnePosition(b2Vec2 _position)
{
	m_blockOne->SetPosition(_position);
}

void DualWoodBlock::SetBlockTwoPosition(b2Vec2 _position)
{
	m_blockTwo->SetPosition(_position);
}

void DualWoodBlock::SetBlockOneRotation(float _rotation)
{
	m_blockOne->SetRotation(_rotation);
}

void DualWoodBlock::SetBlockTwoRotation(float _rotation)
{
	m_blockTwo->SetRotation(_rotation);
}

std::shared_ptr<WoodBlock> DualWoodBlock::GetBlockOne()
{
	return m_blockOne;
}

std::shared_ptr<WoodBlock> DualWoodBlock::GetBlockTwo()
{
	return m_blockTwo;
}
