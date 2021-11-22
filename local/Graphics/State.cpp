#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN

namespace ShaderVar {
const char* names[ShaderVar::VAR_COUNT+1] = {
	"iAudioSeconds",
	"iView",
	"iProjection",
	"iScale",
	"iModel",
	
	"iResolution",
	"iTime",
	"iTimeDelta",
	"iFrame",
	"iMouse",
	"iDate",
	"iSampleRate",
	"iOffset",
	"iChannel0",
	"iChannel1",
	"iChannel2",
	"iChannel3",
	"iFrameRate",
	"iChannelTime",
	"iChannelResolution[0]",
	"iChannelResolution[1]",
	"iChannelResolution[2]",
	"iChannelResolution[3]",
	"iBlockOffset",
	0
};
const bool is_obj_var[ShaderVar::VAR_COUNT+1] = {
	true,
	true,
	true,
	true,
	true,
	
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	false,
	0
};
}

NAMESPACE_TOPSIDE_END
