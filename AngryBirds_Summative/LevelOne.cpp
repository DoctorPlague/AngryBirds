#include "LevelOne.h"
#include "Sprite.h"
#include "Camera.h"
#include "Utilities.h"
#include "AngryBird.h"
#include "Physics.h"
#include "GroundBox.h"
#include "SlingShot.h"
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
	m_SlingShot->SetPosition(b2Vec2(3.0f, 4.3f));
	m_EntityVec.push_back(m_SlingShot);

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

	//Updating the keyboard input
	Input::Update();	

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
		// NOTE: Might want to replace direct transformation with drawing the bird towards the mouse with forces

		//// Process Picking up and Dropping
		// If no bird is held
		if (m_birdHeld)
		{
			// if left click pressed, cycle through all birds and set them all to not picked up
			if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS)
			{
				Input::GetInstance()->MouseState[0] = INPUT_HOLD;
				m_birdHeld = false;

				// Reset all birds to not picked
				for (const auto& it : m_AngryBirdsVec)
				{
					it->SetPicked(false);
				}
			}
		}

		// Do Mouse picking on the birds
		float fRadius = 0.15f;		
		if (Input::GetInstance()->MouseState[0] == INPUT_FIRST_PRESS && !m_birdHeld)
		{
			Input::GetInstance()->MouseState[0] = INPUT_HOLD;
			for (const auto& it0 : m_AngryBirdsVec)
			{
				if (CheckMousePicking(it0->GetPosition(), fRadius))
				{
					it0->SetPicked(true);
					m_birdHeld = true;
				}
			}
		}

		
	}
}

void LevelOne::UpdateMouseWorldPos()
{
	//screen pos
	glm::vec2 normalizedScreenPos = glm::vec2(Input::GetInstance()->GetMousePos().x, Input::GetInstance()->GetMousePos().y);

	//screenpos to Proj Space
	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	//Proj Space to eye space
	glm::mat4 invProjMat = glm::inverse(Camera::GetInstance()->GetProj());
	glm::vec4 eyeCoords = invProjMat * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	//eyespace to world space
	glm::mat4 invViewMat = glm::inverse(Camera::GetInstance()->GetView());
	glm::vec4 rayWorld = invViewMat * eyeCoords;
	glm::vec3 rayDirection = glm::normalize(glm::vec3(rayWorld));	

	m_mousePos = glm::vec2(rayWorld.x, rayWorld.y);
}

bool LevelOne::CheckMousePicking(glm::vec2 _position, float _radius)
{
	UpdateMouseWorldPos();

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
