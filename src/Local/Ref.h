#ifndef _Local_Ref_h_
#define _Local_Ref_h_


NAMESPACE_TOPSIDE_BEGIN



class RefRoot
{
	
public:
	RefRoot();
	~RefRoot();
	
	static bool Is();
	static RefRoot& Get();
	
};


template <class T>
struct RefParent1 {
	T* o = 0;
	
	RefParent1() {}
	RefParent1(T& o) : o(&o) {}
	RefParent1(T* o) : o(o) {}
	template <class C>
	RefParent1(C* c) {static_assert(std::is_convertible<C*, T*>::value, "C must inherit T trivially"); o = static_cast<T*>(c);}
	
	void Clear() {o = 0;}
	
	operator bool() const {return o;}
	operator T&() const {ASSERT(o); return *o;}
	operator T*() const {ASSERT(o); return o;}
	T* operator->() const {ASSERT(o); return o;}
	T* Get() const {ASSERT(o); return o;}
	String ToString() const {return "RefParent1(" + HexStr(o) + ")";}
	
	template <class C>
	C* AsStatic() const {
		static_assert(std::is_convertible<C*, T*>::value, "C must inherit T trivially");
		if (!o) return 0;
		C* c = static_cast<C*>(o);
		return c;
	}
};


template <class A, class B>
struct RefParent2 {
	A* a = 0;
	B* b = 0;
	
	RefParent2() {}
	RefParent2(A* a) : a(a) {}
	RefParent2(B* b) : b(b) {}
	RefParent2(A* a, B* b) : a(a), b(b) {}
	
	void Clear() {a = 0; b = 0;}
	
	operator bool() const {return a || b;}
	String ToString() const {return "RefParent2(" + HexStr(a) + ", " + HexStr(b) + ")";}
	
};


struct RefCommon {
	
};

void DebugRefVisits_AddRef(RefCommon* mem);
void DebugRefVisits_RemoveRef(RefCommon* mem);
#define DBG_REF_CTOR if (IsDebugRefVisits()) {DebugRefVisits_AddRef(this);}
#define DBG_REF_DTOR if (IsDebugRefVisits()) {DebugRefVisits_RemoveRef(this);}
bool IsDebugRefVisits();
void SetDebugRefVisits(bool b=true);

#define SCOPE_REF(x) auto& x = *x##_;


template <class T, class Parent = RefParent1<typename T::Parent> >
class Ref : public RefCommon /*, RTTIBase*/
{
	T* o = 0;
	LockedScopeRefCounter* c = 0; // unfortunately, this must be resolved while setting ".o", because of incomplete type support
	Parent p;
	
	
private:
	// For debugging
	
	#if 0
	void Dump(const char* title) {LOG(title << ": " << ToString());}
	#else
		#define Dump(x)
	#endif
	
public:
	//RTTI_DECL0(Ref)
	using Type = T;
	using ParentT = Parent;
	
    static const char* GetTypeName() {static auto s = "Ref<" + String(T::GetTypeName()) + ">" ; return s;}
    
    #if IS_UPP_CORE
    static TypeCls TypeIdClass() {return typeid(Ref);}
    #else
    static TypeCls TypeIdClass() {static int d = 0; return (size_t) &d;}
	#endif
	
	Ref() {Dump("empty-ctor"); DBG_REF_CTOR}
	Ref(Nuller) {Dump("null-ctor"); DBG_REF_CTOR}
	Ref(Parent p, T* o) : p(p), o(o), c(o) {Dump("ptr-ctor"); if (c) c->IncRef(); DBG_REF_CTOR}
	Ref(const Ref& r) {Dump("copy-ctor"); *this = r; DBG_REF_CTOR}
	~Ref() {Clear(); DBG_REF_DTOR}
	
	// These seems to cause memory errors
	#if 1
	Ref(Ref&& r) {Dump("move-ctor"); *this = r; r.Clear(); DBG_REF_CTOR}
	#elif 0
	Ref(Ref&& r) {Dump("move-ctor"); if (r.o) {o = r.o; r.o = 0; c = r.c; r.c = 0; p = r.p; r.p.Clear();} DBG_REF_CTOR}
	#endif
	
