#include "IGraphics.h"

#include <SerialMach/SerialMach.h>

#ifdef flagSCREEN

NAMESPACE_PARALLEL_BEGIN



template <class Gfx>
bool FboProgAtomT<Gfx>::Initialize(const Script::WorldState& ws) {
	
	return true;
}

template <class Gfx>
bool FboProgAtomT<Gfx>::PostInitialize() {
	
	return true;
}

template <class Gfx>
void FboProgAtomT<Gfx>::Uninitialize() {
	
}

template <class Gfx>
bool FboProgAtomT<Gfx>::IsReady(PacketIO& io) {
	dword iface_sink_mask = this->iface.GetSinkMask();
	bool b = io.active_sink_mask == iface_sink_mask && io.full_src_mask == 0;
	RTLOG("FboProgAtomT<Gfx>::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

template <class Gfx>
bool FboProgAtomT<Gfx>::Recv(int sink_ch, const Packet& p) {
	Format fmt = p->GetFormat();
	
	if (fmt.IsProg()) {
		TODO // sz
		
		if (id.IsEmpty())
			id.Create(sz, 3);
		
		//Size sz = fb.GetSize();
		//int channels = fb.GetChannels();
		InternalPacketData& data = p->GetData<InternalPacketData>();
		DrawCommand* cmd_screen_begin = (DrawCommand*)data.ptr;
		
		//pi.Create(sz, channels);
		pi.Paint(*cmd_screen_begin, id);
		
		img = id->GetImage();
		
		return true;
	}
	else return false;
}

template <class Gfx>
bool FboProgAtomT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("FboProgAtomT<Gfx>::Send");
	auto& buf = this->bf.GetBuffer();
	BufferStageT<Gfx>& stage = buf.InitSingle();
	
	Format fmt = out.GetFormat();
	if (fmt.IsFbo()) {
		if (data.GetModelCount() == 0) {
			ModelState& mdl = this->data.AddModelT();
			
			TODO
		}
		
		InternalPacketData& data = out.SetData<InternalPacketData>();
		
		data.ptr = &(GfxDataState&)this->data;
		data.SetText("gfxstate");
	}
	
	return true;
}



X11SW_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)
SDLSW_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)


NAMESPACE_PARALLEL_END

#endif
