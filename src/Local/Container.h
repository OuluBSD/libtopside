#ifndef _Local_Container_h_
#define _Local_Container_h_

NAMESPACE_TOPSIDE_BEGIN






template <class T>
T Slice(const T& vec, int begin, int end) {
	T ret;
	int c = end - begin;
	if (c > 0)
		ret.Append(vec, begin, c);
	return ret;
}









template <class T, int I>
struct SimpleFixedArray {
	
	static const int size = I;
	
	struct Iterator {
		T* ptr = 0;
		
		Iterator() {}
		Iterator(T* p) : ptr(p) {}
		T* operator->() const {return ptr;}
		T& operator*() const {return *ptr;}
		bool operator!=(const Iterator& i) const {return ptr != i.ptr;}
		bool operator==(const Iterator& i) const {return ptr == i.ptr;}
		void operator++() {++ptr;}
		void operator--() {--ptr;}
	};
	
	
	T vector[I];
	
	
	int GetCount() const {return size;}
	T&       operator[](int i)       {ASSERT(i >= 0 && i < size); return vector[i];}
	const T& operator[](int i) const {ASSERT(i >= 0 && i < size); return vector[i];}
	void operator=(const T& value) {for(int i = 0; i < I; i++) this->vector[i] = value;}
	T& Top() {return vector[I-1];}
	
	Iterator begin() {return Iterator(&vector[0]);}
	Iterator end() {return Iterator(&vector[0] + I);}
	
	bool IsEmpty() const {return false;}
	void SetAll(const T& o) {for(int i = 0; i < I; i++) vector[i] = o;}
	hash_t GetHashValue() const {CombineHash c; for(int i = 0; i < I; i++) c.Put(UPP::GetHashValue<T>(vector[i])); return c;}
	T* Get() {return vector;}
	
};

template <class T, int I>
struct FixedArray : RTTIBase {
	RTTI_DECL0(FixedArray)
	
	static const int size = I;
	
	struct Iterator {
		T* ptr = 0;
		
		Iterator() {}
		Iterator(T* p) : ptr(p) {}
		T* operator->() const {return ptr;}
		T& operator*() const {return *ptr;}
		bool operator!=(const Iterator& i) const {return ptr != i.ptr;}
		bool operator==(const Iterator& i) const {return ptr == i.ptr;}
		void operator++() {++ptr;}
		void operator--() {--ptr;}
	};
	
	T vector[I];
	
	int GetCount() const {return size;}
	T&       operator[](int i)       {ASSERT(i >= 0 && i < size); return vector[i];}
	const T& operator[](int i) const {ASSERT(i >= 0 && i < size); return vector[i];}
	void operator=(const T& value) {for(int i = 0; i < I; i++) this->vector[i] = value;}
	T& Top() {return vector[I-1];}
	
	Iterator begin() {return Iterator(&vector[0]);}
	Iterator end() {return Iterator(&vector[0] + I);}
	
	bool IsEmpty() const {return false;}
	void SetAll(const T& o) {for(int i = 0; i < I; i++) vector[i] = o;}
	String ToString() const {return "FixedArray";}
	int ToInt() const {return I;}
	double ToDouble() const {return I;}
	operator double() const {return I;}
	
	hash_t GetHashValue() const {CombineHash c; for(int i = 0; i < I; i++) c.Put(UPP::GetHashValue<T>(vector[i])); return c;}
	T* Get() {return vector;}
	
};

template <class T, int I>
struct ReservedArray {
	static const int size = I;
	typedef T value_type;
	
	T vector[I];
	byte dyn_size = 0;
	
	
	void SetCount(int i) {ASSERT(i >= 0 && i <= size); dyn_size = i;}
	int GetCount() const {return dyn_size;}
	T& Add(const T& value) {ASSERT(dyn_size < size); T& o = vector[dyn_size++]; o = value; return o;}
	T&       operator[](int i)       {ASSERT(i >= 0 && i < size && i < dyn_size); return vector[i];}
	const T& operator[](int i) const {ASSERT(i >= 0 && i < size && i < dyn_size); return vector[i];}
	void operator=(const T& value) {for(int i = 0; i < dyn_size; i++) this->vector[i] = value;}
	
	T& push_back(const T& value) {return Add(value);}
};


template <class T>
class ParentArray {
	
public:
	typedef ParentArray<T> PA;
	
private:
	PA* parent = NULL;
	Array<T> sub;
	
protected:
	
	T& Add() {T& t = sub.Add(); t.parent = this; return t;}
	T& Insert(int i) {T& t = sub.Insert(i); t.parent = this; return t;}
	
	void Copy(const PA& src) {sub <<= src.sub; for(int i = 0; i < sub.GetCount(); i++) sub[i].parent = this;}
	
public:
	
