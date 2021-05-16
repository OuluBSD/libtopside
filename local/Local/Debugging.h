#ifndef _Local_Debugging_h_
#define _Local_Debugging_h_

NAMESPACE_TOPSIDE_BEGIN


class StackDebugger {
	enum {
		CTOR,
		REF
	};
	struct Item : Moveable<Item> {
		int event;
		TypeId type;
		void* ptr;
		
		bool operator!=(const Item& it) const {return event != it.event || ptr != it.ptr;}
		String ToString() const;
	};
	Vector<Item> ctors, refs;
	bool checking_unrefs = false;
	
	void Construct(const Item& it);
	void Destruct(const Item& it);
	void IncRef(const Item& it);
	void DecRef(const Item& it);
public:
	
	void NonZeroRefError();
	void Dump();
	void Log(String type, const Item& it);
	void CheckUnrefs(bool b=true) {checking_unrefs = b;}
	
	
	template <class T> void Construct(T* o) {Construct(Item {{}, CTOR, typeid(T), o});}
	template <class T> void Destruct(T* o) {Destruct(Item {{}, CTOR, typeid(T), o});}
	template <class T> void IncRef(T* o, TypeId type) {IncRef(Item {{}, REF, type, o});}
	template <class T> void DecRef(T* o, TypeId type) {DecRef(Item {{}, REF, type, o});}
	
	
	static StackDebugger& Static() {static StackDebugger s; return s;}
	
	
};


#ifdef flagDEBUG_STACK
	#define DBG_CONSTRUCT			{SetDebugReferencing(); StackDebugger::Static().Construct(this);}
	#define DBG_DESTRUCT			{StackDebugger::Static().Destruct(this);}
	#define DBG_REF_INC				{StackDebugger::Static().IncRef(this, dbg_type);}
	#define DBG_REF_DEC				{StackDebugger::Static().DecRef(this, dbg_type);}
	#define DBG_REF_NONZERO_ERROR	{StackDebugger::Static().NonZeroRefError();}
	#define DBG_BEGIN_UNREF_CHECK	{StackDebugger::Static().CheckUnrefs();}
#else
	#define DBG_CONSTRUCT
	#define DBG_DESTRUCT
	#define DBG_REF_INC
	#define DBG_REF_DEC
	#define DBG_REF_ZERO_ERROR
	#define DBG_BEGIN_UNREF_CHECK
#endif







class RuntimeDiagnosticVisitor : public RuntimeVisitor {
	struct Var {
		void* mem;
		TypeId type;
		LockedScopeRefCounter* ref;
	};
	struct Scope {
		Scope* parent;
		LinkedList<Scope> sub_scopes;
		LinkedList<Var> refs;
		Var var;
		bool focused;
		
		void Clear();
	};
	
	Scope root;
	Scope* cur_scope = 0;
	LockedScopeRefCounter* cursor = 0;
	
	
	bool OnEntry(TypeId type, void* mem, LockedScopeRefCounter* ref) override;
	void OnExit() override;
	void OnRef(TypeId type, void* mem, LockedScopeRefCounter* ref) override;
	
	void DumpVisit(const Scope& s, int depth, bool only_focused);
	void RecursiveFocus(Scope& s);
	void RecursiveUnfocus(Scope& s);
	
public:
	bool IsEmpty() const {return root.var.mem == 0;}
	void Clear();
	void Dump();
	void DumpFocused();
	void Unfocus();
	void Focus(LockedScopeRefCounter* c);
	
};

class RuntimeDiagnostics {
	void* root = 0;
	Callback visiter;
	RuntimeDiagnosticVisitor vis;
	
	template <class T> void BeginVisit() {
		vis.Clear();
		vis.Visit(*(T*)root);
	}
	
public:
	typedef RuntimeDiagnostics CLASSNAME;
	RuntimeDiagnostics();
	~RuntimeDiagnostics() {Clear();}
	
	void Clear() {vis.Clear();}
	void CaptureSnapshot();
	void OnRefError(LockedScopeRefCounter* r);
	static RuntimeDiagnostics& Static() {static RuntimeDiagnostics s; return s;}
	
	template <class T>
	void SetRoot(T& o) {
		visiter = THISBACK(BeginVisit<T>);
		root = &o;
	}
	
	
	Callback1<String> WhenFatalError;
};



class RefDebugVisitor : public RuntimeVisitor {
	struct Item {
		void* mem;
		bool visited;
		Item() {Clear();}
		void Clear() {mem = 0; visited = false;}
		bool operator==(const Item& i) {return mem == i.mem;}
		String ToString() const;
	};
	LinkedList<Item> items;
	size_t break_ref_add = 0;
	size_t break_ref_rem = 0;

	void OnRef(TypeId type, void* mem, LockedScopeRefCounter* ref) override {
		Item cmp;
		cmp.mem = mem;
		Item* i = items.Find(cmp);
		ASSERT(i);
		if (i) {i->visited = true;}
	}
	
	
public:
	
	void Add(void* mem);
	void Remove(void* mem);
	void DumpUnvisited();
	void BreakRefAdd(size_t addr) {break_ref_add = addr;}
	void BreakRefRemove(size_t addr) {break_ref_rem = addr;}
	
	static RefDebugVisitor& Static() {static RefDebugVisitor v; return v;}
	
	
};

inline void BreakRefAdd(size_t addr)	{RefDebugVisitor::Static().BreakRefAdd(addr);}
inline void BreakRefRemove(size_t addr)	{RefDebugVisitor::Static().BreakRefRemove(addr);}




NAMESPACE_TOPSIDE_END

#endif
