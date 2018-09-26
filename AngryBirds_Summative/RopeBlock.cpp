#include "RopeBlock.h"
#include "WoodBlock.h"
#include "StoneBlock.h"
#include "Physics.h"
#include "Sprite.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"

RopeBlock::RopeBlock()
{
	m_blockOne = std::make_shared<WoodBlock>();
	m_blockTwo = std::make_shared<WoodBlock>();

	// Stuff for the block the other blocks hang from
	m_sprite = std::make_shared<Sprite>();
	m_scale = glm::vec3(1.0f, 0.1f, 0.0f);
	m_rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	// Physics
	b2FixtureDef fixtureDef;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(5.0f, 5.0f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	m_shape.SetAsBox(1.0f, 0.1f);
	fixtureDef.shape = &m_shape;
	fixtureDef.density = 0.5f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_bBodyDestroyed = false;

	// Define the jointdefs
	b2RopeJointDef jointDef0;
	jointDef0.bodyA = m_body;
	jointDef0.bodyB = m_blockOne->GetBody();
	jointDef0.collideConnected = false;
	jointDef0.localAnchorA.Set(1, 0);
	jointDef0.localAnchorB.Set(1, 0);
	jointDef0.maxLength = 0.5f;

	b2RopeJointDef jointDef1;
	jointDef1.bodyA = m_body;
	jointDef1.bodyB = m_blockTwo->GetBody();
	jointDef1.collideConnected = false;
	jointDef1.localAnchorA.Set(-1, 0);
	jointDef1.localAnchorB.Set(1, 0);
	jointDef1.maxLength = 0.5f;

	// Create Joints
	(b2RopeJoint*)Physics::GetInstance()->GetWorld()->CreateJoint(&jointDef0);
	(b2RopeJoint*)Physics::GetInstance()->GetWorld()->CreateJoint(&jointDef1);
}

RopeBlock::~RopeBlock()
{

}

void RopeBlock::Render()
{
	m_sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_rotationAxis) *
		glm::scale(glm::mat4(), m_scale) // might need to change this later, idk what to do 
	);
}

void RopeBlock::Update(float _DeltaTick)
{
}

void RopeBlock::Initialize()
{
	m_sprite->Initialize("Resources/Images/ground.png");
}

void RopeBlock::SetBlockOnePosition(b2Vec2 _position)
{
	m_blockOne->SetPosition(_position);
}

void RopeBlock::SetBlockTwoPosition(b2Vec2 _position)
{
	m_blockTwo->SetPosition(_position);
}

void RopeBlock::SetBlockOneRotation(float _rotation)
{
	m_blockOne->SetRotation(_rotation);
}

void RopeBlock::SetBlockTwoRotation(float _rotation)
{
	m_blockTwo->SetRotation(_rotation);
}

void RopeBlock::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void RopeBlock::SetRotation(float _angle)
{
	m_body->SetTransform(m_body->GetPosition(), _angle);
}

std::shared_ptr<WoodBlock> RopeBlock::GetBlockOne()
{
	return m_blockOne;
}

std::shared_ptr<WoodBlock> RopeBlock::GetBlockTwo()
{
	return m_blockTwo;
}
