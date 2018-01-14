#pragma once
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

#include <windows.h>
#include <exception>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <mmsystem.h>
#include <stdio.h>
#include "vRTTI.h"

#include <d3d11_1.h>
#include <d3dx11Effect.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <dinput.h>
#include <dsound.h>

#include <TLFXEffectsLibrary.h>
#include <TLFXParticleManager.h>
#include <TLFXEffect.h>
#include <fmod.hpp>
#include <fmod_errors.h>

#define DeleteObject(object) if((object) != NULL) { delete object; object = NULL; }
#define DeleteObjects(objects) if((objects) != NULL) { delete[] objects; objects = NULL; }
#define ReleaseObject(object) if((object) != NULL) { object->Release(); object = NULL; }

namespace vEngine {
	typedef unsigned char byte;
}

using namespace DirectX;
using namespace DirectX::PackedVector;