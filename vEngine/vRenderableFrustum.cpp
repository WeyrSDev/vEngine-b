#include "vRenderableFrustum.h"
#include "vEngine.h"
#include "vException.h"
#include "vBasicMaterial.h"
#include "vStructs.h"
#include "vColorHelper.h"
#include "vMatrixHelper.h"
#include "vVectorHelper.h"
#include "vCamera.h"

namespace vEngine
{
	RTTI_DEFINITIONS(RenderableFrustum)

		const DirectX::XMVECTORF32 RenderableFrustum::DefaultColor = ColorHelper::Green;

	const UINT RenderableFrustum::FrustumVertexCount = 8;
	const UINT RenderableFrustum::FrustumPrimitiveCount = 12;
	const UINT RenderableFrustum::FrustumIndicesPerPrimitive = 2;
	const UINT RenderableFrustum::FrustumIndexCount = FrustumPrimitiveCount * FrustumIndicesPerPrimitive;
	const USHORT RenderableFrustum::FrustumIndices[] = {
		// Near plane lines
		0, 1,
		1, 2,
		2, 3,
		3, 0,

		// Sides
		0, 4,
		1, 5,
		2, 6,
		3, 7,

		// Far plane lines
		4, 5,
		5, 6,
		6, 7,
		7, 4
	};

	RenderableFrustum::RenderableFrustum(Engine& game, Camera& camera)
		: DrawableComponent(game, camera),
		mVertexBuffer(nullptr), mIndexBuffer(nullptr), mMaterial(nullptr), mPass(nullptr), mInputLayout(nullptr),
		mColor(DefaultColor), mPosition(Vector3Helper::Zero), mDirection(Vector3Helper::Forward), mUp(Vector3Helper::Up), mRight(Vector3Helper::Right),
		mWorldMatrix(MatrixHelper::Identity)
	{
	}

	RenderableFrustum::RenderableFrustum(Engine& game, Camera& camera, const DirectX::XMFLOAT4& color)
		: DrawableComponent(game, camera),
		mVertexBuffer(nullptr), mIndexBuffer(nullptr), mMaterial(nullptr), mPass(nullptr), mInputLayout(nullptr),
		mColor(color), mPosition(Vector3Helper::Zero), mDirection(Vector3Helper::Forward), mUp(Vector3Helper::Up), mRight(Vector3Helper::Right),
		mWorldMatrix(MatrixHelper::Identity)
	{
	}

	RenderableFrustum::~RenderableFrustum()
	{
		ReleaseObject(mIndexBuffer);
		ReleaseObject(mVertexBuffer);

		if (mMaterial != nullptr)
		{
			delete mMaterial->GetEffect();
			delete mMaterial;
			mMaterial = nullptr;
		}
	}

	const DirectX::XMFLOAT3& RenderableFrustum::Position() const
	{
		return mPosition;
	}

	const DirectX::XMFLOAT3& RenderableFrustum::Direction() const
	{
		return mDirection;
	}

	const DirectX::XMFLOAT3& RenderableFrustum::Up() const
	{
		return mUp;
	}

	const DirectX::XMFLOAT3& RenderableFrustum::Right() const
	{
		return mRight;
	}

	DirectX::XMVECTOR RenderableFrustum::PositionVector() const
	{
		return XMLoadFloat3(&mPosition);
	}

	DirectX::XMVECTOR RenderableFrustum::DirectionVector() const
	{
		return XMLoadFloat3(&mDirection);
	}

	DirectX::XMVECTOR RenderableFrustum::UpVector() const
	{
		return XMLoadFloat3(&mUp);
	}

	DirectX::XMVECTOR RenderableFrustum::RightVector() const
	{
		return XMLoadFloat3(&mRight);
	}

	void RenderableFrustum::SetPosition(FLOAT x, FLOAT y, FLOAT z)
	{
		DirectX::XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
		SetPosition(position);
	}

	void RenderableFrustum::SetPosition(DirectX::FXMVECTOR position)
	{
		XMStoreFloat3(&mPosition, position);
	}

	void RenderableFrustum::SetPosition(const DirectX::XMFLOAT3& position)
	{
		mPosition = position;
	}

