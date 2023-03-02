#ifndef _CoreAlt_Mt_h_
#define _CoreAlt_Mt_h_

NAMESPACE_UPP_BEGIN


template<typename Res, typename... ArgTypes>
class Function<Res(ArgTypes...)>;


inline int CPU_Cores() {return std_thread_hardware_concurrency();}

#define MAIN_THREAD_ID -1
void __ForceSetThreadId(int i);
void RunThreadExitCallbacks();

class Thread {
	One<std_thread> t;
	Callback cb;
	int id;
	
	static bool shutdown;
	static AtomicInt thrd_count;
	
	
	
	static void SetThreadId(int i);
	static int GetThreadId();
	
public:
	Thread() {id = thrd_count++;}
	~Thread() {thrd_count--;}


	static void Start(Callback cb) {
		Thread* t = new Thread();
		t->cb = cb;
		t->t = new std_thread([t, cb]() {
			cb.Execute();
			RunThreadExitBlocks();
			t->t->detach();
			delete t;
		});
	}
	
	template <class T> static void Start(T& fn) {
		Thread* t = new Thread();
		t->cb.Clear();
		int id = t->GetId();
		t->t = new std_thread([id, t, fn]() {
			SetThreadId(id);
			fn();
			RunThreadExitBlocks();
			t->t->detach();
			delete t;
		});
	}
	
	void Run(Callback cb);
	
	void Wait() {t->join();}
	void Detach() {t->detach();}
	
	int GetId() const {return id;}
	
	static bool IsShutdownThreads() {return shutdown;}
	static void ShutdownThreads();
	
	static bool IsMain();
	
};

inline bool IsMainThread() { return Thread::IsMain(); }

class Mutex {
	std_mutex m;
public:
	Mutex() {}
	
	void Enter() {m.lock();}
	void Leave() {m.unlock();}
	bool TryEnter() {return m.try_lock();}
	
	class Lock;
};

class Mutex::Lock {
	Mutex& m;
public:
	Lock(Mutex& m) : m(m) {m.Enter();}
	~Lock() {m.Leave();}
};

class shared_mutex {
    std::atomic<int> refcount{0};
public:
    void lock() {
        int val;
        do {
            val = 0; // Can only take a write lock when refcount == 0
        } while (!refcount.compare_exchange_weak(val, -1, std::memory_order_acquire));
        // can memory_order_relaxed be used if only a single thread takes write locks ?
    }
    void unlock() {
        refcount.store(0, std::memory_order_release);
    }
    void lock_shared() {
        int val;
        do {
            do {
                val = refcount.load(std::memory_order_relaxed);

            } while (val == -1); // spinning until the write lock is released

        } while (!refcount.compare_exchange_weak(val, val+1, std::memory_order_acquire));
    }
    void unlock_shared()  {
        refcount.fetch_sub(1, std::memory_order_relaxed);
    }
};


class RWMutex {
	shared_mutex m;
public:
	RWMutex() {}
	
	void EnterWrite() {m.lock();}
	void LeaveWrite() {m.unlock();}
	void EnterRead() {m.lock_shared();}
	void LeaveRead() {m.unlock_shared();}
};

class RWMutexReadLocker {
	RWMutex* m;
public:
	RWMutexReadLocker(RWMutex& m) : m(&m) {m.EnterRead();}
	~RWMutexReadLocker() {m->LeaveRead();}
};

class RWMutexWriteLocker {
	RWMutex* m;
public:
	RWMutexWriteLocker(RWMutex& m) : m(&m) {m.EnterWrite();}
	~RWMutexWriteLocker() {m->LeaveWrite();}
};

void Sleep(int ms);





typedef std::atomic_flag OnceFlag;

template <class Primitive>
class StaticPrimitive_ : NoCopy {
	Primitive *primitive;
	byte       buffer[sizeof(Primitive)];
	OnceFlag   once;
	
	void Initialize() { primitive = new(buffer) Primitive; }

public:
	Primitive& Get()  { ONCELOCK_(once) Initialize(); return *primitive; }
};

class StaticMutex : StaticPrimitive_<Mutex> {
public:
	operator Mutex&()          { return Get(); }
	bool TryEnter()            { return Get().TryEnter();}
	void Enter()               { Get().Enter();}
	void Leave()               { Get().Leave(); }
};

class SpinLock {
    std::atomic_flag locked = ATOMIC_FLAG_INIT;
public:
    void Enter() {
        while (locked.test_and_set(std::memory_order_acquire)) { ; }
    }
    void Leave() {
        locked.clear(std::memory_order_release);
    }
    bool TryEnter() {
        return !locked.test_and_set(std::memory_order_acquire);
    }
};




struct FakeAtomicInt : Moveable<FakeAtomicInt> {
	SpinLock lock;
	int value;
	FakeAtomicInt() : value(0) {}
	FakeAtomicInt(int i) : value(i) {}
	FakeAtomicInt(const AtomicInt& ai) : value(ai) {}
	operator int() {return value;}
	int operator = (int i) {
		lock.Enter();
		value = i;
		lock.Leave();
		return i;
	}
	int operator++(int) {
		lock.Enter();
		int i = value++;
		lock.Leave();
		return i;
	}
	int operator--(int) {
		lock.Enter();
		int i = value--;
		lock.Leave();
		return i;
	}
	int Get() const {return value;}
};

NAMESPACE_UPP_END


#endif
