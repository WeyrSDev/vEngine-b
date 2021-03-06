#pragma once
#include "vInclude.h"

namespace vEngine {
	class MatrixHelper {
	private:
		MatrixHelper();
		MatrixHelper(const MatrixHelper& rhs);
		MatrixHelper& operator=(const MatrixHelper& rhs);
	public:
		static const DirectX::XMFLOAT4X4 Identity;
		static const DirectX::XMFLOAT4X4 Zero;
	public:
		static void GetForward(DirectX::CXMMATRIX matrix, DirectX::XMFLOAT3 &vector);
		static void GetUp(DirectX::CXMMATRIX matrix, DirectX::XMFLOAT3 &vector);
		static void GetRight(DirectX::CXMMATRIX matrix, DirectX::XMFLOAT3 &vector);
		static void GetTranslation(DirectX::CXMMATRIX matrix, DirectX::XMFLOAT3 &vector);
		static void SetForward(DirectX::XMMATRIX& matrix, DirectX::XMFLOAT3 &forward);
		static void SetUp(DirectX::XMMATRIX& matrix, DirectX::XMFLOAT3 &up);
		static void SetRight(DirectX::XMMATRIX& matrix, DirectX::XMFLOAT3 &right);
		static void SetTranslation(DirectX::XMMATRIX& matrix, DirectX::XMFLOAT3 &translation);
	};
}