#ifndef _ProtoVM_Common_h_
#define _ProtoVM_Common_h_



class Pcb;
struct Link;

class ElectricNodeBase : RTTIBase {
	
	
public:
	typedef enum {
		V_WHOLE,
		V_PARTIAL,
		V_PARTIAL_RANGE,
	} Type;
	
	struct Connector;
	
	struct CLink : Moveable<CLink> {
		Connector* conn = 0;
		Link* link = 0;
	};
	
	struct Connector : Moveable<Connector> {
		String name;
		bool is_sink = false;
		bool is_src = false;
		bool accept_multiconn = false;
		bool required = true;
		 
		Vector<CLink> links;
		ElectricNodeBase* base = 0;
		
		bool IsConnected() const {return !links.IsEmpty();}
		bool IsRequired() const {return required;}
		bool IsConnectable() const {return links.IsEmpty() || accept_multiconn;}
		void SetMultiConn() {accept_multiconn = true;}
		void SetRequired(bool b=true) {required = b;}
	};
	
	
protected:
	friend class Pcb;
	friend class LinkMap;
	
	Pcb* pcb = 0;
	ElectricNodeBase* ptr = 0;
	int ptr_i = -1;
	int ptr_n = 0;
	Connector* ptr_conn = 0;
	String name;
	Array<Connector> conns;
	Type type = V_WHOLE;
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
	
	void Clear();
	ElectricNodeBase& SetName(String s);
	ElectricNodeBase& NotRequired(String s);
	
	bool IsEmpty() const;
	bool IsTrivialSourceDefault() const;
	bool IsTrivialSourceDefaultRange() const;
	bool IsTrivialSinkDefault() const;
	bool IsTrivialSinkDefaultRange() const;
	int GetPinWidth() const;
	Connector& Get(int i);
	Connector& GetTrivialSource();
	Connector& GetTrivialSink();
	String GetName() const {return name;}
	
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
