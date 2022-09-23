#pragma once

#include "Engine/Application.h"
#include "Examples/ExampleTemplate.h"

class MainApplication : public Application
{
public:
	examples::ExampleTemplate* currentApp = nullptr;
	examples::AppsMenu* appMenu = new examples::AppsMenu(currentApp);

	void OnRun() override;

	void Destroy() override;
};