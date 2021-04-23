#ifndef _Oulu_Locked_h_
#define _Oulu_Locked_h_

NAMESPACE_OULU_BEGIN




template <class T>
class Ref : Moveable<Ref<T>> {
	
public:
	Ref() {}
	Ref(const Ref& r);
	
	T* operator->();
	const T* operator->() const;
	T& operator*();
	T* Get();
	void Clear();
	
	template <class V>	V* As();
	template <class V>	void WrapObject(V* o);
	
	bool IsEmpty() const;
	operator bool() const;
	
	
	
};


template <class T>
class LockedScopeEnabler {
	
public:
	LockedScopeEnabler() {}
	virtual ~LockedScopeEnabler() {}
	
	Ref<T> AsRef();
	
	
	operator Ref<T>();
	
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
