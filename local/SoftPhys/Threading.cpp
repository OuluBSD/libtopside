#include "SoftPhys.h"


NAMESPACE_TOPSIDE_BEGIN
namespace SoftPhys {


Threading::Threading() {
	
}


void Threading::Add(ThreadPool& p) {
	pools.Add(&p);
	p.threading = this;
}

void Threading::Detach() {
	for (ThreadPool* p : pools)
		p->threading = this;
	pools.Clear();
}

void Threading::DetachWorld() {
	if (world) {
		world->threading = 0;
		world = 0;
	}
}


}
NAMESPACE_TOPSIDE_END
