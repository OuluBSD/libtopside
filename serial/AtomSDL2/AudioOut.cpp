#include "AtomSDL2.h"

NAMESPACE_SERIAL_BEGIN


bool SDL2AudioOutputBase::AltInitialize(const Script::WorldState& ws) {
	aconfig.frames_after_sync = 0;
	SetAudioSyncInterval(15);
	OBJ_CREATE
	return true;
}

void SDL2AudioOutputBase::AltUninitialize() {
	obj.Clear();
}

void SDL2AudioOutputBase::AltForward(FwdScope& fwd) {
	// pass
}




void AsyncMemForwarderBase::ForwardAsyncMem(byte* mem, int size)  {
	RTLOG("AsyncMemForwarderBase::ForwardAsyncMem");
	ASSERT(size > 0);
	write_mem = mem;
	write_size = size;
	write_pos = 0;
	
	if (partial_packet)
		Consume(partial_pos, partial_packet);
	
	if (write_pos < size)
		ForwardAsync();
	
	if (write_pos < size) {
		RTLOG("AsyncMemForwarderBase::ForwardAsyncMem: warning: not enough packets to read memory entirely");
	}
	write_mem = 0;
	write_size = 0;
	write_pos = 0;
}

void AsyncMemForwarderBase::LoadPacket(int ch_i, const Packet& p) {
	Consume(0, p);
}

void AsyncMemForwarderBase::AltStorePacket(int sink_ch, int src_ch, Packet& p) {
	RTLOG("AsyncMemForwarderBase::AltStorePacket");
}

bool AsyncMemForwarderBase::IsReady(ValDevCls vd) {
	return write_mem != 0 && write_pos < write_size;
}

void AsyncMemForwarderBase::Consume(int data_begin, Packet p) {
	RTLOG("AsyncMemForwarderBase::Consume: " << p->ToString());
	partial_packet.Clear();
	
	const Vector<byte>& data = p->GetData();
	int sz = data.GetCount() - data_begin;
	int remaining = write_size - write_pos;
	
	if (sz > 0 && remaining > 0) {
		int cp_sz = min(sz, remaining);
		byte* dst = write_mem + write_pos;
		const byte* src = (const byte*)data.Begin() + data_begin;
		MemoryCopy(dst, src, cp_sz);
		write_pos += cp_sz;
		int p_remaining = sz - data_begin - cp_sz;
		ASSERT(p_remaining >= 0);
		if (p_remaining > 0) {
			partial_packet = p;
			partial_pos = data_begin + cp_sz;
		}
	}
	
}

NAMESPACE_SERIAL_END
