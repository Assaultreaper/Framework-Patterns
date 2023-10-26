#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Function to load and compile a shader

GLuint CompileShader(GLenum shaderType, const char* shaderSource)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	//Check for errors
	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[512];
		glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
		printf("Shader Compilation error: %d", infoLog);

		return 0;
	}
	return shader;
}

//Function to create a shader program and link shaders
GLuint CompileShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	if (vertexShader == 0 || fragmentShader == 0)
	{
		return 0;
	}

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);

	//Check for Linking Errors;
	GLint success;
	GLchar infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
		printf("Shader Program Linking Error");
		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

int WindowHeight = 1080;
int WindowWidth = 1920;

int main()
{
	if (!glfwInit())
	{
		printf("Failed to Initialize glfw");
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WindowHeight, WindowWidth, "Beserk, On the weekend", nullptr, nullptr);
	if (!window)
	{
		printf("Faile to Create GLFW Window"); 
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLAD to load openGl Functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to Initialize GLAD");
		glfwTerminate();
		return -1;
	}

	const char* vertedShaderSource;
	const char* fragmentShaderSource;
	// 
	//load your 3d model into a voa and vob
	//load the model using your model loading code
	// 
	// setup matrices
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.f / 600.0f, 0.1f, 100.0f);

	//Use the shader Program
	glUseProgram(ShaderProgram);

	// Set Uniform Matrices
	int modelLoc = glGetUniformLocation(ShaderProgram, "model");
	int viewLoc = glGetUniformLocation(ShaderProgram, "view");
	int projectionLoc = glGetUniformLocation(ShaderProgram, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//while rendering loop.

	while (!glfwWindowShouldClose(window))
	{
		// Process user input, clear the screen ,render, swap buffer.

		glfwPollEvents();
	}

	//cleanup

	glfwTerminate();
	return 0;
}