#ifndef _EonBaseGen_Link_h_
#define _EonBaseGen_Link_h_

NAMESPACE_EONGEN_BEGIN


class Unit;
class Node;



class Link {
public:
	typedef enum {
		INVALID,
		
		// Unit to Unit
		BASE_UNIT,
		BASE_SRC_TO_SINK,
		BASE_SIDE_TO_SIDE,
		
		// Node to Unit
		LOOP_UNIT,
		
		// Node to Node
		NODE_LINK,
		CHAIN_LOOP,
		VALID_NODE_LINK,
		MACHINE_TOPCHAIN,
		SYSTEM_MACHINE,
		
	} Type;
	
	
	Type		type = INVALID;
	union {
		Unit*		from_unit;
		Node*		from_node;
	};
	union {
		Unit*		to_unit;
		Node*		to_node;
	};
	
	
};



NAMESPACE_EONGEN_END

#endif
