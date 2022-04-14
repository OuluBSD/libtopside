#ifndef _ProtoVM_Link_h_
#define _ProtoVM_Link_h_


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

struct LinkMap {
	Array<Link> links;
	
	
	void UpdateLinkLayers();
	void GetLayerRange(const ElectricNodeBase& n, int& min, int& max);
	
};


#endif
