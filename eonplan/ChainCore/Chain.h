#ifndef _ChainCore_Chain_h_
#define _ChainCore_Chain_h_


class Chain : public Node {
	
	
public:
	
	
};


template <class T0, class T1, char const* link>
struct Chain2 : public Chain {
	T0		o0;
	T1		o1;
	
	
	void Serialize(EonStream& s) override {s.Link(link); s % o0 % o1;}
	
	
	static const char*& LinkString() {static const char* s; return s;}
	
};

#define CHAIN2(x, a, b, links) char x##_link[] = links; using x = Chain2<a,b,x##_link>;


#endif
