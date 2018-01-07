#include "vDrawableComponent.h"


namespace vEngine {
	RTTI_DEFINITIONS(DrawableComponent)

		DrawableComponent::DrawableComponent()
		: Component(), m_Visible(true), m_Camera(nullptr)
	{
	}

	DrawableComponent::DrawableComponent(Engine& p_Engine)
		: Component(p_Engine), m_Visible(true), m_Camera(nullptr)
	{
	}

	DrawableComponent::DrawableComponent(Engine& p_Engine, Camera& p_Camera)
		: Component(p_Engine), m_Visible(true), m_Camera(&p_Camera)
	{
	}

	DrawableComponent::~DrawableComponent()
	{
	}

	bool DrawableComponent::Visible() const
	{
		return m_Visible;
	}

	void DrawableComponent::SetVisible(bool p_Visible)
	{
		m_Visible = p_Visible;
	}

	Camera* DrawableComponent::GetCamera()
	{
		return m_Camera;
	}

	void DrawableComponent::SetCamera(Camera* p_Camera)
	{
		m_Camera = p_Camera;
	}

	void DrawableComponent::Draw(const Time& p_EngineTime)
	{
	}
}