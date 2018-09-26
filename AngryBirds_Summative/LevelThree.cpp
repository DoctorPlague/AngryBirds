#include "LevelThree.h"
#include "Sprite.h"
#include "Camera.h"
#include "AngryBird.h"
#include "Physics.h"
#include "GroundBox.h"
#include "SlingShot.h"
#include "WoodBlock.h"
#include "GreenPig.h"
#include "StoneBlock.h"
#include "GlassBlock.h"
#include "PulleyBlock.h"
#include "KeyboardInput.h"
#include "TextLabel.h"
#include "SceneManager.h"


LevelThree::LevelThree()
{
	m_background = std::make_shared<Sprite>();
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();
	m_birdHeld = false;
	m_thrownBird = nullptr;
}


LevelThree::~LevelThree()
{
}

void LevelThree::InitializeObjects()
{
	// Initialize Scene Background	
	m_background->Initialize("Resources/Images/BackgroundTexture.png");

	// Initialize text stuff
	if (m_restartText == nullptr)
	{
		m_restartText = std::make_shared<TextLabel>("RESTART", "Resources/Fonts/arial.ttf", glm::vec2(10.0f, 860.0f)); // Play Text	
		m_restartText->SetScale(0.75f);
		m_textLabels.push_back(m_restartText);
	}

	// Initialize Other Objects..
	// Push objects to their appropriate vectors	

	// Create Birds
	std::shared_ptr<AngryBird> TempBird;

	// Bird 0
	TempBird = std::make_shared<AngryBird>(HEAVY);
	TempBird->SetPosition(b2Vec2(3.3f, 4.5f));
	m_entityVec.push_back(TempBird);
	m_angryBirdsVec.push_back(TempBird);

	// Bird 1
	TempBird = std::make_shared<AngryBird>(DIVER);
	TempBird->SetPosition(b2Vec2(3.8f, 4.5f));
	m_entityVec.push_back(TempBird);
	m_angryBirdsVec.push_back(TempBird);

	// Bird 2
	TempBird = std::make_shared<AngryBird>(BOUNCER);
	TempBird->SetPosition(b2Vec2(4.3f, 4.5f));
	m_entityVec.push_back(TempBird);
	m_angryBirdsVec.push_back(TempBird);

	// Bird 3
	TempBird = std::make_shared<AngryBird>(NORMAL);
	TempBird->SetPosition(b2Vec2(4.8f, 4.5f));
	m_entityVec.push_back(TempBird);
	m_angryBirdsVec.push_back(TempBird);

	// GroundBox
	m_groundBox = std::make_shared<GroundBox>();
	m_groundBox->SetPosition(b2Vec2(8.0f, 2.3f));
	m_entityVec.push_back(m_groundBox);

	// SlingShot
	m_slingShot = std::make_shared<SlingShot>();
	m_slingShot->SetPosition(b2Vec2(3.0f, 3.8f));
	m_entityVec.push_back(m_slingShot);

	// Pulleyblock
	m_pulleyBlock = std::make_shared<PulleyBlock>(b2Vec2(6.0f, 3.8f), b2Vec2(7.5f, 3.8f));
	m_pulleyBlock->SetBlockOneRotation(ConvertToRadian(90.0f));
	m_pulleyBlock->SetBlockTwoRotation(ConvertToRadian(90.0f));
	m_entityVec.push_back(m_pulleyBlock->GetBlockOne());
	m_entityVec.push_back(m_pulleyBlock->GetBlockTwo());

	// StoneBlocks
	std::shared_ptr<StoneBlock> TempsStoneBlock;
	TempsStoneBlock = std::make_shared<StoneBlock>();
	TempsStoneBlock->SetPosition(b2Vec2(14.0f, 4.1f));
	TempsStoneBlock->SetRotation(ConvertToRadian(90.0f));
	m_entityVec.push_back(TempsStoneBlock);

	TempsStoneBlock = std::make_shared<StoneBlock>();
	TempsStoneBlock->SetPosition(b2Vec2(14.0f, 6.1f));
	TempsStoneBlock->SetRotation(ConvertToRadian(0.0f));
	m_entityVec.push_back(TempsStoneBlock);

	// WoodBlocks
	std::shared_ptr<WoodBlock> TempBlock;
	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(13.5f, 7.5f));
	TempBlock->SetRotation(ConvertToRadian(90.0f));
	m_entityVec.push_back(TempBlock);

	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(14.5f, 7.5f));
	TempBlock->SetRotation(ConvertToRadian(90.0f));
	m_entityVec.push_back(TempBlock);

	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(14.0f, 9.8f));
	m_entityVec.push_back(TempBlock);

	// GreenPigs
	std::shared_ptr<GreenPig> TempPig;
	TempPig = std::make_shared<GreenPig>();
	TempPig->SetPosition(b2Vec2(14.0f, 7.8f));
	TempPig->SetRotation(ConvertToRadian(0.0f));
	m_entityVec.push_back(TempPig);
	m_greenPigsVec.push_back(TempPig);

	// Iterate through the entity vector and initialize all objects
	if (!m_entityVec.empty())
	{
		for (unsigned int i = 0; i < m_entityVec.size(); i++)
		{
			m_entityVec[i]->Initialize();
		}
	}
}

