#include "vFpsCounter.h"
#include <sstream>
#include <iomanip>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "vEngine.h"
#include "vUtility.h"

namespace vEngine {

	RTTI_DEFINITIONS(FpsCounter)

	FpsCounter::FpsCounter(Engine& game)
		: DrawableComponent(game), mSpriteBatch(nullptr), mSpriteFont(nullptr), mTextPosition(0.0f, 60.0f),
		mFrameCount(0), mFrameRate(0), mLastTotalElapsedTime(0.0)
	{
	}

	FpsCounter::~FpsCounter()
	{
		DeleteObject(mSpriteFont);
		DeleteObject(mSpriteBatch);
	}

	DirectX::XMFLOAT2& FpsCounter::TextPosition()
	{
		return mTextPosition;
	}

	int FpsCounter::FrameRate() const
	{
		return mFrameCount;
	}

	void FpsCounter::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

		mSpriteBatch = new SpriteBatch(mGame->Direct3DDeviceContext());
		mSpriteFont = new SpriteFont(mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");
	}

	void FpsCounter::Update(const Time& gameTime)
	{
		if (gameTime.TotalGameTime() - mLastTotalElapsedTime >= 1)
		{
			mLastTotalElapsedTime = gameTime.TotalGameTime();
			mFrameRate = mFrameCount;
			mFrameCount = 0;
		}

		mFrameCount++;
	}

	void FpsCounter::Draw(const Time& gameTime)
	{
		mSpriteBatch->Begin();

		std::wostringstream fpsLabel;
		fpsLabel << std::setprecision(4) << L"Frame Rate: " << mFrameRate << "    Total Elapsed Time: " << gameTime.TotalGameTime();
		mSpriteFont->DrawString(mSpriteBatch, fpsLabel.str().c_str(), mTextPosition);

		mSpriteBatch->End();
	}
}