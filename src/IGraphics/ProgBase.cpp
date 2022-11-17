#include "IGraphics.h"

#include <SerialMach/SerialMach.h>

#ifdef flagSCREEN

NAMESPACE_PARALLEL_BEGIN



template <class Gfx>
bool FboProgAtomT<Gfx>::Initialize(const Script::WorldState& ws) {
	dbg_info = 0;
	
	resize_multiplier = ws.GetDouble(".resize.multiplier", 0.004);
	
	write_ecs = ws.GetBool(".write.ecs", false);
	
	// Write to ecs, when no side-connections is added
	Serial::Link* link = this->GetLink();
	if (link->SideSinks().IsEmpty())
		write_ecs = true;
	
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
		DrawCommand* cmd = (DrawCommand*)data.ptr;
		DrawCommand* prev = 0;
		if (!cmd) {
			LOG("FboProgAtomT<Gfx>::Recv: error: no ptr");
			return false;
		}
		
		while (cmd->type != DRAW_BIND_WINDOW && cmd)
			cmd = cmd->next;
		
		dbg_win_id = 0;
		while (cmd) {
			prev = cmd;
			cmd = ProcessWindow(cmd);
			dbg_win_id++;
		}
		
		if (dbg_info)
			Panic("stop flood");
		
		return true;
	}
	else return false;
}

template <class Gfx>
void FboProgAtomT<Gfx>::Finalize(RealtimeSourceConfig& cfg) {
	
	//Ecs::Engine& eng = GetActiveEngine();
	
	
	
	//TODO
}

template <class Gfx>
bool FboProgAtomT<Gfx>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	RTLOG("FboProgAtomT<Gfx>::Send");
	auto& buf = this->bf.GetBuffer();
	BufferStageT<Gfx>& stage = buf.InitSingle();
	
	Format fmt = out.GetFormat();
	if (fmt.IsFbo()) {
		InternalPacketData& data = out.SetData<InternalPacketData>();
		
		data.ptr = &(GfxDataState&)this->data;
		data.SetText("gfxstate");
	}
	
	return true;
}

template <class Gfx>
DrawCommand* FboProgAtomT<Gfx>::ProcessWindow(DrawCommand* begin) {
	while (begin && begin->type == 0)
		begin = begin->next;
	if (!begin)
		return 0;
	
	ASSERT(begin->type == DRAW_BIND_WINDOW);
	
	DrawCommand* end = begin;
	while (end) {
		if (end->type == DRAW_UNBIND_WINDOW) {
			end = end->next;
			break;
		}
		end = end->next;
	}
	
	
	if (dbg_info) {
		int i = 0;
		DrawCommand* it = begin;
		LOG("Window " << dbg_win_id);
		while (it != end && it) {
			LOG("\t" << i++ << ": " << it->ToString());
			it = it->next;
		}
	}
	
	ProcessWindowCommands(begin, end);
	
	// Move to the beginning of the next window
	DrawCommand* next = end->next;
	while (next && next->type != DRAW_BIND_WINDOW)
		next = next->next;
	
	return next;
}

template <class Gfx>
void FboProgAtomT<Gfx>::ProcessWindowCommands(DrawCommand* begin, DrawCommand* end) {
	ASSERT(begin->type == DRAW_BIND_WINDOW);
	
	hash_t hash = begin->hash;
	ASSERT(hash);
	
	Window& win = windows.GetAdd(hash);
	
	
	// Get ctrl size from draw command queue
	Size sz(0,0);
	{
		DrawCommand* iter = begin;
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
	win.sz = sz;
	
	
	if (win.id.IsEmpty() || win.id->GetSize() != sz) {
		win.id.Create(sz, 3);
	}
	
	win.id->DrawRect(sz, GrayColor());
	
	win.pi.SkipWindowCommands();
	win.pi.Paint(begin, end, win.id);
	
	if (!win.inited) {
		ModelState& mdl_state = this->data.AddModelT();
		
		vec2 sz_vec(sz.cx * resize_multiplier, sz.cy * resize_multiplier);
		
		ModelBuilder mb;
		Mesh& plane_mesh = mb.AddPlane(vec3(0), sz_vec, 16);
		Model& src_mdl = mb;
		
		plane_mesh.CenterAnchor();
		plane_mesh.TransformVertices(AxesMat(0,M_PI/2,0));
		
		Image img = win.id->GetImage();
		if (0) {
			ImageDraw id(sz);
			id.DrawRect(sz, White());
			win.img = id;
		}
		src_mdl.SetTexture(plane_mesh, TEXTYPE_DIFFUSE, img, "" );
		
		if (!mdl_state.LoadModel(src_mdl)) {
			LOG("FboProgAtomT<Gfx>::Send: error: could not load model");
			return;
		}
		
		auto& mtl = src_mdl.materials.Get(plane_mesh.material);
		
		win.tex_id = mtl.tex_id[TEXTYPE_DIFFUSE];
		win.tex = mdl_state.textures.Get(win.tex_id);
		win.inited = true;
	}
	else {
		
	}
	
}



X11SW_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)
X11OGL_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)
SDLSW_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)
SDLOGL_EXCPLICIT_INITIALIZE_CLASS(FboProgAtomT)


NAMESPACE_PARALLEL_END

#endif
