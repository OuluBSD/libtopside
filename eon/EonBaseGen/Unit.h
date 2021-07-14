#ifndef _EonBaseGen_Unit_h_
#define _EonBaseGen_Unit_h_

NAMESPACE_EONGEN_BEGIN


class Unit {
	
public:
	typedef enum {
		INVALID,
		BASE,
		HEADER,
		IMPL,
	} Type;
	
protected:
	friend class World;
	Vector<Link*>		links;
	String				key;
	ValDevCls			sink;
	ValDevCls			src;
	DevCls				side_dev;
	bool				side_src;
	Type				type = INVALID;
	byte				sink_count;
	byte				src_count;
	
};



NAMESPACE_EONGEN_END

#endif
