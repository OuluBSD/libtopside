// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.4.3 11:11:55

#ifndef _IGraphics_BaseClasses_h_
#define _IGraphics_BaseClasses_h_

NAMESPACE_PARALLEL_BEGIN

struct GfxVertexShader : public Atom {
	RTTI_DECL1(GfxVertexShader, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~GfxVertexShader() {}

};

struct GfxFragmentShader : public Atom {
	RTTI_DECL1(GfxFragmentShader, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~GfxFragmentShader() {}

};

struct GfxDataObject : public Atom {
	RTTI_DECL1(GfxDataObject, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~GfxDataObject() {}

};

struct GfxDataState : public ErrorReporter {
	RTTI_DECL1(GfxDataState, ErrorReporter)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ErrorReporter>(this);}
	
	virtual ~GfxDataState() {}

};

struct GfxInputState : public ErrorReporter {
	RTTI_DECL1(GfxInputState, ErrorReporter)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ErrorReporter>(this);}
	
	virtual ~GfxInputState() {}

};

struct GfxFramebuffer : public ErrorReporter {
	RTTI_DECL1(GfxFramebuffer, ErrorReporter)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ErrorReporter>(this);}
	
	virtual ~GfxFramebuffer() {}

};

struct GfxCompiler : public ErrorReporter {
	RTTI_DECL1(GfxCompiler, ErrorReporter)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ErrorReporter>(this);}
	
	virtual ~GfxCompiler() {}

};

struct GfxLinker : public ErrorReporter {
	RTTI_DECL1(GfxLinker, ErrorReporter)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ErrorReporter>(this);}
	
	virtual ~GfxLinker() {}

};

struct GfxShaderPipeline : public Atom {
	RTTI_DECL1(GfxShaderPipeline, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~GfxShaderPipeline() {}

};

struct GfxRuntimeState : public ErrorReporter {
	RTTI_DECL1(GfxRuntimeState, ErrorReporter)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<ErrorReporter>(this);}
	
	virtual ~GfxRuntimeState() {}

};

struct GfxContextState : public Atom {
	RTTI_DECL1(GfxContextState, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~GfxContextState() {}

};

struct GfxRenderer : public Atom {
	RTTI_DECL1(GfxRenderer, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~GfxRenderer() {}

};

struct GfxStateDraw : public Draw {
	RTTI_DECL1(GfxStateDraw, Draw)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Draw>(this);}
	
	virtual ~GfxStateDraw() {}

};

struct GfxBuffer : public Atom {
	RTTI_DECL1(GfxBuffer, Atom)
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	
	virtual ~GfxBuffer() {}

};

NAMESPACE_PARALLEL_END



#endif

