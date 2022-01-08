#ifndef _SerialMach_Types_h_
#define _SerialMach_Types_h_

NAMESPACE_SERIAL_BEGIN


using ValCls = Parallel::ValCls;
using DevCls = Parallel::DevCls;
using ValDevCls = Parallel::ValDevCls;
using ValDevTuple = Parallel::ValDevTuple;
using Format = Parallel::Format;
using PacketId = Parallel::PacketId;
using TrackerInfo = Parallel::TrackerInfo;
using PacketValue = Parallel::PacketValue;
using Machine = Parallel::Machine;
using Packet = Parallel::Packet;
using SimpleValue = Parallel::SimpleValue;
using Value = Parallel::Value;
using AtomParent = Parallel::AtomParent;
using DefaultExchangePoint = Parallel::DefaultExchangePoint;
using SideStatus = Parallel::SideStatus;
using PacketIO = Parallel::PacketIO;
template <class T> using System = Parallel::System<T>;
template <class T> using RefT_Loop = Parallel::RefT_Loop<T>;

class AtomBase;

struct AtomTypeCls;


#undef INVALID_ATOM

typedef enum : byte {
	INVALID_ATOM,
	
	#define ATOM_TYPE(x) x,
	ATOM_TYPE_LIST
	
	#ifdef flagSCREEN
	flagSCREEN_ATOM_TYPE_LIST
	#endif
	
	#ifdef HAVE_OPENCV
	HAVE_OPENCV_ATOM_TYPE_LIST
	#endif
	
	#undef ATOM_TYPE
	
	#define SERIAL_TYPE(x) x,
	SERIAL_TYPE_LIST
	#undef SERIAL_TYPE
	
	SUBCOMP_COUNT
} SubAtomCls;


#define ATOM_ROLE_LIST \
	ATOM_ROLE(DRIVER) \
	ATOM_ROLE(CUSTOMER) \
	ATOM_ROLE(PIPE) \
	ATOM_ROLE(DRIVER_PIPE) \


typedef enum : int8 {
	INVALID_ROLE=-1,
	
	#define ATOM_ROLE(x) x,
	ATOM_ROLE_LIST
	#undef ATOM_ROLE
	
	ROLE_COUNT
} AtomRole;


String GetSubAtomString(SubAtomCls t);
String GetAtomRoleString(AtomRole t);




struct AtomIfaceTypeCls : Moveable<AtomIfaceTypeCls> {
	ValDevTuple		sink;
	ValDevTuple		src;
	ValDevCls		content;
	
	
	bool IsValid() const {return sink.IsValid() && src.IsValid() && content.IsValid();}
	void operator=(const Nuller& n) {sink = n; src = n; content = n;}
	void operator=(const AtomIfaceTypeCls& o) {
		sink = o.sink;
		src = o.src;
		content = o.content;
	}
	hash_t GetHashValue() const;
	
	bool operator==(const AtomIfaceTypeCls& c) const {
		return	sink		== c.sink &&
				src			== c.src &&
				content		== c.content
				;
	}
	bool operator!=(const AtomIfaceTypeCls& c) const {return !(*this == c);}
	String ToString() const {return "(sink(" + sink.ToString() + "), src(" + src.ToString() + ", content(" + content.ToString() + "))";}
	
	
	AtomIfaceTypeCls() {}
	AtomIfaceTypeCls(const AtomIfaceTypeCls& c) {*this = c;}
	AtomIfaceTypeCls(const ValDevTuple& sink, const ValDevTuple& src) : sink(sink), src(src) {}
	AtomIfaceTypeCls(const ValDevTuple& sink, ValDevCls content, const ValDevTuple& src) : sink(sink), src(src), content(content) {}
	//AtomIfaceTypeCls(ValDevCls sink, ValDevCls src) : sink(sink), src(src) {}
	
	void AddSink(const ValDevCls& vd) {sink.Add(vd);}
	void AddSource(const ValDevCls& vd) {src.Add(vd);}
	
};


struct AtomTypeCls : Moveable<AtomTypeCls> {
	AtomIfaceTypeCls iface;
	SubAtomCls sub = SubAtomCls::INVALID_ATOM;
	AtomRole role = AtomRole::INVALID_ROLE;
	byte user_sink_count = 0;
	byte user_src_count = 0;
	
