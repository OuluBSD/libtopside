#ifndef _ChainCore_Machine_h_
#define _ChainCore_Machine_h_


/*
class Machine : public Node {
	
	
	struct Stream : EonStream {
		Machine* m;
		
		void Serialize(ChainBase& c) override {m->OnChain(c);}
	};
	
	
	void OnChain(ChainBase& c);
	
public:
	Machine();
	
	void Init();
	
};


template <class T0>
class Machine1 : public Machine {
	T0		o0;
	
public:
	Machine1() {}
	
	
	void Serialize(EonStream& s) override {s % o0;}
	
};*/


class MachineBase : public Node {
	
	
public:
	
	
};


template <class First_>
class Machine0 {
	First_		o;
	
public:
	
	using First = First_;
	using Last = First_;
	
};


template <class First_, class Rest>
class MachineN : public Rest {
	First_		o;
	
public:
	
	
	using First = First_;
	using Last = typename Rest::Last;
	
	
	
};



template <class T, char const* link>
class Machine : public MachineBase {
	T			parts;
	
public:
	
	
	void Serialize(EonStream& s) override {TODO}
	
	static const char*& LinkString() {static const char* s; return s;}
	
};


#define MACHINE1(x, a, links) \
	char x##_link[] = links; \
	using x = Machine<Machine0<a>,x##_link>;

#define MACHINE2(x, a, b, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,Machine0<b>>,x##_link>;

#define MACHINE3(x, a, b, c, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,Machine0<c>>>,x##_link>;

#define MACHINE4(x, a, b, c, d, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,Machine0<d>>>>,x##_link>;

#define MACHINE5(x, a, b, c, d, e, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,Machine0<e>>>>>,x##_link>;

#define MACHINE6(x, a, b, c, d, e, f, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,Machine0<f>>>>>>,x##_link>;

#define MACHINE7(x, a, b, c, d, e, f, g, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,MachineN<f,Machine0<g>>>>>>>,x##_link>;

#define MACHINE8(x, a, b, c, d, e, f, g, h, links) \
	char x##_link[] = links; \
	using x = Machine<MachineN<a,MachineN<b,MachineN<c,MachineN<d,MachineN<e,MachineN<f,MachineN<g,Machine0<h>>>>>>>>,x##_link>;


#endif
