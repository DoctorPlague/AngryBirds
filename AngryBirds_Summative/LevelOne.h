#pragma once
#include "Utilities.h"

class SlingShot;
class Entity;
class AngryBird;
class Camera;
class Sprite;
class Input;
class GroundBox;
class LevelOne	
{
public:
	LevelOne();
	~LevelOne();

	void InitializeObjects();
	void RenderObjects();
	void ProcessLevel(float _DeltaTick);

	// Mouse world position
	void UpdateMouseWorldPos();
	// Mouse Picking
	bool CheckMousePicking(glm::vec2 _position, float _radius);


private:	
	glm::vec2 m_mousePos;	
	bool m_birdHeld;

	// Contains all entities, for rendering and updating purposes
	std::vector<std::shared_ptr<Entity>> m_EntityVec;	

	// Contains all AngryBirds, for mouse picking etc purposes
	std::vector<std::shared_ptr<AngryBird>> m_AngryBirdsVec;

	// Other Entities
	std::shared_ptr<GroundBox> m_GroundBox;
	std::shared_ptr<SlingShot> m_SlingShot;
	std::shared_ptr<Sprite> m_Background;
	std::shared_ptr<Camera> m_Camera;	
};

