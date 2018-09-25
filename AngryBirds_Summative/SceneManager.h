#pragma once
#include <vector>
#include <memory>


enum SceneState
{
	MENU_SCENE,
	LEVEL1_SCENE,
	LEVEL2_SCENE,
	LEVEL3_SCENE
};

//Forward Declarations
class LevelThree;
class LevelTwo;
class LevelOne;
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
	SceneState m_CurrentScene;		
	std::shared_ptr<LevelOne> m_LevelOneScene;
	std::shared_ptr<LevelTwo> m_LevelTwoScene;
	std::shared_ptr<LevelThree> m_LevelThreeScene;
	std::shared_ptr<LevelMenu> m_LevelMenuScene;
	//CClock singleton reference
	std::shared_ptr<CClock> m_Clock;
};

