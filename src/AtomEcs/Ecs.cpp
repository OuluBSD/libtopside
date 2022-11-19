#include "AtomEcs.h"
#include <SerialLib/SerialLib.h>
#include <EcsLocal/EcsLocal.h>
#include <EcsVirtualGui/EcsVirtualGui.h>

NAMESPACE_PARALLEL_BEGIN



Callback1<EcsEventsBase*> EcsEventsBase::WhenInitialize;

EcsEventsBase* EcsEventsBase::active;

EcsEventsBase::EcsEventsBase() {
	if (!active)
		active = this;
}

bool EcsEventsBase::Initialize(const Script::WorldState& ws) {
	
	target = ws.Get(".target");
	if (target.IsEmpty()) {
		LOG("EcsEventsBase::Initialize: error: target state argument is required");
		return false;
	}
	
	Space& space = GetParent();
	state = space.FindNearestState(target);
	if (!state) {
		LOG("EcsEventsBase::Initialize: error: state '" << target << "' not found in parent space: " << space.GetDeepName());
		return false;
	}
	
	#if 0
	if (!WhenInitialize) {
		LOG("EcsEventsBase::Initialize: internal error: expected ecs system to prepare this");
		return false;
	}
	
	WhenInitialize(this);
	#endif
	
	return true;
}

bool EcsEventsBase::PostInitialize() {
	return true;
}

void EcsEventsBase::Uninitialize() {
	
}

bool EcsEventsBase::IsReady(PacketIO& io) {
	if (!state) return false;
	int keyboard_iter = state->GetInt(KEYBOARD_STATE_ITER);
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0 &&
		keyboard_iter != prev_iter;
	RTLOG("EcsEventsBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EcsEventsBase::Recv(int sink_ch, const Packet& in) {
	return true;
}

void EcsEventsBase::Finalize(RealtimeSourceConfig& cfg) {
	
}

bool EcsEventsBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}







#if defined flagSCREEN

struct EcsVideoBase::Binder : RTTIBase {
	RTTI_DECL0(Binder);
	
	BinderIfaceVideo* iface = 0;
	Ecs::Entity* win3d = 0; // Ref overly complicates ecs/mach relationship
	DrawCommandImageRenderer rend;
	bool win_inited = false;
	Size sz;
	double resize_multiplier = 0.01;
	ModelBuilder mb;
	
	void Visit(RuntimeVisitor& vis) {
		//vis & win3d;
	}
};


Array<EcsVideoBase::Binder> EcsVideoBase::binders;
EcsVideoBase* EcsVideoBase::active;

EcsVideoBase::EcsVideoBase() {
	if (!active)
		active = this;
}

bool EcsVideoBase::IsActive() const {
	return active == this;
}

bool EcsVideoBase::Initialize(const Script::WorldState& ws) {
	ISourceRef src = this->GetSource();
	int src_count = src->GetSourceCount();
	Value& val = src->GetSourceValue(src_count-1);
	src_type = val.GetFormat().vd;
	
	draw_mem = ws.Get(".drawmem") == "true";
	
	add_ecs = ws.GetBool(".add.ecs", false);
	if (GetSourceValue(0).GetFormat().IsReceipt())
		add_ecs = true;
	
	#ifdef flagGUI
	ents = GetMachine().Get<EntitySystem>();
	if (ents) {
		wins = ents->GetEngine().Get<Ecs::WindowSystem>();
	}
	#endif
	
	return true;
}

bool EcsVideoBase::PostInitialize() {
	
	// Remove alpha channel
	if (src_type == VD(CENTER, VIDEO)) {
		ISourceRef src = this->GetSource();
		int src_count = src->GetSourceCount();
		Serial::Link* link = GetLink();
		int src_ch = link->SideSinks().GetCount() == 1 ? link->SideSources().First().local_ch_i : src_count-1;
		Value& val = src->GetSourceValue(src_ch);
		Format fmt = val.GetFormat();
		fmt.vid.SetType(LightSampleFD::RGB_U8_LE);
		if (!link->NegotiateSourceFormat(src_ch, fmt))
			return false;
	}
	
	return true;
}

void EcsVideoBase::Stop() {
	state.Clear();
	ents.Clear();
	#ifdef flagGUI
	wins.Clear();
	#endif
	if (IsActive())
		binders.Clear();
}

void EcsVideoBase::Uninitialize() {
	if (IsActive()) {
		binders.Clear();
		active = 0;
	}
}

void EcsVideoBase::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<Atom>(this);
	if (IsActive())
		vis | binders;
	vis & state & ents;
	#ifdef flagGUI
	vis & wins;
	#endif
}

