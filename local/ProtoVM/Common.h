#ifndef _ProtoVM_Common_h_
#define _ProtoVM_Common_h_



class Pcb;


class ElectricNodeBase {
	
protected:
	friend class Pcb;
	Pcb* pcb = 0;
	String name;
	
public:
	typedef ElectricNodeBase CLASSNAME;
	ElectricNodeBase();
	
	
	ElectricNodeBase& operator>>(ElectricNodeBase& b);
	
	ElectricNodeBase& operator[](String code);
	ElectricNodeBase& operator[](int i);
	
};

using ElcBase = ElectricNodeBase;




class ElectricNode : public ElectricNodeBase {
	
	
};


using ENode = ElectricNode;



#endif
