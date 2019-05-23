// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>

#include <Image.h>
#include <Text.h>
#include <Input.h>
#include <Screen.h>
#include <common/text2D.hpp>

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

	Screen::width = 1024;
	Screen::height = 768;
	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Tutorial 05 - Textured Cube", NULL, NULL);
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

	
	
	int xint = 20;
	int yint = 20;
	int x = xint;
	int y = yint; 
	int width = 300; 
	int height = 300;
	Image image("images/1.dds", x, y, width, height);
	Text text0_0("BEIJING WEST", x + 5, y+230, 24);
	Text text0_1("MOUNT COMPOUNDI", x + 5, y+260, 20);

	x += xint + width;
	Image image2("images/3.dds", x, y, width, height);
	Text text1_0("Baikal", x + 5, y + 5, 30);
	//Text text2_1("MOUNT COMPOUNDI", x + 5, y + 260);

	x += xint + width;
	Image image3("images/1.dds", x, y, width, height);
	image3.onClick = OnClick;
	Text text2_0("BEIJING WEST", x + 5, y + 230, 24);
	Text text2_1("MOUNT COMPOUNDI", x + 5, y + 260, 20);

	y += yint + height;
	x = xint;
	Image image4("images/3.dds", x, y, width, height);
	Text text3_0("Baikal", x + 5, y + 5, 30);

	x += xint + width;
	Image image5("images/1.dds", x, y, width, height);
	Text text4_0("BEIJING WEST", x + 5, y + 230, 24);
	Text text4_1("MOUNT COMPOUNDI", x + 5, y + 260, 20);

	x += xint + width;
	Image image6("images/3.dds", x, y, width, height);
	Text text5_0("Baikal", x + 5, y + 5, 30);

	


	
	
	
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
		image.Update();
		image2.Update();
		image3.Update();
		image4.Update();
		image5.Update();
		image6.Update();

		image.Draw();
		image2.Draw();
		image3.Draw();
		image4.Draw();
		image5.Draw();
		image6.Draw();

		text0_0.Draw();
		text0_1.Draw();
		text1_0.Draw();

		text2_0.Draw();
		text2_1.Draw();
		text3_0.Draw();

		text4_0.Draw();
		text4_1.Draw();
		text5_0.Draw();
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

	// Cleanup VBO and shader
	glDeleteVertexArrays(1, &VertexArrayID);
	
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

