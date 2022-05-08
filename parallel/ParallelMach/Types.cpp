#include "ParallelMach.h"

NAMESPACE_PARALLEL_BEGIN






DevCls GetCenterDevCls() {
	DevCls c;
	c.type = DevCls::CENTER;
	return c;
}


String ValCls::GetName(Type t) {
	switch (t) {
		case AUDIO:			return "audio";
		case VIDEO:			return "video";
		case VOLUME:		return "volume";
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

AtomTypeCls::AtomTypeCls(SubAtomCls cls, AtomRole role, const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0, int side_sinks, int side_srcs, int user_sinks, int user_srcs, const ValDevCls& si1, const ValDevCls& sr1) : iface(si0,content,sr0), sub(cls), role(role) {
	ASSERT(side_sinks > 0 || side_srcs > 0);
	ASSERT(side_sinks == 0 || si1.IsValid());
	ASSERT(side_srcs == 0 || sr1.IsValid());
	for(int i = 0; i < side_sinks; i++)
		iface.AddSink(si1);
	for(int i = 0; i < side_srcs; i++)
		iface.AddSource(sr1);
	user_sink_count = user_sinks;
	user_src_count = user_srcs;
}

AtomTypeCls::AtomTypeCls(
	SubAtomCls cls, AtomRole role,
	const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0,
	int side_sinks, int side_srcs, int user_sinks, int user_srcs,
	const ValDevCls& si1, const ValDevCls& si2, const ValDevCls& sr1, const ValDevCls& sr2)
: iface(si0,content,sr0), sub(cls), role(role) {
	ASSERT(side_sinks > 0 || side_srcs > 0);
	ASSERT(side_sinks == 0 || (si0.IsValid() && si1.IsValid()));
	ASSERT(side_srcs == 0 || (sr0.IsValid() && sr1.IsValid()));
	ValDevCls last_valid;
	for(int i = 0; i < side_sinks; i++) {
		switch (i+1) {
			case 1: if (si1.IsValid()) last_valid = si1; break;
			case 2: if (si2.IsValid()) last_valid = si2; break;
		}
		iface.AddSink(last_valid);
	}
	last_valid.Clear();
	for(int i = 0; i < side_srcs; i++) {
		switch (i+1) {
			case 1: if (sr1.IsValid()) last_valid = sr1; break;
			case 2: if (sr2.IsValid()) last_valid = sr2; break;
		}
		iface.AddSource(last_valid);
	}
	user_sink_count = user_sinks;
	user_src_count = user_srcs;
}

AtomTypeCls::AtomTypeCls(
	SubAtomCls cls, AtomRole role,
	const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0,
	int side_sinks, int side_srcs, int user_sinks, int user_srcs,
	const ValDevCls& si1, const ValDevCls& si2, const ValDevCls& si3,
	const ValDevCls& sr1, const ValDevCls& sr2, const ValDevCls& sr3
)
: iface(si0,content,sr0), sub(cls), role(role) {
	ASSERT(side_sinks > 0 || side_srcs > 0);
	ASSERT(side_sinks == 0 || (si0.IsValid() && si1.IsValid()));
	ASSERT(side_srcs == 0 || (sr0.IsValid() && sr1.IsValid()));
	ValDevCls last_valid;
	for(int i = 0; i < side_sinks; i++) {
		switch (i+1) {
			case 1: if (si1.IsValid()) last_valid = si1; break;
			case 2: if (si2.IsValid()) last_valid = si2; break;
			case 3: if (si3.IsValid()) last_valid = si3; break;
		}
		iface.AddSink(last_valid);
	}
	last_valid.Clear();
	for(int i = 0; i < side_srcs; i++) {
		switch (i+1) {
			case 1: if (sr1.IsValid()) last_valid = sr1; break;
			case 2: if (sr2.IsValid()) last_valid = sr2; break;
			case 3: if (sr3.IsValid()) last_valid = sr3; break;
		}
		iface.AddSource(last_valid);
	}
	user_sink_count = user_sinks;
	user_src_count = user_srcs;
}

AtomTypeCls::AtomTypeCls(
	SubAtomCls cls, AtomRole role,
	const ValDevCls& si0, const ValDevCls& content, const ValDevCls& sr0,
	int side_sinks, int side_srcs, int user_sinks, int user_srcs,
	const ValDevCls& si1, const ValDevCls& si2, const ValDevCls& si3, const ValDevCls& si4,
	const ValDevCls& sr1, const ValDevCls& sr2, const ValDevCls& sr3, const ValDevCls& sr4
)
: iface(si0,content,sr0), sub(cls), role(role) {
	ASSERT(side_sinks > 0 || side_srcs > 0);
	ASSERT(side_sinks == 0 || (si0.IsValid() && si1.IsValid()));
	ASSERT(side_srcs == 0 || (sr0.IsValid() && sr1.IsValid()));
	ValDevCls last_valid;
	for(int i = 0; i < side_sinks; i++) {
		switch (i+1) {
			case 1: if (si1.IsValid()) last_valid = si1; break;
			case 2: if (si2.IsValid()) last_valid = si2; break;
			case 3: if (si3.IsValid()) last_valid = si3; break;
			case 4: if (si4.IsValid()) last_valid = si4; break;
		}
		iface.AddSink(last_valid);
	}
	last_valid.Clear();
	for(int i = 0; i < side_srcs; i++) {
		switch (i+1) {
			case 1: if (sr1.IsValid()) last_valid = sr1; break;
			case 2: if (sr2.IsValid()) last_valid = sr2; break;
			case 3: if (sr3.IsValid()) last_valid = sr3; break;
			case 4: if (sr4.IsValid()) last_valid = sr4; break;
		}
		iface.AddSource(last_valid);
	}
	user_sink_count = user_sinks;
	user_src_count = user_srcs;
}





String GetSubAtomString(SubAtomCls t) {
	switch (t) {
		#define ATOM_TYPE(x) case x:	return #x;
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
		default: TODO return "invalid";
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


NAMESPACE_PARALLEL_END