	template <class V>
	Ref(const Ref<V,Parent>& r) {
		Dump("copy-ctor-T");
		static_assert(
			std::is_same<V, T>() ||
			std::is_base_of<V,T>() ||
			std::is_base_of<T,V>(), "T must inherit V or vice versa");
		if (!r.IsEmpty()) {
			o = CastPtr<T>(r.Get());
			c = o;
			ASSERT(o && c);
			c->IncRef();
			p = r.GetRefParent();
		}
		DBG_REF_CTOR
	}
	
	T* GetRefPtr() const {return o;}
	const Parent& GetRefParent() const {return p;}
	
	template <class V>
	Ref& operator=(const Ref<V,Parent>& r) {return Set(r);}
	Ref& operator=(const Ref& r) {return Set(r);}
	
	bool operator==(const Ref& r) const {return r.o == o;}
	bool operator!=(const Ref& r) const {return r.o != o;}
	bool operator==(const T* o) const {return this->o == o;}
	bool operator!=(const T* o) const {return this->o != o;}

	T* operator->() {return o;}
	const T* operator->() const {return o;}
	T& operator*() {ASSERT(o); return *o;}
	T& GetMutable() const {ASSERT(o); return *o;}
	operator bool() const {return o != NULL;}
	
	bool IsEmpty() const {return o == NULL;}
	T* Get() const {return o;}
	void Clear() {if (o) {c->DecRef(); o = 0; c = 0;} p.Clear();}
	template <class V>	V* As() {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>() || std::is_base_of<V,T>(), "V must inherit T or vice versa");
		return CastPtr<V>(o);
	}
	template <class V>	Ref<V,Parent> AsRef() {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>() || std::is_base_of<V,T>(), "V must inherit T or vice versa");
		V* v = CastPtr<V>(o);
		return Ref<V,Parent>(p, v);
	}
	template <class V> void WrapObject(const Parent& p, V* v) {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>(), "V must inherit T");
		ASSERT(!o);
		Clear();
		this->p = p;
		o = CastPtr<T>(v);
		c = o;
		o->IncRef();
		ASSERT(o);
	}
	
	Ref& Set(const Ref& r) {
		Clear();
		o = r.o;
		c = o;
		p = r.GetRefParent();
		if (o)
			o->IncRef();
		return *this;
	}
	
	template <class V>
	Ref& Set(const Ref<V,Parent>& r) {
		Clear();
		V* v = r.GetRefPtr();
		o = CastPtr<T>(v);
		c = o;
		p = r.GetRefParent();
		if (o)
			o->IncRef();
		return *this;
	}
	
	String ToString() const {return "Ref(this=" + HexStr((void*)this) + ", o=" + HexStr(o) + ", p=" + p.ToString() + ")";}
	
	#ifdef Dump
		#undef Dump
	#endif
};



template <class RParent>
class RefScopeParent :
	RTTIBase
{
	RParent		parent;
	
public:
	RefScopeParent() {}
	RefScopeParent(RParent p) : parent(p) {}
	template <class T> RefScopeParent(T* p) : parent(p) {}
	template <class T> RefScopeParent(T& p) : parent(&p) {}
	virtual ~RefScopeParent() {}
	
	virtual void SetParent(RParent p) {parent = p;}
	
	const RParent& GetParent() const {
		ASSERT(parent);
		return parent;
	}
	
	const RParent& GetParentUnsafe() const {
		return parent;
	}
	
	template <class V>
	Ref<V,RParent> AsRef() {
		ASSERT(parent);
		return Ref<V,RParent>(parent, CastPtr<V>(this));
	}
	
	template <class V>
	Ref<V,RParent> AsRefUnsafe() {
		return Ref<V,RParent>(parent, CastPtr<V>(this));
	}
	
	template <class V> operator Ref<V,RParent>() {return AsRef<V>();}
	template <class V, class P> operator Ref<V,P>();// {return AsRef<V>();}
	
};


