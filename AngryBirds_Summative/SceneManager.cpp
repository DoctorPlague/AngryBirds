// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	SceneManager.cpp
// Description	:	SceneManager c++ file

#include "SceneManager.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelMenu.h"
#include "LevelFailed.h"
#include "LevelFinish.h"
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
	m_levelMenuScene = std::make_shared<LevelMenu>();
	m_levelOneScene = std::make_shared<LevelOne>();
	m_levelTwoScene = std::make_shared<LevelTwo>();	
	m_levelThreeScene = std::make_shared<LevelThree>();
	m_levelFailedScene = std::make_shared<LevelFailed>();
	m_levelFinishedScene = std::make_shared<LevelFinish>();

	//Initializing the input manager
	Input::GetInstance()->Initialize();
	m_clock = CClock::GetInstance();
	m_clock->Initialise();
}

SceneManager::~SceneManager()
{
}

void SceneManager::RenderCurrentScene()
{
	// Need to renable blending for some reason.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	switch (m_currentScene)
	{
	case MENU_SCENE:
	{
		m_levelMenuScene->RenderObjects();
		break;
	}
	case LEVEL1_SCENE:
	{
		m_levelOneScene->RenderObjects();
		break;
	}
	case LEVEL2_SCENE:
	{
		m_levelTwoScene->RenderObjects();
		break;
	}
	case LEVEL3_SCENE:
	{
		m_levelThreeScene->RenderObjects();
		break;
	}
	case LEVELFAILED_SCENE:
	{
		m_levelFailedScene->RenderObjects();
		break;
	}
	case LEVELFINISHED_SCENE:
	{
		m_levelFinishedScene->RenderObjects();
		break;
	}
	}
}

void SceneManager::UpdateCurrentScene()
{
	m_clock->Process();
	float fDeltaTick = m_clock->GetDeltaTick() / 1000.0f;
	switch (m_currentScene) {
	case MENU_SCENE:
	{
		m_levelMenuScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVEL1_SCENE: 
	{
		m_levelOneScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVEL2_SCENE:
	{
		m_levelTwoScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVEL3_SCENE:
	{
		m_levelThreeScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVELFAILED_SCENE:
	{
		m_levelFailedScene->ProcessLevel(fDeltaTick);
		break;
	}
	case LEVELFINISHED_SCENE:
	{
		m_levelFinishedScene->ProcessLevel(fDeltaTick);
		break;
	}
	default:break;
	}
}

void SceneManager::SetCurrentScene(SceneState _scene)
{
	m_currentScene = _scene;
}

void SceneManager::InitializeScene(SceneState _scene)
{
	// Create the objects for the specified scene
	switch (_scene)
	{
	case MENU_SCENE:
	{
		m_levelMenuScene->InitializeObjects();
		break;
	}
	case LEVEL1_SCENE:
	{
		m_levelOneScene->InitializeObjects();
		break;
	}
	case LEVEL2_SCENE:
	{
		m_levelTwoScene->InitializeObjects();
		break;
	}
	case LEVEL3_SCENE:
	{
		m_levelThreeScene->InitializeObjects();
		break;
	}
	case LEVELFAILED_SCENE:
	{
		m_levelFailedScene->InitializeObjects();
		break;
	}
	case LEVELFINISHED_SCENE:
	{
		m_levelFinishedScene->InitializeObjects();
		break;
	}
	}	
}
