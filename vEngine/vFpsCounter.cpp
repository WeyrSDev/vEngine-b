#include "vFpsCounter.h"
#include <sstream>
#include <iomanip>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include "vEngine.h"
#include "vUtility.h"

namespace vEngine {

	RTTI_DEFINITIONS(FpsCounter)

		FpsCounter::FpsCounter(Engine& p_Engine)
		: DrawableComponent(p_Engine), m_SpriteBatch(nullptr), m_SpriteFont(nullptr), m_TextPosition(0.0f, 60.0f),
		m_FrameCount(0), m_FrameRate(0), m_LastTotalElapsedTime(0.0)
	{
	}

	FpsCounter::~FpsCounter()
	{
		DeleteObject(m_SpriteFont);
		DeleteObject(m_SpriteBatch);
	}

	XMFLOAT2& FpsCounter::TextPosition()
	{
		return m_TextPosition;
	}

	int FpsCounter::FrameRate() const
	{
		return m_FrameCount;
	}

	void FpsCounter::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

		m_SpriteBatch = new SpriteBatch(m_Engine->Direct3DDeviceContext());
		m_SpriteFont = new SpriteFont(m_Engine->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");
	}

	void FpsCounter::Update(const Time& p_EngineTime)
	{
		if (p_EngineTime.TotalEngineTime() - m_LastTotalElapsedTime >= 1)
		{
			m_LastTotalElapsedTime = p_EngineTime.TotalEngineTime();
			m_FrameRate = m_FrameCount;
			m_FrameCount = 0;
		}

		m_FrameCount++;
	}

	void FpsCounter::Draw(const Time& p_EngineTime)
	{
		m_SpriteBatch->Begin();

		std::wostringstream fpsLabel;
		fpsLabel << std::setprecision(4) << L"Frame Rate: " << m_FrameRate << "    Total Elapsed Time: " << p_EngineTime.TotalEngineTime();
		m_SpriteFont->DrawString(m_SpriteBatch, fpsLabel.str().c_str(), m_TextPosition);

		m_SpriteBatch->End();
	}
}