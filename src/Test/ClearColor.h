#pragma once
#include "Test/Application.h"

namespace tests {
	class ClearColor : public Application
	{
	public:
		ClearColor();
		~ClearColor();
		void OnUpdate(float delta) override;
		void OnRender() override;
		void OnUIRender() override;
	private:
		float m_ClearColor[3];
	};
}