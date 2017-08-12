#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	GLfloat radius = 3.0f;
	GLfloat angle = 0.0f;
	glm::vec3 cameraPosition = glm::vec3(3.0f, 0.0f, 4.0f);						 // camera position
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.5f);						 // camera target point
	glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);	 // vector from target to camera
	const glm::vec3 up = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection)); // x axis in camera space
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);			 // y axis in camera space

	GLfloat fov = 45.0f; // field of view value
public:
	Camera();
	void move(GLfloat, bool*);
	void updateCameraPosition();
	glm::vec3 getCameraPos();
	glm::vec3 getCameraTarget();
	glm::vec3 getCameraUp();
	GLfloat getFov();
	~Camera();
	
};

