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


NAMESPACE_PARALLEL_BEGIN

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


using ParallelSystemParent	= MetaSystemParent;
using LoopParent			= HierExBaseParent;
using AtomParent			= ExchangeBaseParent;


template <class T>
using RefT_Loop				= Ref<T,					AtomParent>;

template <class T>
using RefT_Machine			= Ref<T,					ParallelSystemParent>;


//using LoopParent			= RefParent2<LoopStore, Loop>;
//using AtomParent			= AtomParent;
using LoopRef				= Ref<Loop,					LoopParent>;
using AtomBaseRef			= Ref<AtomBase,				AtomParent>;
using LoopStoreRef			= Ref<LoopStore,			ParallelSystemParent>;
using AtomStoreRef			= Ref<AtomStore,			ParallelSystemParent>;
using AtomSystemRef			= Ref<AtomSystem,			ParallelSystemParent>;

using LoopVec				= RefLinkedList<Loop,			LoopParent>;
using StateVec				= RefLinkedList<EnvState,		EnvStateParent>;


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





NAMESPACE_PARALLEL_END


#endif
