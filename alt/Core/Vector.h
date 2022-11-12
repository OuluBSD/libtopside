#ifndef _CoreAlt_Vector_h_
#define _CoreAlt_Vector_h_

NAMESPACE_UPP_BEGIN

template <int size>
struct Data_S_ : Moveable< Data_S_<size> > {
	byte filler[size];
};

template <class T>
inline void Construct(T *t, const T *lim) {
	while(t < lim)
		new(t++) T;
}

template <class T>
inline void Destroy(T *t, const T *end)
{
	while(t != end) {
		t->~T();
		t++;
	}
}





template <class T>
inline void Reverse(T& t) {
	int count = t.GetCount();
	int count_2 = count / 2;
	int a = 0, b = count - 1;
	for (int i = 0; i < count_2; i++) {
		Swap(t[a++], t[b--]);
	}
}

template <class T>
class One : Moveable<One<T>> {
	T* obj = NULL;

public:
	One() {}
	One(T* obj) : obj(obj) {}
	One(One&& o) {obj = o.obj; o.obj = NULL;}
	~One() { Clear(); }

	T& Create() { Attach(new T()); return *obj;}
	template <class... Args>
	T& Create(Args&&... args) { T *q = new T(std::forward<Args>(args)...); Attach(q); return *q; }
	void Attach(T* obj) {Clear(); this->obj = obj;}
	void Clear() { if (obj) { delete obj; obj = NULL; } }
	void operator=(T* obj) { Attach(obj); }
	bool Is() const { return obj != NULL; }
	bool IsEmpty() const { return obj == NULL; }
	T* operator->() {ASSERT(obj); return obj;}
	const T* operator->() const {ASSERT(obj); return obj;}
	T& operator*() {ASSERT(obj); return *obj;}
	const T& operator*() const {ASSERT(obj); return *obj;}
	T* Get() {return obj;}
	const T* Get() const {return obj;}
	T& Object() {return *obj;}
	T* Detach() {ASSERT(obj); T* tmp = obj; obj = NULL; return tmp;}
	operator bool() const {return !IsEmpty();}
	bool operator!=(void* ptr) {return ptr != obj;}
	operator T&() {ASSERT(obj); return *obj;}
	operator const T&() const {ASSERT(obj); return *obj;}
	
	template <class K>
	void CreateAbstract() {static_assert(std::is_base_of<T, K>(), "Class K must be base of T"); Attach(new K());}
	
	bool operator<(const One& o) const {if (!obj) return false; if (!o.obj) return true; return *obj < *o.obj;}
	
};


class NullOpt {};
extern const NullOpt null_opt;


template <class T>
class Optional {
	T* obj = NULL;

public:
	Optional() {}
	Optional(Optional&& o) {obj = o.obj; o.obj = NULL;}
	Optional(const Optional& opt) {if (opt.obj) this->obj = new T(*opt.obj);}
	Optional(const T& obj) {this->obj = new T(obj);}
	Optional(const Nuller& n) {}
	Optional(const NullOpt& n) {}
	Optional(T* obj) : obj(obj) {}
	Optional(const Pick<T>& n) {*this = n;}
	template <class K> Optional(const K& arg) {this->obj = new T(arg);}
	~Optional() { Clear(); }

	void Create() { Clear(); obj = new T(); }
	void Clear() { if (obj) { delete obj; obj = NULL; } }
	void operator=(const NullOpt& obj) { Clear();}
	void operator=(const T& obj) { Clear(); this->obj = new T(obj); }
	void operator=(const Optional& o) { Clear(); if (!o.IsEmpty()) {this->obj = new T(*o.obj); }}
	void operator=(const Pick<Optional<T>>& n) { Clear(); if (!n.Get().IsEmpty()) {Pick(n.Get());}}
	void Pick(Optional& o) {obj = o.obj; o.obj = NULL;}
	bool IsEmpty() const { return obj == NULL; }
	T& GetObject() const {return *obj;}
	T& value() const {return *obj;}
	T* operator->() {ASSERT(obj); return obj;}
	operator bool () const {return obj != NULL;}
	bool has_value() const {return obj != NULL;}
	T& operator*() {return *obj;}
};

template <class T>
Optional<T> MakeOptional(T value) {Optional<T> o; o = value; return o;}



template <class T>
class Unique {
	static One<T> obj;

public:
	Unique() {}
	Unique(Unique&& o) {obj = o.obj;}
	~Unique() { Clear(); }

	void Create() {if (obj.IsEmpty()) obj.Create();}
	void Clear() { obj.Clear(); }
	void Reset() {Clear(); Create();}
	bool IsEmpty() const { return obj.IsEmpty(); }
	T* operator->() {return obj.Get();}
};



template <class K>
class Vector : Moveable<Vector<K>> {
	K* data = NULL;
	int alloc = 0;
	int count = 0;


	void IncreaseReserved() {
		uint64 new_alloc = 1;
		while (new_alloc <= alloc)
			new_alloc <<= 1;
		if (new_alloc >= INT_MAX)
			new_alloc = INT_MAX;
		Reserve((int)new_alloc);
	}
	
	void Pick0(Vector& v) { Clear(); data = v.data; v.data = 0; alloc = v.alloc; v.alloc = 0; count = v.count; v.count = 0; }
	
public:
	using ElPtr = K*;
	using ObjectPtr = K*;
	using value_type = K;
	
