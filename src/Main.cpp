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
#include "Rendering/Utils/Textures/Texture.h"

#include <Examples/DrawTexture2D.h>
#include <Examples/ClearColor.h>
#include <Examples/MultipleTextures.h>

#include <iostream>

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glewInit();

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    auto* window = glfwCreateWindow(854, 480, "OpenLiv", nullptr, nullptr);
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

    examples::Application* currentApp = nullptr;
    examples::AppsMenu* appMenu = new examples::AppsMenu(currentApp);
    currentApp = appMenu;

    appMenu->RegisterApp<examples::ClearColor>("Clear Color");
    appMenu->RegisterApp<examples::DrawTexture2D>("Draw Texture");
    appMenu->RegisterApp<examples::MultipleTextures>("Multiple Textures");

    {
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            /* Render here */
            Renderer::Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            
            if (currentApp)
            {
                currentApp->OnUpdate(1.0f / ImGui::GetIO().Framerate);

                currentApp->OnRender();

                ImGui::Begin("Test");

                if (currentApp != appMenu && ImGui::Button("<-"))
                {
                    delete currentApp;
                    glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
                    currentApp = appMenu;
                }

                currentApp->OnUIRender();

                ImGui::End();
            }

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

        delete currentApp;
        if (currentApp != appMenu)
            delete appMenu;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}