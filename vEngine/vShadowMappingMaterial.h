#pragma once
#include "vInclude.h"
#include "vStructs.h"
#include "vMaterial.h"

namespace vEngine {
	class ShadowMappingMaterial : public Material {
		RTTI_DECLARATIONS(ShadowMappingMaterial, Material)
		MATERIAL_VARIABLE_DECLARATION(WorldViewProjection)
		MATERIAL_VARIABLE_DECLARATION(World)
		MATERIAL_VARIABLE_DECLARATION(SpecularColor)
		MATERIAL_VARIABLE_DECLARATION(SpecularPower)
		MATERIAL_VARIABLE_DECLARATION(AmbientColor)
		MATERIAL_VARIABLE_DECLARATION(LightColor)
		MATERIAL_VARIABLE_DECLARATION(LightPosition)
		MATERIAL_VARIABLE_DECLARATION(LightRadius)
		MATERIAL_VARIABLE_DECLARATION(CameraPosition)
		MATERIAL_VARIABLE_DECLARATION(ColorTexture)
		MATERIAL_VARIABLE_DECLARATION(ProjectiveTextureMatrix)
		MATERIAL_VARIABLE_DECLARATION(ShadowMap)
		MATERIAL_VARIABLE_DECLARATION(ShadowMapSize)
	public:
		ShadowMappingMaterial();
	public:
		void CreateVertexBuffer(ID3D11Device* device, VertexPositionTextureNormal* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
	public:
		virtual void Initialize(Effect& effect) override;
		virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
		virtual UINT VertexSize() const override;
	};
}