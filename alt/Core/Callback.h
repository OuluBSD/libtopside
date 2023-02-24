#ifndef _CoreAlt_Callback_h_
#define _CoreAlt_Callback_h_

NAMESPACE_UPP_BEGIN

class CallBaseObject {
	int refs = 1;

public:
	CallBaseObject() {}
	virtual ~CallBaseObject() {}

	void Inc() { refs++; }
	void Dec() { if ((void*)this == NULL) return; refs--; if (refs <= 0) { delete this; } }
};








class CallBase : public CallBaseObject {
public:
	virtual void Execute() = 0;
	virtual bool IsThis(void*) const {return false;}
};

template <class A0>
class CallBase1 : public CallBaseObject {
public:
	virtual void Execute(const A0& a0) = 0;
	virtual bool IsThis(void*) const {return false;}
};

template <class A0, class A1>
class CallBase2 : public CallBaseObject {
public:
	virtual void Execute(const A0& a0, const A1& a1) = 0;
	virtual bool IsThis(void*) const {return false;}
};








class StaticCaller : public CallBase {
	void (*fn)();

public:
	StaticCaller(void (*fn)()) : fn(fn) {}
	void Execute() override { fn(); }
};

template <class A0>
class StaticCaller1 : public CallBase1<A0> {
	void (* fn)(A0);

public:
	StaticCaller1(void (* fn)(A0)) : fn(fn) {}
	void Execute(const A0& a0) override { (*fn)(a0); }
};

template <class A0, class A1>
class StaticCaller2 : public CallBase2<A0, A1> {
	void (* fn)(A0, A1);

public:
	StaticCaller2(void (* fn)(A0,A1)) : fn(fn) {}
	void Execute(const A0& a0, const A1& a1) override { (*fn)(a0, a1); }
};


template <class A0, class A1>
class StaticCaller_2 : public CallBase {
	void (* fn)(A0, A1);
	A0 a0;
	A1 a1;
	
public:
	StaticCaller_2(void (* fn)(A0,A1), A0 a0, A1 a1) : fn(fn), a0(a0), a1(a1) {}
	void Execute() override { (*fn)(a0, a1); }
};









template <class T>
class Caller : public CallBase {
	void (T::* fn)();
	T* obj;

public:
	Caller(void (T::* fn)(), T* obj) : fn(fn), obj(obj) {}
	void Execute() override { (*obj.*fn)(); }
	bool IsThis(void* p) const override {return obj == p;}
};

template <class T, class A0>
class Caller1 : public CallBase1<A0> {
	void (T::* fn)(A0);
	T* obj;

public:
	Caller1(void (T::* fn)(A0), T* obj) : fn(fn), obj(obj) {}
	void Execute(const A0& a0) override { (*obj.*fn)(a0); }
	bool IsThis(void* p) const override {return obj == p;}
};

template <class T, class A0>
class Caller_1 : public CallBase {
	void (T::* fn)(A0);
	T* obj;
	A0 a0;

public:
	Caller_1(void (T::* fn)(A0), T* obj, A0 a0) : fn(fn), obj(obj), a0(a0) {}
	void Execute() override { (*obj.*fn)(a0); }
	bool IsThis(void* p) const override {return obj == p;}
};

template <class T, class A0, class A1>
class Caller_2 : public CallBase {
	void (T::* fn)(A0, A1);
	T* obj;
	A0 a0;
	A1 a1;

public:
	Caller_2(void (T::* fn)(A0,A1), T* obj, A0 a0, A1 a1) : fn(fn), obj(obj), a0(a0), a1(a1) {}
	void Execute() override { (*obj.*fn)(a0, a1); }
	bool IsThis(void* p) const override {return obj == p;}
};

template <class T, class A0, class A1>
class Caller1_1 : public CallBase1<A0> {
	void (T::* fn)(A0, A1);
	T* obj;
	A1 a1;

public:
	Caller1_1(void (T::* fn)(A0, A1), T* obj, A1 a1) : fn(fn), obj(obj), a1(a1) {}
	void Execute(const A0& a0) override { (*obj.*fn)(a0, a1); }
	bool IsThis(void* p) const override {return obj == p;}
};

template <class T, class A0, class A1>
class Caller2 : public CallBase2<A0, A1> {
	void (T::* fn)(A0, A1);
	T* obj;

public:
	Caller2(void (T::* fn)(A0, A1), T* obj) : fn(fn), obj(obj) {}
	void Execute(const A0& a0, const A1& a1) override { (*obj.*fn)(a0, a1); }
	bool IsThis(void* p) const override {return obj == p;}
};