	T* GetParent() const {return parent;}
	T& Add(T* n) {ASSERT(n->parent == NULL); T& t = sub.Add(n); t.parent = this; return t;}
	T& Insert(int i, T* n) {ASSERT(n->parent == NULL); T& t = sub.Insert(i, n); t.parent = this; return t;}
	
	void Clear() {sub.Clear();}
	void Remove(int i) {sub.Remove(i);}
	void Remove(int i, int count) {sub.Remove(i, count);}
	void RemoveLast() {sub.Remove(sub.GetCount()-1);}
	T* Detach(int i) {T* t = sub.Detach(i); t->parent = NULL; return t;}
	
	T& At(int i) {return sub[i];}
	T& AtTop(int i) {if (i < sub.GetCount()) return sub[i]; return sub.Top();}
	T& At(int i, T& n) {if (i < sub.GetCount()) return sub[i]; return n;}
	const T& At(int i) const {return sub[i];}
	T& operator[](int i) {return sub[i];}
	const T& operator[](int i) const {return sub[i];}
	T& Top() {return sub.Top();}
	
	Array<T>& Sub() {return sub;}
	const Array<T>& Sub() const {return sub;}
	
	int GetCount() const {return sub.GetCount();}
	bool IsEmpty() const {return sub.IsEmpty();}
	
	void SortByInt() {
		struct Sorter {
			bool operator() (const T& a, const T& b) const {return a.GetInt() < b.GetInt();}
		};
		Sort(sub, Sorter());
	}
	
	void Serialize(Stream& s) {
		s % sub;
		if (s.IsLoading())
			for(int i = 0; i < sub.GetCount(); i++)
				sub[i].parent = this;
	}
	
};







template <class T>
class TreeArray {
	
public:
	typedef TreeArray<T> PA;
	
private:
	PA* down = NULL;
	Array<T> branch;
	
protected:
	
	T& Add() {T& t = branch.Add(); t.down = this; return t;}
	T& Insert(int i) {T& t = branch.Insert(i); t.down = this; return t;}
	
	void Copy(const PA& src) {branch <<= src.branch; for(int i = 0; i < branch.GetCount(); i++) branch[i].down = this;}
	
public:
	
	T* GetParent() const {return down;}
	T& Add(T* n) {ASSERT(n->down == NULL); T& t = branch.Add(n); t.down = this; return t;}
	T& Insert(int i, T* n) {ASSERT(n->down == NULL); T& t = branch.Insert(i, n); t.down = this; return t;}
	
	void Clear() {branch.Clear();}
	void Remove(int i) {branch.Remove(i);}
	void Remove(int i, int count) {branch.Remove(i, count);}
	void RemoveLast() {branch.Remove(branch.GetCount()-1);}
	T* Detach(int i) {T* t = branch.Detach(i); t->down = NULL; return t;}
	
	T& At(int i) {return branch[i];}
	T& AtTop(int i) {if (i < branch.GetCount()) return branch[i]; return branch.Top();}
	T& At(int i, T& n) {if (i < branch.GetCount()) return branch[i]; return n;}
	const T& At(int i) const {return branch[i];}
	T& Top() {return branch.Top();}
	
	int GetCount() const {return branch.GetCount();}
	bool IsEmpty() const {return branch.IsEmpty();}
	
	void SortByInt() {
		struct Sorter {
			bool operator() (const T& a, const T& b) const {return a.GetInt() < b.GetInt();}
		};
		Sort(branch, Sorter());
	}
	
	void Serialize(Stream& s) {
		s % branch;
		if (s.IsLoading())
			for(int i = 0; i < branch.GetCount(); i++)
				branch[i].down = this;
	}
};





// Destroying objects is costly and pointless during iterating
template <class T>
struct CachingVector : Moveable<CachingVector<T>> {
	typedef Vector<T> Vec;
	Vector<T> data;
	int count = 0;


	const T& operator[](int i) const {return data[i];}
	T& operator[](int i) {return data[i];}
	int GetCount() const {return count;}
	void SetCount(int i) {if (data.GetCount() < i) data.SetCount(i); count = i;}
	typename Vec::iterator begin() {return data.begin();}
	typename Vec::iterator end() {return data.begin() + count;}
};








template <class K=int, class V=double, class Sorter=StdGreater<V> >
struct TopValueSorterLinkedList {
	struct Item : Moveable<Item> {
		K key;
		V value;
		Item *prev, *next;
		void Set(const K& k, const V& v, Item* p, Item* n) {key = k; value = v; prev = p; next = n;}
	};
	RecyclerPool<Item> pool;
	Item *first = 0, *last = 0;
	int size = 0;
	int max_count = -1;
	Sorter sorter;
	
