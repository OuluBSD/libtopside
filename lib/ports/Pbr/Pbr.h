#pragma once

#include <memory>
#include <numeric>
#include <optional>
#include <vector>
#include <array>
#include <map>

#include <wrl.h>
#include <wrl\client.h>
#include <d3d11.h>
#include <d3d11_3.h>
#include <d3d11_4.h>
#include <sstream>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <DirectXTK/GltfHelper.h>

#include <ports/tiny_gltf/tiny_gltf.h>
#include <ports/stb/stb_image.h>


#ifndef flagVISUALSTUDIO
extern char g_psPbrMain[1024];
extern char g_vsPbrVprtMain[1024];
extern char g_vsPbrNoVprtMain[1024];
extern char g_gsPbrNoVprtMain[1024];
#endif


#include "PbrCommon.h"
#include "PbrResources.h"
#include "PbrMaterial.h"
#include "PbrPrimitive.h"
#include "PbrModel.h"
#include "GltfLoader.h"
