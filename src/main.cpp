#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <SOIL.h>

#include <iostream>
#include <algorithm>

#include "ShaderProgram.h"
#include "Camera.h"
#include "definitions.h"

const GLuint WIDTH = 1024, HEIGHT = 768;

Camera cam;
bool keys[270];								// table for keys reading
glm::vec3 lightDiffuse(0.99f, 0.99f, 0.99f);	// diffuse light coefficients

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 270)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}
// Change press speed
void pressSpeedUpdate(bool * keys)
{
	if (keys[GLFW_KEY_RIGHT])
		tapeSpeed += 0.01;
	if (keys[GLFW_KEY_LEFT])
		tapeSpeed -= 0.01;
}
// Update light intensity
void lightDiffuseUpdate(bool* keys)
{
	if (keys[GLFW_KEY_UP])
	{
		if (lightDiffuse.x < 1.0f)
		{
			lightDiffuse.x += 0.01f;
			lightDiffuse.y += 0.01f;
			lightDiffuse.z += 0.01f;
		}
	}
	if (keys[GLFW_KEY_DOWN])
	{
		if (lightDiffuse.x > 0.0f)
		{
			lightDiffuse.x -= 0.01f;
			lightDiffuse.y -= 0.01f;
			lightDiffuse.z -= 0.01f;
		}
	}
}

