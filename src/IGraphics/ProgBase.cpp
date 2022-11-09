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
		InternalPacketData& data = p->GetData<InternalPacketData>();
		DrawCommand* cmd_screen_begin = (DrawCommand*)data.ptr;
		
		// Get ctrl size from draw command queue
		Size sz(0,0);
		{
			DrawCommand* iter = cmd_screen_begin;
			while (iter) {
				if (iter->type == DRAW_META_SIZE) {
					sz.cx = iter->i[0];
					sz.cy = iter->i[1];
					break;
				}
				iter = iter->next;
			}
		}
		ASSERT(!sz.IsEmpty());
		if (sz.IsEmpty()) sz = Size(320,240);
		
		
		if (id.IsEmpty()) {
			id.Create(sz, 3);
			id->DrawRect(sz, GrayColor());
		}
		
		//pi.Create(sz, channels);
		pi.Paint(*cmd_screen_begin, id);
		
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
		ASSERT(!id.IsEmpty());
		
		if (data.GetModelCount() == 0) {
			ModelState& mdl_state = this->data.AddModelT();
			
			float multiplier = 0.001;
			Size sz = id->GetSize();
			vec2 sz_vec(sz.cx * multiplier, sz.cy * multiplier);
			
			ModelBuilder mb;
			Mesh& plane_mesh = mb.AddPlane(vec3(0), sz_vec);
			Model& src_mdl = mb;
			
			plane_mesh.CenterAnchor();
			plane_mesh.TransformVertices(AxesMat(0,M_PI/2,0));
			
			Image img = id->GetImage();
			if (0) {
				ImageDraw id(sz);
				id.DrawRect(sz, White());
				img = id;
			}
			src_mdl.SetTexture(plane_mesh, TEXTYPE_DIFFUSE, img, "" );
			
			if (!mdl_state.LoadModel(src_mdl)) {
				LOG("FboProgAtomT<Gfx>::Send: error: could not load model");
				return false;
			}
			
			auto& mtl = src_mdl.materials.Get(plane_mesh.material);
			int tex_id = mtl.tex_id[TEXTYPE_DIFFUSE];
			this->tex = mdl_state.textures.Get(tex_id);
			
		}
		else {
			//TODO
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
