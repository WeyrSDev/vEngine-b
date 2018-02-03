#pragma once
#include "vCamera.h"

namespace vEngine {
	class OrthographicCamera : public Camera {
		RTTI_DECLARATIONS(OrthographicCamera, Camera)
	public:
		OrthographicCamera(Engine& game);
		OrthographicCamera(Engine& game, float viewWidth, float viewHeight, float nearPlaneDistance, float farPlaneDistance);
		virtual ~OrthographicCamera();
	private:
		OrthographicCamera(const OrthographicCamera& rhs);
		OrthographicCamera& operator=(const OrthographicCamera& rhs);
	public:
		float ViewWidth() const;
		void SetViewWidth(float viewWidth);
		float ViewHeight() const;
		void SetViewHeight(float viewHeight);
		virtual void UpdateProjectionMatrix() override;
	public:
		static const float DefaultViewWidth;
		static const float DefaultViewHeight;
	protected:
		float mViewWidth;
		float mViewHeight;
	};
}