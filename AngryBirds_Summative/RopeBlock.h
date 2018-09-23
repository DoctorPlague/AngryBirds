#pragma once
#include "Utilities.h"
#include "Entity.h"

class WoodBlock;
class RopeBlock : public Entity
{
public:
	RopeBlock();
	~RopeBlock();

	// Virtual Functions
	void Render();
	void Update(float _DeltaTick);
	void Initialize();
	glm::vec2 GetPosition() { return glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y); }
	int GetEntityType() { return ENTITY_WOODBLOCK; }
	b2Body* GetBody() { return m_body; }

	void SetBlockOnePosition(b2Vec2 _position);
	void SetBlockTwoPosition(b2Vec2 _position);
	void SetBlockOneRotation(float _rotation);
	void SetBlockTwoRotation(float _rotation);
	void SetPosition(b2Vec2 _position);
	void SetRotation(float _angle);

	std::shared_ptr<WoodBlock> GetBlockOne();
	std::shared_ptr<WoodBlock> GetBlockTwo();


private:
	std::shared_ptr<WoodBlock> m_blockOne;
	std::shared_ptr<WoodBlock> m_blockTwo;	
};

