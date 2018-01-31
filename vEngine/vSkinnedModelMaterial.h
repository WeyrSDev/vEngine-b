#pragma once
#include "vInclude.h"
#include "vStructs.h"
#include "vMaterial.h"

namespace vEngine {
	class SkinnedModelMaterial : public Material {
		RTTI_DECLARATIONS(SkinnedModelMaterial, Material)
		MATERIAL_VARIABLE_DECLARATION(WorldViewProjection)
		MATERIAL_VARIABLE_DECLARATION(World)
		MATERIAL_VARIABLE_DECLARATION(SpecularColor)
		MATERIAL_VARIABLE_DECLARATION(SpecularPower)
		MATERIAL_VARIABLE_DECLARATION(AmbientColor)
		MATERIAL_VARIABLE_DECLARATION(LightColor)
		MATERIAL_VARIABLE_DECLARATION(LightPosition)
		MATERIAL_VARIABLE_DECLARATION(LightRadius)
		MATERIAL_VARIABLE_DECLARATION(CameraPosition)
		MATERIAL_VARIABLE_DECLARATION(BoneTransforms)
		MATERIAL_VARIABLE_DECLARATION(ColorTexture)
	public:
		SkinnedModelMaterial();
	public:
		void CreateVertexBuffer(ID3D11Device* device, VertexSkinnedPositionTextureNormal* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
	public:
		virtual void Initialize(Effect& effect) override;
		virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
		virtual UINT VertexSize() const override;
	};
}
