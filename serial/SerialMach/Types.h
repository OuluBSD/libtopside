#ifndef _SerialMach_Types_h_
#define _SerialMach_Types_h_

NAMESPACE_SERIAL_BEGIN


class SoundSample;
class Loop;

typedef dword PacketId;



struct ValCls : Moveable<ValCls> {
	typedef enum : byte {
		INVALID,
		AUDIO,
		VIDEO,
		MIDI,
		EVENT,
		DATA,
		ORDER,
		RECEIPT,
		
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

typedef enum : byte {
	INVALID,
	
	#define SERIAL_BASE(x) x,
	SERIAL_BASE_LIST
	#undef SERIAL_BASE
	
	SUBCOMP_COUNT
} SubCompCls;

String GetSubCompString(SubCompCls t);


struct CompCls : Moveable<CompCls> {
	ValDevCls sink, side, src;
	
	
	bool IsValid() const {return sink.IsValid() && src.IsValid() && side.IsValid();}
	
};

struct TypeCompCls : Moveable<TypeCompCls> {
	ValDevCls sink, src;
	SerialTypeCls side;
	SubCompCls sub = SubCompCls::INVALID;
	int16 ext = -1;
	bool multi_conn = false;
	
	bool IsValid() const {return sink.IsValid() && src.IsValid() && side.IsValid() && sub != SubCompCls::INVALID && ext >= 0;}
	bool IsMultiSideConnection() const {return multi_conn;}
	hash_t GetHashValue() const;
	void operator=(const Nuller& n) {sink = n; src = n; side = n; sub = SubCompCls::INVALID; ext = -1; multi_conn = false;}
	
	bool operator==(const TypeCompCls& c) const {
		return	sink == c.sink &&
				side == c.side &&
				src == c.src &&
				sub == c.sub &&
				ext == c.ext &&
				multi_conn == c.multi_conn
				;
	}
	bool operator!=(const TypeCompCls& c) const {return !(*this == c);}
	String ToString() const {return GetSubCompString(sub) + "-" + side.ToString() + "(sink(" + sink.ToString() + "), src(" + src.ToString() + "), ext=" << IntStr(ext) << ", multiconn=" << IntStr(multi_conn) << ")";}
	
};


template<class T, class Parent = RefParent1<typename T::Parent>>
using RefSerialTypeMapIndirect	= RefLinkedMapIndirect<TypeCompCls, T, Parent>;


template <class T> SerialTypeCls AsSerialTypeCls(ValDevCls vd) {
	SerialTypeCls c;
	c.vd = vd;
	c.type = T::GetSerialType();
	return c;
}

template <class T> TypeCompCls AsTypeCompCls(SubCompCls sub_type, CompCls vd) {
	TypeCompCls c;
	c.sub = sub_type;
	c.side.vd.dev = vd.side.dev;
	c.side.vd.val = vd.side.val;
	c.side.type = T::GetSerialType();
	c.sink = vd.sink;
	c.src  = vd.src;
	return c;
}


DevCls GetCenterDevCls();

NAMESPACE_SERIAL_END

#endif
