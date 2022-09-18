#include "Core.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glewInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    auto* window = glfwCreateWindow(640, 640, "Hello World", nullptr, nullptr);
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
            /*    Positions    */
                -0.5f, -0.5f,
                 0.5f, -0.5f,
                 0.5f,  0.5f,
                -0.5f,  0.5f
        };

        const unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexArray va;
        VertexBuffer vb(vertexData, 4 * 2 * sizeof(float));
        
        VertexBufferLayout layout;
        layout.PushData<float>(3);
        va.AddBuffer(vb, layout);

        glCall(glEnableVertexAttribArray(0));
        glCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));

        IndexBuffer ib(indices, 6);

        Shader mainShader("Main");
        
        va.UnBind();
        mainShader.UnBind();
        vb.UnBind();
        ib.UnBind();

        float v = 0;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            mainShader.Bind();
            mainShader.setVec3("uColor", Vec3(v,v,v));

            va.Bind();
            ib.Bind();

            glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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

        mainShader.~Shader();
    }

    glfwTerminate();
    return 0;
}