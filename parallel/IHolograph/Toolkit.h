#pragma once

#ifndef flagWIN32
	#error DirectXTK compiles on windows only
#endif

#define NOMINMAX

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d11_x.h>
#else
#include <d3d11_1.h>
#endif

#if !defined(NO_D3D11_DEBUG_NAME) && ( defined(_DEBUG) || defined(PROFILE) )
#if !defined(_XBOX_ONE) || !defined(_TITLE)
#pragma comment(lib,"dxguid.lib")
#endif
#endif

#ifndef IID_GRAPHICS_PPV_ARGS
#define IID_GRAPHICS_PPV_ARGS(x) IID_PPV_ARGS(x)
#endif

#pragma warning(disable : 4324)

#include <exception>
#include <memory>
#include <exception>
#include <stdint.h>
#include <vector>

#include <wrl.h>
#include <wrl\client.h>
#include <wincodec.h>

#define NOMINMAX
#include <DirectXMath.h>


// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.


#include <SDKDDKVer.h>


#include <ports/tiny_gltf/tiny_gltf.h>
#include <ports/mikktspace/mikktspace.h>


#include "DDSTextureLoader.h"
#include "dds.h"
#include "DirectXHelpers.h"
#include "PlatformHelpers.h"
#include "LoaderHelpers.h"
#include "GltfHelper.h"
