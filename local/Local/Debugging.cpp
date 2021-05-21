#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


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
















RuntimeDiagnostics::RuntimeDiagnostics() {
	
}

void RuntimeDiagnostics::CaptureSnapshot() {
	vis.Clear();
	vis.SetActiveRefCounter();
	visiter();
}

void RuntimeDiagnostics::OnRefError(LockedScopeRefCounter* r) {
	ASSERT(r);
	String s;
	s << "error: non-zero references (" << r->GetRefCount() << ") at &[" << HexStr(r) << "]";
	LOG(s);
	
	if (vis.IsEmpty())
		CaptureSnapshot();
	else {
		vis.Unfocus();
		vis.Focus(r);
		LOG("\nOld full dump:");
		vis.Dump();
		LOG("\nOld focused dump:");
		vis.DumpFocused();
		CaptureSnapshot();
	}
	LOG("\nRefreshed focused dump:");
	vis.Unfocus();
	vis.Focus(r);
	LOG("\nFull dump:");
	vis.Dump();
	LOG("\nFocused dump:");
	vis.DumpFocused();
	
	if (IsDebugRefVisits())
		RefDebugVisitor::Static().DumpUnvisited();
	else
		{LOG("*** Reference visitor debugging was not enabled ***");}
	
	Panic("Reference error");
}






void RuntimeDiagnosticVisitor::Scope::Clear() {
	sub_scopes.Clear();
	var.type = AsVoidTypeId();
	var.mem = 0;
	parent = 0;
	focused = 0;
}

void RuntimeDiagnosticVisitor::Clear() {
	RuntimeVisitor::Clear();
	root.Clear();
	cur_scope = 0;
}

bool RuntimeDiagnosticVisitor::OnEntry(TypeId type, void* mem, LockedScopeRefCounter* ref) {
	if (!cur_scope) {
		root.parent = 0;
		root.var.mem = mem;
		root.var.type = type;
		root.var.ref = ref;
		root.focused = 0;
		cur_scope = &root;
	}
	else {
		Scope& scope = cur_scope->sub_scopes.Add();
		scope.parent = cur_scope;
		scope.var.mem = mem;
		scope.var.type = type;
		scope.var.ref = ref;
		scope.focused = 0;
		cur_scope = &scope;
	}
	return true;
}

void RuntimeDiagnosticVisitor::OnExit() {
	cur_scope = cur_scope->parent;
}

void RuntimeDiagnosticVisitor::OnRef(TypeId type, void* mem, LockedScopeRefCounter* ref) {
	ASSERT(cur_scope);
	Var& var = cur_scope->refs.Add();
	var.mem = mem;
	var.type = type;
	var.ref = ref;
}

void RuntimeDiagnosticVisitor::Dump() {
	DumpVisit(root, 0, 0);
}

void RuntimeDiagnosticVisitor::DumpFocused() {
	DumpVisit(root, 0, 1);
}

void RuntimeDiagnosticVisitor::DumpVisit(const Scope& scope, int depth, bool only_focused) {
	if (only_focused && !scope.focused)
		return;
	
	String indent, s0, s1;
	indent.Cat('\t', depth);
	
	s0 << scope.var.type.CleanDemangledName() << "[" << HexStr(scope.var.mem) << "]";
	if (scope.var.ref)
		s0 << " &[" << HexStr(scope.var.ref) << "]";
	LOG(indent << s0);
	
	for (const Var& v : scope.refs) {
		if (only_focused && v.ref != cursor)
			continue;
		s1 = "";
		s1 << indent << "\t-->" << v.type.CleanDemangledName() << "[" << HexStr(v.mem) << "]";
		if (v.ref)
			s1 << " &[" << HexStr(v.ref) << "]";
		LOG(s1);
	}
	
	for (const Scope& sub : scope.sub_scopes)
		DumpVisit(sub, depth+1, only_focused);
	
}

void RuntimeDiagnosticVisitor::Focus(LockedScopeRefCounter* c) {
	cursor = c;
	RecursiveFocus(root);
}

void RuntimeDiagnosticVisitor::RecursiveFocus(Scope& s) {
	bool focus = s.var.ref == cursor;
	
	for (const Var& v : s.refs)
		if (v.ref == cursor)
			focus = true;
		
	if (focus) {
		Scope* it = &s;
		while (it) {
			it->focused = true;
			it = it->parent;
		}
	}
	
	for (Scope& sub : s.sub_scopes)
		RecursiveFocus(sub);
}

void RuntimeDiagnosticVisitor::Unfocus() {
	RecursiveUnfocus(root);
}

void RuntimeDiagnosticVisitor::RecursiveUnfocus(Scope& s) {
	s.focused = false;
	for (Scope& sub : s.sub_scopes)
		RecursiveUnfocus(sub);
}





Vector<Callback> __exit_cbs;

EXITBLOCK {
	for (Callback& cb : __exit_cbs)
		cb();
	RuntimeDiagnostics::Static().Clear();
}

void CallInExitBlock(Callback cb) {
	static StaticMutex m;
	m.Enter();
	__exit_cbs << cb;
	m.Leave();
}


String RefDebugVisitor::Item::ToString() const {
	String s;
	s << "[" << HexStr(mem) << "]";
	return s;
}

void RefDebugVisitor::Add(void* mem) {
	LOG("RefDebugVisitor::Add    " << HexStr(mem));
	if (break_ref_add == (size_t)mem) {__BREAK__;}
	Item& it = items.Add();
	it.mem = mem;
}

void RefDebugVisitor::Remove(void* mem) {
	LOG("RefDebugVisitor::Remove " << HexStr(mem));
	if (break_ref_rem == (size_t)mem) {__BREAK__;}
	Item cmp;
	cmp.mem = mem;
	auto i = items.FindIter(cmp);
	if (i) {
		items.Remove(i);
	}
	else {
		LOG("\terror: trying to remove unfollowed Ref at " << HexStr(mem));
	}
}

void RefDebugVisitor::DumpUnvisited() {
	LOG("RefDebugVisitor::DumpUnvisited");
	int i = 0;
	for (auto iter = items.begin(); iter; ++iter) {
		LOG(i++ << ":\t" << iter->ToString());
	}
}

void DebugRefVisits_AddRef(void* mem) {
	RefDebugVisitor::Static().Add(mem);
}

void DebugRefVisits_RemoveRef(void* mem) {
	RefDebugVisitor::Static().Remove(mem);
}



NAMESPACE_TOPSIDE_END
