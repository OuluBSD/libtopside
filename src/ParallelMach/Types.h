#ifndef _ParallelMach_Types_h_
#define _ParallelMach_Types_h_

#define COPY_PANIC(T) void operator=(const T& t) {Panic("Can't copy " #T);}

#define PARALLEL_BASE_LIST \
	PARALLEL_BASE(DUMMY_PARALLEL_BASE) \


#define IFACE_LIST \
	IFACE(AUDIO) \
	IFACE(VIDEO) \
	IFACE(VOLUME) \
	IFACE(MIDI) \
	IFACE(EVENT) \
	IFACE(DATA) \
	IFACE(ORDER) \
	IFACE(RECEIPT) \
	IFACE(FBO) \
	IFACE(PROG) \


#define DEV_IFACE(val) \
	IFACE_CTX_CLS(CENTER, val, ) \
	IFACE_CTX_CLS(NET, val, Net) \
	IFACE_CTX_CLS(OGL, val, Ogl) \

#define SERIAL_TYPE_LIST \
	SERIAL_TYPE(LOOP_STORE) \
	SERIAL_TYPE(LOOP_SYSTEM) \
	SERIAL_TYPE(REGISTRY_SYSTEM) \
	SERIAL_TYPE(ENTITY_SYSTEM) \
	SERIAL_TYPE(ATOM_STORE) \
	SERIAL_TYPE(ATOM_SYSTEM) \
	SERIAL_TYPE(SCRIPT_LOADER_SYSTEM) \
	\
	SERIAL_TYPE(CUSTOM_ATOM) \
	\
	SERIAL_TYPE(DUMMY_SERIAL_TYPE) \


NAMESPACE_PARALLEL_BEGIN

typedef dword PacketId;
typedef dword SpaceId;
typedef dword AtomId;


class AtomBase;
class AtomStore;
class AtomSystem;
class SoundSample;
class Machine;


using ParallelSystemParent	= MetaSystemParent;
using AtomParent			= ExchangeBaseParent;


template <class T>
using RefT_Machine			= Ref<T,					ParallelSystemParent>;
using AtomBaseRef			= Ref<AtomBase,				AtomParent>;
using AtomStoreRef			= Ref<AtomStore,			ParallelSystemParent>;
using AtomSystemRef			= Ref<AtomSystem,			ParallelSystemParent>;

using StateVec				= RefLinkedList<EnvState,	EnvStateParent>;

template <class T> using RefT_Atom = Ref<T, AtomParent>;

typedef enum {
	SIDE_NOT_ACCEPTED,
	SIDE_ACCEPTED,
} SideStatus;







struct ValCls : Moveable<ValCls> {
	typedef enum : byte {
		INVALID,
		#define IFACE(x) x,
		IFACE_LIST
		#undef IFACE
		
		TYPE_COUNT,
		
		Audio = AUDIO,
		Video = VIDEO,
		Volume = VOLUME,
		Midi = MIDI,
		Event = EVENT,
		Data = DATA,
		Order = ORDER,
		Receipt = RECEIPT,
		Fbo = FBO,
		Prog = PROG,
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
	hash_t GetHashValue() const {return (int)type;}
};

struct DevCls : Moveable<DevCls> {
	typedef enum : byte {
		INVALID,
		CENTER,
		PERMA,
		NET,
		OGL,
		
		TYPE_COUNT,
		
		Center = CENTER,
		Perma = PERMA,
		Net = NET,
		Ogl = OGL,
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
	hash_t GetHashValue() const {return (int)dev.type * (int)ValCls::TYPE_COUNT + (int)val.type;}
	String ToString() const {return dev.GetName() + "-" + val.GetName();}
	String GetActionName() const {return ToLower(dev.GetName()) + "." + ToLower(val.GetName());}
};

#define VD(dev, val) Parallel::ValDevCls(Parallel::DevCls::dev, Parallel::ValCls::val)



struct AtomCls : Moveable<AtomCls> {
	ValDevCls sink, side, src;
	
	
	bool IsValid() const {return sink.IsValid() && src.IsValid() && side.IsValid();}
	
};






struct ValDevTuple : Moveable<ValDevTuple> {
	
