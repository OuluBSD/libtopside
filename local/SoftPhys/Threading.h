#ifndef _SoftPhys_Threading_h_
#define _SoftPhys_Threading_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Threading : Object {
	using Object::Object;
	
	Vector<ThreadPool*> pools;
	World* world = 0;
	
	
	Threading();
	
	void Add(ThreadPool& p);
	void Detach();
	void DetachWorld();
	
};


}
NAMESPACE_TOPSIDE_END

#endif
