#pragma once
#include "vInclude.h"
#include "vMaterial.h"

namespace vEngine {
	class SkyboxMaterial : public Material {
		RTTI_DECLARATIONS(SkyboxMaterial, Material)
		MATERIAL_VARIABLE_DECLARATION(WorldViewProjection)
		MATERIAL_VARIABLE_DECLARATION(SkyboxTexture)
	public:
		SkyboxMaterial();
	public:
		virtual void Initialize(Effect& effect) override;
		virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
		void CreateVertexBuffer(ID3D11Device* device, DirectX::XMFLOAT4* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
		virtual UINT VertexSize() const override;
	};
}