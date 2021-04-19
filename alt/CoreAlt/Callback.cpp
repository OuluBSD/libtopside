#include "Core.h"

NAMESPACE_UPP_BEGIN

thread_local static Vector<Callback> __initblocks, __exitblocks;

void AddInitBlock(Callback cb) {
	__initblocks << cb;
}

void AddExitBlock(Callback cb) {
	__exitblocks << cb;
}

void RunInitBlocks() {
	for (Callback& cb : __initblocks)
		cb();
}

void RunExitBlocks() {
	for (Callback& cb : __exitblocks)
		cb();
}








Callinit::Callinit(void (*fn)()) {
	AddInitBlock(Callback(fn));
}

Callexit::Callexit(void (*fn)()) {
	AddExitBlock(Callback(fn));
}

NAMESPACE_UPP_END
