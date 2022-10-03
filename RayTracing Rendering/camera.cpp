#include"camera.h"

Camera::Camera(){
	UpdateVector();
}

Camera::Camera(unsigned int height, unsigned int width):Height(height),Width(width) {
	UpdateVector();
}

Camera::~Camera() {
}

Ray Camera::GetPixelRay(int x, int y){

	if (this->type == PERSPECTIVE) {
		glm::vec3 pix = Position + Front * Focal + Right * (x - Width * 1.0f / 2 + 0.5f) * PixelSize + Up * (y - Height * 1.0f / 2 + 0.5f) * PixelSize;
		return Ray(Position, glm::normalize(pix - Position));
	}

	return Ray();
}


void Camera::Move(CAMERAMOVE moveDir, float deltaTime){

	if (moveDir == CAMERAMOVE::LEFT) {
		Position -= deltaTime * MoveSpeed * Right;
		return;
	}
	if (moveDir == CAMERAMOVE::RIGHT) {
		Position += deltaTime * MoveSpeed * Right;
		return;
	}
	if (moveDir == CAMERAMOVE::FORWARD) {
		Position += deltaTime * MoveSpeed * Front;
		return;
	}
	if (moveDir == CAMERAMOVE::BACKWARD) {
		Position -= deltaTime * MoveSpeed * Front;
		return;
	}
	if (moveDir == CAMERAMOVE::WDUP) {
		Position += deltaTime * MoveSpeed * WorldUp;
		return;
	}
	if (moveDir == CAMERAMOVE::WDDOWN) {
		Position -= deltaTime * MoveSpeed * WorldUp;
		return;
	}
}

void Camera::Roate(float xoffset, float yoffset){
	Yaw += xoffset * RoateSpeedX;
	Pitch -= yoffset * RoateSpeedY;

	if (Pitch > 89.0f) Pitch = 89.0f;
	if (Pitch < -89.0f) Pitch = -89.0f;

	UpdateVector();
}

void Camera::ScaleFOV(float yoffset){
	Focal -= (float)yoffset;
	if (Focal < 1.0f)
		Focal = 1.0f;
}

void Camera::UpdateVector(){

	// updata Right with Yaw

	// calculate the new Front vector directly
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));

}
