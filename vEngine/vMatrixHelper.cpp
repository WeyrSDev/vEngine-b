#include "vMatrixHelper.h"


namespace vEngine {
	const XMFLOAT4X4 MatrixHelper::Identity = XMFLOAT4X4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	void MatrixHelper::GetForward(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector)
	{
		XMFLOAT4 m3;
		XMStoreFloat4(&m3, p_Matrix.r[2]);

		p_Vector.x = -m3.x;
		p_Vector.y = -m3.y;
		p_Vector.z = -m3.z;
	}

	void MatrixHelper::GetUp(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector)
	{
		XMFLOAT4 m2;
		XMStoreFloat4(&m2, p_Matrix.r[1]);

		p_Vector.x = m2.x;
		p_Vector.y = m2.y;
		p_Vector.z = m2.z;
	}

	void MatrixHelper::GetRight(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector)
	{
		XMFLOAT4 m1;
		XMStoreFloat4(&m1, p_Matrix.r[0]);

		p_Vector.x = m1.x;
		p_Vector.y = m1.y;
		p_Vector.z = m1.z;
	}

	void MatrixHelper::GetTranslation(CXMMATRIX p_Matrix, XMFLOAT3 &p_Vector)
	{
		XMFLOAT4 m4;
		XMStoreFloat4(&m4, p_Matrix.r[3]);

		p_Vector.x = m4.x;
		p_Vector.y = m4.y;
		p_Vector.z = m4.z;
	}

	void MatrixHelper::SetForward(XMMATRIX& p_Matrix, XMFLOAT3 &p_Forward)
	{
		XMFLOAT4 m3;
		XMStoreFloat4(&m3, p_Matrix.r[2]);

		m3.x = -p_Forward.x;
		m3.y = -p_Forward.y;
		m3.z = -p_Forward.z;

		p_Matrix.r[2] = XMLoadFloat4(&m3);
	}

	void MatrixHelper::SetUp(XMMATRIX& p_Matrix, XMFLOAT3 &p_Up)
	{
		XMFLOAT4 m2;
		XMStoreFloat4(&m2, p_Matrix.r[1]);

		m2.x = p_Up.x;
		m2.y = p_Up.y;
		m2.z = p_Up.z;

		p_Matrix.r[1] = XMLoadFloat4(&m2);
	}

	void MatrixHelper::SetRight(XMMATRIX& p_Matrix, XMFLOAT3 &p_Right)
	{
		XMFLOAT4 m1;
		XMStoreFloat4(&m1, p_Matrix.r[0]);

		m1.x = p_Right.x;
		m1.y = p_Right.y;
		m1.z = p_Right.z;

		p_Matrix.r[0] = XMLoadFloat4(&m1);
	}

	void MatrixHelper::SetTranslation(XMMATRIX& p_Matrix, XMFLOAT3 &p_Translation)
	{
		XMFLOAT4 m4;
		XMStoreFloat4(&m4, p_Matrix.r[3]);

		m4.x = p_Translation.x;
		m4.y = p_Translation.y;
		m4.z = p_Translation.z;

		p_Matrix.r[3] = XMLoadFloat4(&m4);
	}
}