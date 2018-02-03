#include "vOrthographicCamera.h"
#include "vEngine.h"
#include "vTime.h"
#include "vKeyboard.h"
#include "vMouse.h"
#include "vEnums.h"
#include "vStructs.h"
#include "vVectorHelper.h"

namespace vEngine {
	RTTI_DEFINITIONS(OrthographicCamera)

		const float OrthographicCamera::DefaultViewWidth = 100.0f;
	const float OrthographicCamera::DefaultViewHeight = 100.0f;

	OrthographicCamera::OrthographicCamera(Engine& game) :
		Camera(game),
		mViewWidth(DefaultViewWidth), mViewHeight(DefaultViewHeight)
	{
	}

	OrthographicCamera::OrthographicCamera(Engine& game, float viewWidth, float viewHeight, float nearPlaneDistance, float farPlaneDistance) :
		Camera(game, nearPlaneDistance, farPlaneDistance),
		mViewWidth(viewWidth), mViewHeight(viewHeight)
	{
	}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	float OrthographicCamera::ViewWidth() const
	{
		return mViewWidth;
	}

	void OrthographicCamera::SetViewWidth(float viewWidth)
	{
		if (viewWidth > 0.0f)
		{
			mViewWidth = viewWidth;
		}
	}

	float OrthographicCamera::ViewHeight() const
	{
		return mViewHeight;
	}

	void OrthographicCamera::SetViewHeight(float viewHeight)
	{
		if (viewHeight > 0.0f)
		{
			mViewHeight = viewHeight;
		}
	}

	void OrthographicCamera::UpdateProjectionMatrix()
	{
		DirectX::XMMATRIX projectionMatrix = XMMatrixOrthographicRH(mViewWidth, mViewHeight, mNearPlaneDistance, mFarPlaneDistance);
		XMStoreFloat4x4(&mProjectionMatrix, projectionMatrix);
	}
}