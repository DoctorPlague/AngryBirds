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
#include "GlassBlock.h"
#include "DualWoodBlock.h"
#include "RopeBlock.h"
#include "PulleyBlock.h"
#include "KeyboardInput.h"

LevelOne::LevelOne()
{
	m_Background = std::make_shared<Sprite>();	
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();	
	m_birdHeld = false;
	m_ThrownBird = nullptr;
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
	TempBird = std::make_shared<AngryBird>(HEAVY);
	TempBird->SetPosition(b2Vec2(5.0f, 4.5f));
	m_EntityVec.push_back(TempBird);
	m_AngryBirdsVec.push_back(TempBird);

	// Bird 1
	TempBird = std::make_shared<AngryBird>(DIVER);
	TempBird->SetPosition(b2Vec2(6.0f, 4.5f));
	m_EntityVec.push_back(TempBird);
	m_AngryBirdsVec.push_back(TempBird);
	
	// Bird 2
	TempBird = std::make_shared<AngryBird>(BOUNCER);
	TempBird->SetPosition(b2Vec2(7.0f, 4.5f));
	m_EntityVec.push_back(TempBird);
	m_AngryBirdsVec.push_back(TempBird);
	
	// Bird 3
	TempBird = std::make_shared<AngryBird>(NORMAL);
	TempBird->SetPosition(b2Vec2(8.0f, 4.5f));
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

	// GlassBlocks
	std::shared_ptr<GlassBlock> TempGlassBlock;
	TempGlassBlock = std::make_shared<GlassBlock>();
	TempGlassBlock->SetPosition(b2Vec2(9.0f, 3.8f));
	TempGlassBlock->SetRotation(ConvertToRadian(90.0f));
	m_EntityVec.push_back(TempGlassBlock);

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

	// DualWoodBlocks
	//std::shared_ptr<DualWoodBlock> TempDualBlock = std::make_shared<DualWoodBlock>();	
	//TempDualBlock->SetBlockOnePosition(b2Vec2(5.0f, 5.8f));
	//TempDualBlock->SetBlockTwoPosition(b2Vec2(7.0f, 5.8f));
	//TempDualBlock->SetBlockOneRotation(ConvertToRadian(90.0f));
	//TempDualBlock->SetBlockTwoRotation(ConvertToRadian(0.0f));
	//m_EntityVec.push_back(TempDualBlock->GetBlockOne());
	//m_EntityVec.push_back(TempDualBlock->GetBlockTwo());

	// RopeBlocks
	//std::shared_ptr<RopeBlock> TempRopeBlock;
	//TempRopeBlock = std::make_shared<RopeBlock>();
	//TempRopeBlock->SetPosition(b2Vec2(6.0f, 8.8f));
	//TempRopeBlock->SetRotation(ConvertToRadian(0.0f));
	//m_EntityVec.push_back(TempRopeBlock);
	//TempRopeBlock->SetBlockOnePosition(b2Vec2(5.0f, 4.8f));
	//TempRopeBlock->SetBlockTwoPosition(b2Vec2(7.0f, 4.8f));
	//TempRopeBlock->SetBlockOneRotation(ConvertToRadian(90.0f));
	//TempRopeBlock->SetBlockTwoRotation(ConvertToRadian(90.0f));
	//m_EntityVec.push_back(TempRopeBlock->GetBlockOne());
	//m_EntityVec.push_back(TempRopeBlock->GetBlockTwo());

	// PulleyBlocks	
	//m_PulleyBlock = std::make_shared<PulleyBlock>(b2Vec2(6.0f, 3.8f), b2Vec2(7.0f, 3.8f));
	//m_PulleyBlock->SetBlockOneRotation(ConvertToRadian(90.0f));
	//m_PulleyBlock->SetBlockTwoRotation(ConvertToRadian(90.0f));
	//m_EntityVec.push_back(m_PulleyBlock->GetBlockOne());
	//m_EntityVec.push_back(m_PulleyBlock->GetBlockTwo());

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
		for (int i = 0; i < m_EntityVec.size(); i++)
		{
			int iEntityType = m_EntityVec[i]->GetEntityType();
			switch (iEntityType)
			{
			case ENTITY_GREENPIG:
			{
				// If the green pig is not alive, erase it
				if (!std::static_pointer_cast<GreenPig>(m_EntityVec[i])->GetAlive())
				{
					m_EntityVec.erase(m_EntityVec.begin() + i);
					continue;
				}
				break;
			}
			case ENTITY_GLASSBLOCK:
			{
				// If the glass block has been destroyed, erase it
				if (std::static_pointer_cast<GlassBlock>(m_EntityVec[i])->GetDestroyed())
				{
					m_EntityVec.erase(m_EntityVec.begin() + i);
					continue;
				}
				break;
			}
			}			
			
			m_EntityVec[i]->Update(_DeltaTick);
		}		
	}

	// Process Pulley Block
	m_PulleyBlock->Update();

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

				// Apply impulse to loaded bird	and set thrown true			
				m_AngryBirdsVec.back()->SetLinearVelocity(Direction * (fDistance * 15.0f));
				m_AngryBirdsVec.back()->SetThrown(true);

				// Set the thrown bird variable to the bird we just threw
				m_ThrownBird = m_AngryBirdsVec.back();

				// Remove the bird from the bird vec
				m_AngryBirdsVec.pop_back();
				m_birdsRemaining--;

				// Set the slingshot to unloaded
				m_SlingShot->SetLoaded(false);
			}			
		}
		else
		{
			// Check that no bird is ccurrently being thrown
			if (m_ThrownBird == nullptr)
			{
				// Check for mouse click			
				if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS && m_birdsRemaining > 0)
				{
					m_SlingShot->SetLoaded(true);
				}
			}			
		}			
	}

	// Process the thrown bird if one is thrown currently
	if (m_ThrownBird != nullptr)
	{
		// Check for spacebar pressed		
		if (Input::GetInstance()->KeyState[32] == INPUT_FIRST_PRESS)
		{
			m_ThrownBird->SpecialAbility();
		}

		// If the bird is dead/not thrown anymore, set it to nullptr
		if (!m_ThrownBird->GetThrown())
		{
			m_ThrownBird = nullptr;
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
