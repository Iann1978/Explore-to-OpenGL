#pragma once
#include <Engine/Renderable.h>

class Cube : public IRenderable
{



	typedef void (*FuncOnClick)();
	GLuint program;
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint texture = 0;
	GLuint textureID;
	GLuint rectID;
	GLuint screenWidthID;
	GLuint screenHeightID;
	GLuint statusID;

	GLfloat x, y, w, h;

public:
	GLfloat status;
	FuncOnClick onClick = nullptr;


public:
	Cube(const char* path, float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f);
	~Cube();

	void Update();
	void Render();
	void SetTexture(const char* path);


private:
	bool RayCast(float x, float y);
};

