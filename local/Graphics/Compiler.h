#ifndef _Graphics_Compiler_h_
#define _Graphics_Compiler_h_

NAMESPACE_TOPSIDE_BEGIN


struct GCompiler : ErrorReporter {
	RTTI_DECL1(GCompiler, ErrorReporter)
	
	virtual ~GCompiler() {}
	
};

struct GLinker : ErrorReporter {
	RTTI_DECL1(GLinker, ErrorReporter)
	
	virtual ~GLinker() {}
	
};


NAMESPACE_TOPSIDE_END

#endif
