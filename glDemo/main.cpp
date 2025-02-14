
#include "core.h"

#include <cmath>
#include "MyShapes.h"

using namespace std;


// global variables

mt19937 engine;
uniform_real_distribution<float> range;
uniform_real_distribution<float> colorRange;
uniform_real_distribution<float> sizeRange;

vector<glm::vec2> vertexCoords;
vector<glm::vec4> vertexColors;
vector<float> vertexSizes;

// Window size
const unsigned int initWidth = 1012;
const unsigned int initHeight = 1012;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();
/*void DrawPolygon(int _x, int _y, int _sides, float _radius);
void drawStarDegrees(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points);
void drawTank(float _atX, float _atY, float r, float g, float b, float _orientation);
void drawBlendedRectangles();
void drawSemiCircleStudio();*/



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

	gluOrtho2D(-4.1f, 4.1f, -4.1f, 4.1f);

	random_device rd;
	engine = mt19937(rd());
	range = uniform_real_distribution<float>(-1.0f, 1.0f);
	colorRange = uniform_real_distribution<float>(0.0f, 1.0f);
	sizeRange = uniform_real_distribution<float>(5.0f, 40.0f);

	vertexCoords = vector<glm::vec2>(100, glm::vec2(0.0f, 0.0f));
	vertexColors = vector<glm::vec4>(100, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	vertexSizes = vector<float>(100, 5.0f); 

	// Iterate 100 times (once for each vertex) and calculate and store the random x and y values
	for (int i = 0; i < 100; i++) {

		float x = range(engine);
		float y = range(engine);

		float size = sizeRange(engine);

		float r = colorRange(engine);
		float g = colorRange(engine);
		float b = colorRange(engine);
		float a = 1.0f;

		vertexCoords[i] = glm::vec2(x, y);
		vertexColors[i] = glm::vec4(r, g, b, a);
		vertexSizes[i] = size;
	}

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

	//glPointSize(5.0f);
	//glColor3ub(0, 180, 0);


	// Render objects here...
	for (int i = 0; i < 100; i++) 
	{
		glPointSize(vertexSizes[i]);
		glBegin(GL_POINTS);
		glColor4f(vertexColors[i].r, vertexColors[i].g, vertexColors[i].b, vertexColors[i].a);
		glVertex2f(vertexCoords[i].x, vertexCoords[i].y);
	}

	glEnd();


	// Clear the rendering window
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render objects here...
	/*glBegin(GL_TRIANGLES);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);
		glVertex2f(-1.0f, -1.0f);
		glVertex2f(1.0f, 1.0f);
		glVertex2f(-1.0f, 1.0f);
	glEnd();*/

	//DrawPolygon(0, 0, 3, 3.0f);
	//DrawPolygon(1, 5, 3, 1.0f);
	//DrawPolygon(8, -5, 4, 2.0f);

	//drawStarDegrees(0.0f, 0.0f, 1.0f, 3.0f, 5);
	//drawTank( 0.0f, 0.0f, 255.0f, 0.0f, 0.0f, 0.0f);
	//drawTank(0.0f, 0.0f, 0.0f, 0.0f, 255.0f, 100.0f);
	//drawBlendedRectangles();
	//drawSemiCircleStudio();
}

/*void DrawPolygon(int _x, int _y, int _sides, float _radius)
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

void rotatePoint(float& x, float& y, float angle) {
	float rad = angle * (3.14159265359f / 180.0f);
	float cosTheta = cos(rad);
	float sinTheta = sin(rad);

	float newX = cosTheta * x - sinTheta * y;
	float newY = sinTheta * x + cosTheta * y;

	x = newX;
	y = newY;
}

void drawTank(float _atX, float _atY, float r, float g, float b, float _orientation)
{
	float vertices[][2] = {
		{-0.75f,  0.4f}, { 0.75f,  0.4f}, { 0.75f, -0.4f}, {-0.75f, -0.4f},
		{-0.5f,  0.3f}, { 0.5f,  0.0f}, {-0.5f, -0.3f}
	};

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 255, 255);
	for (int i = 0; i < 4; i++) {
		rotatePoint(vertices[i][0], vertices[i][1], _orientation);
		glVertex2f(_atX + vertices[i][0], _atY + vertices[i][1]);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3ub(r, g, b);
	for (int i = 4; i < 7; i++) {
		rotatePoint(vertices[i][0], vertices[i][1], _orientation);
		glVertex2f(_atX + vertices[i][0], _atY + vertices[i][1]);
	}
	glEnd();
}

void drawBlendedRectangles()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.5f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-0.2f, 0.7f);
	glVertex2f(0.7f, 0.7f);
	glVertex2f(0.7f, 0.2f);
	glVertex2f(-0.2f, 0.2f);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, 0.8f);
	glVertex2f(0.8f, 0.8f);
	glVertex2f(0.8f, 0.3f);
	glVertex2f(0.0f, 0.3f);
	glEnd();

	glDisable(GL_BLEND);
}

void drawSemiCircleStudio()
{

	glShadeModel(GL_FLAT);

	glBegin(GL_TRIANGLE_STRIP);

	glColor3ub(255, 0, 255);
	glVertex2f(-0.25f, 0.0f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.75f, 0.0f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.216506351f, 0.125f);

	glColor3ub(255, 0, 0);
	glVertex2f(-0.649519053f, 0.375f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.125, 0.216506351f);

	glColor3ub(255, 255, 0);
	glVertex2f(-0.375f, 0.649519053f);

	glColor3ub(0, 255, 0);
	glVertex2f(0.0f, 0.25f);

	glColor3ub(0, 255, 0);
	glVertex2f(0.0f, 0.75f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.125f, 0.216506351f);

	glColor3ub(0, 255, 255);
	glVertex2f(0.375f, 0.649519053f);

	glColor3ub(0, 0, 255);
	glVertex2f(0.216506351f, 0.125f);

	glColor3ub(0, 0, 255);
	glVertex2f(0.649519053f, 0.375f);

	glColor3ub(255, 0, 255);
	glVertex2f(0.25f, 0.0f);

	glColor3ub(255, 0, 255);
	glVertex2f(0.75f, 0.0f);

	glEnd();
}*/

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

