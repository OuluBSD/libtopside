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
	IFACE_CTX_CLS(PERMA, val, Perma) \
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
//class CenterCustomer;


using ParallelSystemParent	= MetaSystemParent;
using AtomParent			= ExchangeBaseParent;


//template <class T>
//using RefT_Space				= Ref<T,					SpaceParent>;

template <class T>
using RefT_Machine			= Ref<T,					ParallelSystemParent>;


//using SpaceParent			= RefParent2<SpaceStore, Space>;
//using AtomParent			= AtomParent;
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

#define VD(dev, val) Parallel::ValDevCls(Parallel::DevCls::dev, Parallel::ValCls::val)

#define ATOM11(atom, role, content_dev, content_val, sid0, siv0, srd0, srv0 ) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0 ))

#define ATOM12(atom, role, content_dev, content_val, sid0, siv0, srd0, srv0, srd1, srv1) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0), 0,1,0,0, ValDevCls(), VD(srd1, srv1))

#define ATOM21(atom, role, content_dev, content_val, sid0, siv0, sid1, siv1, srd0, srv0 ) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0 ), 1,0,0,0, VD(sid1, siv1), ValDevCls())

#define ATOM11_U10(atom, role, content_dev, content_val, sid0, siv0, sid1, siv1, srd0, srv0 ) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0 ), 1,0,1,0, VD(sid1, siv1), ValDevCls())

#define ATOM11_U20(atom, role, content_dev, content_val, sid0, siv0, sid1, siv1, sid2, siv2,srd0, srv0) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0), 2,0,2,0, VD(sid1, siv1), VD(sid2, siv2), ValDevCls(), ValDevCls())

#define ATOM11_U01(atom, role, content_dev, content_val, sid0, siv0, srd0, srv0 , srd1, srv1) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0 ), 0,1,0,1, ValDevCls(), VD(srd1, srv1))

#define ATOM11_U02(atom, role, content_dev, content_val, sid0, siv0, srd0, srv0, srd1, srv1, srd2, srv2) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0), 0,1,0,1, ValDevCls(), ValDevCls(), VD(srd1, srv1), VD(srd2, srv2))

#define ATOM11_U04(atom, role, content_dev, content_val, sid0, siv0, srd0, srv0, srd1, srv1, srd2, srv2, srd3, srv3, srd4, srv4) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0), 0,4,0,4, ValDevCls(), ValDevCls(), ValDevCls(), ValDevCls(), VD(srd1, srv1), VD(srd2, srv2), VD(srd3, srv3), VD(srd4, srv4))

#define ATOM11_U11(atom, role, content_dev, content_val, sid0, siv0, sid1, siv1, srd0, srv0 , srd1, srv1) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0 ), 1,1,1,1, VD(sid1, siv1), VD(srd1, srv1))

#define ATOM11_U44(atom, role, content_dev, content_val, sid0, siv0, sid1, siv1, sid2, siv2, sid3, siv3, sid4, siv4, srd0, srv0, srd1, srv1, srd2, srv2, srd3, srv3, srd4, srv4) \
	AtomTypeCls(SubAtomCls::atom, AtomRole::role, VD(sid0, siv0), VD(content_dev, content_val), VD(srd0, srv0), 4,4,4,4, VD(sid1, siv1), VD(sid2, siv2), VD(sid3, siv3), VD(sid4, siv4), VD(srd1, srv1), VD(srd2, srv2), VD(srd3, srv3), VD(srd4, srv4))


struct AtomCls : Moveable<AtomCls> {
	ValDevCls sink, side, src;
	
	
	bool IsValid() const {return sink.IsValid() && src.IsValid() && side.IsValid();}
	
};






struct ValDevTuple : Moveable<ValDevTuple> {
	static const int MAX_VDS = MAX_VDTUPLE_SIZE;
	
