#pragma once
#include "Utilities.h"

class PulleyBlock;
class GreenPig;
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

	// Mouse Picking
	bool CheckMousePicking(glm::vec2 _position, float _radius);


private:	
	glm::vec2 m_mousePos;	
	bool m_birdHeld;
	int m_birdsRemaining;

	// Contains all entities, for rendering and updating purposes
	std::vector<std::shared_ptr<Entity>> m_EntityVec;	

	// Contains all AngryBirds, for mouse picking etc purposes
	std::vector<std::shared_ptr<AngryBird>> m_AngryBirdsVec;	

	// Contains all GreenPigs
	std::vector<std::shared_ptr<GreenPig>> m_GreenPigsVec;

	// Other Entities
	std::shared_ptr<PulleyBlock> m_PulleyBlock;
	std::shared_ptr<AngryBird> m_ThrownBird;
	std::shared_ptr<GroundBox> m_GroundBox;
	std::shared_ptr<SlingShot> m_SlingShot;
	std::shared_ptr<Sprite> m_Background;
	std::shared_ptr<Camera> m_Camera;	
};

