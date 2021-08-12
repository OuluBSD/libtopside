#ifndef _ChainCore_Factory_h_
#define _ChainCore_Factory_h_

NAMESPACE_PLAN_BEGIN


class ValSpec;
class DevSpec;
class ValDevSpec;


class Factory {
	
public:
	struct Val {
		const char* name;
		
	};
	
	static Array<Val>& Vals() {static Array<Val> a; return a;}
	
public:
	typedef Factory CLASSNAME;
	Factory() {}
	
	
	template <class T> static
	void RegVal(const char* name) {
		Val& v = Vals().Add();
		v.name = name;
		
	}
	
	static void Dump();
	
};


NAMESPACE_PLAN_END

#endif
