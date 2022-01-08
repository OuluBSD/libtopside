#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


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
