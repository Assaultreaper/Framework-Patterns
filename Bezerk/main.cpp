#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <glm/exponential.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderManager.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const glm::vec2 Resolution(800, 800);

GLfloat vertices[] =
{
    -0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f,
    -0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f,
    0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f,
    0.0f, 0.8f, 0.0f, 0.92f, 0.86f, 0.76f
};

GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4
};

int main()
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(Resolution.x, Resolution.y, "Bezerk", NULL, NULL);
    if (window == NULL)
    {
        printf("Window Creation Failed");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, Resolution.x, Resolution.y);

    Shader ShaderProgram("default.vert", "default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");

    float rotation = 0.0f;
    double prevTime = glfwGetTime();
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ShaderProgram.Activate();

        double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60)
        {
            rotation += 0.5f;
            prevTime = crntTime;
        }
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)(Resolution.x / Resolution.y), 0.1f, 100.0f);

        int modelLoc = glGetUniformLocation(ShaderProgram.ID, "model");
        int viewLoc = glGetUniformLocation(ShaderProgram.ID, "view");
        int projectionLoc = glGetUniformLocation(ShaderProgram.ID, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glUniform1f(uniID, 0.5f);
        VAO1.Bind();

        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0); // Change the number of indices to 18

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    ShaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
