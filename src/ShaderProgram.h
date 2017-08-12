#pragma once

class ShaderProgram
{
	GLuint program_id;
public:
	// Read and compile shaders
	ShaderProgram(const GLchar* vertexPath, const GLchar* fragmentPath);
	// Use the program
	void Use() const
	{
		glUseProgram(get_programID());
	}
	// return program ID
	GLuint get_programID() const
	{
		return program_id;
	}
};