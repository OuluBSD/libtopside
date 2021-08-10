#ifndef _ChainCore_Machine_h_
#define _ChainCore_Machine_h_



class Machine : public Node {
	
	
	struct Stream : EonStream {
		Machine* m;
		
		void Serialize(Chain& c) override {m->OnChain(c);}
	};
	
	
	void OnChain(Chain& c);
	
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
	
};

#endif
