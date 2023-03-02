#ifndef _Core_Gate_h_
#define _Core_Gate_h_

NAMESPACE_UPP_BEGIN


#if 0


class GateBase : public CallBaseObject {
public:
	virtual bool Execute() = 0;
};

template <class A0>
class GateBase1 : public CallBaseObject {
public:
	virtual bool Execute(const A0& a0) = 0;
};

template <class A0, class A1>
class GateBase2 : public CallBaseObject {
public:
	virtual bool Execute(const A0& a0, const A1& a1) = 0;
};








class StaticGateCaller : public GateBase {
	bool (*fn)();

public:
	StaticGateCaller(bool (*fn)()) : fn(fn) {}
	bool Execute() override { return fn(); }
};

template <class A0>
class StaticGateCaller1 : public GateBase1<A0> {
	bool (*fn)(A0);

public:
	StaticGateCaller1(bool (*fn)(A0)) : fn(fn) {}
	bool Execute(const A0& a0) override { return (*fn)(a0); }
};

template <class A0, class A1>
class StaticGateCaller2 : public GateBase2<A0, A1> {
	bool (*fn)(A0, A1);

public:
	StaticGateCaller2(bool (*fn)(A0,A1)) : fn(fn) {}
	bool Execute(const A0& a0, const A1& a1) override { return (*fn)(a0, a1); }
};









template <class T>
class GateCaller : public GateBase {
	bool (T::* fn)();
	T* obj;

public:
	GateCaller(bool (T::* fn)(), T* obj) : fn(fn), obj(obj) {}
	bool Execute() override { return (*obj.*fn)(); }
};

template <class T, class A0>
class GateCaller1 : public GateBase1<A0> {
	bool (T::* fn)(A0);
	T* obj;

public:
	GateCaller1(bool (T::* fn)(A0), T* obj) : fn(fn), obj(obj) {}
	bool Execute(const A0& a0) override { return (*obj.*fn)(a0); }
};

template <class T, class A0>
class GateCaller_1 : public GateBase {
	bool (T::* fn)(A0);
	T* obj;
	A0 a0;

public:
	GateCaller_1(bool (T::* fn)(A0), T* obj, A0 a0) : fn(fn), obj(obj), a0(a0) {}
	bool Execute() override { return (*obj.*fn)(a0); }
};

template <class T, class A0, class A1>
class GateCaller_2 : public GateBase {
	bool (T::* fn)(A0, A1);
	T* obj;
	A0 a0;
	A1 a1;

public:
	GateCaller_2(bool (T::* fn)(A0,A1), T* obj, A0 a0, A1 a1) : fn(fn), obj(obj), a0(a0), a1(a1) {}
	bool Execute() override { return (*obj.*fn)(a0, a1); }
};

template <class T, class A0, class A1>
class GateCaller1_1 : public GateBase1<A0> {
	bool (T::* fn)(A0, A1);
	T* obj;
	A1 a1;

public:
	GateCaller1_1(bool (T::* fn)(A0, A1), T* obj, A1 a1) : fn(fn), obj(obj), a1(a1) {}
	bool Execute(const A0& a0) override { return (*obj.*fn)(a0, a1); }
};

template <class T, class A0, class A1>
class GateCaller2 : public GateBase2<A0, A1> {
	bool (T::* fn)(A0, A1);
	T* obj;

public:
	GateCaller2(bool (T::* fn)(A0, A1), T* obj) : fn(fn), obj(obj) {}
	bool Execute(const A0& a0, const A1& a1) override { return (*obj.*fn)(a0, a1); }
};

template <class T, class A0, class A1, class A2>
class GateCaller1_2 : public GateBase1<A2> {
	bool (T::* fn)(A2, A0, A1);
	T* obj;
	A0 a0;
	A1 a1;

public:
	GateCaller1_2(bool (T::* fn)(A2,A0,A1), T* obj, A0 a0, A1 a1) : fn(fn), obj(obj), a0(a0), a1(a1) {}
	bool Execute(const A2& a2) override { return (*obj.*fn)(a2, a0, a1); }
};











class Gate0 : Moveable<Gate0> {
	Vector<GateBase*> calls;


public:
	Gate0() {}
	Gate0(const Gate0& cb) { *this = cb; }
	Gate0(GateBase* cb) { ASSERT(cb); calls.Add(cb); }
	Gate0(bool (*fn)()) {calls.Add(new StaticGateCaller(fn));}
	Gate0(const Nuller&) {}
	~Gate0() { Clear(); }
	void operator=(const Gate0& cb) {
		Clear();
		*this << cb;
	}
	void Add(const Gate0& cb) {
		int begin = calls.GetCount();
		calls.Append(cb.calls);
		for (int i = begin; i < calls.GetCount(); i++)
			calls[i]->Inc();
	}
	void operator<<(const Gate0& cb) {Add(cb);}
	void Clear() {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Dec();
		calls.Clear();
	}
	bool Execute() const {
		bool b = calls.GetCount();
		for (int i = 0; i < calls.GetCount(); i++)
			b = calls[i]->Execute() && b;
		return b;
	}

	bool operator()() const { return Execute(); }
	operator bool() const {return calls.GetCount();}
	String ToString() const {return "Gate0";}
	int64 ToInt() const {return calls.GetCount();}
};

