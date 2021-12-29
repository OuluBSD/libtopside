#ifndef _SoftPhys_Threading_h_
#define _SoftPhys_Threading_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct Threading : Object {
	using Object::Object;
	
	
	
	Threading();
	
	void Add(ThreadPool& p);
	void Detach();
	
};


}
NAMESPACE_TOPSIDE_END

#endif
