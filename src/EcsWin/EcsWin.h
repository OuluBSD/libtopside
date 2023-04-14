#ifndef _EcsWin_EcsWin_h_
#define _EcsWin_EcsWin_h_

#include <Core/config.h>

#include <optional>
#include <functional>
#include <memory>
#include <future>
#include <tuple>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <robuffer.h>
#include <algorithm>
#include <array>
#include <map>
#include <sstream>

#include <winapifamily.h>

#if WINAPI_FAMILY != WINAPI_FAMILY_APP
	#error Wrong WINAPI_FAMILY
#endif

#include <Guiddef.h>
#include <wrl.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <stdint.h>

#include <d2d1_2.h>
#include <d3d11_4.h>
#include <DirectXColors.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <WindowsNumerics.h>
#include <Windows.Graphics.Directx.Direct3D11.Interop.h>

#include <wrl\client.h>

#if WINAPI_FAMILY != WINAPI_FAMILY_APP
	#error Wrong WINAPI_FAMILY
#endif

#ifndef __WRL_NO_DEFAULT_LIB__
	#error Not defined: __WRL_NO_DEFAULT_LIB__
#endif

#include <ppl.h>
#include <winrt\Windows.ApplicationModel.Activation.h>
#include <winrt\Windows.ApplicationModel.Core.h>
#include <winrt\Windows.Devices.h>
#include <winrt\Windows.Devices.haptics.h>
#include <winrt\Windows.Foundation.h>
#include <winrt\Windows.Foundation.Collections.h>
#include <winrt\Windows.Gaming.Input.h>
#include <winrt\Windows.Graphics.Display.h>
#include <winrt\Windows.Graphics.Holographic.h>
#include <winrt\Windows.Perception.People.h>
#include <winrt\Windows.Perception.Spatial.h>
#include <winrt\Windows.Storage.h>
#include <winrt\Windows.Storage.Streams.h>
#include <winrt\Windows.UI.Core.h>
#include <winrt\Windows.UI.Input.Spatial.h>


#include <EcsLib/EcsLib.h>

#include <ports/stb/stb_image.h> // not needed: #define STB_IMAGE_IMPLEMENTATION
#include <ports/tiny_gltf/tiny_gltf.h>
#include <ports/mikktspace/mikktspace.h>
#include <ports/DirectXTK/DirectXTK.h>

#include "PbrResources.h"
#include "PbrCommon.h"
#include "PbrMaterial.h"
#include "PbrPrimitive.h"
#include "PbrModel.h"
#include "PbrModelCache.h"

#include "CameraResources.h"
#include "DeviceResources.h"
//#include "DDSTextureLoader.h"
#include "DirectXHelper.h"
#include <ports/DirectXTK/PlatformHelpers.h>

#include "EngineTypeTraits.h"
#include "Engine.h"
#include "EngineCommon.h"
#include "Component.h"
#include "AppLogicSystem.h"
#include "ListenerCollection.h"
#include "HolographicScene.h"
#include "SpatialInteractionSystem.h"
#include "MotionControllerSystem.h"

#include "ToolSystem.h"
#include "ToolboxSystem.h"
#include "PaintingSystem.h"
#include "ShootingSystem.h"
#include "ThrowingSystem.h"
#include "PaintStrokeSystem.h"
#include "EasingSystem.h"
#include "EntityStore.h"

#include "CommonComponents.h"
#include "ComponentStore.h"
#include "ControllerRendering.h"
#include "GltfHelper.h"
#include "GltfLoader.h"

#include "PhysicsSystem.h"
#include "EntityPrefabs.h"

#include "Haptics.h"

#include "StepTimer.h"
#include "Entity.h"

#include "AppView.h"
#include "DemoRoomMain.h"

#include "HolographicRenderer.h"
#include "TextRenderer.h"
#include "QuadRenderer.h"
#include "SkyboxRenderer.h"

#include "Physics.h"

/*
#include "Shaders\Compiled\SkyBoxPixelShader.h"
#include "Shaders\Compiled\SkyBoxVertexShaderVprt.h"
#include "Shaders\Compiled\SkyBoxVertexShaderNoVprt.h"
#include "Shaders\Compiled\SkyBoxGeometryShaderNoVprt.h"

#include "Shaders\Compiled\QuadGeometryShader.h"
#include "Shaders\Compiled\QuadPixelShaderRGB.h"
#include "Shaders\Compiled\QuadVertexShader.h"
#include "Shaders\Compiled\QuadVPRTVertexShader.h"

#include "Shaders\Compiled\PbrPixelShader.h"
#include "Shaders\Compiled\PbrVertexShaderVprt.h"
#include "Shaders\Compiled\PbrVertexShaderNoVprt.h"
#include "Shaders\Compiled\PbrGeometryShaderNoVprt.h"
*/

#endif
