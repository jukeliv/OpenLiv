#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>
#include "GLErrorManager.h"

#include "Rendering/Buffers/VertexBuffer.h"
#include "Rendering/Buffers/IndexBuffer.h"
#include "Rendering/Buffers/VertexArray.h"
#include "Rendering/Utils/Shader.h"
#include "Rendering/Renderer.h"
#include "Rendering/Utils/Texture.h"

#include <iostream>

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    auto* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);//Enable V-Sync

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    {
        const float vertexData[] = {
            /*    Positions    Texture Coords */
                -0.5f, -0.5f,   0.0f, 0.0f,     //0
                 0.5f, -0.5f,   1.0f, 0.0f,     //1
                 0.5f,  0.5f,   1.0f, 1.0f,     //2
                -0.5f,  0.5f,   0.0f, 1.0f      //3
        };

        const unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        glCall(glEnable(GL_BLEND));
        glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(vertexData, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.PushData<float>(2);
        layout.PushData<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6, GL_UNSIGNED_INT);
        Shader mShader("Main");
        mShader.Bind();
        //fixing texture streching
        //projection * view * model = final vertex position
        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);//Set aspect ratio to 4:3
        glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3(-1.0f, 0.0f, 0.0f));//Camera position
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.65f, 0.0f));//Object position

        glm::mat4 mvp = proj * view * model;

        mShader.setUniform<glm::mat4>("uMVP", mvp);

        Texture mTex("res/textures/ricardo.png");
        mTex.Bind();
        mShader.setUniform<int>("uTexture", 0);

        va.UnBind();
        vb.UnBind();
        ib.UnBind();
        mShader.UnBind();

        Renderer renderer;

        float v = 0;
        float increment = 0.01f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            renderer.RenderScene(va, ib, mShader);

            if (v > 1.0f)
                increment = -0.05f;
            else if (v < 0.0f)
                increment = 0.05f;

            v += increment;

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}