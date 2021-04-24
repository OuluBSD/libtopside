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
	
	Ref<T> AsRef() {return this;}
	operator Ref<T>() {return this;}
	
};


template <class T>
class RefLinkedList {
	
public:
	typedef Ref<T> R;
	
	class Iterator {
		
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
	};
	
	R Add(T* o);
	int GetCount() const;
	bool IsEmpty() const;
	Iterator Remove(const Iterator& iter);
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
	//R& operator[](int i);
	//void Remove(int i);
	//int Find(const K& k);
	
	Iterator FindIter(const K& k);
	R* FindPtr(const K& k);
	const R* FindPtr(const K& k) const;
	
	RefLinkedList<V>& GetValues();
	
};

NAMESPACE_OULU_END

#endif