	struct RefGet {
		ElPtr p = 0;
		RefGet(ElPtr p) : p(p) {}
		K& operator()() {return *p;}
	};
	
	template <class P, int I>
	struct Iterator0 {
		P* kit = NULL;
		Iterator0() {}
		Iterator0(K* kit) : kit(kit) {}
		Iterator0(const Iterator0& it) {*this = it;}
		void operator=(const Iterator0& it) {kit = it.kit;}
		Iterator0& operator++() {kit += I; return *this;}
		Iterator0 operator++(int i) {Iterator0 ret = *this; kit += I; return ret;}
		void operator--() {kit -= I;}
		void operator--(int i) {kit -= I;}
		void operator+=(int i) {kit += I * i;}
		void operator-=(int i) {kit -= I * i;}
		P* operator->() const {return kit;}
		P* Get() const {return kit;}
		ElPtr GetElPtr() const {return kit;}
		operator P*() const {return kit;}
		P& operator*() const {return *kit;}
		bool operator==(P* ptr) const {return ptr == kit;}
		bool operator!=(P* ptr) const {return ptr != kit;}
		bool operator==(const Iterator0& it) const {return it.kit == kit;}
		bool operator!=(const Iterator0& it) const {return it.kit != kit;}
		P& operator()() const {return *kit;}
		operator P*() {return Get();}
		operator void*() {return (void*)Get();}
	};
	typedef Iterator0<const K, +1> ConstIterator;
	typedef Iterator0<const K, -1> ConstRIterator;
	typedef Iterator0<K,+1> Iterator;
	typedef Iterator0<K,-1> RIterator;
	typedef Iterator0<K,+1> iterator;

	Vector(std::initializer_list<K> l) {
		Reserve(l.size());
		auto cur = l.begin();
		auto end = l.end();
		while (cur != end) {
			new (&data[count++]) K(*cur++);
		}
	}
	Vector() {}
	Vector(Vector&& v) {Pick0(v);}
	Vector(const Pick<Vector>& pick) {Vector& v = pick.Get(); Swap(data, v.data); Swap(alloc, v.alloc); Swap(count, v.count);}
	Vector(const Vector& v) {*this <<= v;}
	Vector(int i) {SetCount(i);}
	~Vector() {
		Clear();
		return;
		AssertMoveable((K*)0);  // T must be moveable
	}
	
	void Serialize(Stream& s);
	void operator=(const Pick<Vector>& pick) {Clear(); Vector& v = pick.Get(); Swap(data, v.data); Swap(alloc, v.alloc); Swap(count, v.count);}
	void operator=(Vector&& v) {Pick0(v);}
	
	
	Iterator Begin() {return Iterator(data);}
	Iterator End() {return Iterator(data+count);}
	ConstIterator Begin() const {return ConstIterator(data);}
	ConstIterator End() const {return ConstIterator(data+count);}
	K* begin() {return GetData();}
	K* end() {return GetData() + GetCount();}
	const K* begin() const {return GetData();}
	const K* end() const {return GetData() + GetCount();}
	
	RIterator rbegin() {return RIterator(data+count-1);}
	RIterator rend() {return RIterator(data-1);}
	ConstRIterator rbegin() const {return ConstRIterator(data+count-1);}
	ConstRIterator rend() const {return ConstRIterator(data-1);}
	K* GetData() const {return data;}
	
	K& Add() {
		if (count + 1 > alloc) IncreaseReserved();
		if (count >= alloc)
			THROW(MemoryLimitExc("Vector maximum size exceeded"));
		new (&data[count]) K();
		return data[count++];
	}
	K& Add(const K& v) {
		if (count + 1 > alloc) IncreaseReserved();
		if (count >= alloc)
			THROW(MemoryLimitExc("Vector maximum size exceeded"));
		new (&data[count]) K(v);
		return data[count++];
	}
	K& AddPick(const Pick<K>& v) {
		if (count + 1 > alloc) IncreaseReserved();
		if (count >= alloc)
			THROW(MemoryLimitExc("Vector maximum size exceeded"));
		new (&data[count]) K(v);
		return data[count++];
	}
	Vector& operator<<(const K& v) { Add(v); return *this; }
	K& push_back(const K& v) {return Add(v);}
	
