#pragma once
#include "Utilities.h"
#include "ShaderLoader.h"

enum EntityType
{
	ENTITY_WOODBLOCK,
	ENTITY_STONEBLOCK,
	ENTITY_ANGRYBIRD,
	ENTITY_GREENPIG,
	ENTITY_SLINGSHOT,
	ENTITY_GROUNDBOX,
	ENTITY_GLASSBLOCK,
	ENTITY_ROPEBLOCK,
	ENTITY_PULLEYBLOCK
};

class Sprite;
class Entity
{
public:
	Entity();	
	virtual ~Entity();

	// Pure Virtual Functions
	virtual void Render() = 0;
	virtual void Update(float _DeltaTick) = 0;
	virtual void Initialize() = 0;
	virtual glm::vec2 GetPosition() = 0;
	virtual void DrawDebug();
	virtual int GetEntityType() = 0;
	virtual b2Body* GetBody() = 0;

	// Entity Functions
	

protected:
	std::shared_ptr<Sprite> m_Sprite;
	glm::vec3 m_Scale;
	glm::vec3 m_RotationAxis;

	// Physics Variables
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;


private:
	// Member Variables

	// Variables for Debug Drawing
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_program;
	ShaderLoader m_shaderLoader;
};

