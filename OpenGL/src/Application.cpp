#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    ///Setting up Context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    /* Initate GLEW */
    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }
    /* Check (OpenGL version) - Build (GPU driver version)*/
    std::cout << glGetString(GL_VERSION) << std::endl;

    {
        float positions[] = {
            -0.5f,-0.5f,
             0.5f,-0.5f,
             0.5f, 0.5f,
            -0.5f, 0.5f
        };

        unsigned int indices[] = { 0, 1, 2,
                                  2, 3, 0 };

        /*Setting up Vertex Array*/
        VertexArray va;
        /*Setting up Vertex Buffer*/
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        /*Setting Layouts for the Vertex Buffer*/
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        /*Setting up Index Buffer*/
        IndexBuffer ib(indices, 6);

        /*Setting up Shader*/
        Shader shader("res/shaders/Basic.shader");
        /*Using Shader*/
        shader.Bind();
        /*Setting Uniform*/
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        /*Unbinding Everything*/
        va.Unbind(); 
        shader.Unbind();
        vb.Unbind();
        ib.Unbind();

        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            /*Use Shader*/
            shader.Bind();
            /*Set up Uniform*/
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
           
            /*Bind VAO, Bind IB, DRAW!*/
            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));
            /* Poll for and process events */
            GLCall(glfwPollEvents());
        }
    }
    glfwTerminate();
    return 0;
}