#pragma once
#include "vInclude.h"
#include "vStructs.h"
#include "vMaterial.h"

namespace vEngine {
	class DistortionMappingMaterial : public Material {
		RTTI_DECLARATIONS(Material, DistortionMappingMaterial)
		MATERIAL_VARIABLE_DECLARATION(WorldViewProjection)
		MATERIAL_VARIABLE_DECLARATION(SceneTexture)
		MATERIAL_VARIABLE_DECLARATION(DistortionMap)
		MATERIAL_VARIABLE_DECLARATION(DisplacementScale)
	public:
		DistortionMappingMaterial();
	public:
		void CreateVertexBuffer(ID3D11Device* device, VertexPositionTexture* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
	public:
		virtual void Initialize(Effect& effect) override;
		virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
		virtual UINT VertexSize() const override;
	};
}
