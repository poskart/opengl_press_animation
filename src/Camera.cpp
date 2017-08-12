#include "Camera.h"

Camera::Camera(){}

Camera::~Camera(){}

void Camera::updateCameraPosition()
{
	cameraDirection = glm::normalize(cameraPosition - cameraTarget);
	cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
}

glm::vec3 Camera::getCameraPos()
{
	return cameraPosition;
}

glm::vec3 Camera::getCameraTarget()
{
	return cameraTarget;
}

glm::vec3 Camera::getCameraUp()
{
	return cameraUp;
}

GLfloat Camera::getFov()
{
	return fov;
}

void Camera::move(GLfloat deltaTime, bool* keys)
{
	GLfloat cameraSpeed = 1.0f * deltaTime;
	GLfloat newX, newY;
	if (keys[GLFW_KEY_W])
	{
		if (cameraPosition.z < 4.0f)
		{
			cameraPosition.z += 1.0f * cameraSpeed;
			updateCameraPosition();
		}
	}
	if (keys[GLFW_KEY_S])
	{
		if (cameraPosition.z > 0.0f)
		{
			cameraPosition.z -= 1.0f * cameraSpeed;
			updateCameraPosition();
		}
	}
	if (keys[GLFW_KEY_A])
	{
		angle -= 1.0f * cameraSpeed;
		newY = radius * sin(angle);
		newX = radius * cos(angle);
		cameraPosition.x = newX;
		cameraPosition.y = newY;
		updateCameraPosition();
	}
	if (keys[GLFW_KEY_D])
	{
		angle += 1.0f * cameraSpeed;
		newY = radius * sin(angle);
		newX = radius * cos(angle);
		cameraPosition.x = newX;
		cameraPosition.y = newY;
		updateCameraPosition();
	}
	if (keys[GLFW_KEY_Q])
	{
		if (radius < 3.0)
		{
			radius += cameraSpeed;
			newY = radius * sin(angle);
			newX = radius * cos(angle);
			cameraPosition.x = newX;
			cameraPosition.y = newY;
			updateCameraPosition();
		}
	}
	if (keys[GLFW_KEY_E])
	{
		if (radius > 1.0)
		{
			radius -= cameraSpeed;
			newY = radius * sin(angle);
			newX = radius * cos(angle);
			cameraPosition.x = newX;
			cameraPosition.y = newY;
			updateCameraPosition();
		}
	}
}