	void SetCount(int new_count) {
		ASSERT(new_count >= 0);
		if (new_count < 0) return;
		if (new_count > alloc) Reserve(new_count);
		if (new_count == count) return;
		if (new_count > count) {
			for (int i = count; i < new_count; i++)
				new (&data[i]) K();
		}
		else {
			for (int i = count - 1; i >= new_count; i--)
				data[i].~K();
		}
		count = new_count;
	}
	void SetCountZero() {
		for (int i = count - 1; i >= 0; i--) data[i].~K();
		count = 0;
	}
	void SetCount(int new_count, const K& value) {
		ASSERT(new_count >= 0);
		if (new_count < 0) return;
		if (new_count > alloc) Reserve(new_count);
		if (new_count == count) return;
		if (new_count > count) {
			for (int i = count; i < new_count; i++)
				new (&data[i]) K(value);
		}
		else {
			for (int i = count - 1; i >= new_count; i--)
				data[i].~K();
		}
		count = new_count;
	}
	void operator <<=(const Vector& a) {
		SetCountZero();
		Reserve(a.GetCount());
		for (int i = 0; i < a.GetCount(); i++)
			new (&data[i]) K(a[i]);
		count = a.GetCount();
	}
	void Append(const Vector& a) {
		int begin = count;
		int new_count = count + a.GetCount();
		Reserve(new_count);
		for (int i = begin, j = 0; i < new_count; i++, j++)
			new (&data[i]) K(a[j]);
		count = new_count;
	}
	void Append(const Vector& a, int append_begin, int append_count) {
		ASSERT(append_begin >= 0 && append_begin + append_count <= a.GetCount());
		int begin = count;
		int new_count = count + append_count;
		Reserve(new_count);
		for (int i = begin, j = append_begin; i < new_count; i++, j++)
			new (&data[i]) K(a[j]);
		count = new_count;
	}
	void IncreaseReserve(int more_alloc) {Reserve(GetCount() + more_alloc);}
	void Reserve(int new_alloc) {
		if (new_alloc <= alloc || new_alloc <= 0)
			return;
		K* new_data = (K*)malloc(new_alloc * sizeof(K));
		if (data) {
			if (count > 0)
				MemoryCopy((void*)new_data, (void*)data, sizeof(K) * count);
			free(data);
		}
		data = new_data;
		alloc = new_alloc;
	}
	void Shrink() {}
	int GetCount() const { return count; }
	int GetAlloc() const { return alloc; }
	bool IsEmpty() const { return GetCount() == 0; }
	
	K& At(int i) {
		ASSERT(i >= 0 && i < count);
		return *(data + i);
	}
	const K& At(int i) const {
		ASSERT(i >= 0 && i < count);
		return *(data + i);
	}
	K& operator[](int i) {return At(i);}
	const K& operator[](int i) const {return At(i);}

	void Remove(int i) {
		ASSERT(i >= 0 && i < count);
		data[i].~K();
		int tail = count - (i + 1);
		if (tail > 0)
			MemoryMove((void*)(data + i), (void*)(data + i + 1), tail * sizeof(K));
		count--;
	}
	void Remove(int i, int count) {
		if (count <= 0) return;
		ASSERT(i >= 0 && i + count <= this->count);
		data[i].~K();
		int tail = this->count - (i + count);
		if (tail > 0)
			MemoryMove((void*)(data + i), (void*)(data + i + count), tail * sizeof(K));
		this->count -= count;
	}
	void Remove(const Iterator& it) {
		K* begin = data;
		K* cur = it.Get();
		int pos = cur - begin;
		Remove(pos);
	}
	void Remove(const Iterator& it, const Iterator& end) {
		K* begin = data;
		K* cur = it.Get();
		K* cur_end = end.Get();
		int pos0 = cur - begin;
		int pos1 = cur_end - begin;
		int len = pos1 - pos0;
		if (!len) return;
		Remove(pos0, len);
	}
	void Remove(const Vector<int>& sorted_list) {Remove(sorted_list.Begin(), sorted_list.GetCount());}
	void Remove(const int* sorted_list, int n) {
		if(!n) return;
		int pos = *sorted_list;
		int npos = pos;
		for(;;) {
			ASSERT(pos < count);
			if(pos == *sorted_list) {
				(data + pos)->~K();
				pos++;
				sorted_list++;
				if(--n == 0) break;
				ASSERT(*sorted_list >= pos);
			}
			else
				*((Data_S_<sizeof(K)>*)data + npos++)
					= *((Data_S_<sizeof(K)>*)data + pos++);
		}
		while(pos < count)
			*((Data_S_<sizeof(K)>*)data + npos++) = *((Data_S_<sizeof(K)>*)data + pos++);
		count = npos;
	}
	K& Insert(int i) {
		if (count + 1 > alloc) IncreaseReserved();
		if (count >= alloc)
			THROW(MemoryLimitExc("Vector maximum size exceeded"));
		int tail = this->count - i;
		if (tail > 0)
			MemoryMove(data + i + 1, data + i, tail * sizeof(K));
		new (&data[i]) K();
		count++;
		return data[i];
	}
	K& Insert(int i, const K& key) {
		if (count + 1 > alloc) IncreaseReserved();
		if (count >= alloc)
			THROW(MemoryLimitExc("Vector maximum size exceeded"));
		int tail = this->count - i;
		if (tail > 0)
			MemoryMove(data + i + 1, data + i, tail * sizeof(K));
		new (&data[i]) K(key);
		count++;
		return data[i];
	}
	void InsertN(int i, int n) {
		if (n < 1) return;
		ASSERT(i >= 0 && i <= count);
		if (count + n > alloc) Reserve(count + n);
		if (count >= alloc)
			THROW(MemoryLimitExc("Vector maximum size exceeded"));
		int tail = this->count - i;
		if (tail > 0)
			MemoryMove(data + i + n, data + i, tail * sizeof(K));
		for(int j = 0; j < n; j++)
			new (&data[i+j]) K();
		count+=n;
	}
	
	K&       Top()       { ASSERT(GetCount() > 0); return data[count - 1]; }
	const K& Top() const { ASSERT(GetCount() > 0); return data[count - 1]; }
	
	K Pop() {
		ASSERT(GetCount() > 0);
		int i = count - 1;
		K ret(data[i]);
		data[i].~K();
		count--;
		return ret;
	}
	
	void RemoveLast() {
		ASSERT(GetCount() > 0);
		data[--count].~K();
	}

