#include "Input.h"
#include <stdio.h>
#include <string.h>

// Include GLFW
#include <GLFW/glfw3.h>
//GLFWwindow* window;

double Input::mousePosX;
double Input::mousePosY;
bool Input::lastFrameButtons[KeyCount];
bool Input::buttons[KeyCount];

bool Input::GetMouseButtonUp(int button)
{
	return lastFrameButtons[button] && !buttons[button];
}

void Input::Update(void* window)
{
	memcpy(lastFrameButtons, buttons, sizeof(buttons));

	glfwGetCursorPos((GLFWwindow * )window, &Input::mousePosX, &Input::mousePosY);

	buttons[0] = glfwGetMouseButton((GLFWwindow*)window, 0);

	
}