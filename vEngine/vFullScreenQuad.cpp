#include "vFullScreenQuad.h"
#include "vEngine.h"
#include "vException.h"
#include "vMaterial.h"
#include "vStructs.h"

namespace vEngine
{
	RTTI_DEFINITIONS(FullScreenQuad)

	FullScreenQuad::FullScreenQuad(Engine& game)
		: DrawableComponent(game),
		mMaterial(nullptr), mPass(nullptr), mInputLayout(nullptr),
		mVertexBuffer(nullptr), mIndexBuffer(nullptr), mIndexCount(0), mCustomUpdateMaterial(nullptr)
	{
	}

	FullScreenQuad::FullScreenQuad(Engine& game, Material& material)
		: DrawableComponent(game),
		mMaterial(&material), mPass(nullptr), mInputLayout(nullptr),
		mVertexBuffer(nullptr), mIndexBuffer(nullptr), mIndexCount(0), mCustomUpdateMaterial(nullptr)
	{
	}

	FullScreenQuad::~FullScreenQuad()
	{
		ReleaseObject(mIndexBuffer);
		ReleaseObject(mVertexBuffer);
	}

	Material* FullScreenQuad::GetMaterial()
	{
		return mMaterial;
	}

	void FullScreenQuad::SetMaterial(Material& material, const std::string& techniqueName, const std::string& passName)
	{
		mMaterial = &material;
		SetActiveTechnique(techniqueName, passName);
	}

	void FullScreenQuad::SetActiveTechnique(const std::string& techniqueName, const std::string& passName)
	{
		Technique* technique = mMaterial->GetEffect()->TechniquesByName().at(techniqueName);
		assert(technique != nullptr);

		mPass = technique->PassesByName().at(passName);
		assert(mPass != nullptr);
		mInputLayout = mMaterial->InputLayouts().at(mPass);
	}

	void FullScreenQuad::SetCustomUpdateMaterial(std::function<void()> callback)
	{
		mCustomUpdateMaterial = callback;
	}

	void FullScreenQuad::Initialize()
	{
		VertexPositionTexture vertices[] =
		{
			VertexPositionTexture(DirectX::XMFLOAT4(-1.0f, -1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f)),
			VertexPositionTexture(DirectX::XMFLOAT4(-1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f)),
			VertexPositionTexture(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f)),
			VertexPositionTexture(DirectX::XMFLOAT4(1.0f, -1.0f, 0.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f)),
		};

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
		vertexBufferDesc.ByteWidth = sizeof(VertexPositionTexture)* ARRAYSIZE(vertices);
		vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexSubResourceData;
		ZeroMemory(&vertexSubResourceData, sizeof(vertexSubResourceData));
		vertexSubResourceData.pSysMem = vertices;
		if (FAILED(mGame->Direct3DDevice()->CreateBuffer(&vertexBufferDesc, &vertexSubResourceData, &mVertexBuffer)))
		{
			throw Exception("ID3D11Device::CreateBuffer() failed.");
		}

		UINT indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};

		mIndexCount = ARRAYSIZE(indices);

		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.ByteWidth = sizeof(UINT)* mIndexCount;
		indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexSubResourceData;
		ZeroMemory(&indexSubResourceData, sizeof(indexSubResourceData));
		indexSubResourceData.pSysMem = indices;
		if (FAILED(mGame->Direct3DDevice()->CreateBuffer(&indexBufferDesc, &indexSubResourceData, &mIndexBuffer)))
		{
			throw Exception("ID3D11Device::CreateBuffer() failed.");
		}
	}

	void FullScreenQuad::Draw(const Time& gameTime)
	{
		assert(mPass != nullptr);
		assert(mInputLayout != nullptr);

		ID3D11DeviceContext* direct3DDeviceContext = mGame->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		direct3DDeviceContext->IASetInputLayout(mInputLayout);

		UINT stride = sizeof(VertexPositionTexture);
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
		direct3DDeviceContext->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

		if (mCustomUpdateMaterial != nullptr)
		{
			mCustomUpdateMaterial();
		}

		mPass->Apply(0, direct3DDeviceContext);

		direct3DDeviceContext->DrawIndexed(mIndexCount, 0, 0);
	}
}