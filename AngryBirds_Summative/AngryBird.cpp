#include "AngryBird.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"
#include "KeyboardInput.h"


AngryBird::AngryBird()
{
	m_Sprite = std::make_shared<Sprite>();	
	m_Scale = glm::vec3(0.15f, 0.15f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_fVibrationRate = 0.0f;
	m_picked = false;	

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

	//b2FixtureDef fixtureDef;
	//m_bodyDef.type = b2_dynamicBody;
	//m_bodyDef.position.Set(5.0f, 5.0f);
	//m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	//m_shape.SetAsBox(1.0f, 1.0f);
	//fixtureDef.shape = &m_shape;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;
	//m_body->CreateFixture(&fixtureDef);
	//m_body->SetUserData(this);
}


AngryBird::~AngryBird()
{
}

void AngryBird::Render()
{		
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) * 
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void AngryBird::Update()
{	
	if (m_picked)
	{
		m_body->SetTransform(b2Vec2(
			Input::GetInstance()->GetMouseWorldPos().x,
			Input::GetInstance()->GetMouseWorldPos().y),
			m_body->GetAngle()
		);
	}

	// This entityshould always be awake
	m_body->SetAwake(true);

	m_fVibrationRate *= 0.90f;
}

//Update Overload
//Moves the player character by the input Translate
void AngryBird::AddVelocity(float _Speed)
{
	m_body->ApplyForceToCenter(
	b2Vec2(m_body->GetWorldVector(b2Vec2(0, 1)).x * _Speed,
		   m_body->GetWorldVector(b2Vec2(0, 1)).y * _Speed), true);	

	m_fVibrationRate = 3.0f;
}

void AngryBird::AddImpulse(glm::vec2 _direction, float _strength)
{
	m_body->ApplyLinearImpulseToCenter(
		b2Vec2(_direction.x * _strength,
			   _direction.y * _strength), true);

	m_fVibrationRate = 3.0f;
}

void AngryBird::AddRotation(float _Angle)
{	
	m_body->ApplyTorque(_Angle, true);
}

void AngryBird::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

void AngryBird::SetPicked(bool _bool)
{
	if (m_picked && _bool == false)
	{
		// sleep and wake body for a torque and force reset 
		m_body->SetAwake(false);
		m_body->SetAwake(true);
	}

	m_picked = _bool;
}

bool AngryBird::GetPicked() const
{
	return m_picked;
}

void AngryBird::SetLinearVelocity(glm::vec2 _velocity)
{
	m_body->SetAwake(false);
	m_body->SetAwake(true);
	m_body->SetLinearVelocity(b2Vec2(_velocity.x, _velocity.y));
}

void AngryBird::Initialize()
{
	m_Sprite->Initialize("Resources/Images/BirdTexture.png");
}