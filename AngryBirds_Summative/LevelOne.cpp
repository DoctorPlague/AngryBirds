#include "LevelOne.h"
#include "Sprite.h"
#include "Camera.h"
#include "Utilities.h"
#include "AngryBird.h"
#include "Physics.h"
#include "GroundBox.h"
#include "SlingShot.h"
#include "WoodBlock.h"
#include "GreenPig.h"
#include "StoneBlock.h"
#include "KeyboardInput.h"

LevelOne::LevelOne()
{
	m_Background = std::make_shared<Sprite>();	
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();	
	m_birdHeld = false;
}

LevelOne::~LevelOne()
{
}

void LevelOne::InitializeObjects()
{
	// Initialize Scene Background	
	m_Background->Initialize("Resources/Images/BackgroundTexture.png");

	// Initialize Other Objects..
	// Push objects to their appropriate vectors	

	// Create Birds
	std::shared_ptr<AngryBird> TempBird;

	// Bird 0
	TempBird = std::make_shared<AngryBird>();
	TempBird->SetPosition(b2Vec2(5.0f, 8.5f));
	m_EntityVec.push_back(TempBird);
	m_AngryBirdsVec.push_back(TempBird);

	// Bird 1
	TempBird = std::make_shared<AngryBird>();
	TempBird->SetPosition(b2Vec2(6.0f, 8.5f));
	m_EntityVec.push_back(TempBird);
	m_AngryBirdsVec.push_back(TempBird);
	
	// Bird 2
	TempBird = std::make_shared<AngryBird>();
	TempBird->SetPosition(b2Vec2(7.0f, 8.5f));
	m_EntityVec.push_back(TempBird);
	m_AngryBirdsVec.push_back(TempBird);
	
	// Bird 3
	TempBird = std::make_shared<AngryBird>();
	TempBird->SetPosition(b2Vec2(8.0f, 8.5f));
	m_EntityVec.push_back(TempBird);
	m_AngryBirdsVec.push_back(TempBird);

	// GroundBox
	m_GroundBox = std::make_shared<GroundBox>();
	m_GroundBox->SetPosition(b2Vec2(8.0f, 2.3f));
	m_EntityVec.push_back(m_GroundBox);

	// SlingShot
	m_SlingShot = std::make_shared<SlingShot>();
	m_SlingShot->SetPosition(b2Vec2(3.0f, 3.8f));
	m_EntityVec.push_back(m_SlingShot);

	// StoneBlocks
	std::shared_ptr<StoneBlock> TempsStoneBlock;
	TempsStoneBlock = std::make_shared<StoneBlock>();
	TempsStoneBlock->SetPosition(b2Vec2(12.0f, 3.8f));
	TempsStoneBlock->SetRotation(ConvertToRadian(0.0f));
	m_EntityVec.push_back(TempsStoneBlock);

	TempsStoneBlock = std::make_shared<StoneBlock>();
	TempsStoneBlock->SetPosition(b2Vec2(10.5f, 3.8f));
	TempsStoneBlock->SetRotation(ConvertToRadian(90.0f));
	m_EntityVec.push_back(TempsStoneBlock);

	TempsStoneBlock = std::make_shared<StoneBlock>();
	TempsStoneBlock->SetPosition(b2Vec2(13.5f, 3.8f));
	TempsStoneBlock->SetRotation(ConvertToRadian(90.0f));
	m_EntityVec.push_back(TempsStoneBlock);

	// WoodBlocks
	std::shared_ptr<WoodBlock> TempBlock;
	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(11.0f, 5.8f));	
	TempBlock->SetRotation(ConvertToRadian(90.0f));
	m_EntityVec.push_back(TempBlock);

	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(13.0f, 5.8f));
	TempBlock->SetRotation(ConvertToRadian(90.0f));
	m_EntityVec.push_back(TempBlock);

	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(12.0f, 6.9f));	
	m_EntityVec.push_back(TempBlock);

	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(12.3f, 8.0f));
	TempBlock->SetRotation(ConvertToRadian(90.0f));
	m_EntityVec.push_back(TempBlock);

	TempBlock = std::make_shared<WoodBlock>();
	TempBlock->SetPosition(b2Vec2(11.7f, 8.0f));
	TempBlock->SetRotation(ConvertToRadian(90.0f));
	m_EntityVec.push_back(TempBlock);

	// GreenPigs
	std::shared_ptr<GreenPig> TempPig;
	TempPig = std::make_shared<GreenPig>();
	TempPig->SetPosition(b2Vec2(12.0f, 4.8f));
	TempPig->SetRotation(ConvertToRadian(0.0f));
	m_EntityVec.push_back(TempPig);
	m_GreenPigsVec.push_back(TempPig);


	// Iterate through the entity vector and initialize all objects
	if (!m_EntityVec.empty())
	{
		for (unsigned int i = 0; i < m_EntityVec.size(); i++)
		{
			m_EntityVec[i]->Initialize();
		}
	}	
}

