#include "AtomSDL2.h"
#ifdef flagGUI

NAMESPACE_SERIAL_BEGIN



SDL2ImageBase::SDL2ImageBase()
{
	
}

bool SDL2ImageBase::Initialize(const Script::WorldState& ws) {
	LOG(ws.ToString());
	
	String arg_filepath = ws.Get(".filepath");
	if (arg_filepath.IsEmpty()) {
		LOG("SDL2ImageBase: error: no 'filepath' given");
		return false;
	}
	
	String filepath = RealizeFilepathArgument(arg_filepath);
	RTLOG("SDL2ImageBase: filepath=\"" << filepath << "\"");
	
	if (ws.Get(".cubemap") == "true")
		cubemap = true;
	
	if (ws.Get(".vflip") == "true")
		vflip = true;
	
	OBJ_CREATE
	
	
	seq = 0;
	imgs.Clear();
	if (cubemap) {
		String dir = GetFileDirectory(filepath);
		String ext = GetFileExt(filepath);
		String title = GetFileTitle(filepath);
		for(int i = 0; i < 6; i++) {
			String side_path;
			if (i == 0)
				side_path = filepath;
			else
				side_path = AppendFileName(dir, title + "_" + IntStr(i) + ext);
			
			Image img = Image(IMG_Load(side_path.Begin()));
			if (img.IsEmpty()) {
				LOG("SDL2ImageBase: error: empty image: " << side_path);
				return false;
			}
			
			// shadertoy compatibility
			if (vflip)
				img = MirrorVertical(img);
			
			imgs.Add(img);
		}
	}
	else {
		Image img = Image(IMG_Load(filepath.Begin()));
		if (img.IsEmpty()) {
			LOG("SDL2ImageBase: error: empty image: " << filepath);
			return false;
		}
		
		// shadertoy compatibility
		if (vflip)
			img = MirrorVertical(img);
		
		imgs.Add(img);
	}
	
	return true;
}

void SDL2ImageBase::Uninitialize() {
	imgs.Clear();
	obj.Clear();
}

bool SDL2ImageBase::ProcessPackets(PacketIO& io) {
	if (imgs.IsEmpty()) return false;
	
	PacketIO::Sink& sink = io.sink[0];
	Packet& in = sink.p;
	ASSERT(in); if (!in) return false;
	sink.may_remove = true;
	
	RTLOG("SDL2ScreenBase::ProcessPackets: sink #0: " << in->ToString());
	
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
	v.seq = seq++;
	Image& img = imgs[0];
	
	Format fmt = v.GetFormat();
	ASSERT(fmt.IsVideo());
	fmt.vid.SetSize(img.GetSize());
	fmt.vid.SetCubemap();
	v.SetFormat(fmt);
	
	int pack = fmt.vid.GetPackedCount();
	ASSERT(pack == 4);
	DataFromImage(img, v.Data());
	ASSERT(v.GetData().GetCount());
	
	imgs.Remove(0);
	
	return true;
}

bool SDL2ImageBase::IsReady(PacketIO& io) {
	bool b = io.full_src_mask == 0 && !imgs.IsEmpty();
	RTLOG("SDL2ImageBase::IsReady: " << (b ? "true" : "false"));
	return b;
}

Size SDL2ImageBase::GetResolution() const {
	if (imgs.GetCount())
		return imgs[0].GetSize();
	return Size(0,0);
}


NAMESPACE_SERIAL_END

#endif
