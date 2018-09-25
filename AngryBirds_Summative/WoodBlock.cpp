#include "WoodBlock.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


WoodBlock::WoodBlock()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(1.0f, 0.1f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);

	// Physics
	b2FixtureDef fixtureDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(5.0f, 5.0f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	m_shape.SetAsBox(1.0f, 0.1f);
	fixtureDef.shape = &m_shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_bBodyDestroyed = false;
}


WoodBlock::~WoodBlock()
{
	
}

void WoodBlock::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) *
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void WoodBlock::Update(float _DeltaTick)
{
}

void WoodBlock::Initialize()
{
	m_Sprite->Initialize("Resources/Images/WoodTexture.png");
}

void WoodBlock::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void WoodBlock::SetRotation(float _angle)
{
	m_body->SetTransform(m_body->GetPosition(), _angle);
}