	struct Channel : Moveable<Channel> {
		ValDevCls vd;
		bool is_opt = false;
		
		void Set(ValDevCls vd, bool is_opt) {this->vd = vd; this->is_opt = is_opt;}
		String ToString() const {return vd.ToString() + (is_opt ? " optional" : "");}
		bool IsValid() const {return vd.IsValid();}
		bool operator==(const Channel& c) const {return vd == c.vd && is_opt == c.is_opt;}
		bool operator!=(const Channel& c) const {return !(*this == c);}
		hash_t GetHashValue() const {CombineHash c; c.Put(vd.GetHashValue()); c.Put((int)is_opt); return c;}
	};
	Vector<Channel> channels;
	
	
	ValDevTuple() {}
	ValDevTuple(const ValDevCls& v) {Add(v,false);}
	ValDevTuple(const ValDevTuple& v) {*this = v;}
	
	
	
	int GetCount() const {return channels.GetCount();}
	
	
	Channel&       operator[](int i)       {return channels[i];}
	const Channel& operator[](int i) const {return channels[i];}
	
	
	ValDevTuple& Add(const ValDevCls& o, bool is_opt) {channels.Add().Set(o,is_opt); return *this;}
	
	String ToString() const {
		int count = channels.GetCount();
		String s;
		s << "(" << (int)count;
		for(int i = 0; i < count; i++)
			s << ", " << channels[i].ToString();
		s << ")";
		return s;
	}
	
	bool IsValid() const {
		int count = channels.GetCount();
		for(int i = 0; i < count; i++)
			if (!channels[i].IsValid())
				return false;
		return true;
	}
	
	void operator=(const Nuller& n) {memset(this, 0, sizeof(ValDevTuple));}
	void operator=(const ValDevTuple& o) {
		channels <<= o.channels;
	}
	
	bool operator==(const ValDevTuple& o) const {
		if (channels.GetCount() != o.channels.GetCount())
			return false;
		for(int i = 0; i < channels.GetCount(); i++)
			if (channels[i] != o.channels[i])
				return false;
		return true;
	}
	
	bool operator!=(const ValDevTuple& o) const {return !operator==(o);}
	
	hash_t GetHashValue() const {
		int count = channels.GetCount();
		CombineHash ch;
		ch.Put(count);
		for(int i = 0; i < count; i++)
			ch.Put(channels[i].GetHashValue());
		return ch;
	}
	
};




DevCls GetCenterDevCls();





#undef INVALID_ATOM

typedef enum : byte {
	INVALID_ATOM,
	
	#define ATOM_TYPE(x) x,
	
	#define GEN_ATOM_TYPE_LIST
	#include "GenAtom.inl"
	#undef GEN_ATOM_TYPE_LIST
	
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
	
	
	bool IsValid() const {return sink.IsValid() && src.IsValid();}
	void operator=(const Nuller& n) {sink = n; src = n;}
	void operator=(const AtomIfaceTypeCls& o) {
		sink = o.sink;
		src = o.src;
	}
	hash_t GetHashValue() const;
	
	bool operator==(const AtomIfaceTypeCls& c) const {
		return	sink		== c.sink &&
				src			== c.src
				;
	}
	bool operator!=(const AtomIfaceTypeCls& c) const {return !(*this == c);}
	String ToString() const {return "(sink(" + sink.ToString() + "), src(" + src.ToString() + ")";}
	
	
	AtomIfaceTypeCls() {}
	AtomIfaceTypeCls(const AtomIfaceTypeCls& c) {*this = c;}
	AtomIfaceTypeCls(const ValDevTuple& sink, const ValDevTuple& src) : sink(sink), src(src) {}
	
	void AddSink(const ValDevCls& vd, bool is_opt) {sink.Add(vd, is_opt);}
	void AddSource(const ValDevCls& vd, bool is_opt) {src.Add(vd, is_opt);}
	
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
	AtomTypeCls(SubAtomCls cls, AtomRole role, const ValDevCls& sink, const ValDevCls& src) : iface(sink,src), sub(cls), role(role) {}
	AtomTypeCls(SubAtomCls cls, AtomRole role, const ValDevTuple& sink, const ValDevTuple& src) : iface(sink,src), sub(cls), role(role) {}
	
	void AddIn(ValDevCls vd, bool is_opt);
	void AddOut(ValDevCls vd, bool is_opt);
	
	bool IsRoleDriver()		const {return role == AtomRole::DRIVER;}
	bool IsRoleCustomer()	const {return role == AtomRole::CUSTOMER;}
	bool IsRolePipe()		const {return role == AtomRole::PIPE;}
	
	bool IsSourceChannelOptional(int ch_i) const;
	bool IsSinkChannelOptional(int ch_i) const;
	
};



struct IfaceConnLink : Moveable<IfaceConnLink> {
	int conn = -1;
	int local = -1;
	int other = -1;
	
