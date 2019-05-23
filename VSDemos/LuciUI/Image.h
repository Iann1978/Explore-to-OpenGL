#pragma once

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

class Image
{
	typedef void (*FuncOnClick)();
	GLuint programID_image;
	GLuint vertexbuffer_image;
	GLuint uvbuffer_image;
	GLuint texture;
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
	Image(const char* path, float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f);
	~Image();

	void Draw();
	void Update();

private:
	bool RayCast(float x, float y);
};

