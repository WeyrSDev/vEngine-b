#pragma once
#include "vInclude.h"
#include "vRay.h"
#include "vEnums.h"

namespace vEngine {
	class Frustum {
	public:
		Frustum(DirectX::CXMMATRIX matrix);
	private:
		Frustum();
	public:
		const DirectX::XMFLOAT4& Near() const;
		const DirectX::XMFLOAT4& Far() const;
		const DirectX::XMFLOAT4& Left() const;
		const DirectX::XMFLOAT4& Right() const;
		const DirectX::XMFLOAT4& Top() const;
		const DirectX::XMFLOAT4& Bottom() const;
		DirectX::XMVECTOR NearVector() const;
		DirectX::XMVECTOR FarVector() const;
		DirectX::XMVECTOR LeftVector() const;
		DirectX::XMVECTOR RightVector() const;
		DirectX::XMVECTOR TopVector() const;
		DirectX::XMVECTOR BottomVector() const;
		const DirectX::XMFLOAT3* Corners() const;
		DirectX::XMMATRIX Matrix() const;
		void SetMatrix(DirectX::CXMMATRIX matrix);
		void SetMatrix(const DirectX::XMFLOAT4X4& matrix);
	private:
		static Ray ComputeIntersectionLine(DirectX::FXMVECTOR p1, DirectX::FXMVECTOR p2);
		static DirectX::XMVECTOR ComputeIntersection(DirectX::FXMVECTOR& plane, Ray& ray);
	private:
		DirectX::XMFLOAT4X4 mMatrix;
		DirectX::XMFLOAT3 mCorners[8];
		DirectX::XMFLOAT4 mPlanes[6];
	};
}