template <class T, class ParentT, class RParent=RefParent1<ParentT>>
class WeakRefScopeEnabler :
	virtual public LockedScopeRefCounter,
	virtual public RefScopeParent<RParent>
{
	
public:
	using SP_Weak = RefScopeParent<RParent>;
	RTTI_DECL2(WeakRefScopeEnabler, LockedScopeRefCounter, SP_Weak)
	
	WeakRefScopeEnabler() {
		#ifdef flagDEBUG_STACK
		dbg_type = AsTypeCls<T>();
		#endif
	}
	
	
	
};


template <class T, class ParentT, class RParent=RefParent1<ParentT>>
class RefScopeEnabler :
	virtual public LockedScopeRefCounter,
	virtual public RefScopeParent<RParent>
{
	
public:
	using Parent	= ParentT;
	using LScope	= RefScopeEnabler<T,ParentT,RParent>;
	using SP		= RefScopeParent<RParent>;
	RTTI_DECL2(RefScopeEnabler, LockedScopeRefCounter, SP)
	
	template <class V=T>
	Ref<V,RParent> AsRefStatic() {
		static_assert(std::is_convertible<LScope,V>(), "RefScopeEnabler<T> must be convertible to V");
		V* o = static_cast<V*>(this);
		return Ref<V,RParent>(SP::GetParent(), o);
	}
	
	template <class V=T>
	Ref<V,RParent> AsRefT() {
		V* o = CastPtr<V>(this);
		ASSERT(o);
		return Ref<V,RParent>(SP::GetParent(), o);
	}
	
};












template <class T, class Parent = RefParent1<typename T::Parent>>
class RefLinkedList {
	
	struct Item {
		Item* prev = 0;
		Item* next = 0;
		T value;
		Item() {}
	};
	