	void Clear() {
		if (!alloc) return;
		K* it = data;
		K* end = data + count;
		while (it != end)
			it++->~K();
		count = 0;
		free(data);
		data = NULL;
		alloc = 0;
	}
	
	hash_t GetHashValue() const {
		if (!data) return 0;
		CombineHash h;
		K* it = data;
		K* end = data + count;
		while (it != end)
			h.Put(UPP::GetHashValue(*it++));
		return h;
	}
	
};

template <class K>
class Array {
	typedef Vector<K*> VectorK;
	VectorK l;

public:
	using ElPtr = K**;
	using ObjectPtr = K*;
	
	struct RefGet {
		ElPtr p = 0;
		RefGet(ElPtr p) : p(p) {}
		K& operator()() {return **p;}
	};
	
	template <class T, int I>
	struct Iterator0 {
		T kit;
		Iterator0() {}
		Iterator0(T kit) : kit(kit) {}
		Iterator0(const Iterator0& it) {*this = it;}
		void operator=(const Iterator0& it) {kit = it.kit;}
		Iterator0& operator++() {kit += I; return *this;}
		Iterator0 operator++(int i) {Iterator ret = *this; kit += I; return ret;}
		void operator--() {kit -= I;}
		void operator--(int i) {kit -= I;}
		void operator+=(int i) {kit += I * i;}
		void operator-=(int i) {kit -= I * i;}
		Iterator0 operator-(int i) const {Iterator0 o(*this); o.kit -= I * i; return o;}
		Iterator0 operator+(int i) const {Iterator0 o(*this); o.kit += I * i; return o;}
		K* operator->() const {return *kit.Get();}
		K* Get() const {if (!kit) return 0; return *kit.Get();}
		ElPtr GetElPtr() const {return kit.Get();}
		operator K*() const {return Get();}
		K& operator*() const {return *Get();}
		bool operator==(K* ptr) const {return *kit.kit == ptr;}
		bool operator!=(K* ptr) const {return *kit.kit != ptr;}
		bool operator==(const Iterator0& it) const {return it.kit == kit;}
		bool operator!=(const Iterator0& it) const {return it.kit != kit;}
		K& operator()() const {return *Get();}
	};
	typedef Iterator0<typename Vector<K*>::Iterator, +1> Iterator;
	typedef Iterator0<typename Vector<K*>::Iterator, -1> RIterator;
	typedef Iterator0<typename Vector<K*>::ConstIterator, +1> ConstIterator;
	typedef Iterator0<typename Vector<K*>::ConstIterator, -1> ConstRIterator;

	Array() {}
	Array(Array&& a) : l(std::move(a.l)) {}
	Array(std::initializer_list<K> list) {
		auto it = list.begin();
		auto end = list.end();
		while (it != end)
			Add(*it++);
	}
	~Array() { Clear(); }
	
	void Serialize(Stream& s);
	
	Iterator Begin() {return Iterator(l.Begin());}
	Iterator End() {return Iterator(l.End());}
	ConstIterator Begin() const {return ConstIterator(l.Begin());}
	ConstIterator End() const {return ConstIterator(l.End());}
	Iterator begin() {return Begin();}
	Iterator end() {return End();}
	ConstIterator begin() const {return Begin();}
	ConstIterator end() const {return End();}
	RIterator RBegin() {return RIterator(l.End() - 1);}
	RIterator REnd() {return RIterator(l.Begin() - 1);}
	ConstRIterator RBegin() const {return ConstRIterator(l.End() - 1);}
	ConstRIterator REnd() const {return ConstRIterator(l.Begin() - 1);}
	RIterator rbegin() {return RBegin();}
	RIterator rend() {return REnd();}
	ConstRIterator rbegin() const {return RBegin();}
	ConstRIterator rend() const {return REnd();}
	
	void Reserve(int i) {l.Reserve(i);}
	void SetCount(int new_count) {
		int count = l.GetCount();
		if (new_count == count) return;
		if (new_count > count) {
			l.SetCount(new_count);
			for (int i = count; i < new_count; i++)
				l[i] = new K();
		}
		else {
			for (int i = count - 1; i >= new_count; i--)
				delete l[i];
			l.SetCount(new_count);
		}
	}
	K& Add() { K* k = new K(); l.Add(k); return *k; }
	K& Add(const K& v) { K* k = new K(v); l.Add(k); return *k; }
	K& Add(K* k) { l.Add(k); return *k; }
	K& Insert(int i) {return *l.Insert(i, new K());}
	K& Insert(int i, const K& key) {return *l.Insert(i, new K(key));}
	K& Insert(int i, K* key) {return *l.Insert(i, key);}
	int GetCount() const { return l.GetCount(); }
	bool IsEmpty() const { return GetCount() == 0; }
	K* Detach(int i) {K* o = l[i]; l.Remove(i); return o;}
	K* PopDetach() {return l.Pop();}
	
	K& Get(int i) {
		ASSERT(i >= 0 && i < l.GetCount());
		return **(l.GetData() + i);
	}
	const K& Get(int i) const {
		ASSERT(i >= 0 && i < l.GetCount());
		return **(l.GetData() + i);
	}
	K& operator[](int i) {return Get(i);}
	const K& operator[](int i) const {return Get(i);}

