#include "MainApplication.h"

void MainApplication::Destroy()
{
    if (currentApp != appMenu)
        delete appMenu;
    delete currentApp;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

void MainApplication::OnRun()
{
    if (currentApp)
    {
        currentApp->OnUpdate(0.0f);

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
}