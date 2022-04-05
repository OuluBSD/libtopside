#ifndef _SoftRend_Compiler_h_
#define _SoftRend_Compiler_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Backend>
class SoftCompilerT {
	
	
public:
	using SoftShader	= SoftShaderT<Backend>;
	
	typedef SoftCompilerT CLASSNAME;
	SoftCompilerT();
	
	
	bool Compile(SoftShader& s);
	
};


NAMESPACE_TOPSIDE_END

#endif
