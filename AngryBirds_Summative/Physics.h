#pragma once
#include "Utilities.h"

class Physics
{
#pragma region Singleton
public:
	static std::shared_ptr<Physics> GetInstance();
	static void DestroyInstance();
	~Physics();
private:
	static std::shared_ptr<Physics> s_pPhysics;
	Physics(Physics const&);
	void operator=(Physics const&);
	Physics();
#pragma endregion

public:	
	void Process();
	b2Body* CreateBody(b2BodyDef _bodyDef);
	b2World* GetWorld() const;
	

private:	
	b2Vec2 m_gravity = b2Vec2(0.0f, -8.8f);
	b2World* m_world = new b2World(m_gravity);		
	float32 m_timeStep;
	int32 m_velocityIterations;
	int32 m_positionIterations;
};

