#include "prebuild.h"
#include "Engine/Input.h"


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