bool EcsVideoBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	
	bool render_win = false;
	
	#ifdef flagGUI
	if (wins && screen_id < wins->GetScreenCount()) {
		render_win = true;
	}
	#else
	ASSERT_(0, "cannot render without GUI compilation flag");
	#endif
	
	bool b =	io.active_sink_mask == iface_sink_mask &&
				io.full_src_mask == 0 &&
				(binders.GetCount() > 0 || render_win);
	RTLOG("EcsVideoBase::IsReady: " << (b ? "true" : "false") << " (binders " << binders.GetCount() << ", " << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	
	return b;
}

void EcsVideoBase::RedrawScreen() {
	#ifdef flagGUI
	Size sz = VirtualGui3DPtr ? VirtualGui3DPtr->GetSize() : Size(800, 600);
	#else
	Size sz = Size(800, 600);
	#endif
	
	if (pd.GetPageSize() != sz)
		pd.Create(sz);
	
	bool render_win = false;
	#ifdef flagGUI
	if (wins && screen_id < wins->GetScreenCount()) {
		ASSERT(sz.cx > 0 && sz.cy > 0);
		ProgPainter& pp = pd.GetProgPainter();
		Ecs::Windows& w = wins->GetScreen(screen_id);
		
		pd.cmd_screen_begin.Check();
		pp.Attach(w.GetCommandBegin(), w.GetCommandEnd());
		pd.cmd_screen_begin.Check();
		render_win = w.CheckRender();
		pd.cmd_screen_begin.Check();
		
		render_win = true;
		//LOG("EcsVideoBase::IsReady: prog:"); LOG(pd.Dump());
	}
	#endif
	
}

bool EcsVideoBase::Recv(int sink_ch, const Packet& in) {
	
	Format fmt = in->GetFormat();
	if (fmt.IsOrder()) {
		return true;
	}
	
	TODO
	
	return false;
}

void EcsVideoBase::Finalize(RealtimeSourceConfig& cfg) {
	if (IsActive()) {
		RedrawScreen();
		
		for (Binder& b : binders) {
			if (b.win3d) {
				Size& sz = b.sz;
				Ecs::CoreWindowLinkRef cw_link = b.win3d->Find<Ecs::CoreWindowLink>();
				Ecs::CoreWindow& cw = cw_link->GetWindow();
				Rect cw_rect = cw.GetStoredRect();
				sz = cw_rect.GetSize();
				
				// CoreWindow might not have calculated frame yet
				if (sz.IsEmpty()) {
					TopWindow* tw = cw.GetTopWindow();
					if (!tw)
						continue;
					sz = tw->GetSize();
					ASSERT(!sz.IsEmpty());
					// Add room for frame (which TopWindow itself doesn't know
					sz.cx += 30;
					sz.cy += 30;
				}
				
				DrawCommand *begin, *end;
				if (!b.iface->RenderProg(begin, end)) {
					ASSERT(0);
					continue;
				}
				
				DrawCommandImageRenderer::FindBegin(begin);
		
				dbg_win_id = 0;
				while (begin) {
					begin = ProcessWindow(b, begin);
					dbg_win_id++;
				}
				
				if (dbg_info)
					Panic("stop flood");
				
			}
		}
	}
}

bool EcsVideoBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	
	Format fmt = out.GetFormat();
	if (fmt.IsProg()) {
		
		if (binders.GetCount() == 1) {
			Binder& b = binders.Top();
			
			DrawCommand *begin = 0, *end = 0;
			b.iface->RenderProg(begin, end);
			
			#if 0
			b.pd.cmd_screen_begin.Check();
			
			InternalPacketData& data = out.SetData<InternalPacketData>();
			data.ptr = &b.pd.cmd_screen_begin;
			#else
			InternalPacketData& data = out.SetData<InternalPacketData>();
			data.ptr = begin;
			#endif
		}
		else if (binders.GetCount() > 1) {
			TODO // join multiple draw command vectors from binders to one
		}
		else {
			ASSERT_(0, "no binders");
			return false;
		}
	}
	else if (fmt.IsReceipt()){
		// pass
	}
	else {
		TODO
	}
	
	return true;
}

void EcsVideoBase::AddBinder(BinderIfaceVideo* iface) {
	Binder& b = binders.Add();
	b.iface = iface;
	
	if (active) {
		Ecs::DefaultGuiAppComponent* gui = CastPtr<Ecs::DefaultGuiAppComponent>(iface);
		if (gui) {
			Ecs::CoreWindowRef cw = gui->GetEntity()->Find<Ecs::CoreWindow>();
			if (cw)
				active->AddWindow3D(b, *cw);
		}
	}
}

void EcsVideoBase::RemoveBinder(BinderIfaceVideo* iface) {
	int pos = -1, i = 0;
	for (Binder& b0 : binders) {
		if (b0.iface == iface) {
			pos = i;
			break;
		}
		i++;
	}
	ASSERT(pos >= 0);
	if (pos < 0) return;
	
	Binder& b = binders[pos];
	if (active) {
		Ecs::DefaultGuiAppComponent* gui = CastPtr<Ecs::DefaultGuiAppComponent>(iface);
		if (gui) {
			Ecs::CoreWindowRef cw = gui->GetEntity()->Find<Ecs::CoreWindow>();
			if (cw)
				active->RemoveWindow3D(b, *cw);
		}
	}
}

