#pragma once
#include "vInclude.h"

namespace vEngine {
	class MatrixHelper {
	private:
		MatrixHelper();
		MatrixHelper(const MatrixHelper& p_Rhs);
		MatrixHelper& operator=(const MatrixHelper& p_Rhs);
	public:
		static const XMFLOAT4X4 Identity;
	public:
		static void GetForward(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector);
		static void GetUp(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector);
		static void GetRight(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector);
		static void GetTranslation(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector);
		static void SetForward(XMMATRIX& p_Matrix, XMFLOAT3 &p_Forward);
		static void SetUp(XMMATRIX& p_Matrix, XMFLOAT3 &p_Up);
		static void SetRight(XMMATRIX& p_Matrix, XMFLOAT3 &p_Right);
		static void SetTranslation(XMMATRIX& p_Matrix, XMFLOAT3 &p_Translation);
	};
}