void LevelThree::RenderObjects()
{
	// Render Background
	m_background->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_entityVec.empty())
	{
		for (const auto& it : m_entityVec)
		{
			it->Render();
			it->DrawDebug();
		}
	}

	// Render text labels
	if (!m_textLabels.empty())
	{
		for (const auto& it : m_textLabels)
		{
			it->Render();
		}
	}
}

void LevelThree::ProcessLevel(float _DeltaTick)
{
	// Process Physics
	Physics::GetInstance()->Process();

	// Update entities
	if (!m_entityVec.empty())
	{
		for (int i = 0; i < m_entityVec.size(); i++)
		{
			int iEntityType = m_entityVec[i]->GetEntityType();
			switch (iEntityType)
			{
			case ENTITY_GREENPIG:
			{
				// If the green pig is not alive, erase it from entity vec
				if (!std::static_pointer_cast<GreenPig>(m_entityVec[i])->GetAlive())
				{
					m_entityVec.erase(m_entityVec.begin() + i);

					// also erase it from the green pigs vec
					for (int i = 0; i < m_greenPigsVec.size(); i++)
					{
						if (!m_greenPigsVec[i]->GetAlive())
						{
							m_greenPigsVec.erase(m_greenPigsVec.begin() + i);
							continue;
						}
					}
					continue;
				}
				break;
			}
			case ENTITY_GLASSBLOCK:
			{
				// If the glass block has been destroyed, erase it
				if (std::static_pointer_cast<GlassBlock>(m_entityVec[i])->GetDestroyed())
				{
					m_entityVec.erase(m_entityVec.begin() + i);
					continue;
				}
				break;
			}
			}

			m_entityVec[i]->Update(_DeltaTick);
		}
	}

	// Process Pulley Block
	m_pulleyBlock->Update(_DeltaTick);

	// Process AngryBird stuff..
	if (!m_angryBirdsVec.empty())
	{
		// Count the birds avaliable for fire
		m_birdsRemaining = static_cast<int>(m_angryBirdsVec.size());

		bool bLoaded = m_slingShot->GetLoaded();
		if (bLoaded)
		{
			// Set the birds position to the slingshot
			if (m_birdsRemaining > 0)
			{
				glm::vec2 LoadedBirdPosition = glm::vec2(m_slingShot->GetPosition().x, m_slingShot->GetPosition().y + 1.0f);
				LoadedBirdPosition = glm::mix(LoadedBirdPosition, m_mousePos, 0.9f);
				// Set the birds position just to the left of the slingshot
				// Clamp the y value to avoid overlap with ground
				m_angryBirdsVec[m_birdsRemaining - 1]->SetPosition(b2Vec2(
					glm::clamp(LoadedBirdPosition.x, m_slingShot->GetPosition().x - 2.0f, m_slingShot->GetPosition().x),
					glm::clamp(LoadedBirdPosition.y, m_groundBox->GetPosition().y + 0.65f, 9.0f))
				);
			}

			// If the mouse is released, launch the bird
			if (Input::GetInstance()->MouseState[0] == INPUT_RELEASED)
			{
				// Get distance between draw origin and release position
				glm::vec2 ReleasePosition = m_angryBirdsVec.back()->GetPosition();
				glm::vec2 DrawOrigin = glm::vec2(m_slingShot->GetPosition().x - 0.4f, m_slingShot->GetPosition().y + 0.8f);
				float fDistance = glm::distance(ReleasePosition, DrawOrigin);
				glm::vec2 Direction = glm::normalize(DrawOrigin - ReleasePosition);

				// Apply impulse to loaded bird	and set thrown true			
				m_angryBirdsVec.back()->SetLinearVelocity(Direction * (fDistance * 15.0f));
				m_angryBirdsVec.back()->SetThrown(true);

				// Set the thrown bird variable to the bird we just threw
				m_thrownBird = m_angryBirdsVec.back();

				// Remove the bird from the bird vec
				m_angryBirdsVec.pop_back();
				m_birdsRemaining--;

				// Set the slingshot to unloaded
				m_slingShot->SetLoaded(false);
			}
		}
		else
		{
			// Check that no bird is ccurrently being thrown
			if (m_thrownBird == nullptr)
			{
				// Check for mouse click			
				if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS && m_birdsRemaining > 0)
				{
					m_slingShot->SetLoaded(true);
				}
			}
		}
	}	

	// Process the thrown bird if one is thrown currently
	if (m_thrownBird != nullptr)
	{
		// Check for spacebar pressed		
		if (Input::GetInstance()->KeyState[32] == INPUT_FIRST_PRESS)
		{
			m_thrownBird->SpecialAbility();
		}

		// If the bird is dead/not thrown anymore, set it to nullptr
		if (!m_thrownBird->GetThrown())
		{
			m_thrownBird = nullptr;
		}
	}

	// Check if the level is complete
	if (m_greenPigsVec.empty())
	{
		// Destroy everything in the scene
		DestroyLevel();

		// Transition to the next level
		SceneManager::GetInstance()->SetCurrentScene(LEVELFINISHED_SCENE);
		SceneManager::GetInstance()->InitializeScene(LEVELFINISHED_SCENE);
	}
	else if (m_angryBirdsVec.empty() && m_thrownBird == nullptr && !m_greenPigsVec.empty())
	{
		// Angry birds vec empty 
		// Destroy everything in the scene
		DestroyLevel();

		// Transition to the next level
		SceneManager::GetInstance()->SetCurrentScene(LEVELFAILED_SCENE);
		SceneManager::GetInstance()->InitializeScene(LEVELFAILED_SCENE);
	}

	// Check for mouse click			
	if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS)
	{
		bool bRestartCheck = CheckMousePicking(glm::vec2(
			(m_restartText->GetPosition().x + 60.0f) / 100.0f,
			(m_restartText->GetPosition().y + 24.0f) / 100.0f),
			1.3f);

		if (bRestartCheck)
		{
			// Destroy everything in the scene
			DestroyLevel();

			// Transition to the next level
			SceneManager::GetInstance()->SetCurrentScene(MENU_SCENE);
			SceneManager::GetInstance()->InitializeScene(MENU_SCENE);
		}
	}

	// Updating input
	Input::GetInstance()->Update();

	// Update mouse position
	m_mousePos = Input::GetInstance()->GetMouseWorldPos();
}

void LevelThree::DestroyLevel()
{
	for (int i = 0; i < m_entityVec.size(); i++)
	{
		m_entityVec[i].reset();
		m_entityVec.erase(m_entityVec.begin() + i);
	}
	for (int i = 0; i < m_angryBirdsVec.size(); i++)
	{
		m_angryBirdsVec[i].reset();
		m_angryBirdsVec.erase(m_angryBirdsVec.begin() + i);
	}
	for (int i = 0; i < m_greenPigsVec.size(); i++)
	{
		m_greenPigsVec[i].reset();
		m_greenPigsVec.erase(m_greenPigsVec.begin() + i);
	}
	for (int i = 0; i < m_textLabels.size(); i++)
	{
		m_textLabels[i].reset();
		m_textLabels.erase(m_textLabels.begin() + i);
	}

	m_thrownBird = nullptr;
	m_entityVec.clear();
	m_angryBirdsVec.clear();
	m_greenPigsVec.clear();
	m_textLabels.clear();
	m_groundBox.reset();
	m_slingShot.reset();
	m_pulleyBlock.reset();
}
