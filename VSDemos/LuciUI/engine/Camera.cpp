#include "prebuild.h"
#include "Engine/Camera.h"
#include "Engine/Screen.h"

glm::mat4 Camera::projectionMatrix;
glm::mat4 Camera::viewMatrix;

void Camera::UpdateAtGameStart()
{
	projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f * Screen::width / Screen::height, 0.1f, 100.0f);
	// Camera matrix
	viewMatrix = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

}

