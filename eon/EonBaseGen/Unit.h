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
	Type				type = INVALID;
	uint16				id;
	uint16				smallest_link_id = 0xffff;
	
	ValDevCls			sink;
	ValDevCls			src;
	ValDevCls			side;
	bool				side_src;
	bool				accept_side;
	byte				sink_count;
	byte				src_count;
	byte				side_count;
	
	String				dbg_file;
	
	void CopyType(const Unit& u) {
		sink = u.sink;
		src = u.src;
		side = u.side;
		side_src = u.side_src;
		accept_side = u.accept_side;
		sink_count = u.sink_count;
		src_count = u.src_count;
		side_count = u.side_count;
		dbg_file = u.dbg_file;
	}
};



NAMESPACE_EONGEN_END

#endif
