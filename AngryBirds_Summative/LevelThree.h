#pragma once
#include "BaseLevel.h"

class TextLabel;
class PulleyBlock;
class GreenPig;
class SlingShot;
class Entity;
class AngryBird;
class Camera;
class Sprite;
class GroundBox;
class LevelThree :
	public BaseLevel
{
public:
	LevelThree();
	~LevelThree();

	void InitializeObjects();
	void RenderObjects();
	void ProcessLevel(float _DeltaTick);
	void DestroyLevel();

private:
	bool m_birdHeld;
	int m_birdsRemaining;

	// Contains all AngryBirds, for mouse picking etc purposes
	std::vector<std::shared_ptr<AngryBird>> m_AngryBirdsVec;

	// Contains all GreenPigs
	std::vector<std::shared_ptr<GreenPig>> m_GreenPigsVec;

	// Other Entities
	std::shared_ptr<PulleyBlock> m_PulleyBlock;
	std::shared_ptr<AngryBird> m_ThrownBird;
	std::shared_ptr<GroundBox> m_GroundBox;
	std::shared_ptr<SlingShot> m_SlingShot;

	//Textlabels
	std::shared_ptr<TextLabel> m_RestartText;
	std::vector<std::shared_ptr<TextLabel>> m_TextLabels;
};