	bool IsValid() const {return iface.IsValid() && sub != SubAtomCls::INVALID_ATOM && role != AtomRole::INVALID_ROLE;}
	hash_t GetHashValue() const;
	void operator=(const Nuller& n) {iface = n; sub = SubAtomCls::INVALID_ATOM; role = AtomRole::INVALID_ROLE; user_sink_count = 0; user_src_count = 0;}
	void operator=(const AtomTypeCls& o) {
		iface = o.iface;
		sub = o.sub;
		role = o.role;
		user_sink_count = o.user_sink_count;
		user_src_count = o.user_src_count;
	}
	
	bool operator==(const AtomTypeCls& c) const {
		return	iface == c.iface &&
				sub == c.sub &&
				role == c.role &&
				user_sink_count == c.user_sink_count &&
				user_src_count == c.user_src_count
				;
	}
	bool operator!=(const AtomTypeCls& c) const {return !(*this == c);}
	String ToString() const {return GetSubAtomString(sub) + "-" + GetAtomRoleString(role) + "-" + iface.ToString() + "-(" + IntStr(user_sink_count) + "," + IntStr(user_src_count) + ")";}
	
	
	AtomTypeCls() {}
	AtomTypeCls(const AtomTypeCls& c) {*this = c;}
	AtomTypeCls(SubAtomCls cls, AtomRole role, const ValDevCls& sink, const ValDevCls& src) : iface(sink,src), sub(cls), role(role) {}
	AtomTypeCls(SubAtomCls cls, AtomRole role, const ValDevTuple& sink, const ValDevTuple& src) : iface(sink,src), sub(cls), role(role) {}
	AtomTypeCls(SubAtomCls cls, AtomRole role, const ValDevCls& sink, const ValDevCls& content, const ValDevCls& src) : iface(sink,content,src), sub(cls), role(role) {}
	AtomTypeCls(
		SubAtomCls cls, AtomRole role,
		const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0,
		int side_sinks, int side_srcs, int user_sinks, int user_srcs,
		const ValDevCls& si1,
		const ValDevCls& sr1
	);
	AtomTypeCls(
		SubAtomCls cls, AtomRole role,
		const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0,
		int side_sinks, int side_srcs, int user_sinks, int user_srcs,
		const ValDevCls& si1, const ValDevCls& si2,
		const ValDevCls& sr1, const ValDevCls& sr2
	);
	AtomTypeCls(
		SubAtomCls cls, AtomRole role,
		const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0,
		int side_sinks, int side_srcs, int user_sinks, int user_srcs,
		const ValDevCls& si1, const ValDevCls& si2, const ValDevCls& si3,
		const ValDevCls& sr1, const ValDevCls& sr2, const ValDevCls& sr3
	);
	AtomTypeCls(
		SubAtomCls cls, AtomRole role,
		const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0,
		int side_sinks, int side_srcs, int user_sinks, int user_srcs,
		const ValDevCls& si1, const ValDevCls& si2, const ValDevCls& si3, const ValDevCls& si4,
		const ValDevCls& sr1, const ValDevCls& sr2, const ValDevCls& sr3, const ValDevCls& sr4
	);
	
	bool IsRoleDriver()		const {return role == AtomRole::DRIVER;}
	bool IsRoleCustomer()	const {return role == AtomRole::CUSTOMER;}
	bool IsRolePipe()		const {return role == AtomRole::PIPE;}
	bool HasSideChannels()	const {return iface.sink.count > 1 || iface.src.count > 1;}
	
	bool IsSourceChannelOptional(int ch_i) const;
	bool IsSinkChannelOptional(int ch_i) const;
	
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


template <class T> SerialTypeCls AsSerialTypeCls(ValDevCls vd) {
	SerialTypeCls c;
	c.vd = vd;
	c.type = T::GetSerialType();
	return c;
}


template <class T> AtomTypeCls AsAtomTypeCls() {return T::GetAtomType();}





template<class T, class Parent = RefParent1<typename T::Parent>>
using RefAtomTypeMapIndirect	= RefLinkedMapIndirect<AtomTypeCls, T, Parent>;





struct IfaceConnLink {
	int conn = -1;
	int local = -1;
	int other = -1;
	
	String ToString() const {String s; s << "conn:" << conn << ", local:" << local << ", other:" << other; return s;}
};

struct IfaceConnTuple {
	IfaceConnLink		sink	[MAX_VDTUPLE_SIZE];
	IfaceConnLink		src		[MAX_VDTUPLE_SIZE];
	AtomTypeCls			type;
	
	void Realize(const AtomTypeCls& type);
	void SetSource(int conn, int src_ch, int sink_ch);
	void SetSink(int conn, int sink_ch, int src_ch);
	bool IsComplete() const;
	dword GetSinkMask() const;
};


NAMESPACE_SERIAL_END

#endif