// Function for texture loading
GLuint LoadMipmapTexture(GLuint texId, const char* filename)
{
	int width, height;
	// load texture, 4 argument is channel number, 5 argument - load only RGB coeff
	unsigned char* image = SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw std::exception("Cannot read texture file");

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(texId);
	glBindTexture(GL_TEXTURE_2D, texture);
	// 2 - mipmap level, 3 - store only rgb, 7 - get rgb, 8 - as char
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		std::cout << "GLFW initialization failed" << std::endl;
		return -1;
	}
	// version 3.3 openGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		// window creation (optional - glfwGetPrimaryMonitor())
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Press animation", nullptr, nullptr);
		if (window == nullptr)
			throw std::exception("GLFW window not created");
		glfwMakeContextCurrent(window);				// make window main thread's context
		glfwSetKeyCallback(window, key_callback);   // keyboard listening register

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw std::exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT); // render window
		glEnable(GL_DEPTH_TEST);		 // z-buffer enable

		// create shaders programs
		ShaderProgram ourShader("src/shader.vert", "src/shader.frag");
		ShaderProgram lightShader("src/lightShader.vert", "src/lightShader.frag");

		GLfloat bodyVertices[(cylinderBodyVerticesCount*2 + 2) * 8];
		GLfloat* bodyVerticesPtr = getCylinderBodyVertices();
		GLfloat baseVertices[(cylinderBaseVerticesCount + 2) * 8];
		GLfloat* baseVerticesPtr = getCylinderBaseVertices();
		
		for (int i = 0; i < (cylinderBodyVerticesCount*2 + 2) * 8; ++i)
			bodyVertices[i] = bodyVerticesPtr[i];
		for (int i = 0; i < (cylinderBaseVerticesCount + 2) * 8; ++i)
			baseVertices[i] = baseVerticesPtr[i];
			
		// set stretching texture along x and y, repeated texture
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// mapping pixels to texture coords - linear
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load mipmaps for textures
		GLuint texture0 = LoadMipmapTexture(GL_TEXTURE0, "images/deski.png");
		GLuint texture1 = LoadMipmapTexture(GL_TEXTURE1, "images/platform.jpg");
		GLuint texture2 = LoadMipmapTexture(GL_TEXTURE2, "images/tape1.jpg");
		GLuint texture3 = LoadMipmapTexture(GL_TEXTURE3, "images/wall.jpg");
		GLuint texture4 = LoadMipmapTexture(GL_TEXTURE4, "images/puszka.jpg");
		GLuint texture5 = LoadMipmapTexture(GL_TEXTURE5, "images/stamp.jpg");

		// VBO - Vertex Buffer Object, VAO - Vertex Array Object
		GLuint VBO1, VBO2, VBO3, VBO4, VBO5, VBO6, VBO7, VAO;
		GLuint VBOLight, VAOLight;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO1);
		glGenBuffers(1, &VBO2);
		glGenBuffers(1, &VBO3);
		glGenBuffers(1, &VBO4);
		glGenBuffers(1, &VBO5);
		glGenBuffers(1, &VBO6);
		glGenBuffers(1, &VBO7);

		glGenVertexArrays(1, &VAOLight);
		glGenBuffers(1, &VBOLight);
		glBindVertexArray(VAOLight);
		glBindBuffer(GL_ARRAY_BUFFER, VBOLight);
		glBufferData(GL_ARRAY_BUFFER, sizeof(lampVertices), lampVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);

		GLfloat deltaTime = 0.0f;	// delta time between frames
		GLfloat lastFrame = 0.0f;  	// last frame time
		GLfloat tapeDistance = 0.0;	// total tape distance
		GLfloat cycleTime = 0.0;	// tape cycle time

		while (!glfwWindowShouldClose(window))
		{
			// compute deltaTime
			GLfloat currentFrame = (GLfloat)glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			glfwPollEvents();
			cam.move(deltaTime, keys);
			lightDiffuseUpdate(keys);
			pressSpeedUpdate(keys);

			//clear buffers
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			ourShader.Use();

			// update view and projection matrices
			glm::mat4 view;
			glm::vec3 cameraPos = cam.getCameraPos();
			glm::vec3 cameraTarget = cam.getCameraTarget();
			glm::vec3 cameraUp = cam.getCameraUp();
			GLfloat fov = cam.getFov();
			view = glm::lookAt(cameraPos, cameraTarget , cameraUp);
			glm::mat4 projection;
			projection = glm::perspective(fov, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			// Read uniform values locations for coordinates transformation
			GLint modelLoc = glGetUniformLocation(ourShader.get_programID(), "model");
			GLint viewLoc = glGetUniformLocation(ourShader.get_programID(), "view");
			GLint projLoc = glGetUniformLocation(ourShader.get_programID(), "projection");
			// send to shader view and projection matrices. 2 arg - how many matrices, 3 - matrix transpose
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			
			// Set light coefficients: ambient, diffuse, specular
			GLint lightAmbientLoc = glGetUniformLocation(ourShader.get_programID(), "light.ambient");
			GLint lightDiffuseLoc = glGetUniformLocation(ourShader.get_programID(), "light.diffuse");
			GLint lightSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "light.specular");
			GLint lightPosLoc = glGetUniformLocation(ourShader.get_programID(), "light.pos");
			GLint viewPosLoc = glGetUniformLocation(ourShader.get_programID(), "viewPosition");
			glUniform3f(lightAmbientLoc, 0.4f, 0.4f, 0.4f);
			glUniform3f(lightDiffuseLoc, lightDiffuse.x, lightDiffuse.y, lightDiffuse.z);
			glUniform3f(lightSpecularLoc, 0.4f, 0.4f, 0.4f);
			glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
			glUniform3f(viewPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
			// Read material light properties coefficients location
			GLint matAmbientLoc = glGetUniformLocation(ourShader.get_programID(), "material.ambient");
			GLint matDiffuseLoc = glGetUniformLocation(ourShader.get_programID(), "material.diffuse");
			GLint matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "material.specular");
			GLint matShineLoc = glGetUniformLocation(ourShader.get_programID(), "material.shininess");

			glBindVertexArray(VAO);

			// Can label texture
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, texture4);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "isTexture"), true);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "materialTexture.diffuse"), 4);
			matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.specular");
			matShineLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.shininess");
			glUniform3f(matSpecularLoc, 0.2f, 0.2f, 0.2f);
			glUniform1f(matShineLoc, 0.01f);
			// Can body drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO1);
			glBufferData(GL_ARRAY_BUFFER, sizeof(bodyVertices), bodyVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			cycleTime += deltaTime;
			if (tapeDistance > 2.0)
				cycleTime -= 2.0 / tapeSpeed;
			tapeDistance = (GLfloat)cycleTime*tapeSpeed;
			for(GLuint i = 0; i < canCount; ++i)
			{
				glm::mat4 model1;
				model1 = glm::translate(model1, wheelsPositions[i]+ glm::vec3(0.0f, tapeDistance, 0.0f));
				model1 = glm::rotate(model1, (GLfloat)glfwGetTime() * glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model1));
				glDrawArrays(GL_TRIANGLE_STRIP, 0, (cylinderBodyVerticesCount*2 + 2));
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Can base drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO2);
			glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			int cylinderBaseCount = canCount * 2;
			for (GLuint i = 0; i < cylinderBaseCount; ++i)
			{
				glm::mat4 model2;
				model2 = glm::translate(model2, basesWheelsPosition[i]+ glm::vec3(0.0f, tapeDistance, 0.0f));
				model2 = glm::rotate(model2, (GLfloat)glfwGetTime() * glm::radians(-60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
				glDrawArrays(GL_TRIANGLE_FAN, 0, (cylinderBaseVerticesCount + 2));
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Main base texture
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "isTexture"), true);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "materialTexture.diffuse"), 1);
			matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.specular");
			matShineLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.shininess");
			glUniform3f(matSpecularLoc, 0.99f, 0.99f, 0.99f);
			glUniform1f(matShineLoc, 0.99f);
			// Main base drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO3);
			glBufferData(GL_ARRAY_BUFFER, sizeof(platformVertices), platformVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			glm::mat4 model3;
			model3 = glm::translate(model3, glm::vec3(0.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
				
			// Texture for tape
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "isTexture"), true);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "materialTexture.diffuse"), 2);
			matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.specular");
			matShineLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.shininess");
			glUniform3f(matSpecularLoc, 0.2f, 0.2f, 0.2f);
			glUniform1f(matShineLoc, 0.01f);
			// Tape drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO4);
			glBufferData(GL_ARRAY_BUFFER, sizeof(tapeVertices), tapeVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			glm::mat4 model4;
			model4 = glm::translate(model4, glm::vec3(0.0f, 0.0f, 0.0f));
			model4 = glm::translate(model4, glm::vec3(0.0f, tapeDistance, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model4));
			glDrawArrays(GL_TRIANGLES, 0, 30);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Press base color
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "isTexture"), false);
			matAmbientLoc = glGetUniformLocation(ourShader.get_programID(), "material.ambient");
			matDiffuseLoc = glGetUniformLocation(ourShader.get_programID(), "material.diffuse");
			matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "material.specular");
			matShineLoc = glGetUniformLocation(ourShader.get_programID(), "material.shininess");
			glUniform3f(matAmbientLoc, 0.99f, 0.01f, 0.10225f);
			glUniform3f(matDiffuseLoc, 0.99f, 0.01f, 0.10754f);
			glUniform3f(matSpecularLoc, 0.99f, 0.01f, 0.01f);
			glUniform1f(matShineLoc, 0.8f);
			// Pressbase drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO5);
			glBufferData(GL_ARRAY_BUFFER, sizeof(pressBaseVertices), pressBaseVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			glm::mat4 model5;
			model5 = glm::translate(model5, glm::vec3(0.0f, 0.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model5));
			glDrawArrays(GL_TRIANGLES, 0, 72);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Texture for press stamp
			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, texture5);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "isTexture"), true);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "materialTexture.diffuse"), 5);
			matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.specular");
			matShineLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.shininess");
			glUniform3f(matSpecularLoc, 0.2f, 0.2f, 0.2f);
			glUniform1f(matShineLoc, 0.01f);
			// Press stamp side surface drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO1);
			glBufferData(GL_ARRAY_BUFFER, sizeof(bodyVertices), bodyVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			glm::mat4 model8;
			glm::vec3 stampOffset( 0.0f, 0.0f, std::min<GLfloat>(0.0, -0.3*sin(2*PI*tapeSpeed*(GLfloat)glfwGetTime()-PI/2)));
			model8 = glm::translate(model8, pressStampPosition + stampOffset);
			model8 = glm::scale(model8, glm::vec3(1.0f, 1.0f, 4.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model8));
			glDrawArrays(GL_TRIANGLE_STRIP, 0, (cylinderBodyVerticesCount * 2 + 2));
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Press stamp bases drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO2);
			glBufferData(GL_ARRAY_BUFFER, sizeof(baseVertices), baseVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			cylinderBaseCount = 2;
			for (GLuint i = 0; i < 2; ++i)
			{
				glm::mat4 model9;
				model9 = glm::translate(model9, pressStampBasesPosition[i]+ stampOffset);
				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model9));
				glDrawArrays(GL_TRIANGLE_FAN, 0, (cylinderBaseVerticesCount + 2));
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Room texture
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texture3);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "isTexture"), true);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "materialTexture.diffuse"), 3);
			matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.specular");
			matShineLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.shininess");
			glUniform3f(matSpecularLoc, 0.2f, 0.2f, 0.2f);
			glUniform1f(matShineLoc, 0.01f);
			// Room drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO6);
			glBufferData(GL_ARRAY_BUFFER, sizeof(roomVertices), roomVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			glm::mat4 model6;
			model6 = glm::scale(model6, glm::vec3(1, 1, 1));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model6));
			glDrawArrays(GL_TRIANGLES, 0, 30);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Ground texture
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture0);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "isTexture"), true);
			glUniform1i(glGetUniformLocation(ourShader.get_programID(), "materialTexture.diffuse"), 0);
			matSpecularLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.specular");
			matShineLoc = glGetUniformLocation(ourShader.get_programID(), "materialTexture.shininess");
			glUniform3f(matSpecularLoc, 0.9f, 0.9f, 0.2f);
			glUniform1f(matShineLoc, 0.7f);
			// Ground drawing
			glBindBuffer(GL_ARRAY_BUFFER, VBO7);
			glBufferData(GL_ARRAY_BUFFER, sizeof(groundVertices), groundVertices, GL_STATIC_DRAW);
			setVertexAttributes();
			glm::mat4 model7;
			model7 = glm::scale(model7, glm::vec3(20, 20, 1));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model7));
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);
			
			lightShader.Use();
			modelLoc = glGetUniformLocation(lightShader.get_programID(), "model");
			viewLoc = glGetUniformLocation(lightShader.get_programID(), "view");
			projLoc = glGetUniformLocation(lightShader.get_programID(), "projection");
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
			glm::mat4 lightModel;
			lightModel = glm::translate(lightModel, lightPos);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
			
			// Draw light source (lamp)
			glBindVertexArray(VAOLight);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);

			// Swap buffers
			glfwSwapBuffers(window);
		}

		glDeleteVertexArrays(1, &VAO);
		glDeleteVertexArrays(1, &VAOLight);
		glDeleteBuffers(1, &VBO1);
		glDeleteBuffers(1, &VBO2);
		glDeleteBuffers(1, &VBO3);
		glDeleteBuffers(1, &VBO4);
		glDeleteBuffers(1, &VBO5);
		glDeleteBuffers(1, &VBOLight);

		delete [] bodyVerticesPtr;
		delete [] baseVerticesPtr;
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	glfwTerminate();
	return 0;
}