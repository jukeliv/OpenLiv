#pragma once
#include <Rendering/Renderer.h>
#include <ImGui/imgui.h>
#include <GLErrorManager.h>
#include <functional>
#include <vector>

namespace examples {
	class ExampleTemplate {
	public:
		ExampleTemplate() {}
		virtual ~ExampleTemplate() {}
		virtual void OnUpdate(float delta) {}
		virtual void OnRender() {}
		virtual void OnUIRender() {}
	};

	class AppsMenu : public ExampleTemplate
	{
	public:
		AppsMenu(ExampleTemplate*& appPointer);
		~AppsMenu();

		void OnUIRender() override;

		template<typename T>
		void RegisterApp(const std::string& name)
		{
			m_Applications.push_back(std::make_pair(name, []() {return new T(); }));
			std::cout << "Application " << name << " Succefully registered" << std::endl;
		}
	private:
		ExampleTemplate*& m_CurrentApp;
		std::vector<std::pair<std::string, std::function<ExampleTemplate* ()>>> m_Applications;
	};
}