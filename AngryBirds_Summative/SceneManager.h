// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	SceneManager.h
// Description	:	SceneManager header file

#pragma once
#include <vector>
#include <memory>


enum SceneState
{
	MENU_SCENE,
	LEVEL1_SCENE,
	LEVEL2_SCENE,
	LEVEL3_SCENE,
	LEVELFINISHED_SCENE,
	LEVELFAILED_SCENE
};

//Forward Declarations
class LevelThree;
class LevelTwo;
class LevelOne;
class LevelFailed;
class LevelFinish;
class LevelMenu;
class Input;
class CClock;

class SceneManager
{
#pragma region Singleton
public:
	static std::shared_ptr<SceneManager> GetInstance();
	static void DestroyInstance();
	~SceneManager();
private:
	static std::shared_ptr<SceneManager> s_pSceneManager;
	SceneManager(SceneManager const&);
	void operator=(SceneManager const&);
	SceneManager();
#pragma endregion

public:
	void SetCurrentScene(SceneState);	
	void InitializeScene(SceneState);
	void RenderCurrentScene();
	void UpdateCurrentScene();

private:
	SceneState m_currentScene;		
	std::shared_ptr<LevelOne> m_levelOneScene;
	std::shared_ptr<LevelTwo> m_levelTwoScene;
	std::shared_ptr<LevelThree> m_levelThreeScene;
	std::shared_ptr<LevelMenu> m_levelMenuScene;
	std::shared_ptr<LevelFailed> m_levelFailedScene;
	std::shared_ptr<LevelFinish> m_levelFinishedScene;
	//CClock singleton reference
	std::shared_ptr<CClock> m_clock;
};

