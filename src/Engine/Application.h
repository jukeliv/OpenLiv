#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.h>
#include "GLErrorManager.h"

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include "Rendering/Renderer.h"

class Application
{
public:

    void Init(const int& width, const int& height, const std::string& title)
    {
        /* Initialize the library */
        ASSERT(glfwInit());

        glewInit();
        std::string title_c = "OpenLiv - ";
        title_c.append(title);
        /* Create a windowed mode window and its OpenGL context */
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        window = glfwCreateWindow(width, height, title_c.c_str(), nullptr, nullptr);

        if (!window)
            glfwTerminate();

        ASSERT(window);

        /* Make the window's context current */
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);//Enable V-Sync

        GLenum err = glewInit();
        if (GLEW_OK != err)
            /* Problem: glewInit failed, something is seriously wrong. */
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        ASSERT(GLEW_OK == err);

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));
    }

    virtual void Destroy()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwTerminate();
    }

    virtual void OnRun()
    {

    }

    void Run()
    {
        while (!glfwWindowShouldClose(window))
        {
            Renderer::Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            OnRun();

            #ifndef NDEBUG
            ImGui::Begin("Debug");
            ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
            ImGui::Text("Average % .3f ms", 1000.0f / ImGui::GetIO().Framerate);
            ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));
            ImGui::Text("GL Impl: %s", glGetString(GL_VENDOR));
            ImGui::Text("Graphics Card: %s", glGetString(GL_RENDERER));
            ImGui::Text("GLEW: %s", glewGetString(GLEW_VERSION));
            ImGui::Text("Shading Lenguaje: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
            ImGui::End();
            #elif OPENLIV_DEBUG_INFO
            ImGui::Begin("Debug");
            ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
            ImGui::Text("Graphics Card: %s", glGetString(GL_RENDERER));
            ImGui::Text("GLEW: %s", glewGetString(GLEW_VERSION));
            ImGui::End();
            #endif

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);

            glfwPollEvents();
        }
    }

    GLFWwindow* window;
};