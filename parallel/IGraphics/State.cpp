#include "IGraphics.h"

NAMESPACE_TOPSIDE_BEGIN

namespace GVar {
const char* names[TS::GVar::VAR_COUNT+1] = {
	"iAudioSeconds",
	"iView",
	"iLightDir",
	"iViewOverride",
	"iProjectionOverride",
	
	"iCameraPos",
	"iCameraDir",
	
	"iScale",
	"iModel",
	"iModelColor",
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
	
	"iCubeDiffuse",
	"iCubeIrradiance",
	
	"iStageColor0",
	"iStageColor1",
	"iStageColor2",
	"iStageColor3",
	"iStageColor4",
	
	"iBrdfSpecular",
	
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
	"iChannelTime[0]",
	"iChannelResolution[0]",
	
	"iBlockOffset",
	"iLensCenter",
	"iViewportScale",
	"iWarpScale",
	"iHmdWarpParam",
	
	"iAberr",
	
	0
};
const bool is_obj_var[TS::GVar::VAR_COUNT+1] = {
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
	false,
	false,
	
	false,
	true,
	true,
	true,
	true,
	
	true,
	
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
