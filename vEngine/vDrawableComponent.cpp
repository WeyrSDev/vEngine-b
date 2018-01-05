#include "vDrawableComponent.h"


namespace vEngine {
	RTTI_DEFINITIONS(DrawableComponent)

		DrawableComponent::DrawableComponent()
		: Component(), mVisible(true), mCamera(nullptr)
	{
	}

	DrawableComponent::DrawableComponent(Engine& game)
		: Component(game), mVisible(true), mCamera(nullptr)
	{
	}

	DrawableComponent::DrawableComponent(Engine& game, Camera& camera)
		: Component(game), mVisible(true), mCamera(&camera)
	{
	}

	DrawableComponent::~DrawableComponent()
	{
	}

	bool DrawableComponent::Visible() const
	{
		return mVisible;
	}

	void DrawableComponent::SetVisible(bool visible)
	{
		mVisible = visible;
	}

	Camera* DrawableComponent::GetCamera()
	{
		return mCamera;
	}

	void DrawableComponent::SetCamera(Camera* camera)
	{
		mCamera = camera;
	}

	void DrawableComponent::Draw(const Time& gameTime)
	{
	}
}