	void RenderableFrustum::ApplyRotation(DirectX::CXMMATRIX transform)
	{
		DirectX::XMVECTOR direction = XMLoadFloat3(&mDirection);
		DirectX::XMVECTOR up = XMLoadFloat3(&mUp);

		direction = XMVector3TransformNormal(direction, transform);
		direction = XMVector3Normalize(direction);

		up = XMVector3TransformNormal(up, transform);
		up = XMVector3Normalize(up);

		DirectX::XMVECTOR right = XMVector3Cross(direction, up);
		up = XMVector3Cross(right, direction);

		XMStoreFloat3(&mDirection, direction);
		XMStoreFloat3(&mUp, up);
		XMStoreFloat3(&mRight, right);
	}

	void RenderableFrustum::ApplyRotation(const DirectX::XMFLOAT4X4& transform)
	{
		DirectX::XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
		ApplyRotation(transformMatrix);
	}

	void RenderableFrustum::InitializeGeometry(const Frustum& frustum)
	{
		InitializeVertexBuffer(frustum);
	}

	void RenderableFrustum::Initialize()
	{
		Effect* effect = new Effect(*mGame);
		effect->LoadCompiledEffect(L"Content\\Effects\\BasicEffect.cso");

		mMaterial = new BasicMaterial();
		mMaterial->Initialize(*effect);

		mPass = mMaterial->CurrentTechnique()->Passes().at(0);
		mInputLayout = mMaterial->InputLayouts().at(mPass);

		InitializeIndexBuffer();
	}

	void RenderableFrustum::Update(const Time& gameTime)
	{
		DirectX::XMMATRIX worldMatrix = XMMatrixIdentity();
		MatrixHelper::SetForward(worldMatrix, mDirection);
		MatrixHelper::SetUp(worldMatrix, mUp);
		MatrixHelper::SetRight(worldMatrix, mRight);
		MatrixHelper::SetTranslation(worldMatrix, mPosition);

		XMStoreFloat4x4(&mWorldMatrix, worldMatrix);
	}

	void RenderableFrustum::Draw(const Time& gameTime)
	{
		assert(mPass != nullptr);
		assert(mInputLayout != nullptr);

		ID3D11DeviceContext* direct3DDeviceContext = mGame->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
		direct3DDeviceContext->IASetInputLayout(mInputLayout);

		UINT stride = sizeof(VertexPositionColor);
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

		DirectX::XMMATRIX world = XMLoadFloat4x4(&mWorldMatrix);
		DirectX::XMMATRIX wvp = world * mCamera->ViewMatrix() * mCamera->ProjectionMatrix();
		mMaterial->WorldViewProjection() << wvp;

		mPass->Apply(0, direct3DDeviceContext);

		direct3DDeviceContext->DrawIndexed(FrustumIndexCount, 0, 0);
	}

	void RenderableFrustum::InitializeVertexBuffer(const Frustum& frustum)
	{
		ReleaseObject(mVertexBuffer);

		VertexPositionColor vertices[FrustumVertexCount];
		const DirectX::XMFLOAT3* corners = frustum.Corners();
		for (UINT i = 0; i < FrustumVertexCount; i++)
		{
			vertices[i].Position = DirectX::XMFLOAT4(corners[i].x, corners[i].y, corners[i].z, 1.0f);
			vertices[i].Color = mColor;
		}

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
		vertexBufferDesc.ByteWidth = sizeof(VertexPositionColor) * FrustumVertexCount;
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexSubResourceData;
		ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
		vertexSubResourceData.pSysMem = vertices;
		if (FAILED(mGame->Direct3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, &mVertexBuffer)))
		{
			throw Exception("ID3D11Device::CreateBuffer() failed.");
		}
	}

	void RenderableFrustum::InitializeIndexBuffer()
	{
		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.ByteWidth = sizeof(USHORT) * FrustumIndexCount;
		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexSubResourceData;
		ZeroMemory(&indexSubResourceData, sizeof(indexSubResourceData));
		indexSubResourceData.pSysMem = FrustumIndices;
		if (FAILED(mGame->Direct3DDevice()->CreateBuffer(&indexBufferDesc, &indexSubResourceData, &mIndexBuffer)))
		{
			throw Exception("ID3D11Device::CreateBuffer() failed.");
		}
	}
}