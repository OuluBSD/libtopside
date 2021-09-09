#ifndef _SerialMach_Types_h_
#define _SerialMach_Types_h_

#define COPY_PANIC(T) void operator=(const T& t) {Panic("Can't copy " #T);}

#define SERIAL_TYPE_LIST \
	SERIAL_TYPE(LOOP_STORE) \
	SERIAL_TYPE(REGISTRY_SYSTEM) \
	SERIAL_TYPE(ATOM_STORE) \
	SERIAL_TYPE(ATOM_SYSTEM) \
	\
	SERIAL_TYPE(CUSTOM_ATOM) \
	\
	SERIAL_TYPE(DUMMY_SERIAL_TYPE) \
	

#define SERIAL_BASE_LIST \
	SERIAL_BASE(DUMMY_SERIAL_BASE) \


#define IFACE_LIST \
	IFACE(AUDIO) \
	IFACE(VIDEO) \
	IFACE(MIDI) \
	IFACE(EVENT) \
	IFACE(DATA) \
	IFACE(ORDER) \
	IFACE(RECEIPT) \


#define DEV_IFACE(val) \
	IFACE_CTX_CLS(CENTER, val, ) \
	IFACE_CTX_CLS(PERMA, val, Perma) \
	IFACE_CTX_CLS(ACCEL, val, Accel) \
	IFACE_CTX_CLS(NET, val, Net) \


NAMESPACE_SERIAL_BEGIN

typedef dword PacketId;
typedef dword LoopId;
typedef dword AtomId;


class AtomBase;
class AtomStore;
class AtomSystem;
class SoundSample;
class Loop;
class LoopStore;
class Machine;
//class CenterCustomer;
struct AtomTypeCls;



template <class T>
using RefT_Loop				= Ref<T,					RefParent1<Loop>>;

template <class T>
using RefT_Machine			= Ref<T,					RefParent1<Machine>>;

template<class T, class Parent = RefParent1<typename T::Parent>>
using RefAtomTypeMapIndirect	= RefLinkedMapIndirect<AtomTypeCls, T, Parent>;


using LoopParent			= RefParent2<LoopStore,		Loop>;
using AtomParent			= RefParent1<Loop>;
using LoopRef				= Ref<Loop,					LoopParent>;
using LoopStoreRef			= Ref<LoopStore,			RefParent1<Machine>>;
using AtomBaseRef			= Ref<AtomBase,				RefParent1<Loop>>;
using AtomStoreRef			= Ref<AtomStore,			RefParent1<Machine>>;
using AtomSystemRef			= Ref<AtomSystem,			RefParent1<Machine>>;
//using CenterCustomerRef		= Ref<CenterCustomer,			AtomParent>;

using LoopVec				= RefLinkedList<Loop,		LoopParent>;


typedef enum {
	SIDE_NOT_ACCEPTED,
	SIDE_ACCEPTED,
	SIDE_ACCEPTED_MULTI,
} SideStatus;

#undef INVALID_ATOM

typedef enum : byte {
	INVALID_ATOM,
	
	#define ATOM_TYPE(x) x,
	ATOM_TYPE_LIST
	#undef ATOM_TYPE
	
	#define SERIAL_TYPE(x) x,
	SERIAL_TYPE_LIST
	#undef SERIAL_TYPE
	
	SUBCOMP_COUNT
} SubAtomCls;

typedef enum : byte {
	INVALID_ROLE,
	
	CUSTOMER,
	SOURCE,
	SINK,
	CONVERTER,
	PIPE,
	SIDE_SOURCE,
	SIDE_SINK,
	SIDE_PIPE,
	
	ROLE_COUNT
} AtomRole;


struct ValCls : Moveable<ValCls> {
	typedef enum : byte {
		INVALID,
		#define IFACE(x) x,
		IFACE_LIST
		#undef IFACE
		
		TYPE_COUNT,
		
		Audio = AUDIO,
		Video = VIDEO,
		Midi = MIDI,
		Event = EVENT,
		Data = DATA,
		Order = ORDER,
		Receipt = RECEIPT,
	} Type;
	
	Type type = INVALID;
	
	
	ValCls() {}
	ValCls(Type t) : type(t) {}
	ValCls(const ValCls& v) : type(v.type) {}
	void Clear() {type = INVALID;}
	String GetName() const {return GetName(type);}
	String GetActionName() const {return ToLower(GetName());}
	bool IsValid() const {return type > INVALID && type < TYPE_COUNT;}
	static String GetName(Type t);
	static Type Get(String s);
	void operator=(const Nuller& n) {type = INVALID;}
	void operator=(const ValCls& n) {type = n.type;}
	bool operator==(const ValCls& c) const {return type == c.type;}
	bool operator!=(const ValCls& c) const {return type != c.type;}
	//operator bool() const {return IsValid();}
	hash_t GetHashValue() const {return (int)type;}
};

