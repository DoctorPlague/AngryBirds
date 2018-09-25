#include "LevelMenu.h"
#include "Sprite.h"
#include "Camera.h"
#include "Entity.h"
#include "KeyboardInput.h"
#include "TextLabel.h"
#include "SceneManager.h"

LevelMenu::LevelMenu()
{
	m_Background = std::make_shared<Sprite>();
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();
}


LevelMenu::~LevelMenu()
{
	
}

void LevelMenu::InitializeObjects()
{
	// Initialize Scene Background	
	m_Background->Initialize("Resources/Images/BackgroundTexture.png");

	m_PlayText = std::make_shared<TextLabel>("PLAY", "Resources/Fonts/arial.ttf", glm::vec2(190.0f, 350.0f)); // Play Text	
	m_TextLabels.push_back(m_PlayText);
}

void LevelMenu::RenderObjects()
{
	// Render Background
	m_Background->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center	

	if (!m_TextLabels.empty())
	{
		for (const auto& it : m_TextLabels)
		{
			it->Render();
		}
	}
}

void LevelMenu::ProcessLevel(float _DeltaTick)
{
	// Check for mouse click			
	if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS)
	{
		bool bPlayCheck = CheckMousePicking(glm::vec2(
			(m_PlayText->GetPosition().x + 60.0f) / 100.0f,
			(m_PlayText->GetPosition().y + 24.0f) / 100.0f),
			1.3f);

		if (bPlayCheck)
		{						
			SceneManager::GetInstance()->SetCurrentScene(LEVEL1_SCENE);
			SceneManager::GetInstance()->InitializeScene(LEVEL1_SCENE);						
		}
	}

	// Updating input
	Input::GetInstance()->Update();

	// Update mouse position
	m_mousePos = Input::GetInstance()->GetMouseWorldPos();		 
}
