// Include standard headers
#include "prebuild.h"
GLFWwindow* window;

#include <list>


#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/text2D.hpp>

#include <Engine.h>
#include <Image.h>
#include <Text.h>
#include <Input.h>
#include <Screen.h>
#include <StatusBar.h>


#pragma warning (disable: 4996)

void OnClick()
{
	printf("An image is clicked.\n");
}

int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Screen::width = 1920;
	Screen::height = 1080;
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(Screen::width, Screen::height, "Tutorial 05 - Textured Cube", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	std::list<IRenderable *> renders;
	StatusBar* statusBar = new StatusBar();
	renders.push_back(statusBar);
	
	int xint = 20;
	int yint = 20;
	int x = xint;
	int y = yint + 50; 
	int width = 300; 
	int height = 300;
	Image *image = new Image("images/1.dds", x, y, width, height);	
	renders.push_back(image);
	Text *text = new Text("BEIJING WEST", x + 5, y+230, 24);
	renders.push_back(text);
	text = new Text("MOUNT COMPOUNDI", x + 5, y+260, 20);
	renders.push_back(text);

	x += xint + width;
	image = new Image("images/3.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("Baikal", x + 5, y + 5, 30);
	renders.push_back(text);


	x += xint + width;
	image = new Image("images/1.dds", x, y, width, height);
	image->onClick = OnClick;
	renders.push_back(image);
	text = new Text("BEIJING WEST", x + 5, y + 230, 24);
	renders.push_back(text);
	text = new Text("MOUNT COMPOUNDI", x + 5, y + 260, 20);
	renders.push_back(text);

	y += yint + height;
	x = xint;
	image = new Image("images/3.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("Baikal", x + 5, y + 5, 30);
	renders.push_back(text);

	x += xint + width;
	image = new Image("images/1.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("BEIJING WEST", x + 5, y + 230, 24);
	renders.push_back(text);
	text = new Text("MOUNT COMPOUNDI", x + 5, y + 260, 20);
	renders.push_back(text);

	x += xint + width;
	image = new Image("images/3.dds", x, y, width, height);
	renders.push_back(image);
	text = new Text("Baikal", x + 5, y + 5, 30);
	renders.push_back(text);

	


	
	
	
	do {
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Input::Update(window);
		/*glfwGetCursorPos(window, &Input::mousePosX, &Input::mousePosY);

		if (glfwGetMouseButton(window, 0))
		{
			printf("mouse\n");
		}
*/
		
		for (std::list<IRenderable*>::iterator it = renders.begin(); it != renders.end();
			it++)
		{
			(*it)->Update();
		}


		for (std::list<IRenderable*>::iterator it = renders.begin(); it != renders.end();
			it++)
		{
			(*it)->Render();
		}
		/*image.Update();
		image2.Update();
		image3.Update();
		image4.Update();
		image5.Update();
		image6.Update();

		image.Render();
		image2.Render();
		image3.Render();
		image4.Render();
		image5.Render();
		image6.Render();

		text0_0.Render();
		text0_1.Render();
		text1_0.Render();

		text2_0.Render();
		text2_1.Render();
		text3_0.Render();

		text4_0.Render();
		text4_1.Render();
		text5_0.Render();*/
/*
		char text[256];
		sprintf(text, "%.2f sec", glfwGetTime());
		printText2D(text, 0, 0, 60);*/
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	for (std::list<IRenderable*>::iterator it = renders.begin(); it != renders.end();
		it++)
	{
		delete (*it);
	}

	// Cleanup VBO and shader
	glDeleteVertexArrays(1, &VertexArrayID);
	
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

