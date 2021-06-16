#ifndef _CoreAlt_Tuple_h_
#define _CoreAlt_Tuple_h_

NAMESPACE_UPP_BEGIN



template <int N, typename... T>
struct TupleN;

template <int I>
struct IndexI__ {};

template <typename V, typename T, typename I>
const V& GetFromTuple(const T& t, const I&);

template <typename... T>
struct Tuple;

template <typename A>
struct TupleN<1, A>
{
	A a;

	bool  operator==(const TupleN& x) const   { return a == x.a; }
	int   Compare(const TupleN& x) const      { return SgnCompare(a, x.a); }

	void  ToHash(CombineHash& h) const        { h << a; }
	void  ToString(String& r) const           { r << AsString(a); }
	
	void  Serialize(Stream& s)                { s % a; }
	
	int   GetCount() const                    { return 1; }
	
	TupleN(const A& a) : a(a) {}
	TupleN() {}
	
	template <typename AA>
	operator Tuple<AA>()                      { Tuple<AA> t; t.a = (AA)a; return t; }
};

#define TUPLE_N_METHODS(M, I) \
	bool operator==(const TupleN& x) const    { return Base::operator==(x) && M == x.M; } \
	int  Compare(const TupleN& x) const       { int q = Base::Compare(x); return q ? q : SgnCompare(M, x.M); } \
 \
	void ToHash(CombineHash& h) const         { Base::ToHash(h); h << M; } \
	void ToString(String& r) const            { Base::ToString(r); r << ", " << M; } \
	 \
	void Serialize(Stream& s)                 { Base::Serialize(s); s % M; } \
	 \
	int   GetCount() const                    { return I + 1; } \
 \
	TupleN() {} \


template <typename A, typename B>
struct TupleN<2, A, B> : public TupleN<1, A> {
	typedef TupleN<1, A> Base;
	B b;
	
	TUPLE_N_METHODS(b, 1);

	TupleN(const A& a, const B& b) : Base(a), b(b) {}

	template <typename AA, typename BB>
	operator Tuple<AA, BB>()                  { Tuple<AA, BB> t; t.a = (AA)Base::a; t.b = b; return t; }
};

template <typename A, typename B, typename C>
struct TupleN<3, A, B, C> : public TupleN<2, A, B>
{
	typedef TupleN<2, A, B> Base;
	C c;

	TUPLE_N_METHODS(c, 2);

	TupleN(const A& a, const B& b, const C& c) : Base(a, b), c(c) {}

	template <typename AA, typename BB, typename CC>
	operator Tuple<AA, BB, CC>() { Tuple<AA, BB, CC> t; t.a = (AA)Base::a; t.b = (BB)Base::b; t.c = (CC)c; return t; }
};

template <typename A, typename B, typename C, typename D>
struct TupleN<4, A, B, C, D> : public TupleN<3, A, B, C>
{
	typedef TupleN<3, A, B, C> Base;
	D d;

	TUPLE_N_METHODS(d, 3);
	
	TupleN(const A& a, const B& b, const C& c, const D& d) : Base(a, b, c), d(d) {}

	template <typename AA, typename BB, typename CC, typename DD>
	operator Tuple<AA, BB, CC, DD>() { Tuple<AA, BB, CC, DD> t; t.a = (AA)Base::a; t.b = (BB)Base::b; t.c = (CC)Base::c; t.d = (DD)d; return t; }
};


#define GET_FROM_TUPLE(M, I) \
 \
template <typename T> \
auto GetFromTuple(const T& t, const IndexI__<I>&) -> decltype(t.M)& \
{ \
	return const_cast<T&>(t).M; \
} \
 \
template <typename T> \
auto GetFromTupleByType(const T& t, decltype(t.M)*, const IndexI__<I>* = NULL) -> decltype(t.M)& \
{ \
	return const_cast<T&>(t).M; \
}

GET_FROM_TUPLE(a, 0)
GET_FROM_TUPLE(b, 1)
GET_FROM_TUPLE(c, 2)
GET_FROM_TUPLE(d, 3)

template <typename... Args>
struct Tuple : public TupleN<sizeof...(Args), Args...> {
private:
	typedef TupleN<sizeof...(Args), Args...> Base;

	friend void AssertMoveable0(Tuple *) {}

public:
	template <int I>
	const auto& Get() const { return GetFromTuple(*this, IndexI__<I>()); }
	template <int I>
	auto& Get() { return GetFromTuple(*this, IndexI__<I>()); }
	
	template <typename T> const T& Get() const { return GetFromTupleByType(*this, (T*)NULL); }
	template <typename T> T& Get()             { return GetFromTupleByType(*this, (T*)NULL); }

	int  GetCount() const                      { return Base::GetCount(); }

	bool operator==(const Tuple& x) const     { return Base::operator==(x); }
	bool operator!=(const Tuple& x) const     { return !operator==(x); }
	
	int  Compare(const Tuple& x) const        { return Base::Compare(x); }
	bool operator<=(const Tuple& x) const     { return Compare(x) <= 0; }
	bool operator>=(const Tuple& x) const     { return Compare(x) >= 0; }
	bool operator<(const Tuple& x) const      { return Compare(x) < 0; }
	bool operator>(const Tuple& x) const      { return Compare(x) > 0; }

	hash_t GetHashValue() const               { CombineHash h; Base::ToHash(h); return h; }
	
	void Serialize(Stream& s)                 { Base::Serialize(s); }

	String ToString() const                   { String h = "("; Base::ToString(h); h << ")"; return h; }
	
	
	Tuple() {}
	Tuple(const Args... args) : Base(args...) {};
};

template <typename... Args>
Tuple<Args...> MakeTuple(const Args... args) {
	return Tuple<Args...>(args...);
}







template <class A, class B>
struct RefPair : Moveable<RefPair<A,B>> {
	A& a;
	B& b;

	RefPair(A& a, B& b) : a(a), b(b) {}
	RefPair(const RefPair& r) : a(r.a), b(r.b) {}
	
	RefPair* operator->(){return this;} // hack to allow returning object from Iterator
};

template <class A, class B>
struct PtrPair : Moveable<PtrPair<A,B>> {
	A* a;
	B* b;

	PtrPair() : a(0), b(0) {}
	PtrPair(A* a, B* b) : a(a), b(b) {}
	PtrPair(const PtrPair& r) : a(r.a), b(r.b) {}
	
	PtrPair* operator->(){return this;} // hack to allow returning object from Iterator
};

NAMESPACE_UPP_END

#endif