	typedef RecyclerPool<Item> Rec;
	static inline Rec& GetRecyclerPool() {MAKE_STATIC(Rec, r); return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	typedef Ref<T, Parent> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it) ref = it->value.template AsRefT<T>();}
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {MemSwap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void  Clear() {ref.Clear(); it = 0;}
		void ClearRef() const {ref.Clear();}
		Item* GetItem() const {return it;}
		T*   operator->() {ChkRef(); return ref.Get();}
		R&   operator*() const {ChkRef(); return ref;}
		void operator=(const Iterator& i) {Clear(); it = i.it;}
		bool operator==(const Iterator& i) const {return i.it == it;}
		bool operator!=(const Iterator& i) const {return i.it != it;}
		void operator++() {ClearRef(); if (it) {it = it->next;}}
		void operator--() {ClearRef(); if (it) {it = it->prev;}}
		T&   operator()() const {ASSERT(it); return it->value;}
		T&   Get() const {ASSERT(it); return it->value;}
		operator R*() const {ChkRef(); return &ref;}
		operator bool() const {return it;}
	};
	
	class PtrIterator {
		Item* it = 0;
		mutable T* ptr = 0;
		void ChkRef() const {if (ptr == 0 && it) ptr = &it->value;}
	public:
		PtrIterator() {}
		PtrIterator(Item* it) : it(it) {}
		PtrIterator(PtrIterator&& it) {MemSwap(*this, it);}
		PtrIterator(const PtrIterator& i) : it(i.it) {}
		void  Clear() {ptr = 0; it = 0;}
		void ClearRef() const {ptr = 0;}
		Item* GetItem() const {return it;}
		T*   operator->() {ChkRef(); return ptr;}
		T&   operator*() const {ChkRef(); return *ptr;}
		void operator=(const PtrIterator& i) {Clear(); it = i.it;}
		bool operator==(const PtrIterator& i) const {return i.it == it;}
		bool operator!=(const PtrIterator& i) const {return i.it != it;}
		void operator++() {ClearRef(); if (it) {it = it->next;}}
		void operator--() {ClearRef(); if (it) {it = it->prev;}}
		T&   operator()() const {ASSERT(it); return it->value;}
		T&   Get() const {ASSERT(it); return it->value;}
		operator T*() const {ChkRef(); return ptr;}
		operator bool() const {return it;}
	};
	
	
	RefLinkedList() {}
	~RefLinkedList() {Clear();}
	T& GetFirst() {ASSERT(first); return first->value;}
	T& GetLast() {ASSERT(last); return last->value;}
	Item* AddItem() {
		Item* it = GetRecyclerPool().New();
		if (!first) {
			last = first = it;
			first->prev = 0;
			first->next = 0;
		}
		else {
			last->next = it;
			it->prev = last;
			last = it;
		}
		++count;
		return it;
	}
	T& Add() {return AddItem()->value;}
	int GetCount() const {return count;}
	bool IsEmpty() const {return count == 0;}
	void RemoveFirst(int count) {
		if (!count) return;
		ASSERT(count > 0 && count <= this->count);
		count = std::min(count, this->count);
		if (count == this->count)
			Clear();
		else {
			Item* it = first;
			for(int i = 0; i < count; i++)
				it = it->next;
			Item* last_rm = it->prev;
			it->prev = 0;
			this->count -= count;
			first = it;
			it = last_rm;
			while (it) {
				last_rm = it->prev;
				GetRecyclerPool().Return(it);
				it = last_rm;
			}
		}
	}
	Iterator Remove(const Iterator& iter) {
		Item* item = iter.GetItem();
		Item* in_place = 0;
		if (item->prev) {
			if (item->next) {
				in_place = item->next;
				item->prev->next = item->next;
				item->next->prev = item->prev;
			}
			else {
				ASSERT(item == last);
				item->prev->next = 0;
				last = item->prev;
			}
		}
		else {
			ASSERT(item == first);
			if (item->next) {
				in_place = item->next;
				item->next->prev = 0;
				first = item->next;
			}
			else {
				ASSERT(item == last);
				first = 0;
				last = 0;
			}
		}
		--count;
		iter.ClearRef(); // clear ref to avoid errors
		GetRecyclerPool().Return(item);
		return in_place;
	}
	void Reverse() {
		if (IsEmpty())
			return;
		Item* iter = first;
		MemSwap(first, last);
		while (iter) {
			Item* next = iter->next;
			MemSwap(iter->prev, iter->next);
			iter = next;
		}
		ASSERT(first->prev == 0 && last->next == 0);
	}
	void Clear() {
		if (!first) return;
		auto& rec = GetRecyclerPool();
		Item* iter = last;
		while (iter) {
			Item* prev = iter->prev;
			--count;
			if (prev)
				prev->next = 0;
			rec.Return(iter);
			iter = prev;
		}
		first = 0;
		last = 0;
		ASSERT(count == 0);
	}
	
	R At(int i) {
		int j = 0;
		for(Iterator it = begin(); it; ++it, ++j)
			if (j == i)
				return *it;
		ASSERT(0);
		THROW(Exc("Position not found in RefLinkedList: " + IntStr(i)));
	}
	
	Iterator begin()	{return Iterator(first);}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(last);}
	Iterator rend()		{return Iterator();}
	
	PtrIterator pbegin()	{return PtrIterator(first);}
	PtrIterator pend()		{return PtrIterator();}
	PtrIterator rpbegin()	{return PtrIterator(last);}
	PtrIterator rpend()		{return PtrIterator();}
	
};


template <class K, class V, class Parent = RefParent1<typename V::Parent>>
class RefLinkedMap {
	LinkedList<K> keys;
	RefLinkedList<V> values;
	
public:
	typedef Ref<V, Parent> R;
	typedef typename LinkedList<K>::Iterator KeyIter;
	typedef typename RefLinkedList<V>::Iterator ValueIter;
	struct Iterator {
		KeyIter key;
		ValueIter value;
		Iterator() {}
		Iterator(KeyIter&& k, ValueIter&& v) : key(std::move(k)), value(std::move(v)) {}
		Iterator(const KeyIter& k, const ValueIter& v) : key(k), value(v) {}
		void operator=(const Iterator& i) {key = i.key; value = i.value;}
		void operator++() {++key; ++value;}
		void operator--() {--key; --value;}
		bool operator==(const Iterator& i) const {return key == i.key;}
		bool operator!=(const Iterator& i) const {return key != i.key;}
		V*   operator->() {return &value();}
		R&   operator*() {return *value;}
		operator bool() const {return key;}
		V& Get() {return value.Get();}
	};
	