	void Remove(int i) {
		ASSERT(i >= 0 && i < l.GetCount());
		delete *(l.GetData() + i);
		l.Remove(i);
	}
	void Remove(int i, int n) {
		if (!n) return;
		ASSERT(i >= 0 && i+n <= l.GetCount());
		for(int j = 0; j < n; j++)
			delete *(l.GetData() + i+j);
		l.Remove(i, n);
	}
	void Remove(const Vector<int>& sorted_list) {Remove(sorted_list.Begin(), sorted_list.GetCount());}
	void Remove(const int* sorted_list, int n) {
		if(!n) return;
		const int* it  = sorted_list;
		const int* end = sorted_list + n;
		K** vector = l.GetData();
		while (it != end)
			(*(vector + *it++))->~K();
		l.Remove(sorted_list, n);
	}
	void RemoveLast() {ASSERT(GetCount()); Remove(GetCount()-1);}
	void Clear() {
		K** ptr = l.GetData();
		K** end = ptr + l.GetCount();
		while (ptr != end)
			delete *(ptr++);
		l.Clear();
	}

	K&       Top()       {ASSERT(GetCount() > 0); return **(l.GetData() + l.GetCount() - 1);}
	const K& Top() const {ASSERT(GetCount() > 0); return **(l.GetData() + l.GetCount() - 1);}
	
	void operator <<=(const Array& a) {
		Clear();
		l.SetCount(a.GetCount(), 0);
		for (int i = 0; i < a.GetCount(); i++)
			l[i] = new K(*a.l[i]);
	}
	
	void Append(const Array& a) {
		int prev_count = l.GetCount();
		int new_count = prev_count + a.GetCount();
		l.SetCount(new_count, 0);
		for (int i = prev_count, j = 0; i < new_count; i++, j++)
			l[i] = new K(*a.l[j]);
	}
	
};

template <class K>
class Index : Moveable<Index<K>> {
	Vector<hash_t> hashes;
	Vector<K> values;
	
	static const bool chk_duplicates = false;
	
public:
	typedef hash_t* HashPtr;
	typedef K* ObjectPtr;
	
	template <class P, class V, int I>
	struct Iterator0 {
		typedef PtrPair<hash_t,K> ElPtr;
		P hit;
		V kit;
		Iterator0() {}
		Iterator0(P hit, V kit) : hit(hit), kit(kit) {}
		Iterator0(const Iterator0& it) {*this = it;}
		void operator=(const Iterator0& it) {hit = it.hit; kit = it.kit;}
		void operator++() {hit++; kit++;}
		void operator--() {hit--; kit--;}
		void operator++(int i) {hit++; kit++;}
		void operator--(int i) {hit--; kit--;}
		void operator+=(int i) {hit += i; kit += i;}
		const K* operator->()const  {return kit;}
		const K* Get() const {return kit.Get();}
		HashPtr GetHashPtr() const {return hit.GetElPtr();}
		ObjectPtr GetObjectPtr() const {return kit.GetElPtr();}
		ElPtr GetIter() const {return ElPtr(hit.GetElPtr(), kit.GetElPtr());}
		bool operator==(const Iterator0& it) const {return kit == it.kit;}
		bool operator!=(const Iterator0& it) const {return kit != it.kit;}
		const K& operator*() const {return *Get();}
		operator const K*() const {return Get();}
	};
	typedef typename Vector<hash_t>::Iterator HashIterator;
	typedef typename Vector<hash_t>::ConstIterator HashConstIterator;
	typedef typename Vector<K>::Iterator KeyIterator;
	typedef typename Vector<K>::ConstIterator KeyConstIterator;
	
	typedef Iterator0<HashConstIterator, KeyConstIterator, +1> ConstIterator;
	typedef Iterator0<HashConstIterator, KeyConstIterator, -1> ConstRIterator;
	typedef Iterator0<HashIterator, KeyIterator, +1> Iterator;
	typedef Iterator0<HashIterator, KeyIterator, -1> RIterator;
	
	Index() {}
	Index(std::initializer_list<K> l) {
		hashes.Reserve(l.size());
		values.Reserve(l.size());
		auto cur = l.begin();
		auto end = l.end();
		while (cur != end) {
			hash_t hash = GetHashValue(*cur);
			if (chk_duplicates && FindHash(hash) >= 0)
				THROW(Exc("Index has value already"));
			hashes.Add(hash);
			values.Add(*cur++);
		}
	}
	
	void Serialize(Stream& s) {hashes.Serialize(s); values.Serialize(s);}
	
	Iterator Begin() {return Iterator(hashes.Begin(), values.Begin());}
	Iterator begin() {return Iterator(hashes.Begin(), values.Begin());}
	Iterator End() {return Iterator(hashes.End(), values.End());}
	Iterator end() {return Iterator(hashes.End(), values.End());}
	ConstIterator Begin() const {return ConstIterator(hashes.Begin(), values.Begin());}
	ConstIterator End() const {return ConstIterator(hashes.End(), values.End());}
	ConstIterator begin() const {return ConstIterator(hashes.Begin(), values.Begin());}
	ConstIterator end() const {return ConstIterator(hashes.End(), values.End());}
	K* Get() {return values.Get();}
	
	const K& operator[](int i) const {
		ASSERT(i >= 0 && i < values.GetCount());
		return values[i];
	}