template <class A0>
class Gate1 : Moveable<Gate1<A0>> {
	Vector<GateBase1<A0>* > calls;

public:
	Gate1() {}
	Gate1(const Gate1& cb) { *this = cb; }
	Gate1(GateBase1<A0>* cb) { ASSERT(cb); calls.Add(cb); }
	Gate1(const Nuller&) {}
	~Gate1() { Clear(); }
	void operator=(const Gate1& cb) {
		Clear();
		*this << cb;
	}
	void operator<<(const Gate1& cb) {Add(cb);}
	void Add(const Gate1& cb) {
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
	bool Execute(const A0& a0) const {
		bool b = true;
		for (int i = 0; i < calls.GetCount(); i++)
			b = calls[i]->Execute(a0) && b;
		return b;
	}

	bool operator()(const A0& a0) const { return Execute(a0); }
	operator bool() const {return calls.GetCount();}
	String ToString() const {return "Gate1";}
	int64 ToInt() const {return calls.GetCount();}
};

template <class A0, class A1>
class Gate2 : Moveable<Gate2<A0, A1>> {
	Vector<GateBase2<A0, A1>* > calls;

public:
	Gate2() {}
	Gate2(const Gate2& cb) { *this = cb; }
	Gate2(GateBase2<A0, A1>* cb) { ASSERT(cb); calls.Add(cb); }
	Gate2(const Nuller&) {}
	~Gate2() { Clear(); }
	void operator=(const Gate2& cb) {
		Clear();
		*this << cb;
	}
	void Add(const Gate2& cb) {
		int begin = calls.GetCount();
		calls.Append(cb.calls);
		for (int i = begin; i < calls.GetCount(); i++)
			calls[i]->Inc();
	}
	void operator<<(const Gate2& cb) {Add(cb);}
	void Clear() {
		for (int i = 0; i < calls.GetCount(); i++)
			calls[i]->Dec();
		calls.Clear();
	}
	bool Execute(const A0& a0, const A1& a1) const {
		bool b = calls.GetCount();
		for (int i = 0; i < calls.GetCount(); i++)
			b = calls[i]->Execute(a0, a1) && b;
		return b;
	}

	bool operator()(const A0& a0, const A1& a1) const { return Execute(a0, a1); }
	operator bool() const {return calls.GetCount();}
	String ToString() const {return "Gate2";}
	int64 ToInt() const {return calls.GetCount();}
};









class ProxyGateCaller : public GateBase {
	const Gate0* cb;
public:
	ProxyGateCaller(const Gate0& cb) : cb(&cb) {}
	bool Execute() override { return cb->Execute(); }
};

template <class A0>
class ProxyGateCaller1 : public GateBase1<A0> {
	const Gate1<A0>* cb;
public:
	ProxyGateCaller1(const Gate1<A0>& cb) : cb(&cb) {}
	bool Execute(const A0& a0) override { return cb->Execute(a0); }
};





#if 0

inline Gate0 callback(bool (*fn)()) {
	return Gate0(new StaticGateCaller(fn));
}

template <class A0>
inline Gate1<A0> callback(bool (*fn)(A0)) {
	return Gate1<A0>(new StaticGateCaller1<A0>(fn));
}

template <class A0, class A1>
inline Gate2<A0, A1> callback(bool (*fn)(A0,A1)) {
	return Gate2<A0,A1>(new StaticGateCaller2<A0,A1>(fn));
}

template <class T>
inline Gate0 callback(T* obj, bool (T::* fn)()) {
	return Gate0(new GateCaller<T>(fn, obj));
}

template <class T, class A0>
inline Gate1<A0> callback(T* obj, bool (T::* fn)(A0)) {
	return Gate1<A0>(new GateCaller1<T, A0>(fn, obj));
}

template <class T, class A0, class A1>
inline Gate2<A0, A1> callback(T* obj, bool (T::* fn)(A0, A1)) {
	return Gate2<A0, A1>(new GateCaller2<T, A0, A1>(fn, obj));
}

template <class A0>
inline Gate0 callback1(bool (*fn)(A0), A0 a0) {
	return Gate0(new StaticGateCaller1<A0>(fn, a0));
}

template <class T, class A0>
inline Gate0 callback1(T* obj, bool (T::* fn)(A0), A0 a0) {
	return Gate0(new GateCaller_1<T, A0>(fn, obj, a0));
}

template <class T, class A1, class A0>
inline Gate1<A0> callback1(T* obj, bool (T::* fn)(A0, A1), A1 a1) {
	return Gate1<A0>(new GateCaller1_1<T, A0, A1>(fn, obj, a1));
}

template <class A0, class A1>
inline Gate0 callback2(bool (*fn)(A0, A1), A0 a0, A1 a1) {
	return Gate0(new StaticGateCaller2<A0, A1>(fn, a0, a1));
}

template <class T, class A0, class A1>
inline Gate0 callback2(T* obj, bool (T::* fn)(A0, A1), A0 a0, A1 a1) {
	return Gate0(new GateCaller_2<T, A0, A1>(fn, obj, a0, a1));
}

template <class T, class A0, class A1, class A2>
inline Gate1<A2> callback2(T* obj, bool (T::* fn)(A2, A0, A1), A0 a0, A1 a1) {
	return Gate1<A2>(new GateCaller1_2<T, A0, A1, A2>(fn, obj, a0, a1));
}

#endif


#define __GATE_FUNCS \
	Gate() = default; \
	Gate(const Nuller&) {} \
	Gate(const Gate& g) : Base(g) {};

template <class... T> struct Gate;
template <> struct Gate<> : Gate0 {using Base = Gate0; __GATE_FUNCS};
template <class T0> struct Gate<T0> : Gate1<T0> {using Base = Gate1<T0>; __GATE_FUNCS};
template <class T0, class T1> struct Gate<T0,T1> : Gate2<T0,T1> {using Base = Gate2<T0,T1>; __GATE_FUNCS};
#endif


NAMESPACE_UPP_END

#endif
