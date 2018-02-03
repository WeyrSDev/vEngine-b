#pragma once
#include "vInclude.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Pass;
	class Grid : public DrawableComponent {
		RTTI_DECLARATIONS(Grid, DrawableComponent)
	public:
		Grid(Engine& game, Camera& camera);
		Grid(Engine& game, Camera& camera, UINT size, UINT scale, DirectX::XMFLOAT4 color);
		virtual ~Grid();
	private:
		Grid();
		Grid(const Grid& rhs);
		Grid& operator=(const Grid& rhs);
	public:
		const DirectX::XMFLOAT3& Position() const;
		const DirectX::XMFLOAT4& Color() const;
		const UINT Size() const;
		const UINT Scale() const;
		void SetPosition(const DirectX::XMFLOAT3& position);
		void SetPosition(float x, float y, float z);
		void SetColor(const DirectX::XMFLOAT4& color);
		void SetSize(UINT size);
		void SetScale(UINT scale);
		virtual void Initialize() override;
		virtual void Draw(const Time& gameTime) override;
	private:
		void InitializeGrid();
	private:
		static const UINT DefaultSize;
		static const UINT DefaultScale;
		static const DirectX::XMFLOAT4 DefaultColor;
		ID3DX11Effect* mEffect;
		ID3DX11EffectTechnique* mTechnique;
		ID3DX11EffectPass* mPass;
		ID3DX11EffectMatrixVariable* mWvpVariable;
		ID3D11InputLayout* mInputLayout;
		ID3D11Buffer* mVertexBuffer;
		DirectX::XMFLOAT3 mPosition;
		UINT mSize;
		UINT mScale;
		DirectX::XMFLOAT4 mColor;
		DirectX::XMFLOAT4X4 mWorldMatrix;
	};
}