	RefLinkedMap() {}
	~RefLinkedMap() {Clear();}
	void Clear() {keys.Clear(); values.Clear();}
	
	R Add(const K& k) {keys.AddItem()->value = k; return values.Add();}
	int GetCount() const {return keys.GetCount();}
	bool IsEmpty() const {return keys.IsEmpty();}
	Iterator Remove(const Iterator& iter) {
		Iterator it;
		it.key		= keys.Remove(iter.key);
		it.value	= values.Remove(iter.value);
		return it;
	}
	
	Iterator Find(const K& key) {
		KeyIter k = keys.begin();
		ValueIter v = values.begin();
		for (;k; ++k, ++v)
			if (*k == key)
				return Iterator(k, v);
		return Iterator();
	}
	
	RefLinkedList<V>& GetValues() {return values;}
	

	Iterator begin()	{return Iterator(keys.begin(), values.begin());}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(keys.rbegin(), values.rbegin());}
	Iterator rend()		{return Iterator();}
	
};


template <class T, class Parent = RefParent1<typename T::Parent>>
class RefLinkedListIndirect {
	
	struct Item {
		Item* prev = 0;
		Item* next = 0;
		One<T> value;
		
	};
	
	typedef RecyclerPool<Item> Rec;
	static inline Rec& GetRecyclerPool() {MAKE_STATIC(Rec, r); return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	typedef Ref<T, Parent> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it && !it->value.IsEmpty()) ref = it->value->AsRefT();}
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& i) {it = i.it; i.it = 0; ref = i.ref; i.ref.Clear();}
		Iterator(const Iterator& i) : it(i.it) {}
		void Clear() {ref.Clear(); it = 0;}
		void ClearRef() const {ref.Clear();}
		Item* GetItem() const {return it;}
		T*   operator->() {ChkRef(); return ref.Get();}
		R&   operator*() const {ChkRef(); return ref;}
		void operator=(const Iterator& i) {Clear(); it = i.it;}
		bool operator==(const Iterator& i) const {return i.it == it;}
		bool operator!=(const Iterator& i) const {return i.it != it;}
		void operator++() {ClearRef(); if (it) {it = it->next;}}
		void operator--() {ClearRef(); if (it) {it = it->prev;}}
		T&   operator()() const {ASSERT(it && !it->value.IsEmpty()); return *it->value;}
		operator R*() const {ChkRef(); return &ref;}
		operator bool() const {return it;}
	};
	
	class PtrIterator {
		Item* it = 0;
		mutable T* ptr = 0;
		void ChkRef() const {if (ptr == 0 && it && !it->value.IsEmpty()) ptr = &*it->value;}
	public:
		PtrIterator() {}
		PtrIterator(Item* it) : it(it) {}
		PtrIterator(PtrIterator&& i) {it = i.it; i.it = 0; ptr = i.ptr; i.ptr = 0;}
		PtrIterator(const PtrIterator& i) : it(i.it) {}
		void Clear() {ptr = 0; it = 0;}
		void ClearRef() const {ptr = 0;}
		Item* GetItem() const {return it;}
		T*   operator->() {ChkRef(); return ptr;}
		T*   operator*() const {ChkRef(); return ptr;}
		void operator=(const PtrIterator& i) {Clear(); it = i.it;}
		bool operator==(const PtrIterator& i) const {return i.it == it;}
		bool operator!=(const PtrIterator& i) const {return i.it != it;}
		void operator++() {ClearRef(); if (it) {it = it->next;}}
		void operator--() {ClearRef(); if (it) {it = it->prev;}}
		T&   operator()() const {ASSERT(it && !it->value.IsEmpty()); return *it->value;}
		operator T*() const {ChkRef(); return ptr;}
		operator bool() const {return it;}
	};
	
	RefLinkedListIndirect() {}
	~RefLinkedListIndirect() {Clear();}
	One<T>& Add(T* o=NULL) {
		Item* it = GetRecyclerPool().New();
		if (!first) {
			last = first = it;
			first->prev = 0;
			first->next = 0;
		}
		else {
			last->next = it;
			it->prev = last;
			last = it;
		}
		++count;
		if (o)
			it->value.Attach(o);
		return it->value;
	}
	T* Detach(const Iterator& it) {
		T* o = it.GetItem()->value.Detach();
		RemoveItem(it.GetItem());
		return o;
	}
	T* Detach(const PtrIterator& it) {
		T* o = it.GetItem()->value.Detach();
		RemoveItem(it.GetItem());
		return o;
	}
	int GetCount() const {return count;}
	bool IsEmpty() const {return count == 0;}
	Iterator Remove(const Iterator& iter) {
		Item* item = iter.GetItem();
		iter.ClearRef(); // clear ref to avoid errors
		return RemoveItem(item);
	}
	PtrIterator RemovePtr(const PtrIterator& iter) {
		Item* item = iter.GetItem();
		iter.ClearRef(); // clear ref to avoid errors
		return RemoveItem(item);
	}
	Item* RemoveItem(Item* item) {
		if (item->prev) {
			if (item->next) {
				item->prev->next = item->next;
				item->next->prev = item->prev;
			}
			else {
				ASSERT(item == last);
				item->prev->next = 0;
				last = item->prev;
			}
		}
		else {
			ASSERT(item == first);
			if (item->next) {
				item->next->prev = 0;
				first = item->next;
			}
			else {
				ASSERT(item == last);
				first = 0;
				last = 0;
			}
		}
		--count;
		item->value.Clear();
		
		GetRecyclerPool().Return(item);
		return item;
	}
	void Reverse() {
		if (IsEmpty())
			return;
		Item* iter = first;
		MemSwap(first, last);
		while (iter) {
			Item* next = iter->next;
			MemSwap(iter->prev, iter->next);
			iter = next;
		}
		ASSERT(first->prev == 0 && last->next == 0);
	}
	void Clear() {
		if (!first) return;
		auto& rec = GetRecyclerPool();
		Item* iter = last;
		while (iter) {
			Item* prev = iter->prev;
			--count;
			if (prev)
				prev->next = 0;
			iter->value.Clear();
			rec.Return(iter);
			iter = prev;
		}
		first = 0;
		last = 0;
		ASSERT(count == 0);
	}
	
	
	
	Iterator begin()	{return Iterator(first);}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return last ? Iterator(last) : Iterator();}
	Iterator rend()		{return Iterator();}
	
	PtrIterator pbegin()	{return PtrIterator(first);}
	PtrIterator pend()		{return PtrIterator();}
	PtrIterator rpbegin()	{return last ? PtrIterator(last) : PtrIterator();}
	PtrIterator rpend()		{return PtrIterator();}
	
};

