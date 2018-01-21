#include "vPerspectiveCamera.h"
#include "vInclude.h"
#include "vEngine.h"
#include "vTime.h"
#include "vKeyboard.h"
#include "vMouse.h"
#include "vEnums.h"
#include "vStructs.h"
#include "vVectorHelper.h"

namespace vEngine {
	RTTI_DEFINITIONS(PerspectiveCamera)
	const float PerspectiveCamera::DefaultFieldOfView = XM_PIDIV4;
	PerspectiveCamera::PerspectiveCamera(Engine& game) :
		Camera(game),
		mFieldOfView(DefaultFieldOfView), mAspectRatio(game.AspectRatio())
	{
	}

	PerspectiveCamera::PerspectiveCamera(Engine& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance) :
		Camera(game, nearPlaneDistance, farPlaneDistance),
		mFieldOfView(fieldOfView), mAspectRatio(aspectRatio)
	{
	}

	PerspectiveCamera::~PerspectiveCamera()
	{
	}

	float PerspectiveCamera::AspectRatio() const
	{
		return mAspectRatio;
	}

	float PerspectiveCamera::FieldOfView() const
	{
		return mFieldOfView;
	}

	void PerspectiveCamera::UpdateProjectionMatrix()
	{
		XMMATRIX projectionMatrix = XMMatrixPerspectiveFovRH(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
		XMStoreFloat4x4(&mProjectionMatrix, projectionMatrix);
	}
}