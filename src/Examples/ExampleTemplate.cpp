#include "Examples/ExampleTemplate.h"

namespace examples {
	AppsMenu::AppsMenu(ExampleTemplate*& appPointer)
		: m_CurrentApp(appPointer)
	{

	}

	AppsMenu::~AppsMenu()
	{
	}

	void AppsMenu::OnUIRender()
	{
		for (auto& app : m_Applications)
		{
			if (ImGui::Button(app.first.c_str()))
			{
				m_CurrentApp = app.second();
			}
		}
	}
}