#pragma once
#include "BaseLevel.h"

class TextLabel;
class Entity;
class Camera;
class Sprite;
class LevelMenu : public BaseLevel
{
public:
	LevelMenu();
	~LevelMenu();

	void InitializeObjects();
	void RenderObjects();
	void ProcessLevel(float _DeltaTick);

private:
	std::shared_ptr<TextLabel> m_PlayText;
	std::vector<std::shared_ptr<TextLabel>> m_TextLabels;
};