template <class K, class V, class Parent = RefParent1<typename V::Parent>>
class RefLinkedMapIndirect {
	LinkedList<K> keys;
	RefLinkedListIndirect<V> values;
	
public:
	typedef Ref<V, Parent> R;
	typedef typename LinkedList<K>::Iterator KeyIter;
	typedef typename RefLinkedListIndirect<V>::Iterator ValueIter;
	typedef typename RefLinkedListIndirect<V>::PtrIterator ValuePtrIter;
	typedef typename RefLinkedListIndirect<V>::R ValueRef;
	struct Iterator {
		KeyIter key;
		ValueIter value;
		Iterator() {}
		Iterator(KeyIter&& k, ValueIter&& v) : key(std::move(k)), value(std::move(v)) {}
		Iterator(const KeyIter& k, const ValueIter& v) : key(k), value(v) {}
		void operator=(const Iterator& i) {key = i.key; value = i.value;}
		void operator++() {++key; ++value;}
		void operator--() {--key; --value;}
		bool operator==(const Iterator& i) const {return key == i.key;}
		bool operator!=(const Iterator& i) const {return key != i.key;}
		V*   operator->() {return &value();}
		R&   operator*() {return *value;}
		operator bool() const {return key;}
		bool IsEmpty() const {return key.IsEmpty();}
		V& Get() {return value();}
		V& operator()() {return value();}
	};
	
