#pragma once
#include "vInclude.h"


namespace vEngine {
	class Keyframe {
		friend class BoneAnimation;
	private:
		Keyframe(float time, const XMFLOAT3& translation, const XMFLOAT4& rotationQuaternion, const XMFLOAT3& scale);
	private:
		Keyframe();
		Keyframe(const Keyframe& rhs);
		Keyframe& operator=(const Keyframe& rhs);
	public:
		float Time() const;
		const XMFLOAT3& Translation() const;
		const XMFLOAT4& RotationQuaternion() const;
		const XMFLOAT3& Scale() const;
		XMVECTOR TranslationVector() const;
		XMVECTOR RotationQuaternionVector() const;
		XMVECTOR ScaleVector() const;
		XMMATRIX Transform() const;
	private:
		float mTime;
		XMFLOAT3 mTranslation;
		XMFLOAT4 mRotationQuaternion;
		XMFLOAT3 mScale;
	};
}