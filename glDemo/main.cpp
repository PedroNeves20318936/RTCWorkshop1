
#include "core.h"

#include <cmath>


// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();
void DrawPolygon(int _x, int _y, int _sides, float _radius);
void drawStarDegrees(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points);
void drawTank(float _atX, float _atY, float r, float g, float b, float _orientation);



int main() {

	//
	// 1. Initialisation
	//
	

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black

	gluOrtho2D(-8.1f, 8.1f, -8.1f, 8.1f);


	//
	// 2. Main loop
	// 
	

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}



// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render objects here...
	/*glBegin(GL_TRIANGLES);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
	glEnd();*/

	/*DrawPolygon(0, 0, 5, 3.0f);
	DrawPolygon(1, 5, 3, 1.0f);
	DrawPolygon(8, -5, 4, 2.0f);*/

	//drawStarDegrees(0.0f, 0.0f, 0.1f, 0.25f, 5);
	drawTank(- 3.0f, 0.0f, 255.0f, 0.0f, 0.0f, 0.01f);
	drawTank(+ 3.0f, 0.0f, 0.0f, 0.0f, 255.0f, 0.01f);
}

void DrawPolygon(int _x, int _y, int _sides, float _radius)
{
	if (_sides < 3) return;

	const float PI = 3.14159265359f;
	float angleIncrement = 2.0f * PI / _sides;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(_x, _y);

	for (int i = 0; i <= _sides; ++i) {
		float angle = i * angleIncrement;
		float x = _x + _radius * cos(angle);
		float y = _y + _radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

void drawStarDegrees(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points)
{
	if (_points < 4) return;

	const float PI = 3.14159265359f;
	float angleStep = PI / _points;

	glBegin(GL_TRIANGLE_FAN);

	glColor3ub(255, 255, 255);
	glVertex2f(_atX, _atY);

	glColor3ub(0, 0, 0);

	for (int i = 0; i <= _points * 2; i++) {
		float angle = i * angleStep;
		float radius = (i % 2 == 0) ? _outerRadius : _innerRadius;

		float x = _atX + radius * cos(angle);
		float y = _atY + radius * sin(angle);
		glVertex2f(x, y);
	}

	glEnd();
}

void drawTank(float _atX, float _atY, float r, float g, float b, float _orientation)
{
	glBegin(GL_LINE_LOOP);

	glColor3ub(255, 255, 255);
	glVertex2f(_atX + -0.75f, _atY + 0.4f);
	glVertex2f(_atX + 0.75f, _atY + 0.4f);
	glVertex2f(_atX + 0.75f, _atY + -0.4f);
	glVertex2f(_atX + -0.75f, _atY + -0.4f);

	glEnd();

	glBegin(GL_TRIANGLE_FAN);

	glColor3ub(r, g, b);

	glVertex2f(_atX + -0.5f, _atY + 0.3f);
	glVertex2f(_atX + 0.5f, _atY + 0.0f);
	glVertex2f(_atX + -0.5f, _atY + -0.3f);

	glEnd();

}




// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}


// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() {
}

