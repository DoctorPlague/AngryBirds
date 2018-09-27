// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2018 Media Design School
//
// Author		:	Jasper Lyons
// Email		:	Jasper.Lyo7552@mediadesign.school.nz
// File Name	:	Camera.h
// Description	:	Camera header file

#include "Utilities.h"

#pragma once
class Camera
{
#pragma region Singleton
public:
	static std::shared_ptr<Camera> GetInstance();
	static void DestroyInstance();
	~Camera();
	/*!!!!!!!!! YOU SHOULD NOT BE CALLING THIS DIRECTLY !!!!!!!*/
	Camera();
private:
	static std::shared_ptr<Camera> s_pCamera;
	Camera(Camera const&);
	void operator=(Camera const&);
	
#pragma endregion

public:	
	//Getters
	glm::mat4 GetView();
	glm::mat4 GetProj();
	glm::vec3 GetPos();
	//Setters	
	void SetProj(int _screenWidth, int _screenHeight);
	//Other functions
	void Update();
	void MoveLeft();
	void MoveRight();
	
private:
	glm::mat4 m_view;
	glm::mat4 m_proj;
	glm::vec3 m_cameraPos;
	glm::vec3 m_cameraFront;
	glm::vec3 m_upVec;
	float m_fCameraSpeed;
};

