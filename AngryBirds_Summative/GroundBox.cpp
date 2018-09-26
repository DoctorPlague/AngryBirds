#include "GroundBox.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


GroundBox::GroundBox()
{
	m_sprite = std::make_shared<Sprite>();
	m_scale = glm::vec3(10.0f, 0.5f, 0.0f);
	m_rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);	

	// Physics
	b2FixtureDef fixtureDef;	
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(5.0f, 5.0f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	m_shape.SetAsBox(10.0f, 0.5f);
	fixtureDef.shape = &m_shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.3f;
	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_bBodyDestroyed = false;
}


GroundBox::~GroundBox()
{
}

void GroundBox::Render()
{
	m_sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_rotationAxis) *
		glm::scale(glm::mat4(), m_scale) // might need to change this later, idk what to do 
	);
}

void GroundBox::Update(float _DeltaTick)
{

}

void GroundBox::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void GroundBox::Initialize()
{
	m_sprite->Initialize("Resources/Images/GroundTexture.png");
}
