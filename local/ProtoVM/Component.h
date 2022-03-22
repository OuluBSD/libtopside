#ifndef _ProtoVM_Component_h_
#define _ProtoVM_Component_h_



struct Pin : public ElcBase {
	RTTI_DECL1(Pin, ElcBase);
	
	bool is_ref_volt = false;
	double voltage;
	
	Pin();
	Pin& SetReference(double voltage);
	
};

struct Port : public ElcBase {
	RTTI_DECL1(Port, ElcBase);
	
	Array<Pin> pins;
	
	
	void SetCount(int i) {pins.SetCount(i);}
	
	Pin& GetPin(int i) {return pins[i];}
	
};


//template <int Ohm>
class Resistor : public ElcBase {
	RTTI_DECL1(Resistor, ElcBase);
	
	
public:
	Resistor() {
		AddSink("A");
		AddSource("B");
		
	}
	
	
	
};

using Resistor4k7 = Resistor;//<4700>;


template <int Hz>
class Crystal : public ElcBase {
	RTTI_DECL1(Crystal<Hz>, ElcBase);
	
	
	
};

using Crystal4 = Crystal<4000000>;



class ElcNor : public ElcBase {
	RTTI_DECL1(ElcNor, ElcBase);
	
	
};


class ElcNand : public ElcBase {
	RTTI_DECL1(ElcNand, ElcBase);
	
	
};


class ElcNot : public ElcBase {
	RTTI_DECL1(ElcNot, ElcBase);
	
	
};


class ElcCapacitor : public ElcBase {
	RTTI_DECL1(ElcCapacitor, ElcBase);
	
	
};


class FlipFlopJK : public ElcBase {
	RTTI_DECL1(FlipFlopJK, ElcBase);
	
public:
	FlipFlopJK();
	
	
};


#endif
