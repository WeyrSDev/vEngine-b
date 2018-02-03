#include "vDistortionMapping.h"
#include "vEngine.h"
#include "vException.h"
#include "vDistortionMappingMaterial.h"
#include "vFullScreenRenderTarget.h"
#include "vFullScreenQuad.h"
#include "vCamera.h"
#include "vVectorHelper.h"
#include "vMatrixHelper.h"
#include "vUtility.h"
#include "vColorHelper.h"
#include "vMesh.h"

namespace vEngine
{
	RTTI_DEFINITIONS(DistortionMapping)

	DistortionMapping::DistortionMapping(Engine& game, Camera& camera)
		: DrawableComponent(game, camera),
		mDistortionEffect(nullptr), mDistortionMappingMaterial(nullptr), mDistortionPass(nullptr), mDistortionInputLayout(nullptr),
		mDistortionTechnique(DistortionTechniqueDisplacement), mSceneTexture(nullptr), mRenderTarget(nullptr), mFullScreenQuad(nullptr)
	{
	}

	DistortionMapping::~DistortionMapping()
	{
		DeleteObject(mFullScreenQuad);
		DeleteObject(mRenderTarget);
		DeleteObject(mDistortionMappingMaterial);
		DeleteObject(mDistortionEffect);
	}

	DistortionTechnique DistortionMapping::GetDistortionTechnique() const
	{
		return mDistortionTechnique;
	}

	void DistortionMapping::SetDistortionTechnique(DistortionTechnique distortionTechnique)
	{
		mDistortionTechnique = distortionTechnique;
		mDistortionPass = mDistortionMappingMaterial->CurrentTechnique()->Passes().at(0);
		mDistortionInputLayout = mDistortionMappingMaterial->InputLayouts().at(mDistortionPass);
	}

	ID3D11ShaderResourceView* DistortionMapping::SceneTexture()
	{
		return mSceneTexture;
	}

	void DistortionMapping::SetSceneTexture(ID3D11ShaderResourceView& sceneTexture)
	{
		mSceneTexture = &sceneTexture;
	}

	DistortionMappingMaterial* DistortionMapping::GetMaterial()
	{
		return mDistortionMappingMaterial;
	}

	void DistortionMapping::Initialize()
	{
		SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

		mDistortionEffect = new Effect(*mGame);
		mDistortionEffect->LoadCompiledEffect(L"Content\\Effects\\Distortion.cso");

		mDistortionMappingMaterial = new DistortionMappingMaterial();
		mDistortionMappingMaterial->Initialize(*mDistortionEffect);
		SetDistortionTechnique(mDistortionTechnique);

		mRenderTarget = new FullScreenRenderTarget(*mGame);

		mFullScreenQuad = new FullScreenQuad(*mGame, *mDistortionMappingMaterial);
		mFullScreenQuad->Initialize();
	}

	void DistortionMapping::Draw(const Time& gameTime)
	{
		mFullScreenQuad->SetActiveTechnique("distortion_composite", "p0");
		mFullScreenQuad->SetCustomUpdateMaterial(std::bind(&DistortionMapping::UpdateDistortionCompositeMaterial, this));
		mFullScreenQuad->Draw(gameTime);

		mGame->UnbindPixelShaderResources(0, 2);
	}

	void DistortionMapping::BeginDistortionMap()
	{
		mRenderTarget->Begin();
		mGame->Direct3DDeviceContext()->ClearRenderTargetView(mRenderTarget->RenderTargetView(), reinterpret_cast<const float*>(&ColorHelper::Purple));
		mGame->Direct3DDeviceContext()->ClearDepthStencilView(mRenderTarget->DepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void DistortionMapping::DrawMeshToDistortionMap(Mesh& mesh, DirectX::CXMMATRIX worldMatrix)
	{
		assert(mesh.HasCachedVertexBuffer());
		assert(mesh.HasCachedIndexBuffer());

		ID3D11DeviceContext* direct3DDeviceContext = mGame->Direct3DDeviceContext();
		direct3DDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		direct3DDeviceContext->IASetInputLayout(mDistortionInputLayout);

		ID3D11Buffer* vertexBuffer = mesh.VertexBuffer().Buffer();
		UINT stride = mDistortionMappingMaterial->VertexSize();
		UINT offset = 0;
		direct3DDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		ID3D11Buffer* indexBuffer = mesh.IndexBuffer().Buffer();
		direct3DDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

		//XMMATRIX wvp = worldMatrix * mCamera->ViewMatrix() * mCamera->ProjectionMatrix();		
		//mDistortionMappingMaterial->WorldViewProjection() << wvp;
		//
		//mDistortionPass->Apply(0, direct3DDeviceContext);

		direct3DDeviceContext->DrawIndexed(mesh.IndexBuffer().ElementCount(), 0, 0);
	}

	void DistortionMapping::EndDistortionMap()
	{
		mRenderTarget->End();
	}

	void DistortionMapping::UpdateDistortionCompositeMaterial()
	{
		mDistortionMappingMaterial->SceneTexture() << mSceneTexture;
		mDistortionMappingMaterial->DistortionMap() << mRenderTarget->OutputTexture();
	}
}