struct DevCls : Moveable<DevCls> {
	typedef enum : byte {
		INVALID,
		CENTER,
		PERMA,
		ACCEL,
		NET,
		
		TYPE_COUNT,
		
		Center = CENTER,
		Perma = PERMA,
		Accel = ACCEL,
		Net = NET,
	} Type;
	
	Type type = INVALID;
	
	
	DevCls() {}
	DevCls(Type t) : type(t) {}
	DevCls(const DevCls& v) : type(v.type) {}
	String GetName() const {return GetName(type);}
	String GetActionName() const {return ToLower(GetName());}
	void Clear() {type = INVALID;}
	bool IsValid() const {return type > INVALID && type < TYPE_COUNT;}
	static String GetName(Type t);
	static Type Get(String s);
	void operator=(const Nuller& n) {type = INVALID;}
	void operator=(const DevCls& n) {type = n.type;}
	bool operator==(const DevCls& c) const {return type == c.type;}
	bool operator!=(const DevCls& c) const {return type != c.type;}
	//operator bool() const {return IsValid();}
	hash_t GetHashValue() const {return (int)type;}
};

struct ValDevCls : Moveable<ValDevCls> {
	ValCls	val;
	DevCls	dev;
	
	
	ValDevCls() {}
	ValDevCls(DevCls::Type d, ValCls::Type v) : val(v), dev(d) {}
	ValDevCls(ValCls::Type v, DevCls::Type d) : val(v), dev(d) {}
	ValDevCls(const DevCls& d, const ValCls& v) : val(v), dev(d) {}
	ValDevCls(const ValDevCls& v) : val(v.val), dev(v.dev) {}
	void Clear() {val.Clear(); dev.Clear();}
	bool IsValid() const {return val.IsValid() && dev.IsValid();}
	String GetName() const {return dev.GetName() + "." + val.GetName();}
	void operator=(const Nuller& n) {val = n; dev = n;}
	void operator=(const ValDevCls& n) {val = n.val; dev = n.dev;}
	bool operator==(const ValDevCls& c) const {return val == c.val && dev == c.dev;}
	bool operator!=(const ValDevCls& c) const {return val != c.val || dev != c.dev;}
	//operator bool() const {return IsValid();}
	hash_t GetHashValue() const {return (int)dev.type * (int)ValCls::TYPE_COUNT + (int)val.type;}
	String ToString() const {return dev.GetName() + "-" + val.GetName();}
	String GetActionName() const {return ToLower(dev.GetName()) + "." + ToLower(val.GetName());}
};

#define VD(dev, val) Serial::ValDevCls(Serial::DevCls::dev, Serial::ValCls::val)

#define ATOM0(atom, role, sink_dev, sink_val, src_dev, src_val) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sink_dev, sink_val), VD(src_dev, src_val))

#define ATOM1(atom, role, sink_dev, sink_val, side_dev, side_val, src_dev, src_val) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sink_dev, sink_val), VD(side_dev, side_val), VD(src_dev, src_val))


struct AtomCls : Moveable<AtomCls> {
	ValDevCls sink, side, src;
	
	
	bool IsValid() const {return sink.IsValid() && src.IsValid() && side.IsValid();}
	
};




struct SerialTypeCls : Moveable<SerialTypeCls> {
	typedef enum : byte {
		INVALID,
		
		#define SERIAL_TYPE(x) x,
		SERIAL_TYPE_LIST
		#undef SERIAL_TYPE
		
		TYPE_COUNT
	} Type;
	
	ValDevCls		vd;
	Type			type = INVALID;
	
	SerialTypeCls() {}
	SerialTypeCls(ValDevCls vd, Type t) : vd(vd), type(t) {ASSERT(IsValid());}
	SerialTypeCls(const SerialTypeCls& c) : vd(c.vd), type(c.type) {}
	void Clear() {vd.Clear(); type = INVALID;}
	bool IsValid() const {return vd.IsValid() && type > INVALID && type < TYPE_COUNT;}
	void operator=(const Nuller& n) {vd = n;}
	void operator=(const SerialTypeCls& n) {vd = n.vd; type = n.type;}
	bool operator==(const SerialTypeCls& c) const {return vd == c.vd && type == c.type;}
	bool operator!=(const SerialTypeCls& c) const {return vd != c.vd || type != c.type;}
	//operator bool() const {return IsValid();}
	operator ValDevCls() const {return vd;}
	hash_t GetHashValue() const {return ((int)type * (int)DevCls::TYPE_COUNT + (int)vd.dev.type) * (int)ValCls::TYPE_COUNT + (int)vd.val.type;}
	String GetTypeString() const {return GetTypeString(type);}
	static String GetTypeString(Type t);
	String ToString() const {return GetTypeString() + "-" + vd.dev.GetName() + "-" + vd.val.GetName();}
	String GetActionName() const {return ToLower(vd.dev.GetName()) + "." + ToLower(vd.val.GetName());}
};


