#pragma once
#include "vInclude.h"


namespace vEngine {
	class Keyframe {
		friend class BoneAnimation;
	private:
		Keyframe(float time, const DirectX::XMFLOAT3& translation, const DirectX::XMFLOAT4& rotationQuaternion, const DirectX::XMFLOAT3& scale);
	private:
		Keyframe();
		Keyframe(const Keyframe& rhs);
		Keyframe& operator=(const Keyframe& rhs);
	public:
		float Time() const;
		const DirectX::XMFLOAT3& Translation() const;
		const DirectX::XMFLOAT4& RotationQuaternion() const;
		const DirectX::XMFLOAT3& Scale() const;
		DirectX::XMVECTOR TranslationVector() const;
		DirectX::XMVECTOR RotationQuaternionVector() const;
		DirectX::XMVECTOR ScaleVector() const;
		DirectX::XMMATRIX Transform() const;
	private:
		float mTime;
		DirectX::XMFLOAT3 mTranslation;
		DirectX::XMFLOAT4 mRotationQuaternion;
		DirectX::XMFLOAT3 mScale;
	};
}