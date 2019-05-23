#pragma once


class Input
{
public:
	
	enum KeyCode
	{
		LeftButton = 0,
		KeyCount,
	};
	static double mousePosX;
	static double mousePosY;
	static bool lastFrameButtons[KeyCount];
	static bool buttons[KeyCount];

	static bool GetMouseButtonUp(int button);
	static void Update(void* window);
	
};

