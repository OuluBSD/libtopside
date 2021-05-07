#ifndef _Oulu_LinkedList_h_
#define _Oulu_LinkedList_h_

NAMESPACE_OULU_BEGIN





template <class T>
void MemSwap(T& a, T& b) {
	uint8 tmp[sizeof(T)];
	MemoryCopy(tmp, &a, sizeof(T));
	MemoryCopy(&a, &b, sizeof(T));
	MemoryCopy(&b, tmp, sizeof(T));
}



class RefRoot {
	
public:
	
};


template <class T>
struct RefParent1 {
	T* o = 0;
	
	RefParent1() {}
	RefParent1(T* o) : o(o) {}
	void Clear() {o = 0;}
	
};

template <class A, class B>
struct RefParent2 {
	A* a = 0;
	B* b = 0;
	
	RefParent2() {}
	RefParent2(A* a, B* b) : a(a), b(b) {}
	
	void Clear() {a = 0; b = 0;}
	
};

template <class T, class Parent = RefParent1<typename T::Parent> >
class Ref : Moveable<Ref<T,Parent>> {
	T* o = 0;
	Parent p;
	
public:
	Ref() {}
	Ref(Nuller) {}
	Ref(Parent p, T* o) : p(p), o(o) {if (o) o->IncRef();}
	Ref(const Ref& r) {*this = r;}
	Ref(Ref&& r) {if (r.o) {o = r.o; r.o = 0; p = r.p; r.p.Clear();}}
	~Ref() {Clear();}
	
	typedef T Type;
	
	T* GetRefPtr() const {return o;}
	const Parent& GetRefParent() const {return p;}
	
	template <class V>
	Ref(const Ref<V,Parent>& r) {
		static_assert(
			std::is_same<V, T>() ||
			std::is_base_of<V,T>() ||
			std::is_base_of<T,V>(), "T must inherit V or vice versa");
		if (!r.IsEmpty()) {
			o = dynamic_cast<T*>(r.Get());
			ASSERT(o);
			o->IncRef();
		}
	}
	
	template <class V>
	Ref& operator=(const Ref<V,Parent>& r) {return Set(r);}
	Ref& operator=(const Ref& r) {return Set(r);}
	
	bool operator==(const Ref& r) const {return r.o == o;}
	bool operator==(T* o) const {return this->o == o;}
	T* operator->() {return o;}
	const T* operator->() const {return o;}
	T& operator*() {ASSERT(o); return *o;}
	operator bool() const {return o != NULL;}
	
	bool IsEmpty() const {return o == NULL;}
	T* Get() const {return o;}
	void Clear() {if (o) o->DecRef(); o = 0; p.Clear();}
	template <class V>	V* As() {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>() || std::is_base_of<V,T>(), "V must inherit T or vice versa");
		return dynamic_cast<V*>(o);
	}
	template <class V>	Ref<V,Parent> AsRef() {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>() || std::is_base_of<V,T>(), "V must inherit T or vice versa");
		V* v = dynamic_cast<V*>(o);
		return Ref<V,Parent>(p, v);
	}
	template <class V> void WrapObject(const Parent& p, V* v) {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>(), "V must inherit T");
		ASSERT(!o);
		Clear();
		this->p = p;
		o = dynamic_cast<T*>(v);
		o->IncRef();
		ASSERT(o);
	}
	
	template <class V>
	Ref& Set(const Ref<V,Parent>& r) {
		Clear();
		o = dynamic_cast<T*>(r.GetRefPtr());
		p = r.GetRefParent();
		if (o)
			o->IncRef();
		return *this;
	}
	
};


class LockedScopeRefCounter {
	
private:
	std::atomic<int> refs;
	
	#ifdef flagDEBUG_STACK
protected:
	bool dbg_referencing = false;
	std::reference_wrapper<const std::type_info> dbg_type;
	void SetDebugReferencing(bool b=true) {dbg_referencing = b;}
	#endif
	
public:
	LockedScopeRefCounter();
	virtual ~LockedScopeRefCounter();
	
	void IncRef();
	void DecRef();
	
	void ForcedReset() {refs = 0;}
	
};


template <class RParent>
class RefScopeParent {
	RParent parent;
	
public:
	virtual ~RefScopeParent() {}
	
	void SetParent(RParent p) {parent = p;}
	
	const RParent& GetParent() const {return parent;}
	
	template <class V>
	Ref<V,RParent> AsRef() {
		return Ref<V,RParent>(parent, dynamic_cast<V*>(this));
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
		dbg_type = typeid(T);
		#endif
	}
	
