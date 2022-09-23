#pragma once
#include "Examples/Application.h"

namespace examples {
	class ClearColor : public Application
	{
	public:
		ClearColor();
		~ClearColor();
		void OnRender() override;
		void OnUIRender() override;
	private:
		float m_ClearColor[3];
	};
}