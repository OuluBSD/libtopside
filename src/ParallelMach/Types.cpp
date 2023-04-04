#include "ParallelMach.h"

NAMESPACE_PARALLEL_BEGIN






DevCls GetCenterDevCls() {
	DevCls c;
	c.type = DevCls::CENTER;
	return c;
}


String ValCls::GetName(Type t) {
	switch (t) {
		#define IFACE(x) case x: return ToLower(String(#x));
		IFACE_LIST
		#undef IFACE
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
		case NET:		return "net";
		case OGL:		return "ogl";
		case DX:		return "dx";
		case INVALID:
		default: return "invalid";
	}
}

DevCls::Type DevCls::Get(String s) {
	if (s == "center")	return CENTER;
	if (s == "net")		return NET;
	if (s == "ogl")		return OGL;
	if (s == "dx")		return DX;
	
	return INVALID;
}









hash_t AtomIfaceTypeCls::GetHashValue() const {
	CombineHash c;
	c.Put(sink.GetHashValue());
	c.Put(src.GetHashValue());
	return c;
}

hash_t AtomTypeCls::GetHashValue() const {
	CombineHash c;
	c.Put(iface.GetHashValue());
	c.Put(sub);
	c.Put(role);
	return c;
}

bool AtomTypeCls::IsSinkChannelOptional(int ch_i) const {
	return iface.sink[ch_i].is_opt;
}

bool AtomTypeCls::IsSourceChannelOptional(int ch_i) const {
	return iface.src[ch_i].is_opt;
}

void AtomTypeCls::AddIn(ValDevCls vd, bool is_opt) {
	iface.sink.channels.Add().Set(vd, is_opt);
}

void AtomTypeCls::AddOut(ValDevCls vd, bool is_opt) {
	iface.src.channels.Add().Set(vd, is_opt);
}

/*
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

*/



String GetSubAtomString(SubAtomCls t) {
	switch (t) {
		#define ATOM_TYPE(x) case x:	return #x;
		
		#define GEN_ATOM_TYPE_LIST
		#include "GenAtom.inl"
		#undef GEN_ATOM_TYPE_LIST
		
		#undef ATOM_ROLE
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
		//DUMP(type);
		this->type = type;
		const ValDevTuple& type_sink = type.iface.sink;
		const ValDevTuple& type_src = type.iface.src;
		this->sink.SetCount(0); // clear
		this->sink.SetCount(type_sink.channels.GetCount());
		this->src.SetCount(0);
		this->src.SetCount(type_src.channels.GetCount());
	}
	else {
		ASSERT(this->type == type);
	}
}

bool IfaceConnTuple::HasCommonConnection(const IfaceConnTuple& src) const {
	for (const IfaceConnLink& a : this->sink) {
		for (const IfaceConnLink& b : src.src) {
			if (a.conn == b.conn)
				return true;
		}
	}
	for (const IfaceConnLink& a : this->src) {
		for (const IfaceConnLink& b : src.sink) {
			if (a.conn == b.conn)
				return true;
		}
	}
	return false;
}

void IfaceConnTuple::SetSource(int conn, int src_ch, int sink_ch) {
	ASSERT(src_ch >= 0 && src_ch < type.iface.src.GetCount());
	ASSERT(src_ch < type.iface.src.GetCount());
	src[src_ch].conn = conn;
	src[src_ch].local = src_ch;
	src[src_ch].other = sink_ch;
}

void IfaceConnTuple::SetSink(int conn, int sink_ch, int src_ch) {
	ASSERT(sink_ch >= 0 && sink_ch < type.iface.sink.GetCount());
	ASSERT(sink_ch < type.iface.src.GetCount());
	sink[sink_ch].conn = conn;
	sink[sink_ch].local = sink_ch;
	sink[sink_ch].other = src_ch;
}

bool IfaceConnTuple::IsComplete() const {
	ASSERT(sink.GetCount() == type.iface.sink.GetCount());
	if (sink.GetCount() != type.iface.sink.GetCount()) return false;
	
	ASSERT(src.GetCount() == type.iface.src.GetCount());
	if (src.GetCount() != type.iface.src.GetCount()) return false;
	
	for(int i = 1; i < sink.GetCount(); i++)
		if (sink[i].conn < 0 && !type.iface.sink[i].is_opt)
			return false;
		
	for(int i = 1; i < src.GetCount(); i++)
		if (src[i].conn < 0 && !type.iface.src[i].is_opt)
			return false;
	
	return true;
}

dword IfaceConnTuple::GetSinkMask() const {
	// primary link is not usually written to this class,
	// but it's always required so set it true
	dword m = 0;
	for(int i = 0; i < sink.GetCount(); i++)
		m |= (i == 0 || sink[i].conn >= 0) ? 1 << i : 0;
	return m;
}


NAMESPACE_PARALLEL_END
