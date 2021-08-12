#ifndef _ChainCore_Chain_h_
#define _ChainCore_Chain_h_

NAMESPACE_PLAN_BEGIN


class ChainBase : public Node {
	
	
public:
	
	
};


template <class First_>
class Chain0 {
	First_		o;
	
public:
	
	using First = First_;
	using Last = First_;
	
};


template <class First_, class Rest>
class ChainN : public Rest {
	First_		o;
	
public:
	
	
	using First = First_;
	using Last = typename Rest::Last;
	
	
	
};



template <class T>
class Chain : public ChainBase {
	T			parts;
	
public:
	
	
	void Serialize(EonStream& s) override {TODO}
	
	static const char*& LinkString() {static const char* s; return s;}
	
};



NAMESPACE_PLAN_END

#endif
