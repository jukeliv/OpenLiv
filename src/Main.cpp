#include "MainApplication.h"

#include <Examples/DrawTexture2D.h>
#include <Examples/ClearColor.h>
#include <Examples/MultipleTextures.h>

int main(void)
{
    MainApplication app;
    app.Init(854, 480, "TITLE");

    app.currentApp = engine.appMenu;

    app.appMenu->RegisterApp<examples::ClearColor>("Clear Color");
    app.appMenu->RegisterApp<examples::DrawTexture2D>("Draw Texture");
    app.appMenu->RegisterApp<examples::MultipleTextures>("Multiple Textures");

    app.Run();
    
    app.Destroy();

    return 0;
}