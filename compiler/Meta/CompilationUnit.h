#ifndef _Meta_CompilationUnit_h_
#define _Meta_CompilationUnit_h_

NAMESPACE_OULU_BEGIN


class CompilationUnit {
	Tokenizer token;
	Parser parser;
	Compiler comp;
	
	
public:
	typedef CompilationUnit CLASSNAME;
	CompilationUnit();
	
	bool CompileString(String mach, String path, String code);
	const Object& GetObject() const {return comp.GetObject();}
	
	Callback1<ProcMsg> WhenMessage;
};


NAMESPACE_OULU_END

#endif
