#include "Core.h"

NAMESPACE_UPP_BEGIN

Vector<Callback>& __initblocks() {static Vector<Callback> v; return v;}
Vector<Callback>& __exitblocks() {static Vector<Callback> v; return v;}
Vector<Callback>& __threadblocks() {static thread_local Vector<Callback> v; return v;}


void AddInitBlock(Callback cb) {
	__initblocks() << cb;
}

void AddExitBlock(Callback cb) {
	__exitblocks() << cb;
}

void RunInitBlocks() {
	for (Callback& cb : __initblocks())
		cb();
}

void RunExitBlocks() {
	RunThreadExitBlocks();
	auto it = __exitblocks().rbegin();
	auto end = __exitblocks().rend();
	for (; it != end; ++it)
		(*it)();
	__initblocks().Clear();
	__exitblocks().Clear();
}

void AddThreadShutdownCallback(Callback cb) {
	__threadblocks() << cb;
}

void RunThreadExitBlocks() {
	auto it = __threadblocks().rbegin();
	auto end = __threadblocks().rend();
	for (; it != end; ++it)
		(*it)();
	__threadblocks().Clear();
}









Callinit::Callinit(void (*fn)()) {
	AddInitBlock(Callback(fn));
}

Callexit::Callexit(void (*fn)()) {
	AddExitBlock(Callback(fn));
}

NAMESPACE_UPP_END