	struct PtrIterator {
		KeyIter key;
		ValuePtrIter value;
		PtrIterator() {}
		PtrIterator(KeyIter&& k, ValuePtrIter&& v) : key(std::move(k)), value(std::move(v)) {}
		PtrIterator(const KeyIter& k, const ValuePtrIter& v) : key(k), value(v) {}
		void operator=(const PtrIterator& i) {key = i.key; value = i.value;}
		void operator++() {++key; ++value;}
		void operator--() {--key; --value;}
		bool operator==(const PtrIterator& i) const {return key == i.key;}
		bool operator!=(const PtrIterator& i) const {return key != i.key;}
		V*   operator->() {return &value();}
		V&   operator*() {return **value;}
		operator bool() const {return key;}
		bool IsEmpty() const {return key.IsEmpty();}
		V& Get() {return value();}
		V& operator()() {return value();}
	};
	
	RefLinkedMapIndirect() {}
	~RefLinkedMapIndirect() {Clear();}
	void Clear() {keys.Clear(); values.Clear();}
	
	One<V>& Add(const K& k) {keys.AddItem()->value = k; return values.Add();}
	One<V>& Add(const K& k, V* o) {keys.AddItem()->value = k; return values.Add(o);}
	int GetCount() const {return keys.GetCount();}
	bool IsEmpty() const {return keys.IsEmpty();}
	Iterator Remove(const Iterator& iter) {
		Iterator it;
		it.key		= keys.Remove(iter.key);
		it.value	= values.Remove(iter.value);
		return it;
	}
	V* Detach(const Iterator& iter) {
		keys.Remove(iter.key);
		V* v = values.Detach(iter.value);
		return v;
	}
	V* Detach(const PtrIterator& iter) {
		keys.Remove(iter.key);
		V* v = values.Detach(iter.value);
		return v;
	}
	
	Iterator Find(const K& key) {
		KeyIter k = keys.begin();
		ValueIter v = values.begin();
		for (;k; ++k, ++v)
			if (*k == key)
				return Iterator(k, v);
		return Iterator();
	}
	
	PtrIterator FindPtr(const K& key) {
		KeyIter k = keys.begin();
		ValuePtrIter v = values.pbegin();
		for (;k; ++k, ++v)
			if (*k == key)
				return PtrIterator(k, v);
		return PtrIterator();
	}
	
	R At(int i) {
		int j = 0;
		for(Iterator it = begin(); it; ++it, ++j)
			if (j == i)
				return *it;
		ASSERT(0);
		THROW(Exc("Position not found in RefLinkedMapIndirect: " + IntStr(i)));
	}
	
	
	RefLinkedListIndirect<V>& GetValues() {return values;}
	
	Iterator begin()	{return Iterator(keys.begin(), values.begin());}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(keys.rbegin(), values.rbegin());}
	Iterator rend()		{return Iterator();}
	
	PtrIterator pbegin()	{return PtrIterator(keys.pbegin(), values.pbegin());}
	PtrIterator pend()		{return PtrIterator();}
	PtrIterator rpbegin()	{return PtrIterator(keys.rpbegin(), values.rpbegin());}
	PtrIterator rpend()		{return PtrIterator();}
	
};






template<class T, class Parent = RefParent1<typename T::Parent>>
using RefTypeMap			= RefLinkedMap<TypeCls, T, Parent>;

template<class T, class Parent = RefParent1<typename T::Parent>>
using RefTypeMapIndirect	= RefLinkedMapIndirect<TypeCls, T, Parent>;

template<class T, class Parent = RefParent1<typename T::Parent>>
using TypeRefMap			= LinkedMap<TypeCls, Ref<T,Parent>>;






class RefClearVisitor : public RuntimeVisitor {
	
public:
	RefClearVisitor() {
		SetClearRefs();
	}
	
};

NAMESPACE_TOPSIDE_END


#endif