	int GetCount() const {return values.GetCount();}
	bool IsEmpty() const {return values.IsEmpty();}
	void Append(const Index& idx) {
		hashes.Append(idx.hashes);
		values.Append(idx.values);
	}
	const K& Add(const K& value) {
		hash_t hash = GetHashValue(value);
		if (chk_duplicates && FindHash(hash) >= 0)
			THROW(Exc("Index has value already"));
		hashes.Add(hash);
		return values.Add(value);
	}
	K& Insert(int i, const K& value) {
		hash_t hash = GetHashValue(value);
		if (chk_duplicates && FindHash(hash) >= 0)
			THROW(Exc("Index has value already"));
		hashes.Insert(i, hash);
		return values.Insert(i, value);
	}
	int Find(const K& key) const { return FindHash(GetHashValue(key)); }
	int FindAdd(const K& key) {int i = Find(key); if (i >= 0) return i; i = GetCount(); Add(key); return i;}

	int FindHash(hash_t hash) const {
		hash_t* begin = hashes.GetData();
		hash_t* end = hashes.GetData() + hashes.GetCount();
		hash_t* it = begin;
		while (it != end) {
			if (*it == hash)
				return (int)(it - begin);
			it++;
		}
		return -1;
	}

	void Clear() { hashes.Clear(); values.Clear(); }
	void Remove(int i) { hashes.Remove(i); values.Remove(i); }
	void RemoveLast() {ASSERT(GetCount()); if (GetCount()) Remove(GetCount()-1);}
	void RemoveKey(const K& key) {int i = Find(key); if (i >= 0) Remove(i);}
	void Remove(const Vector<int>& list) {hashes.Remove(list); values.Remove(list);}
	
	Index& operator<<(const K& k) {FindAdd(k); return *this;}
	
	void operator <<=(const Index& a) {
		hashes <<= a.hashes;
		values <<= a.values;
	}
	
	const Vector<K>& GetKeys() const {return values;}
	
};

template <class K, class V, template<typename> class Array>
class Map : Moveable<Map<K,V,Array>> {
	Index<K> keys;
	Array<V> values;

public:
	using HashPtr = typename Index<K>::HashPtr;
	using KeyPtr = typename Index<K>::ObjectPtr;
	using ObjectPtr = typename Array<V>::ElPtr;
	
	struct SortRef {
		const K* k = 0;
		const V* v = 0;
		SortRef(const K* k) : k(k) {}
		SortRef(const V* v) : v(v) {}
		SortRef(const K& k) : k(&k) {}
		SortRef(const V& v) : v(&v) {}
		operator const K&() const {return *k;}
		operator const V&() const {return *v;}
	};
	
	template <class P, class S, int I>
	struct Iterator0 {
		typedef RefPair<K, V> Ret;
		typedef Tuple<HashPtr, KeyPtr, ObjectPtr> ElPtr;
		P kit;
		S vit;
		Iterator0() {}
		Iterator0(P kit, S vit) : kit(kit), vit(vit) {}
		Iterator0(const Iterator0& it) {*this = it;}
		void operator=(const Iterator0& it) {kit = it.kit; vit = it.vit;}
		void operator++() {kit++; vit++;}
		void operator++(int i) {kit++; vit++;}
		void operator--(int i) {kit--; vit--;}
		void operator+=(int i) {kit += i; vit += i;}
		Iterator0 operator-(int i) const {Iterator0 o(*this); o.kit -= i; o.vit -= i; return o;}
		Iterator0 operator+(int i) const {Iterator0 o(*this); o.kit += i; o.vit += i; return o;}
		Ret operator->() {return Get();}
		Ret Get() const {return Ret(*kit.Get(), *vit.Get());}
		ElPtr GetIter() const {return ElPtr(kit.GetHashPtr(), kit.GetObjectPtr(), vit.GetElPtr());}
		V& GetObject() const {return Get().second;}
		bool operator==(V* ptr) const {return vit == ptr;}
		bool operator!=(V* ptr) const {return vit != ptr;}
		bool operator==(const Iterator0& it) const {return vit == it.vit;}
		bool operator!=(const Iterator0& it) const {return vit != it.vit;}
		Ret operator()() {return Ret(*kit.Get(), *vit.Get());}
		Ret operator*() const {return Ret(*kit.Get(), *vit.Get());}
	};
	
	typedef typename Index<K>::ConstIterator KeyConstIterator;
	typedef typename Array<V>::ConstIterator ValueConstIterator;
	typedef typename Index<K>::Iterator KeyIterator;
	typedef typename Array<V>::Iterator ValueIterator;
	
	typedef Iterator0<KeyConstIterator, ValueConstIterator, +1> ConstIterator;
	typedef Iterator0<KeyConstIterator, ValueConstIterator, -1> ConstRIterator;
	typedef Iterator0<KeyIterator, ValueIterator, +1> Iterator;
	typedef Iterator0<KeyIterator, ValueIterator, -1> RIterator;
	
	Map() {}
	Map(Map&& m) : keys(std::move(m.keys)), values(std::move(m.values)) {}
	Map(const Pick<Map<K, V, Array>>& p) {auto& a = p.Get(); Swap(keys, a.keys); Swap(values, a.values);}
	Map(const std::initializer_list<std::tuple<K, V>> list) {
		auto it = list.begin();
		auto end = list.end();
		while (it != end) {Add(std::get<0>(*it), std::get<1>(*it)); it++;}
	}
	~Map() { Clear(); }
	
	void Serialize(Stream& s) {keys.Serialize(s); values.Serialize(s);;}
	
