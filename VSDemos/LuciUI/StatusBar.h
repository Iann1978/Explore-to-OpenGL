#pragma once
#include <Engine.h>
#include <Text.h>
class StatusBar : public IRenderable
{
	// time
	char timestr[100];
	Text* time;
	void UpdateTime();
	void RenderTime();

	Text* carrier;

	
public:
	StatusBar();
	~StatusBar();

	void Update();
	void Render();
};

