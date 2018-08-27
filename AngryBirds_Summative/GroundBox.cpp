#include "GroundBox.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


GroundBox::GroundBox()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(10.0f, 0.5f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);	

	// Physics
	b2FixtureDef fixtureDef;
	b2PolygonShape dynamicBox;
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(8.0f, 2.3f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	dynamicBox.SetAsBox(10.3f, 0.32f);
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}


GroundBox::~GroundBox()
{
}

void GroundBox::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) *
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void GroundBox::Update()
{

}

void GroundBox::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void GroundBox::Initialize()
{
	m_Sprite->Initialize("Resources/Images/ground.png");
}
