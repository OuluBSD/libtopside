#ifndef _Oulu_Debugging_h_
#define _Oulu_Debugging_h_

NAMESPACE_OULU_BEGIN


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












#if 0

template <class T, class Parent1, class Parent2=void>
class DebugNode {
	
	
public:
	
	
};

class StructureDebugger {
	
	
public:
	
	
	
	
	
	
	static StructureDebugger& Static() {static StructureDebugger s; return s;}
	
};

#ifdef flagDEBUG_STRUCTURE
	#define DBG_CONSTRUCT			{SetDebugReferencing(); StructureDebugger::Static().Construct(this);}
	#define DBG_DESTRUCT			{StructureDebugger::Static().Destruct(this);}
	#define DBG_REF_INC				{StructureDebugger::Static().IncRef(this, dbg_type);}
	#define DBG_REF_DEC				{StructureDebugger::Static().DecRef(this, dbg_type);}
	#define DBG_REF_NONZERO_ERROR	{StructureDebugger::Static().NonZeroRefError();}
	#define DBG_BEGIN_UNREF_CHECK	{StructureDebugger::Static().CheckUnrefs();}
#else
	#define DBG_CONSTRUCT
	#define DBG_DESTRUCT
	#define DBG_REF_INC
	#define DBG_REF_DEC
	#define DBG_REF_ZERO_ERROR
	#define DBG_BEGIN_UNREF_CHECK
#endif

#endif


NAMESPACE_OULU_END

#endif
