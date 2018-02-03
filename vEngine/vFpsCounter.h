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
		FpsCounter(Engine& game);
		~FpsCounter();
	private:
		FpsCounter();
		FpsCounter(const FpsCounter& rhs);
		FpsCounter& operator=(const FpsCounter& rhs);
	public:
		DirectX::XMFLOAT2& TextPosition();
		int FrameRate() const;
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
		virtual void Draw(const Time& gameTime) override;
	private:
		SpriteBatch* mSpriteBatch;
		SpriteFont* mSpriteFont;
		DirectX::XMFLOAT2 mTextPosition;
		int mFrameCount;
		int mFrameRate;
		double mLastTotalElapsedTime;
	};
}