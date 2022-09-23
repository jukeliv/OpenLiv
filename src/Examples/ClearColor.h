#pragma once
#include "Examples/ExampleTemplate.h"

namespace examples {
	class ClearColor : public ExampleTemplate
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