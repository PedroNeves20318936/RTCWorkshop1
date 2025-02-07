#include "core.h"
#include "MyShapes.h"

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
}