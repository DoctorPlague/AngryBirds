#include "StoneBlock.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


StoneBlock::StoneBlock()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(1.0f, 0.3f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	// Physics
	b2FixtureDef fixtureDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(5.0f, 5.0f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	m_shape.SetAsBox(1.0f, 0.3f);
	fixtureDef.shape = &m_shape;
	fixtureDef.density = 10000.5f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}


StoneBlock::~StoneBlock()
{
}

void StoneBlock::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) *
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void StoneBlock::Update(float _DeltaTick)
{
}

void StoneBlock::Initialize()
{
	m_Sprite->Initialize("Resources/Images/scanline texture.png");
}

void StoneBlock::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void StoneBlock::SetRotation(float _angle)
{
	m_body->SetTransform(m_body->GetPosition(), _angle);
}
