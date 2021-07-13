#ifndef _EonBaseGen_Unit_h_
#define _EonBaseGen_Unit_h_

NAMESPACE_EONGEN_BEGIN


class Unit {
	
protected:
	friend class World;
	Vector<UnitLink*>	links;
	String				key;
	ValDevCls			sink;
	ValDevCls			src;
	bool				side_src;
	
};



NAMESPACE_EONGEN_END

#endif
