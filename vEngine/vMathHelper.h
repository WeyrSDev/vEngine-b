#pragma once
#include "vInclude.h"

namespace vEngine {
	class MathHelper {
	public:
		static const float Infinity;
		static const float Pi;
		static float Clamp(float value, float min, float max);
		static float Saturate(float value);
		static UINT Saturate(UINT value);
		static float RandF();
		static float RandF(float a, float b);
		static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M);
		static DirectX::XMVECTOR RandUnitVec3();
		static DirectX::XMVECTOR RandHemisphereUnitVec3(DirectX::XMVECTOR n);
		template<typename T>
		static T Min(const T& a, const T& b)
		{
			return a < b ? a : b;
		}
		template<typename T>
		static T Max(const T& a, const T& b)
		{
			return a > b ? a : b;
		}
		template<typename T>
		static T Lerp(const T& a, const T& b, float t)
		{
			return a + (b - a)*t;
		}
		static float AngleFromXY(float x, float y);
	};
	const float Infinity = FLT_MAX;
	const float Pi = 3.1415926535f;

	inline DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out 
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		DirectX::XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		DirectX::XMVECTOR det = XMMatrixDeterminant(A);
		return XMMatrixTranspose(XMMatrixInverse(&det, A));
	}

	inline float MathHelper::Clamp(float value, float min, float max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	inline float MathHelper::Saturate(float value)
	{
		return value < 0.0f ? 0.0f : (value > 1.0f ? 1.0f : value);
	}

	inline UINT MathHelper::Saturate(UINT value)
	{
		return value < 0 ? 0 : (value > 255 ? 255 : value);
	}

	inline float MathHelper::AngleFromXY(float x, float y)
	{
		float theta = 0.0f;

		// Quadrant I or IV
		if (x >= 0.0f)
		{
			// If x = 0, then atanf(y/x) = +pi/2 if y > 0
			//                atanf(y/x) = -pi/2 if y < 0
			theta = atanf(y / x); // in [-pi/2, +pi/2]

			if (theta < 0.0f)
				theta += 2.0f*Pi; // in [0, 2*pi).
		}

		// Quadrant II or III
		else
			theta = atanf(y / x) + Pi; // in [0, 2*pi).

		return theta;
	}

	inline DirectX::XMVECTOR MathHelper::RandUnitVec3()
	{
		DirectX::XMVECTOR One = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
		DirectX::XMVECTOR Zero = DirectX::XMVectorZero();

		// Keep trying until we get a point on/in the hemisphere.
		while (true)
		{
			// Generate random point in the cube [-1,1]^3.
			DirectX::XMVECTOR v = DirectX::XMVectorSet(MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), 0.0f);

			// Ignore points outside the unit sphere in order to get an even distribution 
			// over the unit sphere.  Otherwise points will clump more on the sphere near 
			// the corners of the cube.

			if (DirectX::XMVector3Greater(DirectX::XMVector3LengthSq(v), One))
				continue;

			return DirectX::XMVector3Normalize(v);
		}
	}

	inline DirectX::XMVECTOR MathHelper::RandHemisphereUnitVec3(DirectX::XMVECTOR n)
	{
		DirectX::XMVECTOR One = DirectX::XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
		DirectX::XMVECTOR Zero = DirectX::XMVectorZero();

		// Keep trying until we get a point on/in the hemisphere.
		while (true)
		{
			// Generate random point in the cube [-1,1]^3.
			DirectX::XMVECTOR v = XMVectorSet(MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), MathHelper::RandF(-1.0f, 1.0f), 0.0f);

			// Ignore points outside the unit sphere in order to get an even distribution 
			// over the unit sphere.  Otherwise points will clump more on the sphere near 
			// the corners of the cube.

			if (XMVector3Greater(XMVector3LengthSq(v), One))
				continue;

			// Ignore points in the bottom hemisphere.
			if (XMVector3Less(XMVector3Dot(n, v), Zero))
				continue;

			return XMVector3Normalize(v);
		}
	}

	inline float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Returns random float in [a, b).
	inline float RandF(float a, float b)
	{
		return a + RandF()*(b - a);
	}

}

