#ifndef _Oulu_Locked_h_
#define _Oulu_Locked_h_

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
	
protected:
	friend class Ref<T>;
	
	std::atomic<int> refs;
	
	void IncRef() {++refs;}
	void DecRef() {--refs;}
	
public:
	LockedScopeEnabler() {
		refs = 0;
	}
	virtual ~LockedScopeEnabler() {
		ASSERT(refs == 0);
	}
	
	Ref<T> AsRef() {return Ref<T>(static_cast<T*>(this));}
	operator Ref<T>() {return Ref<T>(static_cast<T*>(this));}
	
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
	public:
		void Clear();
		R* operator->();
		R& operator*() const;
		bool operator==(const Iterator& i) const;
		bool operator!=(const Iterator& i) const;
		void operator++() const;
		void operator--() const;
		operator R*() const;
		T& operator()() const;
		operator bool() const;
		Item* GetItem() const {return it;}
	};
	
	RefLinkedList() {}
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
		TODO
	}
	void Reverse();
	void Clear();
	
	
	
	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();
	
};

template <class K, class V>
class RefLinkedMap {
	RefLinkedList<K> keys;
	RefLinkedList<V> values;
	
public:
	typedef Ref<V> R;
	typedef typename RefLinkedList<K>::Iterator KeyIter;
	typedef typename RefLinkedList<V>::Iterator ValueIter;
	struct Iterator {
		KeyIter key;
		ValueIter value;
		operator bool() const;
	};
	
	void Clear();
	
	R& Add(const K& k);
	int GetCount() const;
	bool IsEmpty() const;
	Iterator Remove(const Iterator& iter);
	
	Iterator FindIter(const K& k);
	R* FindPtr(const K& k);
	const R* FindPtr(const K& k) const;
	
	RefLinkedList<V>& GetValues();
	
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
	public:
		void Clear();
		R* operator->();
		R& operator*() const;
		bool operator==(const Iterator& i) const;
		bool operator!=(const Iterator& i) const;
		void operator++() const;
		void operator--() const;
		operator R*() const;
		T& operator()() const;
		operator bool() const;
		Item* GetItem() const {return it;}
	};
	
	RefLinkedListIndirect() {}
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
	void Reverse();
	void Clear();
	
	
	
	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();
	
};

template <class K, class V>
class RefLinkedMapIndirect {
	RefLinkedList<K> keys;
	RefLinkedListIndirect<V> values;
	
public:
	typedef Ref<V> R;
	typedef typename RefLinkedList<K>::Iterator KeyIter;
	typedef typename RefLinkedList<V>::Iterator ValueIter;
	struct Iterator {
		KeyIter key;
		ValueIter value;
		operator bool() const;
	};
	
	void Clear();
	
	R& Add(const K& k);
	int GetCount() const;
	bool IsEmpty() const;
	Iterator Remove(const Iterator& iter);
	
	Iterator FindIter(const K& k);
	R* FindPtr(const K& k);
	const R* FindPtr(const K& k) const;
	
	RefLinkedListIndirect<V>& GetValues();
	
};

NAMESPACE_OULU_END

#endif
