#ifndef _ProtoVM_Component_h_
#define _ProtoVM_Component_h_

NAMESPACE_TOPSIDE_BEGIN


struct Pin : public ElcBase {
	RTTI_DECL1(Pin, ElcBase);
	
	byte is_high = 0;
	
	Pin();
	Pin& SetReference(bool is_high);
	
	bool Tick() override;
	bool Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) override;
	bool PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) override;
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



class ResistorPack : public ElcBase {
	RTTI_DECL1(ResistorPack, ElcBase);
	
	
public:
	ResistorPack(int c) {
		AddSink("A");
		for(int i = 0; i < c; i++)
			AddSource("B" + IntStr(i));
		
	}
	
	
	
};



class Crystal : public ElcBase {
	RTTI_DECL1(Crystal, ElcBase);
	int hz = 0;
	
public:
	Crystal();
	
};




class ElcNor : public ElcBase {
	RTTI_DECL1(ElcNor, ElcBase);
	
	
public:
	ElcNor();
	
};


class ElcNand : public ElcBase {
	RTTI_DECL1(ElcNand, ElcBase);
	bool in0 = 0;
	bool in1 = 0;
	bool out = 0;
	
public:
	ElcNand();
	
	bool Tick() override;
	bool Process(ProcessType type, int bytes, int bits, uint16 conn_id, ElectricNodeBase& dest, uint16 dest_conn_id) override;
	bool PutRaw(uint16 conn_id, byte* data, int data_bytes, int data_bits) override;
};


class ElcNot : public ElcBase {
	RTTI_DECL1(ElcNot, ElcBase);
	
	
public:
	ElcNot();
	
};


class ElcCapacitor : public ElcBase {
	RTTI_DECL1(ElcCapacitor, ElcBase);
	
	
public:
	ElcCapacitor();
	
};


class FlipFlopJK : public ElcBase {
	RTTI_DECL1(FlipFlopJK, ElcBase);
	
public:
	FlipFlopJK();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
