#ifndef _IfaceCore_Lib_h_
#define _IfaceCore_Lib_h_

NAMESPACE_PLAN_BEGIN


class IfaceLib {
	
	static Vector<Package*>& Packages() {static Vector<Package*> v; return v;}
	
public:
	
	static void Dump();
	static void Export(CompilationUnit& cu);
	static void Export();
	static void Add(Package* p) {Packages().Add(p);}
	
};


NAMESPACE_PLAN_END

#endif
