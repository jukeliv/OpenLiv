#pragma once
#include <Rendering/Renderer.h>
#include <ImGui/imgui.h>
#include <GLErrorManager.h>

namespace tests {
	class Application {
	public:
		Application() {}
		virtual ~Application() {}
		virtual void OnUpdate(float delta) {}
		virtual void OnRender() {}
		virtual void OnUIRender() {}
	};
}