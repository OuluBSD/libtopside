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
	void Clear() {o = 0;}
	
	operator bool() const {return o;}
	operator T&() const {ASSERT(o); return *o;}
	operator T*() const {ASSERT(o); return o;}
	T* operator->() const {ASSERT(o); return o;}
	
};

template <class A, class B>
struct RefParent2 {
	A* a = 0;
	B* b = 0;
	
	RefParent2() {}
	RefParent2(A* a, B* b) : a(a), b(b) {}
	
	void Clear() {a = 0; b = 0;}
	
	operator bool() const {return a || b;}
	
};

void DebugRefVisits_AddRef(void* mem);
void DebugRefVisits_RemoveRef(void* mem);
#define DBG_REF_CTOR if (IsDebugRefVisits()) {DebugRefVisits_AddRef(this);}
#define DBG_REF_DTOR if (IsDebugRefVisits()) {DebugRefVisits_RemoveRef(this);}
bool IsDebugRefVisits();
void SetDebugRefVisits(bool b=true);

#define SCOPE_REF(x) auto& x = *x##_;

template <class T, class Parent = RefParent1<typename T::Parent> >
class Ref :
	RTTIBase
{
	T* o = 0;
	Parent p;
	
public:
	RTTI_DECL0(Ref)
	using Type = T;
	using ParentT = Parent;
	
	
	Ref() {DBG_REF_CTOR}
	Ref(Nuller) {DBG_REF_CTOR}
	Ref(Parent p, T* o) : p(p), o(o) {if (o) o->IncRef(); DBG_REF_CTOR}
	Ref(const Ref& r) {*this = r; DBG_REF_CTOR}
	Ref(Ref&& r) {if (r.o) {o = r.o; r.o = 0; p = r.p; r.p.Clear();} DBG_REF_CTOR}
	~Ref() {Clear(); DBG_REF_DTOR}
	
	
	T* GetRefPtr() const {return o;}
	const Parent& GetRefParent() const {return p;}
	
	template <class V>
	Ref(const Ref<V,Parent>& r) {
		static_assert(
			std::is_same<V, T>() ||
			std::is_base_of<V,T>() ||
			std::is_base_of<T,V>(), "T must inherit V or vice versa");
		if (!r.IsEmpty()) {
			o = CastPtr<T>(r.Get());
			ASSERT(o);
			o->IncRef();
		}
	}
	
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
	operator bool() const {return o != NULL;}
	
	bool IsEmpty() const {return o == NULL;}
	T* Get() const {return o;}
	void Clear() {if (o) o->DecRef(); o = 0; p.Clear();}
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
		o->IncRef();
		ASSERT(o);
	}
	
	Ref& Set(const Ref& r) {
		Clear();
		o = r.o;
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
		p = r.GetRefParent();
		if (o)
			o->IncRef();
		return *this;
	}
	
};



template <class RParent>
class RefScopeParent :
	RTTIBase
{
	RParent		parent;
	
public:
	RefScopeParent() {}
	RefScopeParent(RParent p) : parent(p) {}
	virtual ~RefScopeParent() {}
	
	virtual void SetParent(RParent p) {parent = p;}
	
	const RParent& GetParent() const {
		ASSERT(parent);
		return parent;
	}
	
	template <class V>
	Ref<V,RParent> AsRef() {
		ASSERT(parent);
		return Ref<V,RParent>(parent, CastPtr<V>(this));
	}
	
	template <class V> operator Ref<V,RParent>() {return AsRef<V>();}
	
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
	
	RefScopeEnabler() {
		#ifdef flagDEBUG_STACK
		dbg_type = AsTypeCls<T>();
		#endif
	}
	
	/*RefScopeEnabler(RParent p) : SP(p) {
		#ifdef flagDEBUG_STACK
		dbg_type = AsTypeCls<T>();
		#endif
	}*/
	
	
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
	static inline Rec& GetRecyclerPool() {static Rec r(1); return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	typedef Ref<T, Parent> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it) ref = it->value.AsRefT();}
		void ClearRef() {ref.Clear();}
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {MemSwap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void  Clear() {ref.Clear(); it = 0;}
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
	
	
	RefLinkedList() {}
	~RefLinkedList() {Clear();}
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
	//R* FindPtr(const K& k);
	//const R* FindPtr(const K& k) const;
	
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
	static inline Rec& GetRecyclerPool() {static Rec r(1); return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	typedef Ref<T, Parent> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it && !it->value.IsEmpty()) ref = it->value->AsRefT();}
		void ClearRef() {ref.Clear();}
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {MemSwap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void  Clear() {ref.Clear(); it = 0;}
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
		Remove(it);
		return o;
	}
	int GetCount() const {return count;}
	bool IsEmpty() const {return count == 0;}
	Iterator Remove(const Iterator& iter) {
		Item* item = iter.GetItem();
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
	
};

template <class K, class V, class Parent = RefParent1<typename V::Parent>>
class RefLinkedMapIndirect {
	LinkedList<K> keys;
	RefLinkedListIndirect<V> values;
	
public:
	typedef Ref<V, Parent> R;
	typedef typename LinkedList<K>::Iterator KeyIter;
	typedef typename RefLinkedListIndirect<V>::Iterator ValueIter;
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
	
	Iterator Find(const K& key) {
		KeyIter k = keys.begin();
		ValueIter v = values.begin();
		for (;k; ++k, ++v)
			if (*k == key)
				return Iterator(k, v);
		return Iterator();
	}
	//R* FindPtr(const K& k);
	//const R* FindPtr(const K& k) const;
	
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
	
};






template<class T, class Parent = RefParent1<typename T::Parent>>
using RefTypeMap			= RefLinkedMap<TypeId, T, Parent>;

template<class T, class Parent = RefParent1<typename T::Parent>>
using RefTypeMapIndirect	= RefLinkedMapIndirect<TypeId, T, Parent>;

template<class T, class Parent = RefParent1<typename T::Parent>>
using TypeRefMap			= LinkedMap<TypeId, Ref<T,Parent>>;






class RefClearVisitor : public RuntimeVisitor {
	
public:
	RefClearVisitor() {
		SetClearRefs();
	}
	
};

NAMESPACE_TOPSIDE_END


#endif
