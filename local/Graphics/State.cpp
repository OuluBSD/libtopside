#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN

namespace GVar {
const char* names[GVar::VAR_COUNT+1] = {
	"iAudioSeconds",
	"iView",
	"iLightDir",
	"iViewOverride",
	"iProjectionOverride",
	"iScale",
	"iModel",
	"iNone",
	"iDiffuse",
	"iSpecular",
	"iAmbient",
	"iEmissive",
	"iHeight",
	"iNormals",
	"iShininess",
	"iOpacity",
	"iDisplacement",
	"iLightmap",
	"iReflection",
	"iUnknown",
	
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
const bool is_obj_var[GVar::VAR_COUNT+1] = {
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
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



#if 0

void StateDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	TODO
}

void StateDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	TODO
}

void StateDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	                        Color ink, int n, const int *dx) {
	TODO
}

void StateDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
                                    const int *counts, int count_count,
                                    int width, Color color, Color doxor) {
	TODO
}

bool StateDraw::ClipOp(const Rect& r) {
	TODO
}

void StateDraw::EndOp() {
	TODO
}

#endif

NAMESPACE_TOPSIDE_END
