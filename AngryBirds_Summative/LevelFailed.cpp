#include "LevelFailed.h"
#include "Sprite.h"
#include "Camera.h"
#include "Entity.h"
#include "KeyboardInput.h"
#include "TextLabel.h"
#include "SceneManager.h"



LevelFailed::LevelFailed()
{
	m_background = std::make_shared<Sprite>();
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();
}


LevelFailed::~LevelFailed()
{
}

void LevelFailed::InitializeObjects()
{
	// Initialize Scene Background	
	m_background->Initialize("Resources/Images/BackgroundTexture.png");

	m_playText = std::make_shared<TextLabel>("PLAY", "Resources/Fonts/arial.ttf", glm::vec2(190.0f, 350.0f)); // Play Text	
	m_textLabels.push_back(m_playText);
	m_gameLostText = std::make_shared<TextLabel>("You lost the game, try again!", "Resources/Fonts/arial.ttf", glm::vec2(550.0f, 550.0f)); // Play Text	
	m_textLabels.push_back(m_gameLostText);
}

void LevelFailed::RenderObjects()
{
	// Render Background
	m_background->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center	

	if (!m_textLabels.empty())
	{
		for (const auto& it : m_textLabels)
		{
			it->Render();
		}
	}
}

void LevelFailed::ProcessLevel(float _DeltaTick)
{
	// Check for mouse click			
	if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS)
	{
		bool bPlayCheck = CheckMousePicking(glm::vec2(
			(m_playText->GetPosition().x + 60.0f) / 100.0f,
			(m_playText->GetPosition().y + 24.0f) / 100.0f),
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
