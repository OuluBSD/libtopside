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



template <class T>
class Scope : public ScopeBase {
	T			parts;
	
public:
	
	
	void Serialize(EonStream& s) override {TODO}
	
	static const char*& LinkString() {static const char* s; return s;}
	
};



NAMESPACE_PLAN_END

#endif