String GetSubAtomString(SubAtomCls t);
String GetAtomRoleString(AtomRole t);


struct AtomIfaceTypeCls : Moveable<AtomIfaceTypeCls> {
	ValDevCls	sink;
	ValDevCls	src;
	ValDevCls	side;
	
	
	bool IsValid() const {return sink.IsValid() && src.IsValid() /*&& side.IsValid()*/;}
	void operator=(const Nuller& n) {sink = n; src = n; side = n;}
	void operator=(const AtomIfaceTypeCls& o) {
		sink = o.sink;
		src = o.src;
		side = o.side;
	}
	hash_t GetHashValue() const;
	
	bool operator==(const AtomIfaceTypeCls& c) const {
		return	sink		== c.sink &&
				src			== c.src &&
				side		== c.side
				;
	}
	bool operator!=(const AtomIfaceTypeCls& c) const {return !(*this == c);}
	String ToString() const {return "(sink(" + sink.ToString() + "), side(" + side.ToString() + ", src(" + src.ToString() + ")";}
	
	
	AtomIfaceTypeCls() {}
	AtomIfaceTypeCls(const AtomIfaceTypeCls& c) {*this = c;}
	AtomIfaceTypeCls(ValDevCls sink, ValDevCls src) : sink(sink), src(src) {}
	AtomIfaceTypeCls(ValDevCls sink, ValDevCls side, ValDevCls src) : sink(sink), side(side), src(src) {}
	
	
};

struct AtomTypeCls : Moveable<AtomTypeCls> {
	AtomIfaceTypeCls iface;
	SubAtomCls sub = SubAtomCls::INVALID_ATOM;
	AtomRole role = AtomRole::INVALID_ROLE;
	
	bool IsValid() const {return iface.IsValid() && sub != SubAtomCls::INVALID_ATOM && role != AtomRole::INVALID_ROLE;}
	hash_t GetHashValue() const;
	void operator=(const Nuller& n) {iface = n; sub = SubAtomCls::INVALID_ATOM; role = AtomRole::INVALID_ROLE;}
	void operator=(const AtomTypeCls& o) {
		iface = o.iface;
		sub = o.sub;
		role = o.role;
	}
	
	bool operator==(const AtomTypeCls& c) const {
		return	iface == c.iface &&
				sub == c.sub &&
				role == c.role
				;
	}
	bool operator!=(const AtomTypeCls& c) const {return !(*this == c);}
	String ToString() const {return GetSubAtomString(sub) + "-" + GetAtomRoleString(role) + "-" + iface.ToString();}
	
	
	AtomTypeCls() {}
	AtomTypeCls(const AtomTypeCls& c) {*this = c;}
	AtomTypeCls(SubAtomCls cls, AtomRole role, ValDevCls sink, ValDevCls src) : iface(sink,src), sub(cls), role(role) {}
	AtomTypeCls(SubAtomCls cls, AtomRole role, ValDevCls sink, ValDevCls side, ValDevCls src) : iface(sink,side,src), sub(cls), role(role) {}
	
	bool IsRoleCustomer()	const {return role == AtomRole::CUSTOMER;}
	bool IsRoleSource()		const {return role == AtomRole::SOURCE;}
	bool IsRoleSink()		const {return role == AtomRole::SINK;}
	bool IsRoleConverter()	const {return role == AtomRole::CONVERTER;}
	bool IsRolePipe()		const {return role == AtomRole::PIPE;}
	bool IsRoleSideSource()	const {return role == AtomRole::SIDE_SOURCE/*iface.side.IsValid() && iface.side_src*/;}
	bool IsRoleSideSink()	const {return role == AtomRole::SIDE_SINK/*iface.side.IsValid() && !iface.side_src*/;}
	bool IsRoleSide()		const {return role == AtomRole::SIDE_SINK || role == AtomRole::SIDE_SOURCE/*iface.side.IsValid() && !iface.side_src*/;}
	
	bool IsMultiSideConnection() const {return false;}
	
};



template <class T> SerialTypeCls AsSerialTypeCls(ValDevCls vd) {
	SerialTypeCls c;
	c.vd = vd;
	c.type = T::GetSerialType();
	return c;
}

/*
template <class T> AtomTypeCls AsAtomTypeCls(SubAtomCls sub_type, CompCls vd) {
	AtomTypeCls c;
	c.sub = sub_type;
	c.side.vd.dev = vd.side.dev;
	c.side.vd.val = vd.side.val;
	c.side.type = T::GetSerialType();
	c.sink = vd.sink;
	c.src  = vd.src;
	return c;
}
*/

template <class T> AtomTypeCls AsAtomTypeCls() {return T::GetAtomType();}

DevCls GetCenterDevCls();





struct InternalPacketData : RTTIBase {
	RTTI_DECL0(InternalPacketData)
	
	int pos;
	int count;
	void* dev_comp;
	
	void ClearLinks() {dev_comp = 0;}
};


NAMESPACE_SERIAL_END

#endif