template <class T, class A0, class A1, class A2>
class Caller1_2 : public CallBase1<A2> {
	void (T::* fn)(A2, A0, A1);
	T* obj;
	A0 a0;
	A1 a1;

public:
	Caller1_2(void (T::* fn)(A2,A0,A1), T* obj, A0 a0, A1 a1) : fn(fn), obj(obj), a0(a0), a1(a1) {}
	void Execute(const A2& a2) override { (*obj.*fn)(a2, a0, a1); }
	bool IsThis(void* p) const override {return obj == p;}
};











class Callback : Moveable<Callback> {
	Vector<CallBase*> calls;


public:
	Callback() {}
	Callback(const Callback& cb) { *this = cb; }
	Callback(CallBase* cb) { ASSERT(cb); calls.Add(cb); }
	Callback(void (*fn)()) {calls.Add(new StaticCaller(fn));}
	~Callback() { Clear(); }
	void operator=(const Callback& cb) {
		Clear();
		*this << cb;
	}
	void Add(const Callback& cb) {
		int begin = calls.GetCount();
		calls.Append(cb.calls);
		for (int i = begin; i < calls.GetCount(); i++)
			calls[i]->Inc();
	}
	void operator<<(const Callback& cb) {Add(cb);}
	void Clear() {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Dec();
		calls.Clear();
	}
	void Execute() const {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Execute();
	}
	
	void RemoveThis(void* t) {
		for(int i = 0; i < calls.GetCount(); i++)
			if (calls[i]->IsThis(t))
				calls.Remove(i--);
	}
	
	void operator()() const { Execute(); }
	operator bool() const {return calls.GetCount();}
	String ToString() const {return "Callback";}
	int64 ToInt() const {return calls.GetCount();}
	
};

template <class A0>
class Callback1 : Moveable<Callback1<A0>> {
	Vector<CallBase1<A0>* > calls;

public:
	Callback1() {}
	Callback1(const Callback1& cb) { *this = cb; }
	Callback1(CallBase1<A0>* cb) { ASSERT(cb); calls.Add(cb); }
	~Callback1() { Clear(); }
	void operator=(const Callback1& cb) {
		Clear();
		*this << cb;
	}
	void operator<<(const Callback1& cb) {Add(cb);}
	void Add(const Callback1& cb) {
		int begin = calls.GetCount();
		calls.Append(cb.calls);
		for (int i = begin; i < calls.GetCount(); i++)
			calls[i]->Inc();
	}
	void Clear() {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Dec();
		calls.Clear();
	}
	void Execute(const A0& a0) const {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Execute(a0);
	}
	
	void RemoveThis(void* t) {
		for(int i = 0; i < calls.GetCount(); i++)
			if (calls[i]->IsThis(t))
				calls.Remove(i--);
	}
	
	void operator()(const A0& a0) const { Execute(a0); }
	operator bool() const {return calls.GetCount();}
	String ToString() const {return "Callback1";}
	int64 ToInt() const {return calls.GetCount();}
};

template <class A0, class A1>
class Callback2 : Moveable<Callback2<A0, A1>> {
	Vector<CallBase2<A0, A1>* > calls;

public:
	Callback2() {}
	Callback2(const Callback2& cb) { *this = cb; }
	Callback2(CallBase2<A0, A1>* cb) { ASSERT(cb); calls.Add(cb); }
	~Callback2() { Clear(); }
	void operator=(const Callback2& cb) {
		Clear();
		*this << cb;
	}
	void Add(const Callback2& cb) {
		int begin = calls.GetCount();
		calls.Append(cb.calls);
		for (int i = begin; i < calls.GetCount(); i++)
			calls[i]->Inc();
	}
	void operator<<(const Callback2& cb) {Add(cb);}
	void Clear() {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Dec();
		calls.Clear();
	}
	void Execute(const A0& a0, const A1& a1) const {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Execute(a0, a1);
	}
	
	void RemoveThis(void* t) {
		for(int i = 0; i < calls.GetCount(); i++)
			if (calls[i]->IsThis(t))
				calls.Remove(i--);
	}
	
	void operator()(const A0& a0, const A1& a1) const { Execute(a0, a1); }
	operator bool() const {return calls.GetCount();}
	String ToString() const {return "Callback2";}
	int64 ToInt() const {return calls.GetCount();}
};









class ProxyCaller : public CallBase {
	const Callback* cb;
public:
	ProxyCaller(const Callback& cb) : cb(&cb) {}
	void Execute() override { cb->Execute(); }
};

template <class A0>
class ProxyCaller1 : public CallBase1<A0> {
	const Callback1<A0>* cb;
public:
	ProxyCaller1(const Callback1<A0>& cb) : cb(&cb) {}
	void Execute(const A0& a0) override { cb->Execute(a0); }
};







inline Callback callback(void (*fn)()) {
	return Callback(new StaticCaller(fn));
}

