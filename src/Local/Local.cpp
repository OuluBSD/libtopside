#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


INITBLOCK_(Local) {
	DaemonBase::Register<SerialServiceServer>("TcpServer");
	DaemonBase::Register<SerialServiceClient>("TcpClient");
	
	
	using namespace TS::GVar;
	
	gvars[VAR_AUDIOTIME].Set("iAudioSeconds", true);
	gvars[VAR_VIEW].Set("iView", true);
	gvars[VAR_LIGHTDIR].Set("iLightDir", true);
	gvars[VAR_VIEWOVERRIDE].Set("iViewOverride", true);
	gvars[VAR_PROJECTIONOVERRIDE].Set("iProjectionOverride", true);
	gvars[VAR_CAMERA_POS].Set("iCameraPos", true);
	gvars[VAR_CAMERA_DIR].Set("iCameraDir", true);
	gvars[VAR_SCALE].Set("iScale", true);
	gvars[VAR_MODEL].Set("iModel", true);
	gvars[VAR_MODELCOLOR].Set("iModelColor", true);
	
	gvars[VAR_NONE].Set("iNone", true);
	gvars[VAR_DIFFUSE].Set("iDiffuse", true);
	gvars[VAR_SPECULAR].Set("iSpecular", true);
	gvars[VAR_AMBIENT].Set("iAmbient", true);
	gvars[VAR_EMISSIVE].Set("iEmissive", true);
	gvars[VAR_HEIGHT].Set("iHeight", true);
	gvars[VAR_NORMALS].Set("iNormals", true);
	gvars[VAR_SHININESS].Set("iShininess", true);
	gvars[VAR_OPACITY].Set("iOpacity", true);
	gvars[VAR_DISPLACEMENT].Set("iDisplacement", true);
	gvars[VAR_LIGHTMAP].Set("iLightmap", true);
	gvars[VAR_REFLECTION].Set("iReflection", true);
	gvars[VAR_UNKNOWN].Set("iUnknown", true);
	gvars[VAR_CUBE_DIFFUSE].Set("iCubeDiffuse", true);
	gvars[VAR_CUBE_IRRADIANCE].Set("iCubeIrradiance", true);
	gvars[VAR_IS_NONE].Set("iIsNone", true);
	gvars[VAR_IS_DIFFUSE].Set("iIsDiffuse", true);
	gvars[VAR_IS_SPECULAR].Set("iIsSpecular", true);
	gvars[VAR_IS_AMBIENT].Set("iIsAmbient", true);
	gvars[VAR_IS_EMISSIVE].Set("iIsEmissive", true);
	gvars[VAR_IS_HEIGHT].Set("iIsHeight", true);
	gvars[VAR_IS_NORMALS].Set("iIsNormals", true);
	gvars[VAR_IS_SHININESS].Set("iIsShininess", true);
	gvars[VAR_IS_OPACITY].Set("iIsOpacity", true);
	gvars[VAR_IS_DISPLACEMENT].Set("iIsDisplacement", true);
	gvars[VAR_IS_LIGHTMAP].Set("iIsLightmap", true);
	gvars[VAR_IS_REFLECTION].Set("iIsReflection", true);
	gvars[VAR_IS_UNKNOWN].Set("iIsUnknown", true);
	gvars[VAR_IS_CUBE_DIFFUSE].Set("iIsCubeDiffuse", true);
	gvars[VAR_IS_CUBE_IRRADIANCE].Set("iIsCubeIrradiance", true);
	
	
	gvars[VAR_BUFFERSTAGE0_COLOR].Set("iStageColor0", false);
	gvars[VAR_BUFFERSTAGE1_COLOR].Set("iStageColor1", false);
	gvars[VAR_BUFFERSTAGE2_COLOR].Set("iStageColor2", false);
	gvars[VAR_BUFFERSTAGE3_COLOR].Set("iStageColor3", false);
	gvars[VAR_BUFFERSTAGE4_COLOR].Set("iStageColor4", false);
	gvars[VAR_BRDF_SPEC].Set("iBrdfSpecular", false);
	gvars[VAR_COMPAT_RESOLUTION].Set("iResolution", false);
	gvars[VAR_COMPAT_TIME].Set("iTime", false);
	gvars[VAR_COMPAT_TIMEDELTA].Set("iTimeDelta", false);
	gvars[VAR_COMPAT_FRAME].Set("iFrame", false);
	gvars[VAR_COMPAT_MOUSE].Set("iMouse", false);
	gvars[VAR_COMPAT_DATE].Set("iDate", false);
	gvars[VAR_COMPAT_SAMPLERATE].Set("iSampleRate", false);
	gvars[VAR_COMPAT_OFFSET].Set("iOffset", false);
	gvars[VAR_COMPAT_CHANNEL0].Set("iChannel0", false);
	gvars[VAR_COMPAT_CHANNEL1].Set("iChannel1", false);
	gvars[VAR_COMPAT_CHANNEL2].Set("iChannel2", false);
	gvars[VAR_COMPAT_CHANNEL3].Set("iChannel3", false);
	gvars[VAR_COMPAT_FRAMERATE].Set("iFrameRate", false);
	gvars[VAR_COMPAT_CHANNELTIME].Set("iChannelTime[0]", false);
	gvars[VAR_COMPAT_CHANNELRESOLUTION].Set("iChannelResolution[0]", false);
	gvars[VAR_COMPAT_BLOCKOFFSET].Set("iBlockOffset", false);
	gvars[VAR_LENS_CENTER].Set("iLensCenter", false);
	gvars[VAR_VIEWPORT_SCALE].Set("iViewportScale", false);
	gvars[VAR_WARP_SCALE].Set("iWarpScale", false);
	gvars[VAR_HMD_WARP_PARAM].Set("iHmdWarpParam", false);
	gvars[VAR_ABERR].Set("iAberr", false);
	
	for(int i = 0; i < VAR_COUNT; i++) {
		ASSERT(gvars[i].name);
	}
}


NAMESPACE_TOPSIDE_END
