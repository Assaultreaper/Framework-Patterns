#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO VBO, GLuint Layout, GLuint numComponent, GLenum type, GLsizeiptr stride, void* offset)
{
    Bind(); // Bind the VAO before setting up the attribute pointer
    VBO.Bind();
    glVertexAttribPointer(Layout, numComponent, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(Layout); // Use the provided layout
    VBO.Unbind();
    Unbind(); // Unbind the VAO after setting up the attribute pointer
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}
