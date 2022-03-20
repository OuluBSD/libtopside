#ifndef _ProtoVM_Component_h_
#define _ProtoVM_Component_h_



struct Pin : public ElcBase {
	bool is_ref_volt = false;
	double voltage;
	
	Pin& SetReference(double voltage) {is_ref_volt = true; this->voltage = voltage; return *this;}
	
};

struct Port : public ElcBase {
	Array<Pin> pins;
	
	
	void SetCount(int i) {pins.SetCount(i);}
	
	Pin& GetPin(int i) {return pins[i];}
	
};


template <int Ohm>
class Resistor : public ElcBase {
	
	
	
	
};

using Resistor4k7 = Resistor<4700>;


template <int Hz>
class Crystal : public ElcBase {
	
	
};

using Crystal4 = Crystal<4000000>;



class ElcNor : public ElcBase {
	
};


class ElcNand : public ElcBase {
	
};


class ElcNot : public ElcBase {
	
};



#endif
