#include "Oulu.h"

NAMESPACE_OULU_BEGIN


String StackDebugger::Item::ToString() const {
	String s;
	if (event == CTOR)
		s << "()";
	else if (event == REF)
		s << "->";
	s << type.CleanDemangledName() << "[" << HexStr(ptr) << "]";
	return s;
}

void StackDebugger::Construct(const Item& cur) {
	Log("Constructing", cur);
	ctors.Add(cur);
}

void StackDebugger::Destruct(const Item& cur) {
	Log("Destructing", cur);
	if (!ctors.GetCount()) {
		Dump();
		Panic("Empty stack while destructing in StackDebugger");
	}
	Item& top = ctors.Top();
	if (top != cur) {
		Dump();
		Panic("Expected " + top.ToString() + ", but got " + cur.ToString());
	}
	ctors.Remove(ctors.GetCount()-1);
}

void StackDebugger::IncRef(const Item& cur) {
	Log("++ reference", cur);
	refs.Add(cur);
}

void StackDebugger::DecRef(const Item& cur) {
	Log("-- reference ", cur);
	if (!refs.GetCount()) {
		Dump();
		Panic("Empty stack while unreffing in StackDebugger");
	}
	if (checking_unrefs) {
		Item& top = refs.Top();
		if (top != cur) {
			Dump();
			Panic("Expected " + top.ToString() + ", but got " + cur.ToString());
		}
	}
	refs.Remove(refs.GetCount()-1);
}

void StackDebugger::NonZeroRefError() {
	if (!refs.GetCount()) {
		Dump();
		Panic("Empty stack with NonZeroRefError");
	}
	Dump();
	Item& top = refs.Top();
	Panic("Expected " + top.ToString() + ", but got zero refences error");
}

void StackDebugger::Dump() {
	LOG("StackDebugger:");
	DUMPC(ctors);
	DUMPC(refs);
}

void StackDebugger::Log(String type, const Item& it) {
	LOG("StackDebugger:\t" << type << ":\t" << it.ToString());
}
















void RuntimeDiagnostics::OnRefError(LockedScopeRefCounter* r) {
	ASSERT(r);
	TODO
}









void RuntimeDiagnosticVisitor::Clear() {
	TODO
}

NAMESPACE_OULU_END
