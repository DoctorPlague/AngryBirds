// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	Entity.h
// Description	:	Entity header file

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
	std::shared_ptr<Sprite> m_sprite;
	glm::vec3 m_scale;
	glm::vec3 m_rotationAxis;

	// Physics Variables
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	bool m_bBodyDestroyed; // if the body has been destroyed


private:
	// Member Variables

	// Variables for Debug Drawing
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_program;
	ShaderLoader m_shaderLoader;
};

