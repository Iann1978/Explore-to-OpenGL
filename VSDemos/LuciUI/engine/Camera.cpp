#include "prebuild.h"
#include "Engine/Input.h"
#include "Engine/Time.h"
#include "Engine/Screen.h"
#include "Engine/Camera.h"


glm::mat4 Camera::projectionMatrix;
glm::mat4 Camera::viewMatrix;

glm::vec3 eye(0,0,3);
glm::vec3 center(0,0,0);
glm::vec3 wantup(0,1,0);

void Camera::UpdateAtGameStart()
{
	glm::vec3 front = glm::normalize(center - eye);
	glm::vec3 right = glm::cross(front, wantup);
	glm::vec3 up = glm::cross(right, front);
	center = eye + front;

	projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f * Screen::width / Screen::height, 0.1f, 100.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(eye, center, up);
}

void Camera::UpdateAtFrameStart()
{
	float deitaTime = Time::deltaTime;

	float moveSpeed = 1.f;	
	float deitaDis = moveSpeed * deitaTime;

	float rotateSpeed = 0.1f;
	float deitaRot = rotateSpeed * deitaTime;

	glm::vec3 front = glm::normalize(center - eye);
	glm::vec3 right = glm::cross(front, wantup);
	glm::vec3 up = glm::cross(right, front);
	float dot = glm::dot(front, up);

	if (Input::GetKey(Input::KeyA))
	{	
		eye -= deitaDis * right;
	}
	else if (Input::GetKey(Input::KeyD))
	{
		eye += deitaDis * right;
	}
	else if (Input::GetKey(Input::KeyW))
	{
		eye += deitaDis * front;
	}
	else if (Input::GetKey(Input::KeyS))
	{
		eye -= deitaDis * front;
	}
	else if (Input::GetKey(Input::KeyQ))
	{
		glm::mat4 rotationMat(1); // Creates a identity matrix
		rotationMat = glm::rotate(rotationMat, deitaRot, up);
		front = glm::vec3(rotationMat * glm::vec4(front, 1.0));
		dot = glm::dot(front, up);
	}
	else if (Input::GetKey(Input::KeyE))
	{
		glm::mat4 rotationMat(1); // Creates a identity matrix
		rotationMat = glm::rotate(rotationMat, -deitaRot, up);
		front = glm::vec3(rotationMat * glm::vec4(front, 1.0));		
		dot = glm::dot(front, up);
	}


	center = eye + front;
	viewMatrix = glm::lookAt(eye, center, up);

}