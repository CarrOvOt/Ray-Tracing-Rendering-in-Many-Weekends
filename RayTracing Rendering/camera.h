#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ray.h"


enum CAMERATYPE{
	PERSPECTIVE
	//ORTHO, PERSPECTIVE
};

enum CAMERAMOVE {
	LEFT,RIGHT,FORWARD,BACKWARD,
	WDUP, WDDOWN // up and down in world space
};

const glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);


class Camera {

public:

	CAMERATYPE type = PERSPECTIVE;

	unsigned int Height = 720;
	unsigned int Width = 1280;
	float PixelSize = 0.01f;
	float Focal = 3.0f;


	float Pitch = 0;
	float Yaw = -90.0f;

	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);

	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);


	float MoveSpeed = 2.0f;
	float RoateSpeedX = 0.1f;
	float RoateSpeedY = 0.1f;
	float ScaleSpeed = 2.0f;


	Camera();
	Camera(unsigned int height, unsigned int width);

	~Camera();


	Ray GetPixelRay(int x, int y);



	// only affect Postion
	void Move(CAMERAMOVE moveDir,float deltaTime);
		
	// only affect Pitch and Yaw
	void Roate(float xoffset, float yoffset);

	void ScaleFOV(float yoffset);

	
private:

	// updata Front,Up,Right with Pictch and Yaw
	void UpdateVector();


};