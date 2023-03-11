#ifndef _ProtoVM_Link_h_
#define _ProtoVM_Link_h_

NAMESPACE_TOPSIDE_BEGIN


struct Link {
	Link* to = 0;
	ElectricNodeBase::Connector* sink = 0;
	ElectricNodeBase::Connector* src = 0;
	int layer = -1;
	
	typedef Link CLASSNAME;
	Link();
	bool operator()(const Link& a, const Link& b) const;
	
	String ToString() const;
	
};

struct ProcessOp : Moveable<ProcessOp> {
	
	ProcessType type = INVALID;
	Link* link = 0;
	ElectricNodeBase* processor = 0;
	ElectricNodeBase* dest = 0;
	uint16 id = 0;
	uint16 dest_id = 0;
	int mem_bits = 0;
	int mem_bytes = 0;
	//int mem_id = -1;
	
};

struct LinkMap {
	Array<Link> links;
	Array<ProcessOp> init_ops, rt_ops;
	
	
	void UpdateLinkLayers();
	void UpdateProcess();
	void GetLayerRange(const ElectricNodeBase& n, int& min, int& max);
	
};


NAMESPACE_TOPSIDE_END

#endif
