#pragma once
#include "vInclude.h"

namespace vEngine {
	typedef struct _VertexPosition
	{
		DirectX::XMFLOAT4 Position;

		_VertexPosition() { }

		_VertexPosition(const DirectX::XMFLOAT4& position)
			: Position(position) { }
	} VertexPosition;

	typedef struct _VertexPositionColor
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT4 Color;

		_VertexPositionColor() { }

		_VertexPositionColor(const DirectX::XMFLOAT4& position, const DirectX::XMFLOAT4& color)
			: Position(position), Color(color) { }
	} VertexPositionColor;

	typedef struct _VertexPositionTexture
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT2 TextureCoordinates;

		_VertexPositionTexture() { }

		_VertexPositionTexture(const DirectX::XMFLOAT4& position, const DirectX::XMFLOAT2& textureCoordinates)
			: Position(position), TextureCoordinates(textureCoordinates) { }
	} VertexPositionTexture;

	typedef struct _VertexPositionSize
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT2 Size;

		_VertexPositionSize() { }

		_VertexPositionSize(const DirectX::XMFLOAT4& position, const DirectX::XMFLOAT2& size)
			: Position(position), Size(size) { }
	} VertexPositionSize;

	typedef struct _VertexPositionNormal
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT3 Normal;

		_VertexPositionNormal() { }

		_VertexPositionNormal(const DirectX::XMFLOAT4& position, const DirectX::XMFLOAT3& normal)
			: Position(position), Normal(normal) { }
	} VertexPositionNormal;

	typedef struct _VertexPositionTextureNormal
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT2 TextureCoordinates;
		DirectX::XMFLOAT3 Normal;

		_VertexPositionTextureNormal() { }

		_VertexPositionTextureNormal(const DirectX::XMFLOAT4& position, const DirectX::XMFLOAT2& textureCoordinates, const DirectX::XMFLOAT3& normal)
			: Position(position), TextureCoordinates(textureCoordinates), Normal(normal) { }
	} VertexPositionTextureNormal;

	typedef struct _VertexSkinnedPositionTextureNormal
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT2 TextureCoordinates;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMUINT4 BoneIndices;
		DirectX::XMFLOAT4 BoneWeights;

		_VertexSkinnedPositionTextureNormal() { }

		_VertexSkinnedPositionTextureNormal(const DirectX::XMFLOAT4& position, const DirectX::XMFLOAT2& textureCoordinates, const DirectX::XMFLOAT3& normal, const DirectX::XMUINT4& boneIndices, const DirectX::XMFLOAT4& boneWeights)
			: Position(position), TextureCoordinates(textureCoordinates), Normal(normal), BoneIndices(boneIndices), BoneWeights(boneWeights) { }
	} VertexSkinnedPositionTextureNormal;

	struct VertexPositionTextureNormalTangent
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT2 TextureCoordinates;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT3 Tangent;

		VertexPositionTextureNormalTangent() { }

		VertexPositionTextureNormalTangent(const DirectX::XMFLOAT4& position, const DirectX::XMFLOAT2& textureCoordinates, const DirectX::XMFLOAT3& normal, const DirectX::XMFLOAT3& tangent)
			: Position(position), TextureCoordinates(textureCoordinates), Normal(normal), Tangent(tangent) { }
	};


	typedef struct _BasicMaterialVertex
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT4 Color;

		_BasicMaterialVertex() { }

		_BasicMaterialVertex(DirectX::XMFLOAT4 position, DirectX::XMFLOAT4 color)
			: Position(position), Color(color) { }
	} BasicMaterialVertex;

	typedef struct _PostProcessingMaterialVertex
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT2 TextureCoordinates;
		_PostProcessingMaterialVertex() { }
		_PostProcessingMaterialVertex(DirectX::XMFLOAT4 position, DirectX::XMFLOAT2 textureCoordinates)
			: Position(position), TextureCoordinates(textureCoordinates) { }
	} PostProcessingMaterialVertex;

	typedef struct _BloomSettings
	{
		float BloomThreshold;
		float BlurAmount;
		float BloomIntensity;
		float BloomSaturation;
		float SceneIntensity;
		float SceneSaturation;
	} BloomSettings;
}