	const Index<K>& GetKeys() const {return keys;}
	const Array<V>& GetValues() const {return values;}
	Array<V>& GetValues() {return values;}
	
	bool IsUnlinked(int) const {return false;}
	
	void PickValues(Array<V>& dst_values) {
		dst_values.Clear();
		Swap(dst_values, values);
		keys.Clear();
	}
	V& Add(const K& key) {
		keys.Add(key);
		return values.Add();
	}

	V& Add(const K& key, const V& value) {
		keys.Add(key);
		return values.Add(value);
	}
	
	V& Add(const K& key, V* value) {
		keys.Add(key);
		return values.Add(value);
	}
	
	V& GetAdd(const K& key) {
		int i = keys.Find(key);
		if (i >= 0) return values[i];
		keys.Add(key);
		return values.Add();
	}
	V& GetAdd(const K& key, const V& value) {
		int i = keys.Find(key);
		if (i >= 0) return values[i];
		keys.Add(key);
		return values.Add(value);
	}
	
	V* Detach(int i) {
		V* v = values.Detach(i);
		keys.Remove(i);
		return v;
	}

	Iterator InsertIterator(const Iterator& it, const K& key, const V& value) {int pos = GetPos(it); Insert(pos, key, value); Iterator cur = Begin(); cur += pos; return cur;}
	Iterator InsertIterator(const Iterator& it, const K& key, V* value) {int pos = GetPos(it); Insert(pos, key, value); Iterator cur = Begin(); cur += pos; return cur;}
	Iterator InsertIterator(const Iterator& it, const K& key) {int pos = GetPos(it); Insert(pos, key); Iterator cur = Begin(); cur += pos; return cur;}
	
	V& Insert(int i, const K& key) {keys.Insert(i, key); return values.Insert(i);}
	V& Insert(int i, const K& key, const V& value) {keys.Insert(i, key); return values.Insert(i, value);}
	
	const K& GetKey(int i) const { return keys[i]; }

	const V& GetPos(int i) const {
		ASSERT(i >= 0 && i < values.GetCount());
		return values[i];
	}

	V& GetPos(int i) {
		ASSERT(i >= 0 && i < values.GetCount());
		return values[i];
	}
	
	const V& operator[](int i) const {return GetPos(i);}
	V& operator[](int i) {return GetPos(i);}
	
	V& Top() { ASSERT(GetCount() > 0); return values.Top(); }
	V Pop() {V v(std::move(values.Top())); Remove(values.GetCount()-1); return v;}

	int Find(const K& key) const { return keys.Find(key); }
	Iterator FindIterator(const K& key) const { Iterator it = Begin(); int pos = Find(key); it += pos == -1 ? GetCount() : pos; return it;}
	V* FindPtr(const K& key) {int pos = Find(key); if (pos < 0) return 0; return &values.Get(pos);}
	const V* FindPtr(const K& key) const {int pos = Find(key); if (pos < 0) return 0; return &values.Get(pos);}
	V& Get(const K& key) { return values[Find(key)]; }
	const V& Get(const K& key) const { return values[Find(key)]; }
	const V& Get(const K& key, const V& value) const {int i = Find(key); if (i < 0) return value; return values[i]; }
	int GetCount() const { return keys.GetCount(); }
	bool IsEmpty() const { return GetCount() == 0; }

	int GetIterPos(const Iterator& it) {
		K* begin = keys.Get();
		K* cur = &it.Get().first;
		int pos = cur - begin;
		ASSERT(pos >= 0 && pos <= GetCount());
		return pos;
	}
	void RemoveKey(const K& key) {int i = Find(key); if (i >= 0) Remove(i);}
	void Remove(int i) { ASSERT(i >= 0 && i < keys.GetCount()); keys.Remove(i); values.Remove(i); }
	void Remove(const Iterator& it) {Remove(GetIterPos(it));}
	void Clear() {
		keys.Clear();
		values.Clear();
	}
	
	Iterator Begin() {return Iterator(keys.Begin(), values.Begin());}
	Iterator End() {return Iterator(keys.End(), values.End());}
	ConstIterator Begin() const {return Iterator(keys.Begin(), values.Begin());}
	ConstIterator End() const {return Iterator(keys.End(), values.End());}
	Iterator begin() {return Begin();}
	Iterator end() {return End();}
	ConstIterator begin() const {return Begin();}
	ConstIterator end() const {return End();}
	
	KeyIterator KeyBegin() {return keys.Begin();}
	KeyIterator KeyEnd() {return keys.End();}
	KeyConstIterator KeyBegin() const {return keys.Begin();}
	KeyConstIterator KeyEnd() const {return keys.End();}
	
	void operator <<=(const Map& a) {
		keys <<= a.keys;
		values <<= a.values;
	}
	void operator =(Map&& a) {Clear(); Swap(a.keys, keys); Swap(a.values, values);}
	
};

template <class K, class V> using VectorMap			= Map<K, V, Vector>;
template <class K, class V> using ArrayMap			= Map<K, V, Array>;
template <class K, class V> using ArrayMapOrdered	= ArrayMap<K, V>;

Vector<String> Split(String to_split, String split_str, bool ignore_empty=true);
Vector<WString> Split(WString to_split, WString split_str, bool ignore_empty=true);
String Join(const Vector<String>& v, String join_str, bool ignore_empty=true);


