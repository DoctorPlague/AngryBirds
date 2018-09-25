#include "SlingShot.h"
#include "Sprite.h"
#include "Physics.h"
#include "Dependencies/glm/gtx/string_cast.hpp"
#include "Dependencies/glm/gtx/rotate_vector.hpp"


SlingShot::SlingShot()
{
	m_Sprite = std::make_shared<Sprite>();
	m_Scale = glm::vec3(0.08f, 1.00f, 0.0f);
	m_RotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	m_loaded = false;

	// Physics
	b2FixtureDef fixtureDef;	
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(0.0f, 0.0f);
	m_body = Physics::GetInstance()->CreateBody(m_bodyDef);
	m_shape.SetAsBox(0.08f, 1.00f);
	fixtureDef.shape = &m_shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.filter.categoryBits = 0x0000;
	fixtureDef.filter.maskBits = 0x0000;
	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
	m_body->SetAwake(false);
	m_bBodyDestroyed = false;
}


SlingShot::~SlingShot()
{
}

void SlingShot::Render()
{
	m_Sprite->Render(
		glm::translate(glm::mat4(), glm::vec3(m_body->GetPosition().x, m_body->GetPosition().y, 0.0f)) *
		glm::rotate(glm::mat4(), m_body->GetAngle(), m_RotationAxis) *
		glm::scale(glm::mat4(), m_Scale) // might need to change this later, idk what to do 
	);
}

void SlingShot::Update(float _DeltaTick)
{
}

void SlingShot::SetPosition(b2Vec2 _position)
{
	m_body->SetTransform(_position, m_body->GetAngle());
}

bool SlingShot::GetLoaded()
{
	return m_loaded;	
}

void SlingShot::SetLoaded(bool _loaded)
{
	m_loaded = _loaded;
}

glm::vec2 SlingShot::GetDrawOrigin()
{
	return m_drawOrigin;
}

glm::vec2 SlingShot::GetReleasePosition()
{
	return m_releasePosition;
}

void SlingShot::SetDrawOrigin(glm::vec2 _mouseXY)
{
	m_drawOrigin = _mouseXY;
}

void SlingShot::SetReleasePosition(glm::vec2 _mouseXY)
{
	m_releasePosition = _mouseXY;
}

void SlingShot::Initialize()
{
	m_Sprite->Initialize("Resources/Images/SlingshotTexture.png");
}
