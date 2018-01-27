#pragma once
#include "vInclude.h"
#include "vStructs.h"
#include "vPostProcessingMaterial.h"

namespace vEngine {
	class GaussianBlurMaterial : public PostProcessingMaterial {
		RTTI_DECLARATIONS(PostProcessingMaterial, GaussianBlurMaterial)
		MATERIAL_VARIABLE_DECLARATION(SampleOffsets)
		MATERIAL_VARIABLE_DECLARATION(SampleWeights)
	public:
		GaussianBlurMaterial();
	public:
		virtual void Initialize(Effect& effect) override;
	};
}
