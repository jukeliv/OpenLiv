#pragma once
#include <Rendering/Renderer.h>
#include <ImGui/imgui.h>
#include <GLErrorManager.h>
#include <functional>
#include <vector>

namespace tests {
	class Application {
	public:
		Application() {}
		virtual ~Application() {}
		virtual void OnUpdate(float delta) {}
		virtual void OnRender(Renderer& renderer) {}
		virtual void OnUIRender() {}
	};

	class AppsMenu : public Application
	{
	public:
		AppsMenu(Application*& appPointer);
		~AppsMenu();

		void OnUIRender() override;

		template<typename T>
		void RegisterApp(const std::string& name)
		{
			m_Applications.push_back(std::make_pair(name, []() {return new T(); }));
			std::cout << "Application " << name << " Succefully registered" << std::endl;
		}
	private:
		Application*& m_CurrentApp;
		std::vector<std::pair<std::string, std::function<Application* ()>>> m_Applications;
	};
}