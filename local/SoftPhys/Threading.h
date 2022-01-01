#ifndef _SoftPhys_Threading_h_
#define _SoftPhys_Threading_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Threading : Object {
	RTTI_DECL1(Threading, Object)
	using Object::Object;
	
	Vector<ThreadPool*> pools;
	World* world = 0;
	
	
	Threading();
	
	void Visit(RuntimeVisitor& vis) override {VIS_THIS(Object);}
	void Add(ThreadPool& p);
	void Detach();
	void DetachWorld();
	
};


}
NAMESPACE_TOPSIDE_END

#endif