	/*Ref<T> AsRef() {
		static_assert(std::is_base_of<RefScopeEnabler<T>,T>(), "T must inherit RefScopeEnabler<T>");
		return Ref<T>(static_cast<T*>(this));
	}
	
	operator Ref<T>() {
		static_assert(std::is_base_of<RefScopeEnabler<T>,T>(), "T must inherit RefScopeEnabler<T>");
		return Ref<T>(static_cast<T*>(this));
	}*/
	
	
	template <class V=T>
	Ref<V,RParent> AsRefStatic() {
		static_assert(std::is_convertible<LScope,V>(), "RefScopeEnabler<T> must be convertible to V");
		return Ref<V,RParent>(SP::GetParent(), static_cast<V*>(this));
	}
	
	template <class V=T>
	Ref<V,RParent> AsRefDynamic() {
		return Ref<V,RParent>(SP::GetParent(), dynamic_cast<V*>(this));
	}
	
	
};



template <class T>
class LinkedList {
	
	struct Item {
		Item* prev = 0;
		Item* next = 0;
		T value;
		
	};
	
	typedef RecyclerPool<Item> Rec;
	static inline Rec& GetRecyclerPool() {static Rec r; return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	
	class Iterator {
		Item* it = 0;
		
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {MemSwap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void	Clear() {it = 0;}
		Item*	GetItem() const {return it;}
		bool	IsEmpty() const {return it == 0;}
		T*   operator->() {ASSERT(it); return &it->value;}
		T&   operator*() const {ASSERT(it); return it->value;}
		void operator=(const Iterator& i) {Clear(); it = i.it;}
		bool operator==(const Iterator& i) const {return i.it == it;}
		bool operator!=(const Iterator& i) const {return i.it != it;}
		void operator++() {if (it) it = it->next;}
		void operator--() {if (it) it = it->prev;}
		T&   operator()() const {ASSERT(it); return it->value;}
		T&   Get() const {ASSERT(it); return it->value;}
		operator T*() const {return &it->value;}
		operator bool() const {return it;}
	};
	
	
	LinkedList() {}
	~LinkedList() {Clear();}
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
	T& Add(const T& o) {T& r = AddItem()->value; r = o; return r;}
	int GetCount() const {return count;}
	bool IsEmpty() const {return count == 0;}
	operator bool() const {return count > 0;}
	void RemoveFirst(int count=1) {
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
	
	
	
	Iterator begin() const		{return Iterator(first);}
	Iterator end() const		{return Iterator();}
	Iterator rbegin() const		{return last ? Iterator(last) : Iterator();}
	Iterator rend() const		{return Iterator();}
	
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
	static inline Rec& GetRecyclerPool() {static Rec r; return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	typedef Ref<T, Parent> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it) ref = it->value.AsRefDynamic();}
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
	R Add() {return AddItem()->value.AsRefDynamic();}
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
	
	
	
	Iterator begin()	{return Iterator(first);}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(last);}
	Iterator rend()		{return Iterator();}
	
};


template <class K, class V>
class LinkedMap {
	LinkedList<K> keys;
	LinkedList<V> values;
	
public:
	typedef typename LinkedList<K>::Iterator KeyIter;
	typedef typename LinkedList<V>::Iterator ValueIter;
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
		V&   operator*() {return *value;}
		operator bool() const {return key;}
		V& Get() {return value.Get();}
	};
	
	LinkedMap() {}
	~LinkedMap() {Clear();}
	void Clear() {keys.Clear(); values.Clear();}
	
	V& Add(const K& k) {keys.AddItem()->value = k; return values.Add();}
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
	
	LinkedList<V>& GetValues() {return values;}
	

	Iterator begin()	{return Iterator(keys.begin(), values.begin());}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(keys.rbegin(), values.rbegin());}
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
	static inline Rec& GetRecyclerPool() {static Rec r; return r;}
	
	Item* first = 0;
	Item* last = 0;
	int count = 0;
	
public:
	typedef Ref<T, Parent> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it && !it->value.IsEmpty()) ref = it->value->AsRefDynamic();}
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
	R Add(T* o=NULL) {
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
		return it->value->AsRefDynamic();
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
	
	R Add(const K& k) {keys.AddItem()->value = k; return values.Add();}
	R Add(const K& k, V* o) {keys.AddItem()->value = k; return values.Add(o);}
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
	
	RefLinkedListIndirect<V>& GetValues() {return values;}
	
	Iterator begin()	{return Iterator(keys.begin(), values.begin());}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(keys.rbegin(), values.rbegin());}
	Iterator rend()		{return Iterator();}
	
};

NAMESPACE_OULU_END

#endif
