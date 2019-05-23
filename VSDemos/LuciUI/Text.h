#pragma once

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

class Text
{
	unsigned int Text2DTextureID;
	unsigned int Text2DVertexBufferID;
	unsigned int Text2DUVBufferID;
	unsigned int Text2DShaderID;
	unsigned int Text2DUniformID;
	GLuint screenWidthID;
	GLuint screenHeightID;
	const char* text;
	int x, y;
	int fontSize;
public:
	void initText2D(const char* texturePath);
	void printText2D(const char* text, int x, int y, int size);
	void cleanupText2D();

public:
	Text(const char* text, int x, int y, int fontSize);
	~Text();

	void Draw();
};

