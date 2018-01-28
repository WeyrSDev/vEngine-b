#pragma once
#include "vInclude.h"
#include "vStructs.h"
#include "vMaterial.h"

namespace vEngine {
	class DepthMapMaterial : public Material {
		RTTI_DECLARATIONS(DepthMapMaterial, Material)
		MATERIAL_VARIABLE_DECLARATION(WorldLightViewProjection)
	public:
		DepthMapMaterial();
	public:
		void CreateVertexBuffer(ID3D11Device* device, VertexPosition* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
	public:
		virtual void Initialize(Effect& effect) override;
		virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
		virtual UINT VertexSize() const override;
	};
}