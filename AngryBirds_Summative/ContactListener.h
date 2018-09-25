#pragma once
#include "Utilities.h"
#include "AngryBird.h"
#include "GreenPig.h"
#include "GlassBlock.h"

class ContactListener : public b2ContactListener
{
public:
	/* handle begin event */
	void BeginContact(b2Contact* contact)
	{		
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyUserDataA && bodyUserDataB)
		{			
			// Check if a green pig had contact with a wood block
			if (static_cast<Entity*>(bodyUserDataA)->GetEntityType() == ENTITY_GREENPIG)
			{
				if (static_cast<Entity*>(bodyUserDataB)->GetEntityType() == ENTITY_WOODBLOCK)
				{
					static_cast<GreenPig*>(bodyUserDataA)->SetAlive(false);
				}
			}
			else if (static_cast<Entity*>(bodyUserDataA)->GetEntityType() == ENTITY_WOODBLOCK)
			{
				if (static_cast<Entity*>(bodyUserDataB)->GetEntityType() == ENTITY_GREENPIG)
				{
					static_cast<GreenPig*>(bodyUserDataB)->SetAlive(false);
				}
			}
			else if (static_cast<Entity*>(bodyUserDataA)->GetEntityType() == ENTITY_GLASSBLOCK)
			{				
				if (static_cast<Entity*>(bodyUserDataB)->GetEntityType() == ENTITY_ANGRYBIRD)
				{
					static_cast<GlassBlock*>(bodyUserDataA)->SetDestroyed(true);
				}
			}
			else if (static_cast<Entity*>(bodyUserDataB)->GetEntityType() == ENTITY_GLASSBLOCK)
			{
				if (static_cast<Entity*>(bodyUserDataA)->GetEntityType() == ENTITY_ANGRYBIRD)
				{
					static_cast<GlassBlock*>(bodyUserDataB)->SetDestroyed(true);
				}
			}
		}	
	}
	/* handle end event */
	void EndContact(b2Contact* contact)
	{ 
		
	}
	/* handle pre-solve event */
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{ 

	}
	/* handle post-solve event */
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{ 

	}
};

