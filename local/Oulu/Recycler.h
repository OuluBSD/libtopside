#ifndef _Oulu_Recycler_h_
#define _Oulu_Recycler_h_


NAMESPACE_OULU_BEGIN




template <class T, bool keep_as_constructed=false>
class RecyclerPool {
	Vector<T*> pool;
	Mutex lock;
	
public:
	RecyclerPool() {}
	~RecyclerPool() {Clear();}
	
	void Clear() {
		lock.Enter();
		auto t = pool.Begin();
		auto end = pool.End();
		while(t != end) {
			T* o = *t;
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
	
	T* New() {
		T* o;
		if (pool.IsEmpty()) {
			o = (T*)MemoryAlloc(sizeof(T));
			new (o) T();
		}
		else {
			lock.Enter();
			o = pool.Pop();
			lock.Leave();
			if (!keep_as_constructed)
				new (o) T();
		}
		return o;
	}
	
	void Return(T* o) {
		if (!keep_as_constructed)
			o->~T();
		lock.Enter();
		pool.Add(o);
		lock.Leave();
	}
	
};


template <class T, bool keep_as_constructed>
class Recycler {
	typedef RecyclerPool<T, keep_as_constructed> Pool;
	
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







NAMESPACE_OULU_END


#endif
