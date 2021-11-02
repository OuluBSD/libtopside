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
		case FBO:			return "fbo";
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
	if (s == "fbo")
		return FBO;
	
	return INVALID;
}



String DevCls::GetName(Type t) {
	switch (t) {
		case CENTER:	return "center";
		case PERMA:		return "perma";
		case NET:		return "net";
		case OGL:		return "ogl";
		case INVALID:
		default: return "invalid";
	}
}

DevCls::Type DevCls::Get(String s) {
	if (s == "center")
		return CENTER;
	if (s == "perma")
		return PERMA;
	if (s == "ogl")
		return OGL;
	if (s == "net")
		return NET;
	if (s == "ogl")
		return OGL;
	
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
	c.Put(user_sink_count);
	c.Put(user_src_count);
	return c;
}

bool AtomTypeCls::IsSinkChannelOptional(int ch_i) const {
	int sink_begin = iface.sink.count - user_sink_count;
	int sink_end = iface.sink.count;
	return ch_i >= sink_begin && ch_i < sink_end;
}

bool AtomTypeCls::IsSourceChannelOptional(int ch_i) const {
	int src_begin = iface.src.count - user_src_count;
	int src_end = iface.src.count;
	return ch_i >= src_begin && ch_i < src_end;
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




void IfaceConnTuple::Realize(const AtomTypeCls& type) {
	if (!this->type.IsValid()) {
		this->type = type;
	}
	else {
		ASSERT(this->type == type);
	}
}

void IfaceConnTuple::SetSource(int conn, int src_ch, int sink_ch) {
	ASSERT(src_ch >= 0 && src_ch < type.iface.src.count);
	ASSERT(src_ch < MAX_VDTUPLE_SIZE);
	src[src_ch].conn = conn;
	src[src_ch].local = src_ch;
	src[src_ch].other = sink_ch;
}

void IfaceConnTuple::SetSink(int conn, int sink_ch, int src_ch) {
	ASSERT(sink_ch >= 0 && sink_ch < type.iface.sink.count);
	ASSERT(sink_ch < MAX_VDTUPLE_SIZE);
	sink[sink_ch].conn = conn;
	sink[sink_ch].local = sink_ch;
	sink[sink_ch].other = src_ch;
}

bool IfaceConnTuple::IsComplete() const {
	int c0 = type.iface.sink.count - type.user_sink_count;
	for(int i = 1; i < c0; i++)
		if (sink[i].conn < 0 /*&& !type.IsSinkChannelOptional(i)*/)
			return false;
	int c1 = type.iface.src.count - type.user_src_count;
	for(int i = 1; i < c1; i++)
		if (src[i].conn < 0 /*&& !type.IsSourceChannelOptional(i)*/)
			return false;
	return true;
}

dword IfaceConnTuple::GetSinkMask() const {
	// primary link is not usually written to this class,
	// but it's always required so set it true
	dword m = 0;
	for(int i = 0; i < MAX_VDTUPLE_SIZE; i++)
		m |= (i == 0 || sink[i].conn >= 0) ? 1 << i : 0;
	return m;
}
	
	
	
NAMESPACE_SERIAL_END
