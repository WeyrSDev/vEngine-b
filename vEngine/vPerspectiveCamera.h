#pragma once
#include "vCamera.h"

namespace vEngine {
	class PerspectiveCamera : public Camera {
		RTTI_DECLARATIONS(PerspectiveCamera, Camera)
	public:
		PerspectiveCamera(Engine& game);
		PerspectiveCamera(Engine& game, float fieldOfView, float aspectRatio, float nearPlaneDistance, float farPlaneDistance);
		virtual ~PerspectiveCamera();
	private:
		PerspectiveCamera(const PerspectiveCamera& rhs);
		PerspectiveCamera& operator=(const PerspectiveCamera& rhs);
	public:
		float AspectRatio() const;
		float FieldOfView() const;
		virtual void UpdateProjectionMatrix() override;
	public:
		static const float DefaultFieldOfView;
	protected:
		float mFieldOfView;
		float mAspectRatio;
	};
}