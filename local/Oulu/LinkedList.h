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


template <class T>
class Ref : Moveable<Ref<T>> {
	T* o = 0;
	
public:
	Ref() {}
	Ref(const Ref& r) {*this = r;}
	Ref(T* o) : o(o) {if (o) o->IncRef();}
	Ref(Ref&& r) {if (r.o) {o = r.o; r.o = 0;}}
	~Ref() {Clear();}
	
	typedef T Type;
	
	template <class V>
	Ref(const Ref<V>& r) {
		static_assert(std::is_same<V, T>() || std::is_base_of<V,T>() || std::is_base_of<T,V>(), "T must inherit V or vice versa");
		if (!r.IsEmpty()) {
			o = dynamic_cast<T*>(r.Get());
			ASSERT(o);
			o->IncRef();
		}
	}
	
	
	bool operator==(const Ref& r) {return r.o == o;}
	Ref& operator=(const Ref& r) {return Set(r);}
	Ref& operator=(T* o) {Clear(); if (o) {this->o = o; o->IncRef();} return *this;}
	T* operator->() {return o;}
	const T* operator->() const {return o;}
	T& operator*() {ASSERT(o); return *o;}
	operator bool() const {return o != NULL;}
	
	bool IsEmpty() const {return o == NULL;}
	T* Get() const {return o;}
	void Clear() {if (o) o->DecRef(); o = 0;}
	template <class V>	V* As() {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>() || std::is_base_of<V,T>(), "V must inherit T or vice versa");
		return dynamic_cast<V*>(o);
	}
	template <class V>	Ref<V> AsRef() {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>() || std::is_base_of<V,T>(), "V must inherit T or vice versa");
		V* v = dynamic_cast<V*>(o);
		return Ref<V>(v);
	}
	template <class V> void WrapObject(V* v) {
		static_assert(std::is_same<V, T>() || std::is_base_of<T,V>(), "V must inherit T");
		ASSERT(!o);
		Clear();
		o = static_cast<T*>(v);
		o->IncRef();
		ASSERT(o);
	}
	
	
	Ref& Set(const Ref& r) {
		Clear();
		o = r.o;
		if (o)
			o->IncRef();
		return *this;
	}
	
};


class LockedScopeRefCounter {
	
private:
	std::atomic<int> refs;
	
public:
	LockedScopeRefCounter() {
		refs = 0;
	}
	virtual ~LockedScopeRefCounter() {
		ASSERT(refs == 0);
	}
	
	void IncRef() {++refs;}
	void DecRef() {ASSERT(refs > 0); --refs;}
	
	
};


template <class T>
class LockedScopeEnabler : virtual public LockedScopeRefCounter {
	
	
public:
	LockedScopeEnabler() {}
	
	Ref<T> AsRef() {
		static_assert(std::is_base_of<LockedScopeEnabler<T>,T>(), "T must inherit LockedScopeEnabler<T>");
		return Ref<T>(static_cast<T*>(this));
	}
	
	operator Ref<T>() {
		static_assert(std::is_base_of<LockedScopeEnabler<T>,T>(), "T must inherit LockedScopeEnabler<T>");
		return Ref<T>(static_cast<T*>(this));
	}
	
	template <class V>	Ref<V> AsRef() {
		static_assert(std::is_base_of<T,V>(), "V must inherit T");
		V* v = dynamic_cast<V*>(static_cast<T*>(this));
		return Ref<V>(v);
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
	Iterator rbegin()	{return last ? Iterator(last) : Iterator();}
	Iterator rend()		{return Iterator();}
	
};



template <class T>
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
	typedef Ref<T> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it) ref = &it->value;}
		void ClearRef() {ref.Clear();}
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {MemSwap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void  Clear() {ref.Clear(); it = 0;}
		Item* GetItem() const {return it;}
		T*   operator->() {ChkRef(); return ref;}
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
	R Add() {return AddItem()->value.AsRef();}
	int GetCount() const {return count;}
	bool IsEmpty() const {return count == 0;}
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
	
	RefLinkedList<V>& GetValues() {return values;}
	

	Iterator begin()	{return Iterator(keys.begin(), values.begin());}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return Iterator(keys.rbegin(), values.rbegin());}
	Iterator rend()		{return Iterator();}
	
};


template <class K, class V>
class RefLinkedMap {
	LinkedList<K> keys;
	RefLinkedList<V> values;
	
public:
	typedef Ref<V> R;
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


template <class T>
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
	typedef Ref<T> R;
	
	class Iterator {
		Item* it = 0;
		mutable R ref;
		void ChkRef() const {if (ref.IsEmpty() && it && !it->value.IsEmpty()) ref = &*it->value;}
		void ClearRef() {ref.Clear();}
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {MemSwap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void  Clear() {ref.Clear(); it = 0;}
		Item* GetItem() const {return it;}
		T*   operator->() {ChkRef(); return ref;}
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
		return it->value->AsRef();
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

template <class K, class V>
class RefLinkedMapIndirect {
	LinkedList<K> keys;
	RefLinkedListIndirect<V> values;
	
public:
	typedef Ref<V> R;
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