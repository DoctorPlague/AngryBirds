#include "GreenPig.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


GreenPig::GreenPig()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(0.15f, 0.15f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);	

	// Creating and Initializing Body
	b2FixtureDef fixtureDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(13.0f, 4.5f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	b2CircleShape dynamicCircle;
	dynamicCircle.m_p.Set(0.0f, 0.0f);
	dynamicCircle.m_radius = 0.15f;
	fixtureDef.shape = &dynamicCircle;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.10f;
	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}


GreenPig::~GreenPig()
{
}

void GreenPig::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) *
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void GreenPig::Update()
{
}

void GreenPig::Initialize()
{
	m_Sprite->Initialize("Resources/Images/PigTexture.png");
}

void GreenPig::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void GreenPig::SetRotation(float _angle)
{
	m_body->SetTransform(m_body->GetPosition(), _angle);
}
