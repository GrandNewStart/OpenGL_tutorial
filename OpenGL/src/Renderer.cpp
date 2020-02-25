#include <iostream>

#include "Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << ") " << function << " " << file << ": " << line << std::endl;
        return false;
    }
    return true;
}

Renderer::Renderer() {};
Renderer::~Renderer() {};

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    /*Bind Vertex Array*/
    va.Bind();
    /*Bind Index Buffer*/
    ib.Bind();

    /*DRAW!*/
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); 
}