// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

#ifndef _IGraphics_BaseClasses_h_
#define _IGraphics_BaseClasses_h

NAMESPACE_TOPSIDE_BEGIN

struct GfxVertexShader : RTTIBase {
	RTTI_DECL0(GfxVertexShader)
	
	virtual ~GfxVertexShader() {}

};

struct GfxFragmentShader : RTTIBase {
	RTTI_DECL0(GfxFragmentShader)
	
	virtual ~GfxFragmentShader() {}

};

struct GfxDataObject : RTTIBase {
	RTTI_DECL0(GfxDataObject)
	
	virtual ~GfxDataObject() {}

};

struct GfxDataState : ErrorReporter {
	RTTI_DECL1(GfxDataState, ErrorReporter)
	
	virtual ~GfxDataState() {}

};

struct GfxInputState : ErrorReporter {
	RTTI_DECL1(GfxInputState, ErrorReporter)
	
	virtual ~GfxInputState() {}

};

struct GfxFramebuffer : ErrorReporter {
	RTTI_DECL1(GfxFramebuffer, ErrorReporter)
	
	virtual ~GfxFramebuffer() {}

};

struct GfxCompiler : ErrorReporter {
	RTTI_DECL1(GfxCompiler, ErrorReporter)
	
	virtual ~GfxCompiler() {}

};

struct GfxLinker : ErrorReporter {
	RTTI_DECL1(GfxLinker, ErrorReporter)
	
	virtual ~GfxLinker() {}

};

struct GfxShaderPipeline : RTTIBase {
	RTTI_DECL0(GfxShaderPipeline)
	
	virtual ~GfxShaderPipeline() {}

};

struct GfxRuntimeState : ErrorReporter {
	RTTI_DECL1(GfxRuntimeState, ErrorReporter)
	
	virtual ~GfxRuntimeState() {}

};

struct GfxContextState : RTTIBase {
	RTTI_DECL0(GfxContextState)
	
	virtual ~GfxContextState() {}

};

struct GfxRenderer : RTTIBase {
	RTTI_DECL0(GfxRenderer)
	
	virtual ~GfxRenderer() {}

};

struct GfxStateDraw : Draw {
	RTTI_DECL1(GfxStateDraw, Draw)
	
	virtual ~GfxStateDraw() {}

};

struct GfxBuffer : RTTIBase {
	RTTI_DECL0(GfxBuffer)
	
	virtual ~GfxBuffer() {}

};

NAMESPACE_TOPSIDE_END



#endif

