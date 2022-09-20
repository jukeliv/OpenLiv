#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>
#include "GLErrorManager.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

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
    auto* window = glfwCreateWindow(640, 480, "OpenLiv", nullptr, nullptr);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    {
        const float vertexData[] = {
            /*    Positions    Texture Coords */
                -0.5f, -0.5f,   0.0f, 0.0f,     //0
                 0.5f, -0.5f,   1.0f, 0.0f,     //1
                 0.5f,  0.5f,   1.0f, 1.0f,     //2
                -0.5f,  0.5f,   0.0f, 1.0f      //3
        };

        const uint32_t indices[] = {
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
        Texture mTex("res/textures/ricardo.png");
        mTex.Bind();
        mShader.setUniform<int>("uTexture", 0);
        va.UnBind();
        vb.UnBind();
        ib.UnBind();
        mShader.UnBind();

        glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);//Set aspect ratio to 4:3
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));//Camera position

        ImVec4 color(1.0f, 1.0f, 1.0f, 1.0f);
        float v = 1.0f;
        float increment = 0.01f;

        glm::vec3 translation(0, 0, 0);
        glm::vec3 translationB(1, 1, 0);

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glCall(glClearColor(color.x, color.y, color.z, 1.0f));
            renderer.Clear();

            mShader.setUniform<float>("uAlpha", v);


            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::SliderFloat("Alpha", &v, 0.0f, 1.0f);
                ImGui::ColorEdit3("Color", (float*)&color);
                ImGui::SliderFloat3("Position", &translation.x, -2.0f, 2.0f);
                ImGui::SliderFloat3("Position 2", &translationB.x, -2.0f, 2.0f);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);//Object position
                //projection * view * model = final vertex position
                glm::mat4 mvp = proj * view * model;
                mShader.Bind();
                mShader.setUniform<glm::mat4>("uMVP", mvp);

                renderer.RenderScene(va, ib, mShader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);//Object position
                //projection * view * model = final vertex position
                glm::mat4 mvp = proj * view * model;
                mShader.Bind();
                mShader.setUniform<glm::mat4>("uMVP", mvp);

                renderer.RenderScene(va, ib, mShader);
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}