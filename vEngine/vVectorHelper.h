#pragma once
#include "vInclude.h"

namespace vEngine {
	class Vector2Helper {
	private:
		Vector2Helper();
		Vector2Helper(const Vector2Helper& rhs);
		Vector2Helper& operator=(const Vector2Helper& rhs);
	public:
		static const DirectX::XMFLOAT2 Zero;
		static const DirectX::XMFLOAT2 One;
	public:
		static std::string ToString(const DirectX::XMFLOAT2& vector);
	};

	class Vector3Helper {
	private:
		Vector3Helper();
		Vector3Helper(const Vector3Helper& rhs);
		Vector3Helper& operator=(const Vector3Helper& rhs);
	public:
		static const DirectX::XMFLOAT3 Zero;
		static const DirectX::XMFLOAT3 One;
		static const DirectX::XMFLOAT3 Forward;
		static const DirectX::XMFLOAT3 Backward;
		static const DirectX::XMFLOAT3 Up;
		static const DirectX::XMFLOAT3 Down;
		static const DirectX::XMFLOAT3 Right;
		static const DirectX::XMFLOAT3 Left;
	public:
		static std::string ToString(const DirectX::XMFLOAT3& vector);
	};

	class Vector4Helper {
	private:
		Vector4Helper();
		Vector4Helper(const Vector3Helper& rhs);
		Vector4Helper& operator=(const Vector3Helper& rhs);
	public:
		static const DirectX::XMFLOAT4 Zero;
		static const DirectX::XMFLOAT4 One;
	public:
		static std::string ToString(const DirectX::XMFLOAT4& vector);
	};
}