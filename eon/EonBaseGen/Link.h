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
		
		// Node to Unit
		LOOP_UNIT,
		
		// Node to Node
		NODE_LINK,
		CHAIN_LOOP,
		VALID_NODE_LINK,
		
	} Type;
	
	
	Type		type = INVALID;
	union {
		Unit*		from_unit;
		Node*	from_node;
	};
	union {
		Unit*		to_unit;
		Node*	to_node;
	};
	
	
};



NAMESPACE_EONGEN_END

#endif
