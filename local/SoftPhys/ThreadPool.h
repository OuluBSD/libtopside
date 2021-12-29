#ifndef _SoftPhys_ThreadPool_h_
#define _SoftPhys_ThreadPool_h_

NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


struct ThreadPool : Object {
	using Object::Object;
	
	Threading* threading = 0;
	
	
	ThreadPool() {}
	
};


}
NAMESPACE_TOPSIDE_END

#endif
