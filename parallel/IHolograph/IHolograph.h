#pragma once

#include <ports/tiny_gltf/tiny_gltf.h>
#include <ports/mikktspace/mikktspace.h>

#include <IGraphics/IGraphics.h>


#ifdef flagDX11
#include "Dx11.h"
#include "DirectXHelper.h"
#endif

#include "CameraResources.h"
#include "DeviceResources.h"
#include "ControllerRendering.h"
//#include "HolographicScene.h"
#include "TextRenderer.h"
#include "Physics.h"
#include "QuadRenderer.h"
#include "SkyboxRenderer.h"
//#include "PbrModelCache.h"
#include "AppView.h"
//#include "MotionControllerSystem.h"
#include "GltfHelper.h"



NAMESPACE_PARALLEL_BEGIN


struct SpatialInteractionSource;
struct SpatialInteractionSourceLocation;
/*using SpatialInteractionSource				= SpatialSource;
using SpatialInteractionSourceLocation		= SpatialSourceLocation;
using SpatialInteractionSourceEventArgs		= SpatialSourceEventArgs;
using SpatialInteractionSourceHandedness	= SpatialSourceHandedness;*/


NAMESPACE_PARALLEL_END