	void Set(int conn, int local, int other) {this->conn = conn; this->local = local; this->other = other;}
	String ToString() const {String s; s << "conn:" << conn << ", local:" << local << ", other:" << other; return s;}
};

struct IfaceConnTuple {
	Vector<IfaceConnLink>		sink;
	Vector<IfaceConnLink>		src;
	AtomTypeCls					type;
	
	void Realize(const AtomTypeCls& type);
	void SetSource(int conn, int src_ch, int sink_ch);
	void SetSink(int conn, int sink_ch, int src_ch);
	bool IsComplete() const;
	dword GetSinkMask() const;
	void operator=(const IfaceConnTuple& s) {
		sink <<= s.sink;
		src <<= s.src;
		type = s.type;
	}
	
	bool HasCommonConnection(const IfaceConnTuple& src) const;
	
};



struct ParallelTypeCls : Moveable<ParallelTypeCls> {
	typedef enum : byte {
		INVALID,
		
		#define SERIAL_TYPE(x) x,
		SERIAL_TYPE_LIST
		#undef SERIAL_TYPE
		
		TYPE_COUNT
	} Type;
	
	ValDevCls		vd;
	Type			type = INVALID;
	
	ParallelTypeCls() {}
	ParallelTypeCls(ValDevCls vd, Type t) : vd(vd), type(t) {ASSERT(IsValid());}
	ParallelTypeCls(const ParallelTypeCls& c) : vd(c.vd), type(c.type) {}
	void Clear() {vd.Clear(); type = INVALID;}
	bool IsValid() const {return vd.IsValid() && type > INVALID && type < TYPE_COUNT;}
	void operator=(const Nuller& n) {vd = n;}
	void operator=(const ParallelTypeCls& n) {vd = n.vd; type = n.type;}
	bool operator==(const ParallelTypeCls& c) const {return vd == c.vd && type == c.type;}
	bool operator!=(const ParallelTypeCls& c) const {return vd != c.vd || type != c.type;}
	operator ValDevCls() const {return vd;}
	hash_t GetHashValue() const {return ((int)type * (int)DevCls::TYPE_COUNT + (int)vd.dev.type) * (int)ValCls::TYPE_COUNT + (int)vd.val.type;}
	String GetTypeString() const {return GetTypeString(type);}
	static String GetTypeString(Type t);
	String ToString() const {return GetTypeString() + "-" + vd.dev.GetName() + "-" + vd.val.GetName();}
	String GetActionName() const {return ToLower(vd.dev.GetName()) + "." + ToLower(vd.val.GetName());}
};


template <class T> ParallelTypeCls AsParallelTypeCls(ValDevCls vd) {
	ParallelTypeCls c;
	c.vd = vd;
	c.type = T::GetSerialType();
	return c;
}


template <class T> AtomTypeCls AsAtomTypeCls() {return T::GetAtomType();}

template<class T, class Parent = RefParent1<typename T::Parent>>
using RefAtomTypeMapIndirect	= RefLinkedMapIndirect<AtomTypeCls, T, Parent>;



typedef void (*DataCallbackFn)(void*, char* data, int size);



namespace FboKbd {

static const int key_tex_w = 256;
static const int key_tex_h = 1;//256;
typedef FixedArray<byte, 256> KeyVec;

}

NAMESPACE_PARALLEL_END


#endif
