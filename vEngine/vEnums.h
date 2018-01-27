#pragma once

namespace vEngine {
	typedef enum _MouseButtons
	{
		MouseButtonsLeft = 0,
		MouseButtonsRight = 1,
		MouseButtonsMiddle = 2,
		MouseButtonsX1 = 3
	}MouseButtons;

	typedef enum _TextureType
	{
		TextureTypeDifffuse = 0,
		TextureTypeSpecularMap,
		TextureTypeAmbient,
		TextureTypeEmissive,
		TextureTypeHeightmap,
		TextureTypeNormalMap,
		TextureTypeSpecularPowerMap,
		TextureTypeDisplacementMap,
		TextureTypeLightMap,
		TextureTypeEnd
	}TextureType;

	typedef enum _FrustumPlane
	{
		FrustumPlaneNear = 0,
		FrustumPlaneFar,
		FrustumPlaneLeft,
		FrustumPlaneRight,
		FrustumPlaneTop,
		FrustumPlaneBottom
	}FrustumPlane;

	typedef enum _DistortionTechnique
	{
		DistortionTechniqueDisplacement = 0,
		DistortionTechniqueEnd
	}DistortionTechnique;

	typedef enum _BloomDrawMode
	{
		BloomDrawModeNormal = 0,
		BloomDrawModeExtractedTexture1,
		BloomDrawModeBlurredTexture,
		BloomDrawModeEnd
	}BloomDrawMode;

}