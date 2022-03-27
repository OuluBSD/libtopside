#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


VolumeLoaderBase::VolumeLoaderBase() {
	
}

bool VolumeLoaderBase::Initialize(const Script::WorldState& ws) {
	//LOG(ws.ToString());
	
	String arg_filepath = ws.Get(".filepath");
	if (arg_filepath.IsEmpty()) {
		LOG("VolumeLoaderBase: error: no 'filepath' given");
		return false;
	}
	
	filepath = RealizeFilepathArgument(arg_filepath);
	RTLOG("VolumeLoaderBase: filepath=\"" << filepath << "\"");
	
	if (ws.Get(".vflip") == "true")
		vflip = true;
	
	return LoadFile();
}

bool VolumeLoaderBase::LoadFile() {
	if (!FileExists(filepath)) {
		LOG("VolumeLoaderBase::LoadFile: error: file does not exist: '" << filepath << "'");
		return false;
	}
	
	String s = UPP::LoadFile(filepath);
	if (s.IsEmpty()) {
		LOG("VolumeLoaderBase::LoadFile: error: empty file");
		return false;
	}
	
	MemReadStream data(s.Begin(), s.GetCount());
	int magic, w, h, d, channels, len;
	data.Get(&magic, 4); // "BIN "
	if (magic == 0x004e4942) {
		data.Get(&w, 4);
		data.Get(&h, 4);
		data.Get(&d, 4);
		data.Get(&channels, 4);
		len = w * h * d * channels;
		if (len <= 0) {
			LOG("VolumeLoaderBase::LoadFile: error: invalid size");
			return false;
		}
		values.SetCount(len);
		data.Get(values.Begin(), len);
	}
	else {
		int len = 0;
		for(int i = 1; i <= 4; i++) {
			int per_ch = s.GetCount() / i;
			int root = (int)pow(per_ch, 1.0/3.0);
			int test_len = root * root * root * i;
			if (test_len == s.GetCount()) {
				channels = i;
				len = root;
				break;
			}
		}
		if (channels <= 0 || len <= 0) {
			LOG("VolumeLoaderBase::LoadFile: error: couldn't find volume data dimensions");
			return false;
		}
		w = h = d = len;
		len = w * h * d * channels;
		if (len <= 0) {
			LOG("VolumeLoaderBase::LoadFile: error: invalid size");
			return false;
		}
		values.SetCount(len);
		MemoryCopy(values.Begin(), s.Begin(), len);
	}
	
	sz = Size3(w, h, d);
	this->stride = channels;
	
	BinarySample::Type type;
	switch (stride) {
		case 4:		type = BinarySample::U8_LE_ABCD; break;
		case 3:		type = BinarySample::U8_LE_ABC; break;
		case 2:		type = BinarySample::U8_LE_AB; break;
		case 1:		type = BinarySample::U8_LE_A; break;
		default: return false;
	}
	fmt.SetVolume(DevCls::CENTER, type, sz.cx, sz.cy, sz.cz, 1, 1);
	
	InterfaceSourceRef iface = GetSource();
	int src_count = iface->GetSourceCount();
	for(int i = 1; i < src_count; i++)
		iface->GetSourceValue(i).SetFormat(fmt);
	
	return true;
}

void VolumeLoaderBase::Uninitialize() {
	
}

bool VolumeLoaderBase::ProcessPackets(PacketIO& io) {
	if (values.IsEmpty()) return false;
	
	PacketIO::Sink& sink = io.sink[0];
	Packet& in = sink.p;
	ASSERT(in); if (!in) return false;
	sink.may_remove = true;
	
	RTLOG("VolumeLoaderBase::ProcessPackets: sink #0: " << in->ToString());
	
	PacketIO::Sink& prim_sink = io.sink[0];
	PacketIO::Source& prim_src = io.src[0];
	Packet& prim_out = prim_src.p;
	prim_src.from_sink_ch = 0;
	prim_out = ReplyPacket(0, prim_sink.p);
	
	ASSERT(io.src_count >= 2);
	PacketIO::Source& src = io.src[1];
	Packet& out = src.p;
	src.from_sink_ch = 0;
	
	out = ReplyPacket(1, prim_sink.p);
	
	PacketValue& v = *out;
	
	v.SetFormat(fmt);
	
	Swap(v.Data(), values);
	
	return true;
}

bool VolumeLoaderBase::IsReady(PacketIO& io) {
	return io.full_src_mask == 0 && !values.IsEmpty();
}


NAMESPACE_SERIAL_END