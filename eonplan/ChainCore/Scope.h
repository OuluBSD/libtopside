#ifndef _ChainCore_Scope_h_
#define _ChainCore_Scope_h_

NAMESPACE_PLAN_BEGIN


class ScopeBase : public Node {
	
	
public:
	
	
};


template <class First_>
class Scope0 {
	First_		o;
	
public:
	
	using First = First_;
	using Last = First_;
	
};


template <class First_, class Rest>
class ScopeN : public Rest {
	First_		o;
	
public:
	
	
	using First = First_;
	using Last = typename Rest::Last;
	
	
	
};



template <class T, char const* link>
class Scope : public ScopeBase {
	T			parts;
	
public:
	
	
	void Serialize(EonStream& s) override {TODO}
	
	static const char*& LinkString() {static const char* s; return s;}
	
};


#define SCOPE1(x, a, links) \
	char x##_link[] = links; \
	using x = Scope<Scope0<a>,x##_link>;

#define SCOPE2(x, a, b, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,Scope0<b>>,x##_link>;

#define SCOPE3(x, a, b, c, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,Scope0<c>>>,x##_link>;

#define SCOPE4(x, a, b, c, d, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,Scope0<d>>>>,x##_link>;

#define SCOPE5(x, a, b, c, d, e, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,Scope0<e>>>>>,x##_link>;

#define SCOPE6(x, a, b, c, d, e, f, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,Scope0<f>>>>>>,x##_link>;

#define SCOPE7(x, a, b, c, d, e, f, g, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,ScopeN<f,Scope0<g>>>>>>>,x##_link>;

#define SCOPE8(x, a, b, c, d, e, f, g, h, links) \
	char x##_link[] = links; \
	using x = Scope<ScopeN<a,ScopeN<b,ScopeN<c,ScopeN<d,ScopeN<e,ScopeN<f,ScopeN<g,Scope0<h>>>>>>>>,x##_link>;


NAMESPACE_PLAN_END

#endif
