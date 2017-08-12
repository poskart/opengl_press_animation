#pragma once
#ifndef CERTICES_H
#define VERTICES_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.141592653589793

const GLint cylinderBodyVerticesCount = 60;
const GLint cylinderBaseVerticesCount = 60;
const GLint canCount = 8;
const glm::vec3 pressStampPosition = { 0.0f, 0.0f, 1.2f };

const glm::vec3 lightPos(2.9f, 2.9f, 2.9f);

GLfloat tapeSpeed = 0.25;

// Cans coordinates
const glm::vec3 wheelsPositions[] = {
	glm::vec3(0.0f, -4.5f, 0.4f),
	glm::vec3(0.0f, -3.5f, 0.4f),
	glm::vec3(0.0f, -2.5f, 0.4f),
	glm::vec3(0.0f, -1.5f, 0.4f),
	glm::vec3(0.0f, -0.5f, 0.4f),
	glm::vec3(0.0f, 0.5f, 0.4f),
	glm::vec3(0.0f, 1.5f, 0.4f),
	glm::vec3(0.0f, 2.5f, 0.4f)
};

// Can lids coordinates
const glm::vec3 basesWheelsPosition[] = {
	glm::vec3(0.0f, -4.5f, 0.30101f),
	glm::vec3(0.0f, -4.5f, 0.5f),
	glm::vec3(0.0f, -3.5f, 0.301f),
	glm::vec3(0.0f, -3.5f, 0.5f),
	glm::vec3(0.0f, -2.5f, 0.301f),
	glm::vec3(0.0f, -2.5f, 0.5f),
	glm::vec3(0.0f, -1.5f, 0.301f),
	glm::vec3(0.0f, -1.5f, 0.5f),
	glm::vec3(0.0f, -0.5f, 0.301f),
	glm::vec3(0.0f, -0.5f, 0.5f),
	glm::vec3(0.0f, 0.5f, 0.301f),
	glm::vec3(0.0f, 0.5f, 0.5f),
	glm::vec3(0.0f, 1.5f, 0.301f),
	glm::vec3(0.0f, 1.5f, 0.5f),
	glm::vec3(0.0f, 2.5f, 0.301f),
	glm::vec3(0.0f, 2.5f, 0.5f),
};
// pressStamp bases positions
const glm::vec3 pressStampBasesPosition[] = {
	glm::vec3(0.0f, 0.0f, 0.8f),
	glm::vec3(0.0f, 0.0f, 1.6f)
};

