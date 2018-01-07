#pragma once
#include "vComponent.h"

namespace vEngine {
	class Camera;
	class DrawableComponent : public Component {
		RTTI_DECLARATIONS(DrawableComponent, Component)
	public:
		DrawableComponent();
		DrawableComponent(Engine& p_Engine);
		DrawableComponent(Engine& p_Engine, Camera& p_Camera);
		virtual ~DrawableComponent();
	private:
		DrawableComponent(const DrawableComponent& p_Rhs);
		DrawableComponent& operator=(const DrawableComponent& p_Rhs);
	public:
		bool Visible() const;
		void SetVisible(bool p_Visible);
		Camera* GetCamera();
		void SetCamera(Camera* p_Camera);
		virtual void Draw(const Time& p_EngineTime);
	protected:
		bool m_Visible;
		Camera* m_Camera;
	};
}