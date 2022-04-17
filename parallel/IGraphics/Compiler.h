#ifndef _SoftRend_Compiler_h_
#define _SoftRend_Compiler_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
class SoftCompilerT {
	
	
public:
	using SoftShader	= SoftShaderT<Gfx>;
	
	typedef SoftCompilerT CLASSNAME;
	SoftCompilerT();
	
	
	bool Compile(SoftShader& s);
	
};


NAMESPACE_PARALLEL_END

#endif
