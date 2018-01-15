#pragma once
#include "vInclude.h"
#include "vDrawableComponent.h"

namespace vEngine {
	class Pass;
	class Grid : public DrawableComponent {
		RTTI_DECLARATIONS(Grid, DrawableComponent)
	public:
		Grid(Engine& game, Camera& camera);
		Grid(Engine& game, Camera& camera, UINT size, UINT scale, XMFLOAT4 color);
		virtual ~Grid();
	private:
		Grid();
		Grid(const Grid& rhs);
		Grid& operator=(const Grid& rhs);
	public:
		const XMFLOAT3& Position() const;
		const XMFLOAT4& Color() const;
		const UINT Size() const;
		const UINT Scale() const;
		void SetPosition(const XMFLOAT3& position);
		void SetPosition(float x, float y, float z);
		void SetColor(const XMFLOAT4& color);
		void SetSize(UINT size);
		void SetScale(UINT scale);
		virtual void Initialize() override;
		virtual void Draw(const Time& gameTime) override;
	private:
		void InitializeGrid();
	private:
		static const UINT DefaultSize;
		static const UINT DefaultScale;
		static const XMFLOAT4 DefaultColor;
		ID3DX11Effect * mEffect;
		ID3DX11EffectTechnique* mTechnique;
		ID3DX11EffectPass* mPass;
		ID3DX11EffectMatrixVariable* mWvpVariable;
		ID3D11InputLayout* mInputLayout;
		ID3D11Buffer* mVertexBuffer;
		XMFLOAT3 mPosition;
		UINT mSize;
		UINT mScale;
		XMFLOAT4 mColor;
		XMFLOAT4X4 mWorldMatrix;
	};
}