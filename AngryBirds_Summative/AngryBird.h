#pragma once
#include "Entity.h"
#include "Utilities.h"

class Sprite;
class AngryBird :
	public Entity
{
public:
	AngryBird();
	~AngryBird();

	// Virtual Functions
	void Render();
	void Update();
	void Initialize();	
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }

	// Non-Virtual Functions
	void AddVelocity(float _Speed);
	void AddRotation(float _Angle);
	void SetPosition(b2Vec2 _position);
	float GetVibrateRate() { return m_fVibrationRate; };	
	void SetPicked(bool _bool);
	bool GetPicked() const;
	

private:
	bool m_picked;	
	float m_fVibrationRate;

		
};

