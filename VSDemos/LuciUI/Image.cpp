#include "Image.h"
#include "Screen.h"

#include <common/shader.hpp>
#include <common/texture.hpp>

Image::Image(const char* path, float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	static const GLfloat g_vertex_buffer_data_image[] = {
		0.0f,0.0f,0.0f,
		0.0f,1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		0.0f,0.0f,0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f,0.0f,0.0f,
	};

	// Two UV coordinatesfor each vertex. They were created with Blender.
	static const GLfloat g_uv_buffer_data_image[] = {
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
	programID_image = LoadShaders("Image_vert.shader", "Image_frag.shader");
	textureID = glGetUniformLocation(programID_image, "myTextureSampler");
	rectID = glGetUniformLocation(programID_image, "rect");
	screenWidthID = glGetUniformLocation(programID_image, "screenWidth");
	screenHeightID = glGetUniformLocation(programID_image, "screenHeight");
	
	glGenBuffers(1, &vertexbuffer_image);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_image);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data_image), g_vertex_buffer_data_image, GL_STATIC_DRAW);

	
	glGenBuffers(1, &uvbuffer_image);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data_image), g_uv_buffer_data_image, GL_STATIC_DRAW);
}


Image::~Image()
{
}

void Image::Draw()
{

	glUseProgram(programID_image);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(textureID, 0);

	glUniform4fv(rectID, 1, &x);

	glUniform1f(screenWidthID, Screen::width);
	glUniform1f(screenHeightID, Screen::height);

	//glUniform4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer_image);
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
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer_image);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 6); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}