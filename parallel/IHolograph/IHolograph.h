#pragma once


#ifdef flagDX11
#include "Dx11.h"
#include "DirectXHelper.h"
#endif

#include "CameraResources.h"
#include "DeviceResources.h"
#include "ControllerRendering.h"
#include "Haptics.h"
#include "HolographicRenderer.h"
#include "HolographicScene.h"
#include "TextRenderer.h"
#include "Physics.h"
#include "QuadRenderer.h"
#include "SkyboxRenderer.h"
#include "PbrModelCache.h"
#include "SpatialInteractionSystem.h"
#include "AppView.h"
#include "MotionControllerSystem.h"



NAMESPACE_PARALLEL_BEGIN


using SpatialInteractionSource				= SpatialSource;
using SpatialInteractionSourceLocation		= SpatialSourceLocation;
using SpatialInteractionSourceEventArgs		= SpatialSourceEventArgs;
using SpatialInteractionSourceHandedness	= SpatialSourceHandedness;


NAMESPACE_PARALLEL_END