template <class A0>
inline Callback1<A0> callback(void (* fn)(A0)) {
	return Callback1<A0>(new StaticCaller1<A0>(fn));
}

template <class A0, class A1>
inline Callback2<A0, A1> callback(void (* fn)(A0,A1)) {
	return Callback2<A0,A1>(new StaticCaller2<A0,A1>(fn));
}

template <class T>
inline Callback callback(T* obj, void (T::* fn)()) {
	return Callback(new Caller<T>(fn, obj));
}

template <class T, class A0>
inline Callback1<A0> callback(T* obj, void (T::* fn)(A0)) {
	return Callback1<A0>(new Caller1<T, A0>(fn, obj));
}

template <class T, class A0>
inline Callback callback1(T* obj, void (T::* fn)(A0), A0 a0) {
	return Callback(new Caller_1<T, A0>(fn, obj, a0));
}

template <class T, class A1, class A0>
inline Callback1<A0> callback1(T* obj, void (T::* fn)(A0, A1), A1 a1) {
	return Callback1<A0>(new Caller1_1<T, A0, A1>(fn, obj, a1));
}

template <class T, class A0, class A1>
inline Callback2<A0, A1> callback(T* obj, void (T::* fn)(A0, A1)) {
	return Callback2<A0, A1>(new Caller2<T, A0, A1>(fn, obj));
}

template <class A0, class A1>
inline Callback callback2(void (*fn)(A0, A1), A0 a0, A1 a1) {
	return Callback(new StaticCaller_2<A0, A1>(fn, a0, a1));
}

template <class T, class A0, class A1>
inline Callback callback2(T* obj, void (T::* fn)(A0, A1), A0 a0, A1 a1) {
	return Callback(new Caller_2<T, A0, A1>(fn, obj, a0, a1));
}

template <class T, class A0, class A1, class A2>
inline Callback1<A2> callback2(T* obj, void (T::* fn)(A2, A0, A1), A0 a0, A1 a1) {
	return Callback1<A2>(new Caller1_2<T, A0, A1, A2>(fn, obj, a0, a1));
}


/*wrong
template <class T, class A0, class A1>
inline Callback callback2(void (T::* fn)(A0, A1), T* obj) {
	return Callback(new Caller2<T, A0, A1>(fn, obj));
}*/

#define THISBACK(x) callback<CLASSNAME>(this, &CLASSNAME::x)
#define THISBACK1(x, a0) callback1<CLASSNAME, decltype(a0)>(this, &CLASSNAME::x, a0)
#define THISBACK2(x, a0, a1) callback2<CLASSNAME, decltype(a0), decltype(a1)>(this, &CLASSNAME::x, a0, a1)


inline Callback Proxy(const Callback& cb) {return Callback(new ProxyCaller(cb));}
inline Callback Proxy0(const Callback& cb) {return Callback(new ProxyCaller(cb));}

template <class A0>
inline Callback1<A0> Proxy(const Callback1<A0>& cb) {
	return Callback1<A0>(new ProxyCaller1<A0>(cb));
}



void AddInitBlock(Callback cb);
void AddExitBlock(Callback cb);
void RunInitBlocks();
void RunExitBlocks();
void AddThreadShutdownCallback(Callback cb);
void RunThreadExitBlocks();

struct Callinit {
	Callinit(void (*fn)());
	void Clear();
};

struct Callexit {
	Callexit(void (*fn)());
	void Clear();
};


template <class T> ManagedStatic<T>::ManagedStatic(const char* f, int l) : file(f), line(l) {AddExitBlock(THISBACK(Destruct));}
template <class T> template <class Arg>
ManagedStatic<T>::ManagedStatic(const char* f, int l, const Arg& value) : file(f), line(l), o(value) {AddExitBlock(THISBACK(Destruct));}

template <class T> ManagedStaticThreadLocal<T>::ManagedStaticThreadLocal(const char* f, int l) : file(f), line(l) {AddThreadShutdownCallback(THISBACK(Destruct));}
template <class T> template <class Arg>
ManagedStaticThreadLocal<T>::ManagedStaticThreadLocal(const char* f, int l, const Arg& value) : file(f), line(l), o(value) {AddThreadShutdownCallback(THISBACK(Destruct));}







template <class... T> struct Event;
template <> struct Event<> : Callback {
	Event() {}
	Event(const Callback& cb) : Callback(cb) {}
	void operator=(const Callback& cb) {Callback::operator=(cb);}
};
template <class T> struct Event<T> : Callback1<T> {
	Event() {}
	Event(const Callback1<T>& cb) : Callback(cb) {}
	void operator=(const Callback1<T>& cb) {Callback1<T>::operator=(cb);}
};




NAMESPACE_UPP_END

#endif
