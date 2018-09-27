// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	LevelFailed.h
// Description	:	LevelFailed header file

#pragma once
#include "BaseLevel.h"

class TextLabel;
class Entity;
class Camera;
class Sprite;
class LevelFailed :
	public BaseLevel
{
public:
	LevelFailed();
	~LevelFailed();

	void InitializeObjects();
	void RenderObjects();
	void ProcessLevel(float _DeltaTick);

private:
	std::shared_ptr<TextLabel> m_playText;
	std::shared_ptr<TextLabel> m_gameLostText;
};

