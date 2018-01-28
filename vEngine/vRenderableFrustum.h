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
		RenderableFrustum(Engine& game, Camera& camera, const XMFLOAT4& color);
		~RenderableFrustum();
	private:
		RenderableFrustum();
		RenderableFrustum(const RenderableFrustum& rhs);
		RenderableFrustum& operator=(const RenderableFrustum& rhs);
	public:
		const XMFLOAT3& Position() const;
		const XMFLOAT3& Direction() const;
		const XMFLOAT3& Up() const;
		const XMFLOAT3& Right() const;
		XMVECTOR PositionVector() const;
		XMVECTOR DirectionVector() const;
		XMVECTOR UpVector() const;
		XMVECTOR RightVector() const;
		void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		void SetPosition(FXMVECTOR position);
		void SetPosition(const XMFLOAT3& position);
		void ApplyRotation(CXMMATRIX transform);
		void ApplyRotation(const XMFLOAT4X4& transform);
		void InitializeGeometry(const Frustum& frustum);
	public:
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
		virtual void Draw(const Time& gameTime) override;
	private:
		void InitializeVertexBuffer(const Frustum& frustum);
		void InitializeIndexBuffer();
	private:
		static const XMVECTORF32 DefaultColor;
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
		XMFLOAT4 mColor;
		XMFLOAT3 mPosition;
		XMFLOAT3 mDirection;
		XMFLOAT3 mUp;
		XMFLOAT3 mRight;
		XMFLOAT4X4 mWorldMatrix;
	};
}