#include "LevelOne.h"
#include "Sprite.h"
#include "Camera.h"
#include "Utilities.h"
#include "PlayerCharacter.h"
#include "Physics.h"
#include "GroundBox.h"

LevelOne::LevelOne()
{
	m_Background = std::make_shared<Sprite>();	
	Camera::GetInstance()->SetProj(ki_SCREENWIDTH, ki_SCREENHEIGHT);
	Camera::GetInstance()->Update();

	CurrentPlayers.push_back(std::make_shared<XBOXController>(1));
	CurrentPlayers.push_back(std::make_shared<XBOXController>(2));	
}

LevelOne::~LevelOne()
{
}

void LevelOne::InitializeObjects()
{
	// Initialize Scene Background	
	m_Background->Initialize("Resources/Images/Background.png");

	// Initialize Other Objects..
	// Push objects to their appropriate vectors	
	m_PlayerOne = std::make_shared<PlayerCharacter>();	
	m_PlayerOne->SetPosition(b2Vec2(3.0f, 4.5f));
	m_PlayerVec.push_back(m_PlayerOne);
	m_EntityVec.push_back(m_PlayerOne);

	m_GroundBox = std::make_shared<GroundBox>();
	m_GroundBox->SetPosition(b2Vec2(8.0f, 2.3f));
	m_EntityVec.push_back(m_GroundBox);

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
	//Reading inputs
	//PLAYER_0 INPUTS
	auto& p0_Controller = CurrentPlayers[0];
	p0_Controller->Vibrate(0, static_cast<int>(1000.0f * m_PlayerOne->GetVibrateRate()));
	if (Input::KeyState['w'] == INPUT_HOLD || p0_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(1500.0f * _DeltaTick);		
	}
	if (Input::KeyState['s'] == INPUT_HOLD || p0_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(-1500.0f * _DeltaTick);
	}
	if (Input::KeyState['a'] == INPUT_HOLD || p0_Controller->normalizedLX < -0.8f) {
		m_PlayerOne->AddRotation(100.0f * _DeltaTick);
	}
	if (Input::KeyState['d'] == INPUT_HOLD || p0_Controller->normalizedLX > 0.8f) {
		m_PlayerOne->AddRotation(-100.0f * _DeltaTick);
	}

	//Reading inputs
	//PLAYER_1 INPUTS
	auto& p1_Controller = CurrentPlayers[1];
	//Making the controller vibrate
	p1_Controller->Vibrate(0, static_cast<int>(1000.0f * m_PlayerOne->GetVibrateRate()));
	if (Input::KeyState['8'] == INPUT_HOLD || p1_Controller->ControllerButtons[BOTTOM_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerTwo->AddVelocity(50.0f * _DeltaTick);
	}
	if (Input::KeyState['5'] == INPUT_HOLD || p1_Controller->ControllerButtons[LEFT_FACE_BUTTON] == INPUT_HOLD) {
		m_PlayerOne->AddVelocity(-50.0f * _DeltaTick);
	}	
	if (Input::KeyState['4'] == INPUT_HOLD || p1_Controller->normalizedLX < -0.9f) {
		m_PlayerTwo->AddRotation(3.0f * _DeltaTick);
	}
	if (Input::KeyState['6'] == INPUT_HOLD || p1_Controller->normalizedLX > 0.9f) {
		m_PlayerTwo->AddRotation(-3.0f * _DeltaTick);
	}

	//Updating the keyboard input
	Input::Update();

	//Updating player controllers
	for (const auto& it : CurrentPlayers) it->Update();

	//Updating the players
	for (const auto& it : m_PlayerVec) it->Update();
}

void LevelOne::RenderObjects()
{
	// Render Background
	m_Background->Render(glm::scale(glm::mat4(), glm::vec3(16.0f, 9.0f, 0.0f))); // spawn in the center

	// Render Object Vectors (check that the vectors are not empty)
	if (!m_EntityVec.empty())
	{
		for (const auto& it : m_EntityVec) it->Render();
	}	
}
