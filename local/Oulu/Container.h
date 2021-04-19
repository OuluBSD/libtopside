#ifndef _Oulu_Container_h_
#define _Oulu_Container_h_

NAMESPACE_OULU_BEGIN






template <class T>
T Slice(const T& vec, int begin, int end) {
	T ret;
	int c = end - begin;
	if (c > 0)
		ret.Append(vec, begin, c);
	return ret;
}









template <class T, int I>
struct FixedArray {
	static const int size = I;
	
	T vector[I];
	
	int GetCount() const {return size;}
	T&       operator[](int i)       {ASSERT(i >= 0 && i < size); return vector[i];}
	const T& operator[](int i) const {ASSERT(i >= 0 && i < size); return vector[i];}
	void operator=(const T& value) {for(int i = 0; i < I; i++) this->vector[i] = value;}
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
	/*void Jsonize(JsonIO& json) {
		json ("sub", sub);
		if (json.IsLoading())
			for(int i = 0; i < sub.GetCount(); i++)
				sub[i].parent = this;
	}*/
	//for(int i = 0; i < sub.GetCount(); i++) sub[i].parent = NULL;
};






/*
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
};*/





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







template <class T>
class RecyclerPool {
	Array<T> pool;
	
public:
	RecyclerPool() {
		
	}
	
	T* New() {
		if (pool.IsEmpty())
			return new T();
		else
			return pool.PopDetach();
	}
	
	void Return(T* o) {
		pool.Add(o);
	}

};


template <class T>
class Recycler {
	typedef RecyclerPool<T> Pool;
	
	Pool& pool;
	One<T> o;
	
public:
	Recycler(Pool& pool) : pool(pool), o(pool.New()) {o->SetCount(0);}
	~Recycler() {if (!o.IsEmpty()) pool.Return(o.Detach());}
	
	
	T& Get() {ASSERT(!o.IsEmpty()); return *o;}
	
	T& operator*() {return Get();}
	T& operator->() {return Get();}
	
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

NAMESPACE_OULU_END


#endif
