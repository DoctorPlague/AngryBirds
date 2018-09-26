#include "PulleyBlock.h"
#include "StoneBlock.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"

PulleyBlock::PulleyBlock(b2Vec2 _position0, b2Vec2 _position1)
{
	m_bMovementDirection = false;
	m_blockOne = std::make_shared<StoneBlock>();
	m_blockTwo = std::make_shared<StoneBlock>();
	m_blockOne->SetPosition(_position0);
	m_blockTwo->SetPosition(_position1);

	b2PulleyJointDef jointDef;

	// Define Joint Definition 	
	jointDef.bodyA = m_blockOne->GetBody();
	jointDef.bodyB = m_blockTwo->GetBody();
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(0, 0);
	jointDef.localAnchorB.Set(0, 0);	
	jointDef.groundAnchorA.Set(m_blockOne->GetPosition().x, m_blockOne->GetPosition().y + 5.0f);
	jointDef.groundAnchorB.Set(m_blockTwo->GetPosition().x, m_blockTwo->GetPosition().y + 5.0f);
	jointDef.lengthA = 3.0f;
	jointDef.lengthB = 3.0f;
	jointDef.ratio = 1.0f;	

	// Create Joint
	(b2PulleyJoint*)Physics::GetInstance()->GetWorld()->CreateJoint(&jointDef);
}

PulleyBlock::~PulleyBlock()
{
	
}

void PulleyBlock::Update(float _deltaTime)
{
	// Check and decide movement direction
	if (m_blockOne->GetPosition().y < 3.85f)
	{
		m_bMovementDirection = true;
	}
	else if (m_blockOne->GetPosition().y > 7.5f)
	{
		m_bMovementDirection = false;
	}

	// Set block one linear velocity
	switch (m_bMovementDirection)
	{
	case false:
	{
		m_blockOne->GetBody()->SetLinearVelocity(b2Vec2(0.0f, -50.0f * _deltaTime));
		break;
	}
	case true:
	{
		m_blockOne->GetBody()->SetLinearVelocity(b2Vec2(0.0f, 50.0f * _deltaTime));
		break;
	}
	}
}

void PulleyBlock::SetBlockOnePosition(b2Vec2 _position)
{
	m_blockOne->SetPosition(_position);
}

void PulleyBlock::SetBlockTwoPosition(b2Vec2 _position)
{
	m_blockTwo->SetPosition(_position);
}

void PulleyBlock::SetBlockOneRotation(float _rotation)
{
	m_blockOne->SetRotation(_rotation);
}

void PulleyBlock::SetBlockTwoRotation(float _rotation)
{
	m_blockTwo->SetRotation(_rotation);
}

std::shared_ptr<StoneBlock> PulleyBlock::GetBlockOne()
{
	return m_blockOne;
}

std::shared_ptr<StoneBlock> PulleyBlock::GetBlockTwo()
{
	return m_blockTwo;
}
