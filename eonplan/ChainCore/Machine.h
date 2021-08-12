#ifndef _ChainCore_Machine_h_
#define _ChainCore_Machine_h_

NAMESPACE_PLAN_BEGIN


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



template <class T>
class Machine : public MachineBase {
	T			parts;
	
public:
	
	
	void Serialize(EonStream& s) override {TODO}
	
	static const char*& LinkString() {static const char* s; return s;}
	
};



NAMESPACE_PLAN_END

#endif