	ValDevCls	vd[MAX_VDS];
	byte		count = 0;
	
	
	ValDevTuple() : count(0) {}
	ValDevTuple(const ValDevCls& v) : count(1) {vd[0] = v;}
	ValDevTuple(const ValDevTuple& v) : count(0) {*this = v;}
	
	
	
	int GetCount() const {return count;}
	
	
	ValDevCls&       operator[](int i)       {ASSERT(i >= 0 && i < count && count <= MAX_VDS); return vd[i];}
	const ValDevCls& operator[](int i) const {ASSERT(i >= 0 && i < count && count <= MAX_VDS); return vd[i];}
	ValDevCls&       operator()()            {ASSERT(count >= 1); return vd[0];}
	const ValDevCls& operator()() const      {ASSERT(count >= 1); return vd[0];}
	
	
	
	ValDevCls GetCommon(const ValDevTuple& o) const {
		for(int i = 0; i < MAX_VDS; i++) {
			const ValDevCls& a = vd[i];
			for(int j = 0; j < MAX_VDS; j++) {
				const ValDevCls& b = o.vd[i];
				if (a == b)
					return a;
			}
		}
		return ValDevCls();
	}
	
	ValDevTuple& Add(const ValDevCls& o) {ASSERT(count < MAX_VDS); vd[count] = o; count++; return *this;}
	
	String ToString() const {
		String s;
		s << "(" << (int)count;
		for(int i = 0; i < count; i++)
			s << ", " << vd[i].ToString();
		s << ")";
		return s;
	}
	
	bool IsValid() const {
		if (count <= 0 || count > MAX_VDS)
			return false;
		for(int i = 0; i < count; i++)
			if (!vd[i].IsValid())
				return false;
		return true;
	}
	
	void operator=(const Nuller& n) {memset(this, 0, sizeof(ValDevTuple));}
	void operator=(const ValDevTuple& o) {
		count = o.count;
		ASSERT(count >= 0 && count <= MAX_VDS);
		for(int i = 0; i < count; i++)
			vd[i] = o.vd[i];
	}
	
	bool operator==(const ValDevTuple& o) const {
		if (count != o.count)
			return false;
		ASSERT(count >= 0 && count <= MAX_VDS);
		for(int i = 0; i < count; i++)
			if (vd[i] != o.vd[i])
				return false;
		return true;
	}
	
	bool operator!=(const ValDevTuple& o) const {return !operator==(o);}
	
	hash_t GetHashValue() const {
		ASSERT(count >= 0 && count <= MAX_VDS);
		CombineHash ch;
		ch.Put(count);
		for(int i = 0; i < count; i++)
			ch.Put(vd[i].GetHashValue());
		return ch;
	}
	
};




DevCls GetCenterDevCls();




#undef INVALID_ATOM

typedef enum : byte {
	INVALID_ATOM,
	
	#define ATOM_TYPE(x) x,
	ATOM_TYPE_LIST
	
	#ifdef flagSCREEN
	flagSCREEN_ATOM_TYPE_LIST
	#endif
	
	#ifdef flagOPENCV
	flagOPENCV_ATOM_TYPE_LIST
	#endif
	
	#ifdef flagLINUX
	flagLINUX_ATOM_TYPE_LIST
	#endif
	
	#ifdef flagSDL2
	flagSDL2_ATOM_TYPE_LIST
	#endif
	
	#ifdef flagOPENHMD
	flagOPENHMD_ATOM_TYPE_LIST
	#endif
	
	#ifdef flagVR
	flagVR_ATOM_TYPE_LIST
	#endif
	
	#ifdef flagOGL
	flagOGL_ATOM_TYPE_LIST
	#endif
	
	#ifdef flagPOSIX
	#ifdef flagPOSIX_ATOM_TYPE_LIST
	flagPOSIX_ATOM_TYPE_LIST
	#endif
	#endif
	
	#ifdef flagFFMPEG
	flagFFMPEG_ATOM_TYPE_LIST
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
	//operator bool() const {return IsValid();}
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
