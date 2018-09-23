#include "Physics.h"

std::shared_ptr<Physics> Physics::s_pPhysics;

std::shared_ptr<Physics> Physics::GetInstance()
{
	if (!s_pPhysics)
	{
		s_pPhysics = std::shared_ptr<Physics>(new Physics());
	}
	return s_pPhysics;
}

void Physics::DestroyInstance()
{
	s_pPhysics.reset();
	//s_pSceneManager = nullptr;
}

Physics::Physics()
{	
	m_timeStep = 1.0f / 120.0f;
	m_velocityIterations = 8;
	m_positionIterations = 3;
	m_world->SetContactListener(&m_contactListenerInstance);
}

void Physics::Process()
{
	m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
	m_world->ClearForces();	
}

b2Body * Physics::CreateBody(b2BodyDef _bodyDef)
{
	b2Body* body = m_world->CreateBody(&_bodyDef);
	return body;
}

b2World* Physics::GetWorld() const
{
	return m_world;
}

Physics::~Physics()
{
}
