#include "SoftRend.h"


NAMESPACE_UPP_BEGIN


void InitObjViewSoft() {
	SoftShaderLibrary::AddShaderClass<ObjViewVertex>(GVar::VERTEX_SHADER, "obj_view_vertex");
	SoftShaderLibrary::AddShaderClass<ObjViewFragment>(GVar::FRAGMENT_SHADER, "obj_view_fragment");
}

void InitUtils() {
	SoftShaderLibrary::AddShaderClass<PassVertex>(GVar::VERTEX_SHADER, "pass_vertex");
	SoftShaderLibrary::AddShaderClass<StereoShader>(GVar::VERTEX_SHADER, "stereo_vertex");
	SoftShaderLibrary::AddShaderClass<PassFragment>(GVar::FRAGMENT_SHADER, "pass_fragment");
	SoftShaderLibrary::AddShaderClass<StereoShader>(GVar::FRAGMENT_SHADER, "stereo_fragment");
	SoftShaderLibrary::AddShaderClass<ColorTestFragment>(GVar::FRAGMENT_SHADER, "color_test_fragment");
	SoftShaderLibrary::AddShaderClass<ProxyInput0Fragment>(GVar::FRAGMENT_SHADER, "proxy_input0_fragment");
}




INITBLOCK_(SoftRendShaders) {
	using namespace TS;
	
	InitObjViewSoft();
	InitUtils();
	
}


NAMESPACE_UPP_END
