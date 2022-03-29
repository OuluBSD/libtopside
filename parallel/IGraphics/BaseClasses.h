// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 29.3.29 19:55:44

#ifndef _IGraphics_BaseClasses_h_
#define _IGraphics_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct GfxVertexShader : public Atom {
	RTTI_DECL1(GfxVertexShader, Atom)
	
	virtual ~GfxVertexShader() {}

};

struct GfxFragmentShader : public Atom {
	RTTI_DECL1(GfxFragmentShader, Atom)
	
	virtual ~GfxFragmentShader() {}

};

struct GfxDataObject : public Atom {
	RTTI_DECL1(GfxDataObject, Atom)
	
	virtual ~GfxDataObject() {}

};

struct GfxDataState : public ErrorReporter {
	RTTI_DECL1(GfxDataState, ErrorReporter)
	
	virtual ~GfxDataState() {}

};

struct GfxInputState : public ErrorReporter {
	RTTI_DECL1(GfxInputState, ErrorReporter)
	
	virtual ~GfxInputState() {}

};

struct GfxFramebuffer : public ErrorReporter {
	RTTI_DECL1(GfxFramebuffer, ErrorReporter)
	
	virtual ~GfxFramebuffer() {}

};

struct GfxCompiler : public ErrorReporter {
	RTTI_DECL1(GfxCompiler, ErrorReporter)
	
	virtual ~GfxCompiler() {}

};

struct GfxLinker : public ErrorReporter {
	RTTI_DECL1(GfxLinker, ErrorReporter)
	
	virtual ~GfxLinker() {}

};

struct GfxShaderPipeline : public Atom {
	RTTI_DECL1(GfxShaderPipeline, Atom)
	
	virtual ~GfxShaderPipeline() {}

};

struct GfxRuntimeState : public ErrorReporter {
	RTTI_DECL1(GfxRuntimeState, ErrorReporter)
	
	virtual ~GfxRuntimeState() {}

};

struct GfxContextState : public Atom {
	RTTI_DECL1(GfxContextState, Atom)
	
	virtual ~GfxContextState() {}

};

struct GfxRenderer : public Atom {
	RTTI_DECL1(GfxRenderer, Atom)
	
	virtual ~GfxRenderer() {}

};

struct GfxStateDraw : public Draw {
	RTTI_DECL1(GfxStateDraw, Draw)
	
	virtual ~GfxStateDraw() {}

};

struct GfxBuffer : public Atom {
	RTTI_DECL1(GfxBuffer, Atom)
	
	virtual ~GfxBuffer() {}

};

NAMESPACE_PARALLEL_END



#endif