void EcsVideoBase::AddWindow3D(Binder& b, Ecs::CoreWindow& cw) {
	ASSERT(!b.win3d);
	
	Ecs::PoolRef pool = ents->GetEngine().Get<Ecs::EntityStore>()->GetRoot();
	b.win3d = &*pool->Create<Ecs::Window3D>();
	
	Ecs::CoreWindowLinkRef linked_win = b.win3d->Get<Ecs::CoreWindowLink>();
	linked_win->Link(&cw);
}

void EcsVideoBase::RemoveWindow3D(Binder& b, Ecs::CoreWindow& cw) {
	if (b.win3d) {
		Ecs::CoreWindowLinkRef linked_win = b.win3d->Find<Ecs::CoreWindowLink>();
		if (linked_win) {
			linked_win->Unlink(&cw);
			b.win3d->Destroy();
		}
	}
}

DrawCommand* EcsVideoBase::ProcessWindow(Binder& b, DrawCommand* begin) {
	if (!DrawCommandImageRenderer::TrimBegin(begin))
		return 0;
	
	DrawCommand* end = DrawCommandImageRenderer::FindEnd(begin);
	
	if (dbg_info) {
		int i = 0;
		DrawCommand* it = begin;
		LOG("Window " << dbg_win_id);
		while (it != end && it) {
			LOG("\t" << i++ << ": " << it->ToString());
			it = it->next;
		}
	}
	
	ProcessWindowCommands(b, begin, end);
	
	// Move to the beginning of the next window
	return DrawCommandImageRenderer::MoveEnd(end->next);
}

void EcsVideoBase::ProcessWindowCommands(Binder& b, DrawCommand* begin, DrawCommand* end) {
	ASSERT(begin->type == DRAW_BIND_WINDOW);
	
	hash_t hash = begin->hash;
	ASSERT(hash);
	
	if (0) {
		DrawCommand* it = begin;
		int i = 0;
		while (it != end) {
			LOG(i++ << ": " << it->ToString());
			it = it->next;
		}
	}
	
	b.rend.ProcessWindowCommands(begin, end);
	
	if (!b.win_inited) {
		Ecs::ModelComponentRef mdl = b.win3d->Find<Ecs::ModelComponent>();
		ASSERT(mdl);
		if (!mdl) return;
		
		//ModelLoader& mdl_loader = mdl->GetLoader();
		//Model& src_mdl = mdl_loader.Realize();
		
		vec2 sz_vec(b.sz.cx * b.resize_multiplier, b.sz.cy * b.resize_multiplier);
		
		
		Mesh& plane_mesh = b.mb.AddPlane(vec3(0), sz_vec, 16);
		Model& src_mdl = b.mb;
		
		plane_mesh.CenterAnchor();
		plane_mesh.TransformVertices(AxesMat(0,M_PI/2,0));
		
		Image img = b.rend.GetImage();
		src_mdl.SetTexture(plane_mesh, TEXTYPE_DIFFUSE, img, "" );
		
		#if 0
		if (!mdl_state.LoadModel(src_mdl)) {
			LOG("FboProgAtomT<Gfx>::Send: error: could not load model");
			return;
		}
		
		auto& mtl = src_mdl.materials.Get(plane_mesh.material);
		
		win.tex_id = mtl.tex_id[TEXTYPE_DIFFUSE];
		win.tex = mdl_state.textures.Get(win.tex_id);
		#endif
		
		mdl->Attach(b.mb.Detach());
		mdl->SetModelChanged();
		b.win_inited = true;
	}
	else {
		// TODO window resize etc.
		
		// call Model::SetModelChanged()
		
	}
	#endif
}





#if 0
Callback1<EcsOglBase*> EcsOglBase::WhenInitialize;


EcsOglBase::EcsOglBase() {
	
}

bool EcsOglBase::Initialize(const Script::WorldState& ws) {
	
	if (!WhenInitialize) {
		LOG("EcsOglBase::Initialize: internal error: expected ecs system to prepare this");
		return false;
	}
	
	WhenInitialize(this);
	
	return true;
}

bool EcsOglBase::PostInitialize() {
	return true;
}

void EcsOglBase::Uninitialize() {
	
}

bool EcsOglBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0;
	RTLOG("EcsOglBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool EcsOglBase::Recv(int sink_ch, const Packet& in) {
	TODO
}

bool EcsOglBase::end(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

void EcsOglBase::AddBinder(BinderIfaceOgl* iface) {
	VectorFindAdd(binders, iface);
}

void EcsOglBase::RemoveBinder(BinderIfaceOgl* iface) {
	VectorRemoveKey(binders, iface);
}
#endif


NAMESPACE_PARALLEL_END
