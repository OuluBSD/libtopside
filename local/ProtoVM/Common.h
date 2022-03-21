#ifndef _ProtoVM_Common_h_
#define _ProtoVM_Common_h_



class Pcb;


class ElectricNodeBase : RTTIBase {
	
protected:
	
	typedef enum {
		V_VOID,
		V_WHOLE,
		V_PARTIAL,
	} Type;
	
	struct Connector : Moveable<Connector> {
		String name;
		bool is_sink = false;
		bool is_src = false;
		bool accept_multiconn = false;
		
		Vector<Connector*> links;
		
		bool IsConnectable() const {return links.IsEmpty() || accept_multiconn;}
		void SetMultiConn() {accept_multiconn = true;}
	};
	
	friend class Pcb;
	Pcb* pcb = 0;
	String name;
	Array<Connector> conns;
	Type type = V_VOID;
	int sink_count = 0;
	int src_count = 0;
	int bi_count = 0;
	
	
	
	Connector& AddSource(String name);
	Connector& AddSink(String name);
	Connector& AddBidirectional(String name);
	
public:
	typedef ElectricNodeBase CLASSNAME;
	ElectricNodeBase();
	virtual ~ElectricNodeBase() {}
	
	RTTI_DECL0(ElectricNodeBase);
	
	bool IsEmpty() const {return conns.IsEmpty();}
	bool IsTrivialSourceDefault() const;
	bool IsTrivialSinkDefault() const;
	
	Connector& GetTrivialSource();
	Connector& GetTrivialSink();
	
	ElectricNodeBase& operator>>(ElectricNodeBase& b);
	ElectricNodeBase& operator[](String code);
	ElectricNodeBase& operator[](int i);
	
};

using ElcBase = ElectricNodeBase;




class ElectricNode : public ElectricNodeBase {
	
	
public:
	typedef ElectricNode CLASSNAME;
	ElectricNode();
	
	RTTI_DECL1(ElectricNode, ElectricNodeBase);
	
};


using ENode = ElectricNode;



#endif
