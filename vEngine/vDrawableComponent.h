#pragma once
#include "vComponent.h"

namespace vEngine {
	class Camera;
	class DrawableComponent : public Component {
		RTTI_DECLARATIONS(DrawableComponent, Component)
	public:
		DrawableComponent();
		DrawableComponent(Engine& game);
		DrawableComponent(Engine& game, Camera& camera);
		virtual ~DrawableComponent();
	private:
		DrawableComponent(const DrawableComponent& rhs);
		DrawableComponent& operator=(const DrawableComponent& rhs);
	public:
		bool Visible() const;
		void SetVisible(bool visible);
		Camera* GetCamera();
		void SetCamera(Camera* camera);
		virtual void Draw(const Time& gameTime);
	protected:
		bool mVisible;
		Camera* mCamera;
	};
}