#ifndef _EonBaseGen_Compiler_h_
#define _EonBaseGen_Compiler_h_

NAMESPACE_EONGEN_BEGIN


class Compiler {
	World world;
	
	
public:
	typedef Compiler CLASSNAME;
	Compiler();
	
	bool Compile(UppProject& p, const UppAssembly& as, UppAssemblyData& asd);
	
	
	
	Callback1<String>	WhenOutput;
	Callback1<ProcMsg>	WhenMessage;
};


NAMESPACE_EONGEN_END

#endif
