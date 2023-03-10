#ifndef _ProtoVM_Pcb_h_
#define _ProtoVM_Pcb_h_


class Machine;


class Pcb {
	
protected:
	friend class Machine;
	Machine* mach = 0;
	Array<ElectricNodeBase> nodes;
	Array<ElectricNodeBase> refs;
	String name;
	
public:
	
	
	template <class T>
	T& Add(String name="") {
		T* o = new T();
		o->pcb = this;
		o->name = name;
		nodes.Add(o);
		return *o;
	}
	
	template <class T>
	T& Add(int i, String name="") {
		T* o = new T(i);
		o->pcb = this;
		o->name = name;
		nodes.Add(o);
		return *o;
	}
	
	bool Tick();
	
	ENode& AddNode(String name);
	ElcBase& AddReferenceSingle(ElcBase& n, int pin_i);
	ElcBase& AddReferenceRange(ElcBase& n, int pin_i, int pin_count);
	
	bool IsAllConnected() const;
	String GetName() const {return name;}
	
	void Attach(ElectricNodeBase& from, ElectricNodeBase& to);
	void GetLinks(Array<Link>& links);
	
};



#endif
