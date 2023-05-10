#include "SerialMach.h"

NAMESPACE_SERIAL_BEGIN


AsyncMemForwarderBase::AsyncMemForwarderBase() : dbg_offset(dbg_off_gen) {
	
}

bool AsyncMemForwarderBase::ForwardAsyncMem(byte* mem, int size)  {
	
	RTLOG("AsyncMemForwarderBase::ForwardAsyncMem: size " << size << " at " << HexStr(mem));
	ASSERT(size > 0);
	write_mem = mem;
	write_size = size;
	write_pos = 0;
	
	ASSERT(partial_pos == 0 || !partial_packet.IsEmpty());
	if (partial_packet) {
		RTLOG("AsyncMemForwarderBase::ForwardAsyncMem: consuming partial packet: seq=" << IntStr64(partial_packet->seq) << " + " << partial_pos);
		Consume(partial_pos, partial_packet);
	}
	else {
		RTLOG("AsyncMemForwarderBase::ForwardAsyncMem: no partial packet");
	}
	
	if (write_pos < size) {
		ForwardAsync();
		
		if (buffer.IsFilled()) {
			buffer.EnterWrite();
			Packet p = buffer.PopFirst();
			Consume(0, p);
			buffer.LeaveWrite();
		}
	}
	
	if (write_pos < size) {
		RTLOG("AsyncMemForwarderBase::ForwardAsyncMem: warning: not enough packets to read memory entirely");
	}
	
	bool succ = write_pos == size;
	
	write_mem = 0;
	write_size = 0;
	write_pos = 0;
	
	//RTLOG("AsyncMemForwarderBase::ForwardAsyncMem: returning");
	
	return succ;
}

bool AsyncMemForwarderBase::IsReady(PacketIO& io) {
	bool b = false;
	
	if (buffer.GetCount() >= 1)
		return false;
	
	if (!write_mem || write_pos >= write_size)
		return false;
	
	if (io.sinks.GetCount() == 1) {
		b = io.sinks[0].filled;
	}
	else if (io.sinks.GetCount() > 1) {
		b = io.sinks[0].filled && io.sinks[1].filled;
	}
	
	return b;
}

bool AsyncMemForwarderBase::ProcessPackets(PacketIO& io) {
	PacketIO::Sink& sink0 = io.sinks[0];
	PacketIO::Source& src = io.srcs[0];
	
	if (io.sinks.GetCount() == 1) {
		sink0.may_remove = true;
		src.from_sink_ch = 0;
		src.p = ReplyPacket(0, sink0.p);
		RTLOG("AsyncMemForwarderBase::ProcessPackets: sink #0 " << sink0.p->ToString());
		if (PassConsumePacket(src.from_sink_ch, sink0.p)) {
			buffer.EnterWrite();
			//Consume(src.from_sink_ch, sink0.p);
			buffer.Add(sink0.p);
			buffer.LeaveWrite();
		}
	}
	else if (io.sinks.GetCount() > 1) {
		PacketIO::Sink& sink1 = io.sinks[1];
		sink0.may_remove = true;
		sink1.may_remove = true;
		src.from_sink_ch = 1;
		src.p = ReplyPacket(0, sink1.p);
		RTLOG("AsyncMemForwarderBase::ProcessPackets: sink #1 " << sink1.p->ToString());
		if (PassConsumePacket(src.from_sink_ch, sink1.p)) {
			buffer.EnterWrite();
			//Consume(src.from_sink_ch, sink1.p);
			buffer.Add(sink1.p);
			buffer.LeaveWrite();
		}
	}
	else return false;
	
	#if HAVE_PACKETTRACKER
	src.p->AddRouteData(src.from_sink_ch);
	#endif
	
	return true;
}

void AsyncMemForwarderBase::Consume(int data_begin, Packet p) {
	ASSERT(p);
	
	RTLOG("AsyncMemForwarderBase::Consume: seq=" << IntStr64(p->seq) << ", " << p->ToString());
	partial_packet.Clear();
	partial_pos = 0;
	
	// error checking
	off32 p_off = p->GetOffset();
	off32 p_off1 = p_off;
	p_off1++;
	ASSERT(!(dbg_data_offset == data_begin && p_off == dbg_offset));
	if (p_off < dbg_offset)
		Panic("AsyncMemForwarderBase::Consume: got older packet");
	else if (p_off > p_off1)
		Panic("AsyncMemForwarderBase::Consume: got too new packet, which skipped one in between");
	else if (p_off > dbg_offset)
		dbg_offset = p_off;
	dbg_data_offset = data_begin;
	
	#if HAVE_PACKETTIMINGCHECK
	p->CheckTiming();
	static int iter;
	if (iter % 500 == 0) {
		Cout() << "AsyncMemForwarderBase::Consume: consuming age " << p->GetAge() << EOL;
		LOG("AsyncMemForwarderBase::Consume: consuming age " << p->GetAge());
		iter = 0;
	}
	iter++;
	#endif
	
	const Vector<byte>& data = p->GetData();
	int data_sz = data.GetCount();
	int sz = data_sz - data_begin;
	int remaining = write_size - write_pos;
	
	Format fmt = p->GetFormat();
	
	if (sz > 0 && remaining > 0) {
		int cp_sz = min(sz, remaining);
		byte* dst = write_mem + write_pos;
		const byte* src = (const byte*)data.Begin() + data_begin;
		MemoryCopy(dst, src, cp_sz);
		write_pos += cp_sz;
		int p_remaining = data_sz - data_begin - cp_sz;
		ASSERT(p_remaining >= 0);
		RTLOG("AsyncMemForwarderBase::Consume: got " << write_pos << "/" << write_size);
		if (p_remaining > 0) {
			partial_packet = p;
			partial_pos = data_begin + cp_sz;
			RTLOG("AsyncMemForwarderBase::Consume: storing partial packet: remaining " << data_sz-partial_pos << "/" << data_sz);
		}
	}
	
}
















void FramePollerBase::Update(double dt) {
	ASSERT(dt > 0.0);
	frame_age += dt;
	RTLOG("FramePollerBase::Update: dt: " << dt << ", frame_age: " << frame_age);
}

bool FramePollerBase::IsReady(PacketIO& io) {
	bool b = frame_age >= dt;
	RTLOG("FramePollerBase::IsReady: " << (b ? "true" : "false"));
	return b;
}




NAMESPACE_SERIAL_END
