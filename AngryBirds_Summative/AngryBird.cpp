#include "AngryBird.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"
#include "KeyboardInput.h"


AngryBird::AngryBird()
{
	// Set Bird Type
	m_birdType = NORMAL;

	// Initialize non physics stuff
	m_Sprite = std::make_shared<Sprite>();	
	m_Scale = glm::vec3(0.15f, 0.15f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_thrown = false;
	m_specialActive = false;
	m_birdRestitution = 1.0f;
	m_birdDensity = 1.0f;

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
	fixtureDef.friction = 1.3f;
	fixtureDef.restitution = 0.10f;
	fixtureDef.filter.categoryBits = 0x0002;
	fixtureDef.filter.maskBits = 0x0002;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_numContacts = 0;
	m_bBodyDestroyed = false;
}

AngryBird::AngryBird(BirdType _type)
{
	// Set Bird Type
	m_birdType = _type;

	// Initialize non physics stuff
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(0.15f, 0.15f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);		
	m_thrown = false;
	m_specialActive = false;
	m_birdRestitution = 1.0f;
	m_birdDensity = 1.0f;

	// Creating and Initializing Body
	b2FixtureDef fixtureDef;
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(13.0f, 4.5f);
	m_bodyDef.angularDamping = 6.0f;
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
	m_numContacts = 0;
	m_bBodyDestroyed = false;
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

void AngryBird::Update(float _DeltaTick)
{	
	// Check if the bird is within the level
	if (m_body->GetPosition().x > 17.0f || m_body->GetPosition().x < 0.0f)
	{		
		m_thrown = false;
	}

	// if the bird is thrown, check if its live
	if (m_thrown)
	{
		CheckBirdAlive();
	}

	// reduce angular velocity
	//m_body->SetAngularVelocity((m_body->GetAngularVelocity() * 0.98f) * _DeltaTick);

	// This entityshould always be awake
	m_body->SetAwake(true);
}

//Update Overload
//Moves the player character by the input Translate
void AngryBird::AddVelocity(float _Speed)
{
	m_body->ApplyForceToCenter(
	b2Vec2(m_body->GetWorldVector(b2Vec2(0, 1)).x * _Speed,
		   m_body->GetWorldVector(b2Vec2(0, 1)).y * _Speed), true);	
}

void AngryBird::AddImpulse(glm::vec2 _direction, float _strength)
{
	m_body->ApplyLinearImpulseToCenter(
		b2Vec2(_direction.x * _strength,
			   _direction.y * _strength), true);		
}

void AngryBird::AddRotation(float _Angle)
{	
	m_body->ApplyTorque(_Angle, true);
}

void AngryBird::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}


void AngryBird::SetThrown(bool _bool)
{
	m_thrown = _bool;
}

bool AngryBird::GetThrown() const
{
	return m_thrown;
}

void AngryBird::SetLinearVelocity(glm::vec2 _velocity)
{
	m_body->SetAwake(false);
	m_body->SetAwake(true);
	m_body->SetLinearVelocity(b2Vec2(_velocity.x, _velocity.y));
}

void AngryBird::SpecialAbility()
{
	switch (m_birdType)
	{
	case NORMAL:
	{
		// Do nothing
		break;
	}
	case DIVER:
	{
		// B-line straight down towards the ground
		if (!m_specialActive)
		{			
			m_body->SetLinearVelocity(b2Vec2(0.0f, -30.0f));
			m_specialActive = true;
		}		
		break;
	}
	case HEAVY:
	{
		if (!m_specialActive)
		{
			m_body->GetFixtureList()->SetDensity(350.0f);
			m_body->ResetMassData();
			m_specialActive = true;
		}		
		break;
	}
	case BOUNCER:
	{
		if (!m_specialActive)
		{
			m_body->GetFixtureList()->SetRestitution(0.7f);
			m_body->ResetMassData();
			m_specialActive = true;
		}
		break;
	}
	}
}

/*If the bird has less than a specified amount of linear and angular velocity, we consider it dead*/
void AngryBird::CheckBirdAlive()
{
	if (m_body->GetLinearVelocity().Length() < 0.2f
		&& m_body->GetAngularVelocity() < 0.6f)
	{
		m_thrown = false;
	}	
}

void AngryBird::Initialize()
{
	switch (m_birdType)
	{
	case DIVER:
	{
		m_Sprite->Initialize("Resources/Images/DiveBirdTexture.png");
		break;
	}
	case HEAVY:
	{
		m_Sprite->Initialize("Resources/Images/GrowBirdTexture.png");
		break;
	}
	case BOUNCER:
	{
		m_Sprite->Initialize("Resources/Images/BounceBirdTexture.png");
		break;
	}
	case NORMAL:
	{
		m_Sprite->Initialize("Resources/Images/BirdTexture.png");
		break;
	}
	default:
	{
		m_Sprite->Initialize("Resources/Images/BirdTexture.png");
		break;
	}
	}
	
}