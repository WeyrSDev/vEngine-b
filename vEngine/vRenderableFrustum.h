#pragma once
#include "vDrawableComponent.h"
#include "vFrustum.h"

namespace vEngine {
	class BasicMaterial;
	class Pass;
	class RenderableFrustum : public DrawableComponent {
		RTTI_DECLARATIONS(RenderableFrustum, DrawableComponent)
	public:
		RenderableFrustum(Engine& game, Camera& camera);
		RenderableFrustum(Engine& game, Camera& camera, const DirectX::XMFLOAT4& color);
		~RenderableFrustum();
	private:
		RenderableFrustum();
		RenderableFrustum(const RenderableFrustum& rhs);
		RenderableFrustum& operator=(const RenderableFrustum& rhs);
	public:
		const DirectX::XMFLOAT3& Position() const;
		const DirectX::XMFLOAT3& Direction() const;
		const DirectX::XMFLOAT3& Up() const;
		const DirectX::XMFLOAT3& Right() const;
		DirectX::XMVECTOR PositionVector() const;
		DirectX::XMVECTOR DirectionVector() const;
		DirectX::XMVECTOR UpVector() const;
		DirectX::XMVECTOR RightVector() const;
		void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		void SetPosition(DirectX::FXMVECTOR position);
		void SetPosition(const DirectX::XMFLOAT3& position);
		void ApplyRotation(DirectX::CXMMATRIX transform);
		void ApplyRotation(const DirectX::XMFLOAT4X4& transform);
		void InitializeGeometry(const Frustum& frustum);
	public:
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
		virtual void Draw(const Time& gameTime) override;
	private:
		void InitializeVertexBuffer(const Frustum& frustum);
		void InitializeIndexBuffer();
	private:
		static const DirectX::XMVECTORF32 DefaultColor;
		static const UINT FrustumVertexCount;
		static const UINT FrustumPrimitiveCount;
		static const UINT FrustumIndicesPerPrimitive;
		static const UINT FrustumIndexCount;
		static const USHORT FrustumIndices[];
	private:
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		BasicMaterial* mMaterial;
		Pass* mPass;
		ID3D11InputLayout* mInputLayout;
		DirectX::XMFLOAT4 mColor;
		DirectX::XMFLOAT3 mPosition;
		DirectX::XMFLOAT3 mDirection;
		DirectX::XMFLOAT3 mUp;
		DirectX::XMFLOAT3 mRight;
		DirectX::XMFLOAT4X4 mWorldMatrix;
	};
}