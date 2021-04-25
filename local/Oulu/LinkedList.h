#ifndef _Oulu_LinkedList_h_
#define _Oulu_LinkedList_h_

NAMESPACE_OULU_BEGIN





template <class T>
class Ref : Moveable<Ref<T>> {
	T* o = 0;
	
public:
	Ref() {}
	Ref(const Ref& r) {*this = r;}
	Ref(T* o) : o(o) {o->IncRef();}
	Ref(Ref&& r) {if (r.o) {o = r.o; r.o = 0;}}
	~Ref() {Clear();}
	
	Ref& operator=(const Ref& r) {return Set(r);}
	Ref& operator=(T* o) {Clear(); if (o) {this->o = o; o->IncRef();} return *this;}
	T* operator->() {return o;}
	const T* operator->() const {return o;}
	T& operator*() {ASSERT(o); return *o;}
	operator bool() const {return o != NULL;}
	
	bool IsEmpty() const {return o == NULL;}
	T* Get() {return o;}
	void Clear() {if (o) o->DecRef(); o = 0;}
	template <class V>	V* As() {
		static_assert(std::is_convertible<T,V>() || std::is_convertible<V,T>(), "V must be convertible with T");
		return dynamic_cast<V*>(o);
	}
	template <class V> void WrapObject(V* v) {
		static_assert(std::is_convertible<T,V>() || std::is_convertible<V,T>(), "V must be convertible with T");
		o = dynamic_cast<T*>(v);
		o->IncRef();
		ASSERT(o);
	}
	
	
	Ref& Set(const Ref& r) {
		Clear();
		o = r.o;
		o->IncRef();
		return *this;
	}
	
};


template <class T>
class LockedScopeEnabler {
	
private:
	
	std::atomic<int> refs;
	
	
public:
	LockedScopeEnabler() {
		refs = 0;
	}
	virtual ~LockedScopeEnabler() {
		ASSERT(refs == 0);
	}
	
	void IncRef() {++refs;}
	void DecRef() {--refs;}
	Ref<T> AsRef() {return Ref<T>(static_cast<T*>(this));}
	operator Ref<T>() {return Ref<T>(static_cast<T*>(this));}
	
};



template <class T>
class LinkedList {
	
	struct Item {
		Item* prev;
		Item* next;
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
		Iterator(Iterator&& it) {Swap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void	Clear() {it = 0;}
		Item*	GetItem() const {return it;}
		bool	IsEmpty() const {return it;}
		T*   operator->() {ASSERT(it); return &it->value;}
		T&   operator*() const {ASSERT(it); return it->value;}
		void operator=(const Iterator& i) {Clear(); it = i.it;}
		bool operator==(const Iterator& i) const {return i.it == it;}
		bool operator!=(const Iterator& i) const {return i.it != it;}
		void operator++() {if (it) it = it->next;}
		void operator--() {if (it) it = it->prev;}
		T&   operator()() const {ASSERT(it); return it->value;}
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
		Swap(first, last);
		while (iter) {
			Item* next = iter->next;
			Swap(iter->prev, iter->next);
			iter = next;
		}
		ASSERT(first->prev == 0 && last->next == 0);
	}
	void Clear() {
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
		ASSERT(count == 0);
	}
	
	
	
	Iterator begin()	{return Iterator(first);}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return last ? Iterator(last->prev) : Iterator();}
	Iterator rend()		{return Iterator();}
	
};



template <class T>
class RefLinkedList {
	
	struct Item {
		Item* prev;
		Item* next;
		T value;
		
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
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {Swap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void  Clear() {ref.Clear(); it = 0;}
		Item* GetItem() const {return it;}
		R*   operator->() {ChkRef(); return &ref;}
		R&   operator*() const {ChkRef(); return ref;}
		void operator=(const Iterator& i) {Clear(); it = i.it;}
		bool operator==(const Iterator& i) const {return i.it == it;}
		bool operator!=(const Iterator& i) const {return i.it != it;}
		void operator++() {if (it) it = it->next;}
		void operator--() {if (it) it = it->prev;}
		T&   operator()() const {ASSERT(it); return it->value;}
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
		Swap(first, last);
		while (iter) {
			Item* next = iter->next;
			Swap(iter->prev, iter->next);
			iter = next;
		}
		ASSERT(first->prev == 0 && last->next == 0);
	}
	void Clear() {
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
		ASSERT(count == 0);
	}
	
	
	
	Iterator begin()	{return Iterator(first);}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return last ? Iterator(last->prev) : Iterator();}
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
		operator bool() const {return key;}
		V& Get() {V* v = value->Get(); ASSERT(v); return v;}
	};
	
	RefLinkedMap() {}
	~RefLinkedMap() {Clear();}
	void Clear() {keys.Clear(); values.Clear();}
	
	R& Add(const K& k) {keys.AddItem()->value = k; return values.Add();}
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
		for (;k; ++k)
			if (*k == key)
				return Iterator(k, v);
		return Iterator();
	}
	//R* FindPtr(const K& k);
	//const R* FindPtr(const K& k) const;
	
	RefLinkedList<V>& GetValues() {return values;}
	
};


template <class T>
class RefLinkedListIndirect {
	
	struct Item {
		Item* prev;
		Item* next;
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
	public:
		Iterator() {}
		Iterator(Item* it) : it(it) {}
		Iterator(Iterator&& it) {Swap(*this, it);}
		Iterator(const Iterator& i) : it(i.it) {}
		void  Clear() {ref.Clear(); it = 0;}
		Item* GetItem() const {return it;}
		R*   operator->() {ChkRef(); return &ref;}
		R&   operator*() const {ChkRef(); return ref;}
		void operator=(const Iterator& i) {Clear(); it = i.it;}
		bool operator==(const Iterator& i) const {return i.it == it;}
		bool operator!=(const Iterator& i) const {return i.it != it;}
		void operator++() {if (it) it = it->next;}
		void operator--() {if (it) it = it->prev;}
		T&   operator()() const {ASSERT(it); return it->value;}
		operator R*() const {ChkRef(); return &ref;}
		operator bool() const {return it;}
	};
	
	RefLinkedListIndirect() {}
	~RefLinkedListIndirect() {Clear();}
	R Add() {
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
		return it->value.AsRef();
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
		GetRecyclerPool().Return(item);
		TODO
	}
	void Reverse() {
		if (IsEmpty())
			return;
		Item* iter = first;
		Swap(first, last);
		while (iter) {
			Item* next = iter->next;
			Swap(iter->prev, iter->next);
			iter = next;
		}
		ASSERT(first->prev == 0 && last->next == 0);
	}
	void Clear() {
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
		ASSERT(count == 0);
	}
	
	
	
	Iterator begin()	{return Iterator(first);}
	Iterator end()		{return Iterator();}
	Iterator rbegin()	{return last ? Iterator(last->prev) : Iterator();}
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
		operator bool() const {return key;}
		ValueRef* operator->() {return value;}
		bool IsEmpty() const {return key.IsEmpty();}
		V& Get() {return value();}
	};
	
	RefLinkedMapIndirect() {}
	~RefLinkedMapIndirect() {Clear();}
	void Clear() {keys.Clear(); values.Clear();}
	
	R& Add(const K& k) {keys.AddItem()->value = k; return values.Add();}
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
		for (;k; ++k)
			if (*k == key)
				return Iterator(k, v);
		return Iterator();
	}
	//R* FindPtr(const K& k);
	//const R* FindPtr(const K& k) const;
	
	RefLinkedListIndirect<V>& GetValues() {return values;}
	
};

NAMESPACE_OULU_END

#endif
