#pragma once
#include "Entity.h"
#include "Utilities.h"

enum BirdType
{
	NORMAL,
	DIVER, 
	HEAVY,
	BOUNCER
};

class Sprite;
class AngryBird :
	public Entity
{
public:
	AngryBird();
	AngryBird(BirdType _type);
	~AngryBird();

	// Virtual Functions
	void Render();
	void Update(float _DeltaTick);
	void Initialize();	
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_ANGRYBIRD; }
	b2Body* GetBody() { return m_body; }

	// Non-Virtual Functions
	void AddVelocity(float _Speed);
	void AddImpulse(glm::vec2 _direction, float _strength);
	void AddRotation(float _Angle);
	void SetPosition(b2Vec2 _position);	
	void SetThrown(bool _bool);	
	int GetBirdType() const { return m_birdType; }
	bool GetThrown() const;
	bool GetSpecialState() const { return m_specialActive; }
	void SetSpecialState(bool _bool) { m_specialActive = _bool; }
	float GetRestitution() const { return m_birdRestitution; }	
	void SetLinearVelocity(glm::vec2 _velocity);
	void SpecialAbility();
	void CheckBirdAlive(); 
	void startContact() { m_numContacts++; }
	void endContact() { m_numContacts--; }	

private:	
	float m_birdDensity; 
	float m_birdRestitution;
	int m_numContacts;
	bool m_specialActive; // whether the birds special ability has been triggered
	bool m_thrown; // whether the bird is currently thrown
	BirdType m_birdType;
		
};