	TopValueSorterLinkedList() {}
	~TopValueSorterLinkedList() {Clear();}
	
	void Clear() {
		Item* iter = first;
		while (iter) {
			Item* it = iter;
			iter = iter->next;
			pool.Return(it);
		}
		first = 0;
		last = 0;
		size = 0;
	}
	void Reserve(int i) {pool.Reserve(i);}
	void SetMaxCount(int i) {max_count = i;}
	void RemoveItem(Item* iter) {
		if (iter->prev && iter->next) {
			iter->prev->next = iter->next;
			iter->next->prev = iter->prev;
		}
		else if (iter->prev) {
			ASSERT(last == iter);
			iter->prev->next = 0;
			last = iter->prev;
		}
		else if (iter->next) {
			ASSERT(first == iter);
			iter->next->prev = 0;
			first = iter->next;
		}
		else {
			ASSERT(size == 1);
			first = 0;
			last = 0;
		}
		size--;
		pool.Return(iter);
	}
	void RemoveKey(const K& key) {
		Item* iter = first;
		while (iter) {
			if (iter->key == &key) {
				RemoveItem(iter);
				break;
			}
			iter = iter->next;
		}
	}
	Item* Find(const K& key) {
		for(Item* iter = first; iter; iter = iter->next)
			if (iter->key == key)
				return iter;
		return 0;
	}
	bool UpdateValue(Item* iter, const V& value) {
		bool fail = false;
		if (iter->prev && !sorter(iter->prev->value, value))
			fail = true;
		if (iter->next && !sorter(value, iter->next->value))
			fail = true;
		if (!fail) {
			iter->value = value; // just update value
			return true;
		}
		return false;
	}
	void SetAdd(const K& key, const V& value) {
		Item* iter = first;
		while (iter) {
			if (iter->key == key) {
				if (UpdateValue(iter, value))
					return;
				RemoveItem(iter);
				break;
			}
			iter = iter->next;
		}
		Add(key, value);
	}
	void Add(const K& key, const V& value) {
		if (!first) {
			ASSERT(!size);
			size++;
			first = pool.New();
			ASSERT(first);
			first->Set(key, value, 0, 0);
			last = first;
		}
		// default: value <= last->value
		else if (sorter(last->value, value) || !sorter(value, last->value)) {
			if (max_count < 0 || (max_count >= 0 && size < max_count)) {
				size++;
				Item* it = pool.New();
				ASSERT(it);
				it->Set(key, value, last, 0);
				last->next = it;
				last = it;
			}
		}
		else {
			int i = 0;
			Item* iter = first;
			while (iter) {
				// default value > iter->value
				if (sorter(value, iter->value)) {
					Item* new_link = pool.New();
					ASSERT(new_link);
					if (iter->prev) {
						new_link->Set(key, value, iter->prev, iter);
						new_link->prev->next = new_link;
						iter->prev = new_link;
					}
					else {
						ASSERT(iter == first);
						new_link->Set(key, value, 0, iter);
						iter->prev = new_link;
						first = new_link;
					}
					size++;
					if (size > max_count) {
						int rem_count = size - max_count;
						Item* rev_iter = last;
						for(int i = 0; i < rem_count; i++) {
							Item* it = rev_iter;
							rev_iter = it->prev;
							pool.Return(it);
						}
						last = rev_iter;
						size = max_count;
					}
					break;
				}
				iter = iter->next;
			}
		}
	}
	int GetCount() const {return size;}
	bool IsEmpty() const {return size == 0;}
	Item PickFirst() {
		ASSERT(first);
		Item i;
		if (!first) {
			i.prev = 0;
			i.next = 0;
		}
		else {
			i = *first;
			if (size == 1) {
				pool.Return(first);
				first = 0;
				last = 0;
				size = 0;
			}
			else {
				Item* it = first;
				first = first->next;
				first->prev = 0;
				ASSERT(first);
				pool.Return(it);
				size--;
			}
		}
		return i;
	}
};


struct HugePersistent {
	
	// Persistent
	String filename;
	int64 data_size = 0;
	int64 persistent_size = 0;
	
	
	// Persistent in own file
	void* data = NULL;
	
	
	
	~HugePersistent() {Free();}
	void Alloc() {Free(); ASSERT(data_size > 0); data = MemoryAlloc(data_size);}
	void Free() {if (data) {MemoryFree(data); data = NULL;}}
	void StoreData();
	void LoadData();
	
	
	void Serialize(Stream& s) {
		s	% filename
			% data_size
			% persistent_size
			;
	}
};



template <class T> int VectorFind(const Vector<T>& v, const T& o) {
	for(int i = 0; i < v.GetCount(); i++) {
		auto& local = v[i];
		if (local == o)
			return i;
	}
	return -1;
}

