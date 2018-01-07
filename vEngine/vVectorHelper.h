#pragma once
#include "vInclude.h"

namespace vEngine {
	class Vector2Helper {
	private:
		Vector2Helper();
		Vector2Helper(const Vector2Helper& p_Rhs);
		Vector2Helper& operator=(const Vector2Helper& p_Rhs);
	public:
		static const XMFLOAT2 Zero;
		static const XMFLOAT2 One;
	public:
		static std::string ToString(const XMFLOAT2& p_Vector);
	};

	class Vector3Helper {
	private:
		Vector3Helper();
		Vector3Helper(const Vector3Helper& p_Rhs);
		Vector3Helper& operator=(const Vector3Helper& p_Rhs);
	public:
		static const XMFLOAT3 Zero;
		static const XMFLOAT3 One;
		static const XMFLOAT3 Forward;
		static const XMFLOAT3 Backward;
		static const XMFLOAT3 Up;
		static const XMFLOAT3 Down;
		static const XMFLOAT3 Right;
		static const XMFLOAT3 Left;
	public:
		static std::string ToString(const XMFLOAT3& p_Vector);
	};

	class Vector4Helper {
	private:
		Vector4Helper();
		Vector4Helper(const Vector3Helper& p_Rhs);
		Vector4Helper& operator=(const Vector3Helper& p_Rhs);
	public:
		static const XMFLOAT4 Zero;
		static const XMFLOAT4 One;
	public:
		static std::string ToString(const XMFLOAT4& p_Vector);
	};
}