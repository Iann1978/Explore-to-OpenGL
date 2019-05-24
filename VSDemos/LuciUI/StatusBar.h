#pragma once
#include <Engine.h>
#include <Text.h>
#include <Image.h>
class StatusBar : public IRenderable
{
	// time
	char timestr[100];
	Text* time;
	void UpdateTime();
	void RenderTime();

	Text* carrier;

	Image* wifi;
	Image* volume;

	
public:
	StatusBar();
	~StatusBar();

	void Update();
	void Render();
};

