#ifndef _SoftPhys_ThreadPool_h_
#define _SoftPhys_ThreadPool_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct ThreadPool : Object {
	RTTI_DECL1(ThreadPool, Object)
	using Object::Object;
	
	Threading* threading = 0;
	
	
	ThreadPool() {}
	
	void ClearThreading() {TODO}
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
};


}
NAMESPACE_TOPSIDE_END

#endif
