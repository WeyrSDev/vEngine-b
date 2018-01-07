#pragma once
#include "vDrawableComponent.h"

namespace DirectX
{
	class SpriteBatch;
	class SpriteFont;
}

namespace vEngine {
	class FpsCounter : public DrawableComponent {
		RTTI_DECLARATIONS(FpsCounter, DrawableComponent)
	public:
		FpsCounter(Engine& p_Engine);
		~FpsCounter();
	private:
		FpsCounter();
		FpsCounter(const FpsCounter& p_Rhs);
		FpsCounter& operator=(const FpsCounter& p_Rhs);
	public:
		XMFLOAT2 & TextPosition();
		int FrameRate() const;
		virtual void Initialize() override;
		virtual void Update(const Time& p_EngineTime) override;
		virtual void Draw(const Time& p_EngineTime) override;
	private:
		SpriteBatch* m_SpriteBatch;
		SpriteFont* m_SpriteFont;
		XMFLOAT2 m_TextPosition;
		int m_FrameCount;
		int m_FrameRate;
		double m_LastTotalElapsedTime;
	};
}