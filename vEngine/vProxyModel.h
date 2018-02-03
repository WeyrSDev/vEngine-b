#pragma once
#include "vInclude.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Effect;
	class BasicMaterial;
	class ProxyModel : public DrawableComponent {
		RTTI_DECLARATIONS(ProxyModel, DrawableComponent)
	public:
		ProxyModel(Engine& game, Camera& camera, const std::string& modelFileName, float scale = 1.0f);
		~ProxyModel();
	private:
		ProxyModel();
		ProxyModel(const ProxyModel& rhs);
		ProxyModel& operator=(const ProxyModel& rhs);
	public:
		const DirectX::XMFLOAT3& Position() const;
		const DirectX::XMFLOAT3& Direction() const;
		const DirectX::XMFLOAT3& Up() const;
		const DirectX::XMFLOAT3& Right() const;
		DirectX::XMVECTOR PositionVector() const;
		DirectX::XMVECTOR DirectionVector() const;
		DirectX::XMVECTOR UpVector() const;
		DirectX::XMVECTOR RightVector() const;
		bool& DisplayWireframe();
		void SetPosition(FLOAT x, FLOAT y, FLOAT z);
		void SetPosition(DirectX::FXMVECTOR position);
		void SetPosition(const DirectX::XMFLOAT3& position);
		void ApplyRotation(DirectX::CXMMATRIX transform);
		void ApplyRotation(const DirectX::XMFLOAT4X4& transform);
	public:
		virtual void Initialize() override;
		virtual void Update(const Time& gameTime) override;
		virtual void Draw(const Time& gameTime) override;
	private:
		std::string mModelFileName;
		Effect* mEffect;
		BasicMaterial* mMaterial;
		ID3D11Buffer* mVertexBuffer;
		ID3D11Buffer* mIndexBuffer;
		UINT mIndexCount;
		DirectX::XMFLOAT4X4 mWorldMatrix;
		DirectX::XMFLOAT4X4 mScaleMatrix;
		bool mDisplayWireframe;
		DirectX::XMFLOAT3 mPosition;
		DirectX::XMFLOAT3 mDirection;
		DirectX::XMFLOAT3 mUp;
		DirectX::XMFLOAT3 mRight;
	};
}