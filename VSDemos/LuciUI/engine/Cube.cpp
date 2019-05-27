#include "prebuild.h"
#include <common/shader.hpp>
#include <common/texture.hpp>


#include <Engine/Cube.h>
#include <Engine/Input.h>
#include <Engine/Screen.h>





Cube::Cube(const char* path, float x, float y, float w, float h)
{

	this->status = 0.7 * (rand() % 5) / 5;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	static const GLfloat g_vertex_buffer_data_Cube[] = {
		0.0f,0.0f,0.0f,
		0.0f,1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f,0.0f,0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f,0.0f,0.0f,
	};

	// Two UV coordinatesfor each vertex. They were created with Blender.
	static const GLfloat g_uv_buffer_data_Cube[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
	};

	x = y = 0.0f;
	w = h = 0.5f;
	//texture = loadDDS("uvtemplate.DDS");
	texture = loadDDS(path);
	//texture = loadDDS("1.dds");
	program = LoadShaders("shaders/geo_vert.shader", "shaders/geo_frag.shader");
	textureID = glGetUniformLocation(program, "myTextureSampler");
	rectID = glGetUniformLocation(program, "rect");
	screenWidthID = glGetUniformLocation(program, "screenWidth");
	screenHeightID = glGetUniformLocation(program, "screenHeight");
	statusID = glGetUniformLocation(program, "status");

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_Cube), g_vertex_buffer_data_Cube, GL_STATIC_DRAW);


	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_Cube), g_uv_buffer_data_Cube, GL_STATIC_DRAW);
}


Cube::~Cube()
{
	glDeleteBuffers(1, &uvbuffer);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(program);
	glDeleteTextures(1, &texture);
}

void Cube::SetTexture(const char* path)
{
	if (texture)
	{
		glDeleteTextures(1, &texture);
		texture = 0;
	}

	texture = loadDDS(path);
}

bool Cube::RayCast(float x, float y)
{
	return  (x >= this->x && x <= (this->x + this->w) &&
		y >= this->y && y <= (this->y + this->h));
}
void Cube::Render()
{
	if (RayCast(Input::mousePosX, Input::mousePosY))
	{
		status = 0.3f;
	}
	else
	{
		status = 0.0f;
	}

	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);

	glUniform4fv(rectID, 1, &x);

	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);
	glUniform1f(statusID, status);


	//glUniform4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

void Cube::Update()
{
	if (Input::GetMouseButtonUp(0) && RayCast(Input::mousePosX, Input::mousePosY))
	{
		//printf("click a Cube.\n");
		if (onClick)
		{
			onClick();
		}
	}
}