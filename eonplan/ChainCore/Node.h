#ifndef _ChainCore_Node_h_
#define _ChainCore_Node_h_


class Node {
	Node*		parent = 0;
	
public:
	
	
	void SetParent(Node* n) {ASSERT(!parent || !n); parent = n;}
	
	void Dump();
	
	
	virtual void Serialize(EonStream& s) = 0;
	
};


#endif
