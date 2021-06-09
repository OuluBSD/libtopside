#ifndef _Local_Recycler_h_
#define _Local_Recycler_h_


NAMESPACE_TOPSIDE_BEGIN


void CallInExitBlock(Callback cb);

template <class T, bool keep_as_constructed=false>
class RecyclerPool {
	Vector<T*> pool;
	Mutex lock;
	bool destructed = false;
	
public:
	typedef RecyclerPool CLASSNAME;
	RecyclerPool() {}
	RecyclerPool(bool exit_block_clear) {if (exit_block_clear) CallInExitBlock(THISBACK(Destruct));}
	~RecyclerPool() {Destruct();}
	
	void Destruct() {if (!destructed) {Clear(); destructed = true;}}
	
	void Clear() {
		lock.Enter();
		auto t = pool.Begin();
		auto end = pool.End();
		while(t != end) {
			T* o = *t;
			if (keep_as_constructed)
				o->~T();
			MemoryFree(o);
			t++;
		}
		pool.Clear();
		lock.Leave();
	}
	void Reserve(int i) {
		lock.Enter();
		pool.Reserve(i);
		lock.Leave();
	}
	
	template <typename... Args>
	T* New(const Args&... args) {
		T* o;
		if (pool.IsEmpty()) {
			o = (T*)MemoryAlloc(sizeof(T));
			new (o) T(args...);
		}
		else {
			lock.Enter();
			o = pool.Pop();
			lock.Leave();
			if (!keep_as_constructed)
				new (o) T(args...);
		}
		return o;
	}
	
	void Return(T* o) {
		if (destructed)
			return;
		if (!keep_as_constructed)
			o->~T();
		lock.Enter();
		pool.Add(o);
		lock.Leave();
	}
	
	static RecyclerPool& StaticPool() {static RecyclerPool pool(1); return pool;}
	
};


template <class T, bool keep_as_constructed>
class Recycler {
	
public:
	using Pool = RecyclerPool<T, keep_as_constructed> ;
	
private:
	Pool* pool = 0;
	One<T> o;
	
public:
	Recycler() {}
	Recycler(Pool& pool) : pool(&pool), o(pool.New()) {o->SetCount(0);}
	~Recycler() {Clear();}
	
	void Clear() {if (o && pool) pool->Return(o.Detach());}
	void Create(Pool& pool) {Clear(); this->pool = &pool; o = pool.New();}
	T& Get() {ASSERT(!o.IsEmpty()); return *o;}
	
	T& operator*() {return Get();}
	T* operator->() {return &Get();}
	
};


template <class T>
class RecyclerRefBase {
	T* obj = NULL;
	Vector<WeakBase*> weaks;
	Atomic refs;
	
public:
	using Pool = RecyclerPool<RecyclerRefBase<T>>;
	
	RecyclerRefBase() {refs = 1;}
	virtual ~RecyclerRefBase() {ASSERT(!obj);}
	void SetObj(T* o) {obj = o;}
	void Clear() {T::Pool::StaticPool().Return(obj); obj = 0;}
	void Inc() {refs++;}
	void Dec() {
		refs--;
		if (refs <= 0) {
			for(int i = 0; i < weaks.GetCount(); i++) weaks[i]->SetDeleted();
			Clear();
			Pool::StaticPool().Return(this);
		}
	}
	void IncWeak(WeakBase* w) {weaks.Add(w);}
	void DecWeak(WeakBase* w) {for(int i = 0; i < weaks.GetCount(); i++) if (weaks[i] == w) {weaks.Remove(i--);}}
};


template <class T> using SharedRecycler = Shared<T, RecyclerRefBase<T>>;




NAMESPACE_TOPSIDE_END


#endif
