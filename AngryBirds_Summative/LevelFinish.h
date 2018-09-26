#pragma once
#include "BaseLevel.h"

class TextLabel;
class Entity;
class Camera;
class Sprite;
class LevelFinish :
	public BaseLevel
{
public:
	LevelFinish();
	~LevelFinish();

	void InitializeObjects();
	void RenderObjects();
	void ProcessLevel(float _DeltaTick);

private:
	std::shared_ptr<TextLabel> m_playText;
	std::shared_ptr<TextLabel> m_gameCompleteText;
};

