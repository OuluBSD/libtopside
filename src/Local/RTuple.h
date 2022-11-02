#ifndef _Local_RTuple_h_
#define _Local_RTuple_h_

NAMESPACE_TOPSIDE_BEGIN


template<std::size_t N, typename T, typename... types>
struct GetNthType
{
    using type = typename GetNthType<N - 1, types...>::type;
};

template<typename T, typename... types>
struct GetNthType<0, T, types...>
{
    using type = T;
};

template<std::size_t N, typename... Args>
using GetType = typename GetNthType<N, Args...>::type;




// Recursive Tuple

template<typename First, typename... Rest>
struct RTuple : Moveable<RTuple<First, Rest...>> {
	RTuple() {}
	RTuple(First a, Rest... b): b(b...), a(a) {}
	RTuple(First a, RTuple<Rest...> b): b(b), a(a) {}
	RTuple(const RTuple& t) {*this = t;}
	void operator=(const RTuple& t) {a = t.a; b = t.b;}
	
	First a;
	RTuple<Rest...> b;
	
	First& operator->() {return a;}
	template <class T> T* Find() const {if (AsTypeCls<First>() == AsTypeCls<T>()) return (T*)&a; if (AsTypeCls<First>() == AsTypeCls<T>()) return (T*)&a; return b.template Find<T>();}
	template <class T> void ForEach(T fn) const {fn(a); b.ForEach(fn);}
	
	template <class T> T& Get() {
		T* ptr = Find<T>();
		if (!ptr) THROW(Exc("Could not find type from tuple"))
		return *ptr;
	}
	
	static String GetTypeNames() {
		String s;
		s << First::GetTypeName() << ", ";
		s << RTuple<Rest...>::GetTypeNames();
		return s;
	}
};

template<typename First>
struct RTuple<First> : Moveable<RTuple<First>> {
	RTuple() {}
	RTuple(First a): a(a) {}
	RTuple(const RTuple& t) {*this = t;}
	void operator=(const RTuple& t) {a = t.a;}
	
	First a;
	
	First& operator->() {return a;}
	template <class T> T* Find() const {
		if (AsTypeCls<First>() == AsTypeCls<T>())
			return (T*)&a;
		return NULL;
	}
	template <class T> void ForEach(T fn) const {fn(a);}
	
	operator First& () {return a;}
	operator const First& () const {return a;}
	
	template <class T> T& Get() {
		T* ptr = Find<T>();
		if (!ptr) THROW(Exc("Could not find type from tuple"))
		return *ptr;
	}
	
	static String GetTypeNames() {
		String s;
		s << First::GetTypeName() << ", ";
		return s;
	}
	
};

template<int index, typename First, typename... Rest>
struct GetImpl {
	static auto value(const RTuple<First, Rest...>* t) -> decltype(GetImpl < index - 1, Rest... >::value(&t->b)) {
		return GetImpl < index - 1, Rest... >::value(&t->b);
	}
};

template<typename First, typename... Rest>
struct GetImpl<0, First, Rest...> {
	static First value(const RTuple<First, Rest...>* t) {
		return t->a;
	}
};

template<int index, typename First, typename... Rest>
auto Get(const RTuple<First, Rest...>& t) -> decltype(GetImpl<index, First, Rest...>::value(&t)) { //typename Type<index, First, Rest...>::value {
	return GetImpl<index, First, Rest...>::value(&t);
}

template <class T, class A> T Get(const A& a) {
	T* ptr = a.template Find<T>();
	if (!ptr) THROW(Exc("Couldn't find type from tuple"))
	return *ptr;
}


template <class ... T>
RTuple<T...> MakeRTuple(T... args) {
	return RTuple<T...>(args...);
}


NAMESPACE_TOPSIDE_END

#endif
