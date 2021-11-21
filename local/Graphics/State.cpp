#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN

namespace ShaderVar {
const char* names[ShaderVar::VAR_COUNT+1] = {
	"in_mouse",
	"in_audio_seconds",
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
}

NAMESPACE_TOPSIDE_END