template<class InputIterator, class UnaryPredicate>
InputIterator FindIf(InputIterator first, InputIterator last, UnaryPredicate pred) {
	while (first != last) {
		if (pred(*first))
			return first;
			
		++first;
	}
	
	return last;
}


template <class T, class UnaryPredicate>
T RemoveIf(T first, T last, UnaryPredicate p) {
	first = FindIf(first, last, p);
    if (first != last)
        for(T i = first; ++i != last; )
            if (!p(*i))
                *first++ = Pick<T>(*i);
    return first;
}







// Never moveable
template <class T>
class Slot {
	T* ptr = NULL;
	
public:
	
	
	virtual ~Slot() {Clear();}
	
	bool IsEmpty() const {return ptr == NULL;}
	void Set(T* ptr) {
		ASSERT(ptr && ptr->IsAttached(this));
		Clear();
		this->ptr = ptr;
	}
	void Clear() {
		if (ptr) {
			T* p = ptr;
			ptr = NULL;
			p->Detach(this);
		}
	}
	void __ZeroPtr() {ptr = NULL;}
	
	T* operator->() const {return ptr;}
	operator bool() const {return ptr != NULL;}
	T& Get() const {return *ptr;}
	T* GetPtr() const {return ptr;}
	
	T& operator*() const {return *ptr;}
	
};

// Never moveable
template <class T>
class Attachable {
	typedef Slot<T> SlotT;
	
	Vector<SlotT*> slots;
	
	
public:
	
	virtual ~Attachable() {DetachAll();}
	
	void Attach(SlotT& s) {
		ASSERT(s.IsEmpty());
		ASSERT(!IsAttached(&s));
		static_assert(std::is_base_of<Attachable<T>, T>(), "The class T must inherit Attachable<T>");
		T* o = CastPtr<T>(this);
		ASSERT(o);
		slots.Add(&s);
		s.Set(o);
	}
	void DetachAll() {
		for (SlotT* s : slots)
			s->__ZeroPtr();
		slots.Clear();
	}
	bool IsAttached(SlotT* ptr) {
		for(SlotT* p : slots)
			if (p == ptr)
				return true;
		return false;
	}
	void Detach(SlotT* ptr) {
		int rem_count = 0;
		for(int i = 0; i < slots.GetCount(); i++) {
			SlotT* s = slots[i];
			if (s == ptr) {
				slots.Remove(i--);
				rem_count++;
			}
		}
		ASSERT(rem_count == 1);
	}
	int GetCount() const {return slots.GetCount();}
	SlotT& GetSlot(int i) const {return *slots[i];}
	
	
	
};













class Huge {
public:
	enum { CHUNK = 1024 * 1024 };

private:
	struct Block {
		byte data[CHUNK];
	};
	
	Array<Block>  data;
	size_t        size;

public:
	byte  *AddChunk();
	void   Finish(int last_chunk_size);
	
	size_t GetSize() const                              { return size; }
	void   Get(void *t, size_t pos, size_t sz) const;
	void   Get(void *t)                                 { Get(t, 0, GetSize()); }
	String Get() const;
	
	Huge();
};








template <class T>
class Buffer : Moveable< Buffer<T> > {
	T *ptr;
	
	void Malloc(size_t size) {
		if(std::is_trivially_destructible<T>::value)
			ptr = (T *)MemoryAlloc(size * sizeof(T));
		else {
			void *p = MemoryAlloc(size * sizeof(T) + 16);
			*(size_t *)p = size;
			ptr = (T *)((byte *)p + 16);
		}
	}
	void New(size_t size) {
		Malloc(size);
		Construct(ptr, ptr + size);
	}
	void New(size_t size, const T& in) {
		Malloc(size);
		DeepCopyConstructFill(ptr, ptr + size, in);
	}
	void Free() {
		if(ptr) {
			if(std::is_trivially_destructible<T>::value)
				MemoryFree(ptr);
			else {
				void *p = (byte *)ptr - 16;
				size_t size = *(size_t *)p;
				Destroy(ptr, ptr + size);
				MemoryFree(p);
			}
		}
	}

public:
	operator T*()                        { return ptr; }
	operator const T*() const            { return ptr; }
	T *operator~()                       { return ptr; }
	const T *operator~() const           { return ptr; }
	T          *Get()                    { return ptr; }
	const T    *Get() const              { return ptr; }
	T          *begin()                  { return ptr; }
	const T    *begin() const            { return ptr; }

	void Alloc(size_t size)              { Clear(); New(size); }
	void Alloc(size_t size, const T& in) { Clear(); New(size, in); }

	void Clear()                         { Free(); ptr = NULL; }
	bool IsEmpty() const                 { return ptr == NULL; }

	Buffer()                             { ptr = NULL; }
	Buffer(size_t size)                  { New(size); }
	Buffer(size_t size, const T& init)   { New(size, init); }
	~Buffer()                            { Free(); }

	void operator=(Buffer&& v)           { if(&v != this) { Clear(); ptr = v.ptr; v.ptr = NULL; } }
	Buffer(Buffer&& v)                   { ptr = v.ptr; v.ptr = NULL; }

	Buffer(size_t size, std::initializer_list<T> init) {
		Malloc(size); T *t = ptr; for(const auto& i : init) new (t++) T(i);
	}
	Buffer(std::initializer_list<T> init) : Buffer(init.size(), init) {}
};





NAMESPACE_UPP_END

#endif