void LevelOne::ProcessLevel(float _DeltaTick) {

	// Process Physics
	Physics::GetInstance()->Process();	

	// Update entities
	if (!m_EntityVec.empty())
	{
		for (const auto& it : m_EntityVec)
		{
			it->Update();			
		}
	}	

	// Process AngryBird stuff..
	if (!m_AngryBirdsVec.empty())
	{	
		// Count the birds avaliable for fire
		m_birdsRemaining = static_cast<int>(m_AngryBirdsVec.size());

		bool bLoaded = m_SlingShot->GetLoaded();
		if (bLoaded)
		{
			// Set the birds position to the slingshot
			if (m_birdsRemaining > 0)
			{
				glm::vec2 LoadedBirdPosition = glm::vec2(m_SlingShot->GetPosition().x, m_SlingShot->GetPosition().y + 1.0f);
				LoadedBirdPosition = glm::mix(LoadedBirdPosition, m_mousePos, 0.9f);
				// Set the birds position just to the left of the slingshot
				// Clamp the y value to avoid overlap with ground
				m_AngryBirdsVec[m_birdsRemaining - 1]->SetPosition(b2Vec2(
						   glm::clamp(LoadedBirdPosition.x, m_SlingShot->GetPosition().x - 2.0f, m_SlingShot->GetPosition().x),
						   glm::clamp(LoadedBirdPosition.y, m_GroundBox->GetPosition().y + 0.65f, 9.0f))
				);
			}

			// If the mouse is released, launch the bird
			if (Input::GetInstance()->MouseState[0] == INPUT_RELEASED)
			{
				// Get distance between draw origin and release position
				glm::vec2 ReleasePosition = m_AngryBirdsVec.back()->GetPosition();
				glm::vec2 DrawOrigin = glm::vec2(m_SlingShot->GetPosition().x - 0.4f, m_SlingShot->GetPosition().y + 0.8f);
				float fDistance = glm::distance(ReleasePosition, DrawOrigin);
				glm::vec2 Direction = glm::normalize(DrawOrigin - ReleasePosition);

				// Apply impulse to loaded bird				
				m_AngryBirdsVec.back()->SetLinearVelocity(Direction * (fDistance * 15.0f));

				// Remove the bird from the bird vec
				m_AngryBirdsVec.pop_back();
				m_birdsRemaining--;

				m_SlingShot->SetLoaded(false);
			}			
		}
		else
		{
			// Check for mouse click
			if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS && m_birdsRemaining > 0)
			{
				m_SlingShot->SetLoaded(true);
			}
		}			
	}

	// Updating input
	Input::GetInstance()->Update();
	
	// Update mouse position
	m_mousePos = Input::GetInstance()->GetMouseWorldPos();
}

bool LevelOne::CheckMousePicking(glm::vec2 _position, float _radius)
{
	if (glm::distance(_position, m_mousePos) <= _radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_Background->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_EntityVec.empty())
	{
		for (const auto& it : m_EntityVec)
		{
			it->Render();
			it->DrawDebug();
		}
	}	
}
