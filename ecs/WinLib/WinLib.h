#pragma once

#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <future>
#include <tuple>
#include <mutex>
#include <algorithm>
#include <robuffer.h>

#include <array>
#include <optional>
#include <future>
#include <map>
#include <unordered_set>
#include <mutex>
#include <vector>
#include <tuple>
#include <sstream>
#include <numeric>

#define _USE_MATH_DEFINES
#include <cmath>

#include <stdint.h>

#include <d2d1_2.h>
#include <d3d11_4.h>
#include <DirectXColors.h>
#include <dwrite_2.h>
#include <wincodec.h>
#include <WindowsNumerics.h>
#include <Windows.Graphics.Directx.Direct3D11.Interop.h>

#include <wrl\client.h>
#include <ppl.h>

#include <ports/Pbr/Pbr.h>
#include <ports/DirectXTK\DirectXTK.h>


#pragma comment(lib, "windowsapp")
#pragma comment(lib, "ole32")
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Devices.h>
#include <winrt/Windows.Devices.haptics.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.Graphics.Holographic.h>
#include <winrt/Windows.Perception.People.h>
#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Storage.AccessCache.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.Spatial.h>

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.Gaming.Input.h>
#include <winrt/Windows.Graphics.Display.h>
#include <winrt/Windows.Graphics.Holographic.h>
#include <winrt/Windows.Perception.People.h>
#include <winrt/Windows.Perception.Spatial.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.UI.Core.h>
  
#include <Pbr/Pbr.h>

#include <ports/DirectXTK/DirectXTK.h>


using namespace DirectX;
using namespace Microsoft::WRL;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::Perception::Spatial;

using namespace std::placeholders;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace winrt::Windows::Storage::Streams;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace D2D1;
using namespace Microsoft::WRL;
using namespace winrt::Windows::Graphics::DirectX::Direct3D11;
using namespace winrt::Windows::Graphics::Display;
using namespace winrt::Windows::Graphics::Holographic;

using namespace Neso;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::Perception;
using namespace winrt::Windows::Perception::Spatial;
using namespace DirectX;

using namespace concurrency;
using namespace std::placeholders;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::UI::Core;

using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace concurrency;
using namespace DirectX;
using namespace std::placeholders;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Gaming::Input;
using namespace winrt::Windows::Graphics::Holographic;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace Neso;
using namespace DemoRoom;

using namespace Neso;
using namespace DemoRoom;
using namespace DirectX;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;
using namespace std::literals::chrono_literals;

using namespace Neso;
using namespace DirectX;
using namespace winrt::Windows::Foundation::Numerics;

using namespace Neso;
using namespace DemoRoom;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;
using namespace std::chrono_literals;

using namespace Neso;
using namespace DemoRoom;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;

using namespace Neso;
using namespace DemoRoom;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Perception::Spatial;
using namespace winrt::Windows::UI::Input::Spatial;



#include "DirectXHelper.h"
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


NAMESPACE_TOPSIDE_BEGIN


using SpatialInteractionSource				= winrt::Windows::UI::Input::Spatial::SpatialInteractionSource;
using SpatialInteractionSourceLocation		= winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceLocation;
using SpatialInteractionSourceEventArgs		= winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceEventArgs;
using SpatialInteractionSourceHandedness	= winrt::Windows::UI::Input::Spatial::SpatialInteractionSourceHandedness;


NAMESPACE_TOPSIDE_END