template <class T> T& VectorFindAdd(Vector<T>& v, const T& o, int* found=0) {
	if (found) {
		for(int i = 0; i < v.GetCount(); i++) {
			auto& local = v[i];
			if (local == o) {
				*found = i;
				return local;
			}
		}
		*found = -1;
	}
	else {
		for(auto& i : v)
			if (i == o)
				return i;
	}
	return v.Add(o);
}

template <class T> int VectorRemoveKey(Vector<T>& v, const T& o) {
	int rem_count = 0;
	for(int i = 0; i < v.GetCount(); i++) {
		if (v[i] == o) {
			v.Remove(i--);
			rem_count++;
		}
	}
	return rem_count;
}



template <class T> int ArrayFind(const Array<T>& v, const T& o) {
	for(int i = 0; i < v.GetCount(); i++) {
		auto& local = v[i];
		if (local == o)
			return i;
	}
	return -1;
}

template <class T> T& ArrayFindAdd(Array<T>& v, const T& o, int* found=0) {
	if (found) {
		for(int i = 0; i < v.GetCount(); i++) {
			auto& local = v[i];
			if (local == o) {
				*found = i;
				return local;
			}
		}
		*found = -1;
	}
	else {
		for(auto& i : v)
			if (i == o)
				return i;
	}
	return v.Add(o);
}

template <class T> int ArrayRemoveKey(Array<T>& v, const T& o) {
	int rem_count = 0;
	for(int i = 0; i < v.GetCount(); i++) {
		if (v[i] == o) {
			v.Remove(i--);
			rem_count++;
		}
	}
	return rem_count;
}









template <class T>
class BitField {
	T bits = 0;
	
public:
	
	BitField() {}
	BitField(const BitField& f) : bits(f.bits) {}
	
	void operator=(const BitField& f) {bits = f.bits;}
	
	void Check(int bit) const {ASSERT(bit >= 0 && bit < sizeof(bits) * 8);}
	void Set(int bit, bool b) {if (b) SetTrue(bit); else SetFalse(bit);}
	void SetTrue(int bit) {Check(bit); bits |= ((T)1 << (T)bit);}
	void SetFalse(int bit) {Check(bit); bits &= ~((T)1 << (T)bit);}
	bool Is(int bit) const {Check(bit); return bits & ((T)1 << (T)bit);}
	
	
};









class EnvState :
	public RefScopeEnabler<EnvState, MetaSpaceBase>
{
	VectorMap<dword, Object> data;
	String name;
	
public:
	RTTI_DECL0(EnvState)
	
	void Visit(RuntimeVisitor& vis) {}
	void SetName(String s) {name = s;}
	const String& GetName() const {return name;}
	
	
	bool&	SetBool(dword key, bool b);
	int&	SetInt(dword key, int i);
	
	bool&	GetBool(dword key);
	int&	GetInt(dword key);
	
	template <class T>
	T& Set(dword key) {
		Object& o = data.GetAdd(key);
		if (o.Is<T>())
			return o.Get<T>();
		else
			return o.Create<T>();
	}
	
	template <class T>
	T* Get(dword key) {
		int i = data.Find(key);
		if (i < 0)
			return 0;
		Object& o = data[i];
		if (o.Is<T>())
			return &o.Get<T>();
		return 0;
	}
};

using ExchangeBaseParent	= RefParent1<MetaSpaceBase>;
using EnvStateParent		= ExchangeBaseParent;
using EnvStateRef			= Ref<EnvState,				EnvStateParent>;




template <typename T>
class TrackChanges {
public:
	TrackChanges() {
		change_count = 0;
	}
	TrackChanges(TrackChanges<T> && o) : value(std::move(o.value)) {
		change_count = 0;
	}
	TrackChanges(const TrackChanges<T>& o) : value(o.Get()) {
		change_count = 0;
	}
	
	TrackChanges<T>& operator=(TrackChanges<T> && o) {
		++change_count;
		value = std::move(o.value);
		return *this;
	}
	
	TrackChanges<T>& operator=(const TrackChanges<T>& o) {
		++change_count;
		value = o.value;
		return *this;
	}
	
	template <typename Func>
	void Set(Func func) {
		++change_count;
		func(value);
	}
	
	bool UpdateChangeCountBookmark(uint32* change_count_bookmark) const {
		uint32 new_value = *change_count_bookmark;
		uint32 prev = change_count.exchange(new_value);
		return prev != new_value;
	}
	
	const T& Get() const {
		return value;
	}
	
	T* operator->() {return &value;}
	const T* operator->() const {return &value;}
	
private:
	T value;
	mutable Atomic change_count;
};




NAMESPACE_TOPSIDE_END


#endif
