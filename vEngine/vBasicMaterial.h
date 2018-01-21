#pragma once
#include "vInclude.h"
#include "vStructs.h"
#include "vMaterial.h"


namespace vEngine {
	class BasicMaterial : public Material
	{
		RTTI_DECLARATIONS(BasicMaterial, Material)
		MATERIAL_VARIABLE_DECLARATION(WorldViewProjection)
	public:
		BasicMaterial();
	public:
		virtual void Initialize(Effect* effect) override;
		virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertexBuffer) const override;
		void CreateVertexBuffer(ID3D11Device* device, BasicMaterialVertex* vertices, UINT vertexCount, ID3D11Buffer** vertexBuffer) const;
		virtual UINT VertexSize() const override;
	};
}