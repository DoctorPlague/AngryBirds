#include "SceneManager.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelMenu.h"
#include "Sprite.h"
#include "clock.h"
#include "KeyboardInput.h"

std::shared_ptr<SceneManager> SceneManager::s_pSceneManager;

std::shared_ptr<SceneManager> SceneManager::GetInstance()
{
	if (!s_pSceneManager)
	{
		s_pSceneManager = std::shared_ptr<SceneManager>(new SceneManager());
	}
	return s_pSceneManager;
}

void SceneManager::DestroyInstance()
{
	s_pSceneManager.reset();
	//s_pSceneManager = nullptr;
}

SceneManager::SceneManager()
{
	m_LevelMenuScene = std::make_shared<LevelMenu>();
	m_LevelOneScene = std::make_shared<LevelOne>();
	m_LevelTwoScene = std::make_shared<LevelTwo>();	
	m_LevelThreeScene = std::make_shared<LevelThree>();

	//Initializing the input manager
	Input::GetInstance()->Initialize();
	m_Clock = CClock::GetInstance();
	m_Clock->Initialise();
}

SceneManager::~SceneManager()
{
}

void SceneManager::RenderCurrentScene()
{
	// Need to renable blending for some reason.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	switch (m_CurrentScene)
	{
	case MENU_SCENE:
	{
		m_LevelMenuScene->RenderObjects();
		break;
	}
	case LEVEL1_SCENE:
	{
		m_LevelOneScene->RenderObjects();
		break;
	}
	case LEVEL2_SCENE:
	{
		m_LevelTwoScene->RenderObjects();
		break;
	}
	case LEVEL3_SCENE:
	{
		m_LevelThreeScene->RenderObjects();
		break;
	}
	}
}

void SceneManager::UpdateCurrentScene()
{
	m_Clock->Process();
	float fDeltaTick = m_Clock->GetDeltaTick() / 1000.0f;
	switch (m_CurrentScene) {
	case MENU_SCENE:
	{
		m_LevelMenuScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVEL1_SCENE: 
	{
		m_LevelOneScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVEL2_SCENE:
	{
		m_LevelTwoScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVEL3_SCENE:
	{
		m_LevelThreeScene->ProcessLevel(fDeltaTick);
		break;
	}
	default:break;
	}
}

void SceneManager::SetCurrentScene(SceneState _scene)
{
	m_CurrentScene = _scene;
}

void SceneManager::InitializeScene(SceneState _scene)
{
	// Create the objects for the specified scene
	switch (_scene)
	{
	case MENU_SCENE:
	{
		m_LevelMenuScene->InitializeObjects();
		break;
	}
	case LEVEL1_SCENE:
	{
		m_LevelOneScene->InitializeObjects();
		break;
	}
	case LEVEL2_SCENE:
	{
		m_LevelTwoScene->InitializeObjects();
		break;
	}
	case LEVEL3_SCENE:
	{
		m_LevelThreeScene->InitializeObjects();
		break;
	}
	}	
}
