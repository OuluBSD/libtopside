#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN







DevCls GetCenterDevCls() {
	DevCls c;
	c.type = DevCls::CENTER;
	return c;
}


String GetSubAtomString(SubAtomCls t) {
	switch (t) {
		#define ATOM_TYPE(x) case x:	return #x;
		ATOM_TYPE_LIST
		
		#ifdef flagGUI
		GUI_ATOM_TYPE_LIST
		#endif
		
		#undef ATOM_TYPE
		default: return "invalid";
	}
}

String GetAtomRoleString(AtomRole t) {
	switch (t) {
		#define ATOM_ROLE(x) case x: return #x;
		ATOM_ROLE_LIST
		#undef ATOM_ROLE
		default:			return "invalid";
	}
}


String ValCls::GetName(Type t) {
	switch (t) {
		case AUDIO:			return "audio";
		case VIDEO:			return "video";
		case MIDI:			return "midi";
		case EVENT:			return "event";
		case DATA:			return "data";
		case ORDER:			return "order";
		case RECEIPT:		return "receipt";
		case INVALID:
		default: return "invalid";
	}
}

ValCls::Type ValCls::Get(String s) {
	if (s == "audio")
		return AUDIO;
	if (s == "video")
		return VIDEO;
	if (s == "midi")
		return MIDI;
	if (s == "event")
		return EVENT;
	if (s == "data")
		return DATA;
	if (s == "order")
		return ORDER;
	if (s == "receipt")
		return RECEIPT;
	
	return INVALID;
}



String DevCls::GetName(Type t) {
	switch (t) {
		case CENTER:	return "center";
		case PERMA:		return "perma";
		case ACCEL:		return "accel";
		case NET:		return "net";
		case INVALID:
		default: return "invalid";
	}
}

DevCls::Type DevCls::Get(String s) {
	if (s == "center")
		return CENTER;
	if (s == "perma")
		return PERMA;
	if (s == "accel")
		return ACCEL;
	if (s == "net")
		return NET;
	
	return INVALID;
}






hash_t AtomIfaceTypeCls::GetHashValue() const {
	CombineHash c;
	c.Put(sink.GetHashValue());
	c.Put(src.GetHashValue());
	c.Put(content.GetHashValue());
	return c;
}

hash_t AtomTypeCls::GetHashValue() const {
	CombineHash c;
	c.Put(iface.GetHashValue());
	c.Put(sub);
	c.Put(role);
	return c;
}







String SerialTypeCls::GetTypeString(Type t) {
	switch (t) {
		case INVALID:				return "invalid";
		#define SERIAL_TYPE(x) case x: return #x;
		SERIAL_TYPE_LIST
		#undef SERIAL_TYPE
		default: return "invalid";
	}
}


NAMESPACE_SERIAL_END
