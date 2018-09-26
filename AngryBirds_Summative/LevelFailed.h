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

