#include "IVolumetric.h"
#include <SerialCore/SerialCore.h>




NAMESPACE_PARALLEL_BEGIN


struct VolRawByte::NativeStaticSource {
    Vector<byte> values;
    Format fmt;
    String filepath;
    Size3 sz;
    int stride;
    bool vflip;
};


bool VolRawByte::StaticSource_Create(NativeStaticSource*& dev) {
	dev = new NativeStaticSource;
	return true;
}

void VolRawByte::StaticSource_Destroy(NativeStaticSource*& dev) {
	delete dev;
}

void VolRawByte::StaticSource_Visit(NativeStaticSource& dev, AtomBase&, RuntimeVisitor& vis) {
	
}



bool VolRawByte__LoadFile(VolRawByte::NativeStaticSource& dev, AtomBase& a) {
	if (!FileExists(dev.filepath)) {
		LOG("VolumeLoaderBase::LoadFile: error: file does not exist: '" << dev.filepath << "'");
		return false;
	}
	
	String s = UPP::LoadFile(dev.filepath);
	if (s.IsEmpty()) {
		LOG("VolumeLoaderBase::LoadFile: error: empty file");
		return false;
	}
	
	MemReadStream data(s.Begin(), s.GetCount());
	int magic = 0, w = 0, h = 0, d = 0, channels = 0, len = 0;
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
		dev.values.SetCount(len);
		data.Get(dev.values.Begin(), len);
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
		dev.values.SetCount(len);
		MemoryCopy(dev.values.Begin(), s.Begin(), len);
	}
	
	dev.sz = Size3(w, h, d);
	dev.stride = channels;
	
	BinarySample::Type type;
	switch (dev.stride) {
		case 4:		type = BinarySample::U8_LE_ABCD; break;
		case 3:		type = BinarySample::U8_LE_ABC; break;
		case 2:		type = BinarySample::U8_LE_AB; break;
		case 1:		type = BinarySample::U8_LE_A; break;
		default: return false;
	}
	dev.fmt.SetVolume(DevCls::CENTER, type, dev.sz.cx, dev.sz.cy, dev.sz.cz, 1, 1);
	
	InterfaceSourceRef iface = a.GetSource();
	int src_count = iface->GetSourceCount();
	for(int i = 1; i < src_count; i++)
		iface->GetSourceValue(i).SetFormat(dev.fmt);
	
	return true;
}

bool VolRawByte::StaticSource_Initialize(NativeStaticSource& dev, AtomBase& a, const Script::WorldState& ws) {
	dev.vflip = false;
	
	String arg_filepath = ws.Get(".filepath");
	if (arg_filepath.IsEmpty()) {
		LOG("VolumeLoaderBase: error: no 'filepath' given");
		return false;
	}
	
	dev.filepath = RealizeFilepathArgument(arg_filepath);
	RTLOG("VolumeLoaderBase: filepath=\"" << dev.filepath << "\"");
	
	if (ws.Get(".vflip") == "true")
		dev.vflip = true;
	
	return VolRawByte__LoadFile(dev, a);
}

bool VolRawByte::StaticSource_PostInitialize(NativeStaticSource& dev, AtomBase& a) {
	InterfaceSourceRef iface = a.GetSource();
	int src_count = iface->GetSourceCount();
	for(int i = 1; i < src_count; i++)
		a.GetLink()->NegotiateSourceFormat(i, dev.fmt);
	
	return true;
}

bool VolRawByte::StaticSource_Start(NativeStaticSource& dev, AtomBase& a) {
	// pass
	return true;
}

void VolRawByte::StaticSource_Stop(NativeStaticSource& dev, AtomBase& a) {
	// pass
}

void VolRawByte::StaticSource_Uninitialize(NativeStaticSource& dev, AtomBase& a) {
	// pass
}

bool VolRawByte::StaticSource_Send(NativeStaticSource& dev, AtomBase& a, RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	if (dev.values.IsEmpty())
		return false;
	
	Format fmt = out.GetFormat();
	if (fmt.IsVolume()) {
		out.SetFormat(dev.fmt);
		out.Data() <<= dev.values;
	}
	
	return true;
}

bool VolRawByte::StaticSource_IsReady(NativeStaticSource& dev, AtomBase&, PacketIO& io) {
	return io.full_src_mask == 0 && !dev.values.IsEmpty();
}




NAMESPACE_PARALLEL_END

