// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	LevelThree.h
// Description	:	LevelThree header file

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
	std::vector<std::shared_ptr<AngryBird>> m_angryBirdsVec;

	// Contains all GreenPigs
	std::vector<std::shared_ptr<GreenPig>> m_greenPigsVec;

	// Other Entities
	std::shared_ptr<PulleyBlock> m_pulleyBlock;
	std::shared_ptr<AngryBird> m_thrownBird;
	std::shared_ptr<GroundBox> m_groundBox;
	std::shared_ptr<SlingShot> m_slingShot;

	//Textlabels
	std::shared_ptr<TextLabel> m_restartText;	
};

