#ifndef _ChainCore_Chain_h_
#define _ChainCore_Chain_h_


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



template <class T, char const* link>
class Chain : public ChainBase {
	T			parts;
	
public:
	
	
	void Serialize(EonStream& s) override {TODO}
	
	static const char*& LinkString() {static const char* s; return s;}
	
};


#define CHAIN1(x, a, links) \
	char x##_link[] = links; \
	using x = Chain<Chain0<a>,x##_link>;

#define CHAIN2(x, a, b, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,Chain0<b>>,x##_link>;

#define CHAIN3(x, a, b, c, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,Chain0<c>>>,x##_link>;

#define CHAIN4(x, a, b, c, d, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,Chain0<d>>>>,x##_link>;

#define CHAIN5(x, a, b, c, d, e, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,Chain0<e>>>>>,x##_link>;

#define CHAIN6(x, a, b, c, d, e, f, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,Chain0<f>>>>>>,x##_link>;

#define CHAIN7(x, a, b, c, d, e, f, g, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,ChainN<f,Chain0<g>>>>>>>,x##_link>;

#define CHAIN8(x, a, b, c, d, e, f, g, h, links) \
	char x##_link[] = links; \
	using x = Chain<ChainN<a,ChainN<b,ChainN<c,ChainN<d,ChainN<e,ChainN<f,ChainN<g,Chain0<h>>>>>>>>,x##_link>;


#endif