void setVertexAttributes(void)
{
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

GLfloat * getCylinderBodyVertices(void)
{
	GLfloat * cylinderBodyVertices = new GLfloat[(cylinderBodyVerticesCount * 2 + 2) * 8];
	for (int i = 0; i <= cylinderBodyVerticesCount; ++i)
	{
		const GLdouble step = 2.0 * PI / (double)(cylinderBodyVerticesCount);
		const GLdouble textureStep = 1.0 / (double)(cylinderBodyVerticesCount);
		cylinderBodyVertices[16 * i] = (0.1 * cos(i * step));
		cylinderBodyVertices[16 * i + 1] = (0.1 * sin((i * step)));
		cylinderBodyVertices[16 * i + 2] = -0.1f;
		cylinderBodyVertices[16 * i + 3] = textureStep * i;
		cylinderBodyVertices[16 * i + 4] = 1.0f;
		cylinderBodyVertices[16 * i + 5] = cos(i * step);
		cylinderBodyVertices[16 * i + 6] = sin(i * step);
		cylinderBodyVertices[16 * i + 7] = 0.0f;

		cylinderBodyVertices[16 * i + 8] = (0.1 * cos(i * step));
		cylinderBodyVertices[16 * i + 9] = (0.1 * sin((i * step)));
		cylinderBodyVertices[16 * i + 10] = 0.1f;
		cylinderBodyVertices[16 * i + 11] = textureStep * i;
		cylinderBodyVertices[16 * i + 12] = 0.0f;
		cylinderBodyVertices[16 * i + 13] = cos(i * step);
		cylinderBodyVertices[16 * i + 14] = sin(i * step);
		cylinderBodyVertices[16 * i + 15] = 0.0f;
	}
	// add first 2 vertices to the end to close circle
	for (int i = 0; i < 16; ++i)
		cylinderBodyVertices[16 * cylinderBodyVerticesCount + i] = cylinderBodyVertices[i];
	return cylinderBodyVertices;
}


GLfloat * getCylinderBaseVertices(void)
{
	GLfloat * cylinderBaseVertices = new GLfloat[(cylinderBaseVerticesCount + 2) * 8];
	for (int i = 0; i < cylinderBaseVerticesCount; ++i)
	{
		const GLdouble step = 2.0 * PI / (double)(cylinderBaseVerticesCount);
		cylinderBaseVertices[8 * i] = (0.1 * cos(i * step));
		cylinderBaseVertices[8 * i + 1] = (0.1 * sin((i * step)));
		cylinderBaseVertices[8 * i + 2] = 0;
		cylinderBaseVertices[8 * i + 3] = 0.0f;
		cylinderBaseVertices[8 * i + 4] = 0.0f;
		cylinderBaseVertices[8 * i + 5] = 0.0f;
		cylinderBaseVertices[8 * i + 6] = 0.0f;
		cylinderBaseVertices[8 * i + 7] = 1.0f;
	}
	// add first 2 vertices to the end to close circle
	for (int i = 0; i < 16; ++i)
		cylinderBaseVertices[8 * cylinderBaseVerticesCount + i] = cylinderBaseVertices[i];
	return cylinderBaseVertices;
}

// light source vertices
GLfloat lampVertices[] = {
	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	-0.1f, 0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f, -0.1f, 0.1f,
	0.1f, -0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, -0.1f, 0.1f,

	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, -0.1f,
	-0.1f, -0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,

	0.1f, 0.1f, 0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,

	-0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, -0.1f,
	0.1f, -0.1f, 0.1f,
	0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, 0.1f,
	-0.1f, -0.1f, -0.1f,

	-0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, -0.1f,
	0.1f, 0.1f, 0.1f,
	0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, 0.1f,
	-0.1f, 0.1f, -0.1f
};

// platform
GLfloat platformVertices[] = {
	// down base
	-1.0f, -3.2f, -0.2f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	1.0f, -3.2f, -0.2f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	1.0f, 3.2f, -0.2f,  1.0f, 2.0f,  0.0f, 0.0f, -1.0f,
	1.0f, 3.2f, -0.2f,  1.0f, 2.0f,  0.0f, 0.0f, -1.0f,
	-1.0f, 3.2f, -0.2f,  0.0f, 2.0f,  0.0f, 0.0f, -1.0f,
	-1.0f, -3.2f, -0.2f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,

	// top base
	-1.0f, -3.2f, 0.2f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	1.0f, -3.2f, 0.2f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	1.0f, 3.2f, 0.2f,  1.0f, 2.0f,  0.0f, 0.0f, 1.0f,
	1.0f, 3.2f, 0.2f,  1.0f, 2.0f,  0.0f, 0.0f, 1.0f,
	-1.0f, 3.2f, 0.2f,  0.0f, 2.0f,  0.0f, 0.0f, 1.0f,
	-1.0f, -3.2f, 0.2f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

	// left wall
	-1.0f, 3.2f, 0.2f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-1.0f, 3.2f, -0.2f,  1.0f, 2.0f,  -1.0f, 0.0f, 0.0f,
	-1.0f, -3.2f, -0.2f,  0.0f, 2.0f,  -1.0f, 0.0f, 0.0f,
	-1.0f, -3.2f, -0.2f,  0.0f, 2.0f,  -1.0f, 0.0f, 0.0f,
	-1.0f, -3.2f, 0.2f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-1.0f, 3.2f, 0.2f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

	// front wall
	-1.0f, 3.2f, 0.2f,  0.0f, 2.0f,  0.0f, 1.0f,  0.0f,
	1.0f, 3.2f, 0.2f,  1.0f, 2.0f,  0.0f, 1.0f,  0.0f,
	1.0f, 3.2f, -0.2f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,
	1.0f, 3.2f, -0.2f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,
	-1.0f, 3.2f, -0.2f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f,
	-1.0f, 3.2f, 0.2f,  0.0f, 2.0f,  0.0f, 1.0f,  0.0f,

	// right wall
	1.0f, 3.2f, 0.2f,  1.0f, 0.0f,  2.0f, 0.0f, 0.0f,
	1.0f, 3.2f, -0.2f,  1.0f, 2.0f,  1.0f, 0.0f, 0.0f,
	1.0f, -3.2f, -0.2f,  0.0f, 2.0f,  1.0f, 0.0f, 0.0f,
	1.0f, -3.2f, -0.2f,  0.0f, 2.0f,  1.0f, 0.0f, 0.0f,
	1.0f, -3.2f, 0.2f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	1.0f, 3.2f, 0.2f,  1.0f, 0.0f,  2.0f, 0.0f, 0.0f,

	// rear wall
	-1.0f, -3.2f, 0.2f,  0.0f, 2.0f,  0.0f, -1.0f,  0.0f,
	1.0f, -3.2f, 0.2f,  1.0f, 2.0f,  0.0f, -1.0f,  0.0f,
	1.0f, -3.2f, -0.2f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	1.0f, -3.2f, -0.2f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-1.0f, -3.2f, -0.2f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-1.0f, -3.2f, 0.2f,  0.0f, 2.0f,  0.0f, -1.0f,  0.0f,
};

// press base
GLfloat pressBaseVertices[] = {
	// front
	-0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.4f, 0.2f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.4f, 0.9f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.4f, 0.9f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	-0.8f, -0.4f, 1.2f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	-0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

	-0.5f, -0.4f, 0.9f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	-0.8f, -0.4f, 1.2f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	0.8f, -0.4f, 1.2f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.8f, -0.4f, 1.2f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.5f, -0.4f, 0.9f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	-0.5f, -0.4f, 0.9f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,

	0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	0.5f, -0.4f, 0.2f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	0.5f, -0.4f, 0.9f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.5f, -0.4f, 0.9f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.8f, -0.4f, 1.2f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

	// rear
	-0.8f, 0.4f, 0.2f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, 0.4f, 0.2f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	-0.8f, 0.4f, 1.2f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	-0.8f, 0.4f, 0.2f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,

	-0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	-0.8f, 0.4f, 1.2f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	-0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,

	0.8f, 0.4f, 0.2f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.5f, 0.4f, 0.2f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.8f, 0.4f, 1.2f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.8f, 0.4f, 0.2f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,

	// rightOuter
	0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.8f, -0.4f, 1.2f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	0.8f, 0.4f, 0.2f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	// leftOuter
	-0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.8f, -0.4f, 1.2f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.8f, 0.4f, 0.2f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.8f, -0.4f, 0.2f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	// rightInner
	0.5f, -0.4f, 0.2f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.5f, -0.4f, 0.9f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	0.5f, 0.4f, 0.2f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	0.5f, -0.4f, 0.2f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	// leftInner
	-0.5f, -0.4f, 0.2f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.4f, 0.9f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, 0.4f, 0.2f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-0.5f, -0.4f, 0.2f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	// belowInner
	-0.5f, -0.4f, 0.9f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	0.5f, -0.4f, 0.9f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	0.5f, 0.4f, 0.9f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	-0.5f, 0.4f, 0.9f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	-0.5f, -0.4f, 0.9f,  0.0f, 0.0f,  0.0f, 0.0f, -1.0f,
	// topOuter
	-0.8f, -0.4f, 1.2f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	0.8f, -0.4f, 1.2f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	0.8f, 0.4f, 1.2f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	-0.8f, 0.4f, 1.2f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	-0.8f, -0.4f, 1.2f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
};

// tape
GLfloat tapeVertices[] = {
	// top
	-0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	0.4f, -5.0f, 0.3f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	0.4f, 5.0f, 0.3f,  1.0f, 40.0f,  0.0f, 0.0f, 1.0f,
	0.4f, 5.0f, 0.3f,  1.0f, 40.0f,  0.0f, 0.0f, 1.0f,
	-0.4f, 5.0f, 0.3f,  0.0f, 40.0f,  0.0f, 0.0f, 1.0f,
	-0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

	// right side
	0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.4f, -5.0f, 0.2f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	0.4f, 5.0f, 0.2f,  1.0f, 40.0f,  1.0f, 0.0f, 0.0f,
	0.4f, 5.0f, 0.2f,  1.0f, 40.0f,  1.0f, 0.0f, 0.0f,
	0.4f, 5.0f, 0.3f,  0.0f, 40.0f,  1.0f, 0.0f, 0.0f,
	0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,

	// left side
	-0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.4f, -5.0f, 0.2f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-0.4f, 5.0f, 0.2f,  1.0f, 40.0f,  -1.0f, 0.0f, 0.0f,
	-0.4f, 5.0f, 0.2f,  1.0f, 40.0f,  -1.0f, 0.0f, 0.0f,
	-0.4f, 5.0f, 0.3f,  0.0f, 40.0f,  -1.0f, 0.0f, 0.0f,
	-0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

	// front side
	-0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	0.4f, -5.0f, 0.3f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
	0.4f, -5.0f, 0.2f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	0.4f, -5.0f, 0.2f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	-0.4f, -5.0f, 0.2f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	-0.4f, -5.0f, 0.3f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,

	// rear side
	-0.4f, 5.0f, 0.3f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.4f, 5.0f, 0.3f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	0.4f, 5.0f, 0.2f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	0.4f, 5.0f, 0.2f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	-0.4f, 5.0f, 0.2f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,
	-0.4f, 5.0f, 0.3f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
};

// Ground vertices
GLfloat groundVertices[] =
{
	-1.0f, -1.0f, -0.25f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	1.0f, -1.0f, -0.25f,  10.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, -0.25f,  10.0f, 10.0f,  0.0f, 0.0f, 1.0f,
	1.0f, 1.0f, -0.25f,  10.0f, 10.0f,  0.0f, 0.0f, 1.0f,
	-1.0f, 1.0f, -0.25f,  0.0f, 10.0f,  0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, -0.25f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f

};


GLfloat roomVertices[] = {
	// ceiling
	-3.0f, -3.0f, 4.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	3.0f, -3.0f, 4.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	3.0f, 3.0f, 4.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	3.0f, 3.0f, 4.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	-3.0f, 3.0f, 4.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
	-3.0f, -3.0f, 4.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,

	// left wall
	-3.0f, 3.0f, 4.0f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-3.0f, 3.0f, -0.2f,  1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-3.0f, -3.0f, -0.2f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-3.0f, -3.0f, -0.2f,  0.0f, 1.0f,  -1.0f, 0.0f, 0.0f,
	-3.0f, -3.0f, 4.0f,  0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
	-3.0f, 3.0f, 4.0f,  1.0f, 0.0f,  -1.0f, 0.0f, 0.0f,

	// front wall
	-3.0f, 3.0f, 4.0f,  0.0f, 1.0f,  0.0f, 1.0f,  0.0f,
	3.0f, 3.0f, 4.0f,  1.0f, 1.0f,  0.0f, 1.0f,  0.0f,
	3.0f, 3.0f, -0.2f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,
	3.0f, 3.0f, -0.2f,  1.0f, 0.0f,  0.0f, 1.0f,  0.0f,
	-3.0f, 3.0f, -0.2f,  0.0f, 0.0f, 0.0f, 1.0f,  0.0f,
	-3.0f, 3.0f, 4.0f,  0.0f, 1.0f,  0.0f, 1.0f,  0.0f,

	// right wall
	3.0f, 3.0f, 4.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	3.0f, 3.0f, -0.2f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	3.0f, -3.0f, -0.2f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	3.0f, -3.0f, -0.2f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
	3.0f, -3.0f, 4.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
	3.0f, 3.0f, 4.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

	// rear wall
	-3.0f, -3.0f, 4.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
	3.0f, -3.0f, 4.0f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
	3.0f, -3.0f, -0.2f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	3.0f, -3.0f, -0.2f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-3.0f, -3.0f, -0.2f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
	-3.0f, -3.0f, 4.0f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
};

#endif