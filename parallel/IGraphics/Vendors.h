// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IGraphics_Vendors_h_
#define _IGraphics_Vendors_h_

NAMESPACE_PARALLEL_BEGIN

#define GFX_CLS_LIST(x) \
	GFX_CLS(VertexShader, x) \
	GFX_CLS(FragmentShader, x) \
	GFX_CLS(DataObject, x) \
	GFX_CLS(DataState, x) \
	GFX_CLS(InputState, x) \
	GFX_CLS(Framebuffer, x) \
	GFX_CLS(Compiler, x) \
	GFX_CLS(Linker, x) \
	GFX_CLS(ShaderPipeline, x) \
	GFX_CLS(RuntimeState, x) \
	GFX_CLS(ContextState, x) \
	GFX_CLS(Renderer, x) \
	GFX_CLS(StateDraw, x) \
	GFX_CLS(Buffer, x) \



#define GFX_VNDR_LIST \
	GFX_VNDR(GfxCpu) \
	GFX_VNDR(GfxOgl) \



#define GFX_CLS(x, v) struct v##x;
#define GFX_VNDR(x) GFX_CLS_LIST(x)
GFX_VNDR_LIST
#undef GFX_VNDR
#undef GFX_CLS



struct GfxCpu {
	using NativeTexture = uint32;
	using NativeShader = uint32;
	using NativeColorBuffer = uint32;
	using NativeDepthBuffer = uint32;
	using NativeFrameBuffer = uint32;
	using NativeVertexArray = uint32;
	using NativeVertexBuffer = uint32;
	using NativeElementBuffr = uint32;
	using NativeProgram = uint32;
	using NativePipeline = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};

struct GfxOgl {
	using NativeTexture = uint32;
	using NativeShader = uint32;
	using NativeColorBuffer = uint32;
	using NativeDepthBuffer = uint32;
	using NativeFrameBuffer = uint32;
	using NativeVertexArray = uint32;
	using NativeVertexBuffer = uint32;
	using NativeElementBuffr = uint32;
	using NativeProgram = uint32;
	using NativePipeline = uint32;
	
	struct Thread {
		
	};
	static Thread& Local() {thread_local static Thread t; return t;}
	
	#include "IfaceFuncs.inl"
	
};



NAMESPACE_PARALLEL_END


#endif

