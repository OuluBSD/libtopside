#include "AtomHandle.h"
#include <SerialLib/SerialLib.h>


NAMESPACE_PARALLEL_BEGIN



Callback1<HandleEventsBase*> HandleEventsBase::WhenInitialize;

HandleEventsBase* HandleEventsBase::active;

HandleEventsBase::HandleEventsBase() {
	if (!active)
		active = this;
}

bool HandleEventsBase::Initialize(const Script::WorldState& ws) {
	
	target = ws.Get(".target");
	if (target.IsEmpty()) {
		LOG("HandleEventsBase::Initialize: error: target state argument is required");
		return false;
	}
	
	Space& space = GetParent();
	state = space.FindNearestState(target);
	if (!state) {
		LOG("HandleEventsBase::Initialize: error: state '" << target << "' not found in parent space: " << space.GetDeepName());
		return false;
	}
	
	#if 0
	if (!WhenInitialize) {
		LOG("HandleEventsBase::Initialize: internal error: expected ecs system to prepare this");
		return false;
	}
	
	WhenInitialize(this);
	#endif
	
	return true;
}

bool HandleEventsBase::PostInitialize() {
	return true;
}

void HandleEventsBase::Uninitialize() {
	
}

bool HandleEventsBase::IsReady(PacketIO& io) {
	if (!state) return false;
	int keyboard_iter = state->GetInt(KEYBOARD_STATE_ITER);
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0 &&
		keyboard_iter != prev_iter;
	RTLOG("HandleEventsBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool HandleEventsBase::Recv(int sink_ch, const Packet& in) {
	return true;
}

void HandleEventsBase::Finalize(RealtimeSourceConfig& cfg) {
	
}

bool HandleEventsBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	return true;
}







#if defined flagSCREEN

struct HandleVideoBase::Binder : RTTIBase {
	RTTI_DECL0(Binder);
	
	BinderIfaceVideo* iface = 0;
	AbsoluteInterface* abs_iface = 0;
	DrawCommandImageRenderer rend;
	bool win_inited = false;
	Size sz;
	double resize_multiplier = 0.01;
	ModelBuilder mb;
	
	void Visit(RuntimeVisitor& vis) {
		//vis & win3d;
	}
};


Array<HandleVideoBase::Binder> HandleVideoBase::binders;
HandleVideoBase* HandleVideoBase::active;

HandleVideoBase::HandleVideoBase() {
	if (!active) {
		active = this;
	}
}

bool HandleVideoBase::IsActive() const {
	return active == this;
}

bool HandleVideoBase::Initialize(const Script::WorldState& ws) {
	ISourceRef src = this->GetSource();
	int src_count = src->GetSourceCount();
	Value& val = src->GetSourceValue(src_count-1);
	src_type = val.GetFormat().vd;
	
	screen_id = ws.GetInt(".screen.id", -1);
	draw_mem = ws.Get(".drawmem") == "true";
	
	add_ecs = ws.GetBool(".add.ecs", false);
	if (GetSourceValue(0).GetFormat().IsReceipt())
		add_ecs = true;
	
	#ifdef flagGUI
	wins = GetMachine().Get<WindowSystem>();
	gubos = GetMachine().Get<GuboSystem>();
	#endif
	
	return true;
}

bool HandleVideoBase::PostInitialize() {
	
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
	
	if (active == this)
		AddBinders();
	
	return true;
}

void HandleVideoBase::Stop() {
	state.Clear();
	#ifdef flagGUI
	wins.Clear();
	gubos.Clear();
	#endif
	if (IsActive())
		binders.Clear();
}

void HandleVideoBase::Uninitialize() {
	if (IsActive()) {
		binders.Clear();
		active = 0;
	}
}

void HandleVideoBase::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<Atom>(this);
	if (IsActive())
		vis | binders;
	vis & state;
	
	#ifdef flagGUI
	vis & wins & gubos;
	#endif
}

bool HandleVideoBase::IsReady(PacketIO& io) {
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
	RTLOG("HandleVideoBase::IsReady: " << (b ? "true" : "false") << " (binders " << binders.GetCount() << ", " << io.nonempty_sinks << ", " << io.sinks.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	
	return b;
}

void HandleVideoBase::RedrawScreen() {
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
		ProgPainter& pp = pd.GetPainter();
		
		WindowManager& w = wins->GetScope(screen_id);
		
		pd.cmd_screen_begin.Check();
		
		pp.Attach(w.GetCommandBegin(), w.GetCommandEnd()); // <-- attach window to this
		
		pd.cmd_screen_begin.Check();
		
		render_win = w.CheckRender(); // <--- render
		
		pd.cmd_screen_begin.Check();
		
		pp.Dump(); TODO
		
		render_win = true;
		//LOG("HandleVideoBase::IsReady: prog:"); LOG(pd.Dump());
	}
	#endif
}

bool HandleVideoBase::Recv(int sink_ch, const Packet& in) {
	
	Format fmt = in->GetFormat();
	if (fmt.IsOrder()) {
		return true;
	}
	
	TODO
	
	return false;
}

void HandleVideoBase::Finalize(RealtimeSourceConfig& cfg) {
	if (IsScreenMode()) {
		RedrawScreen();
	}
	else if (IsActive()) {
		
		for (Binder& b : binders) {
			Absolute2DInterface* abs2d_iface = CastPtr<Absolute2DInterface>(b.abs_iface);
			
			if (abs2d_iface) {
				Size& sz = b.sz;
				//Handle::Geom2DComponentLinkRef cw_link = b.win_entity->Find<Handle::Geom2DComponentLink>();
				//Handle::Geom2DComponent& cw = cw_link->GetWindow();
				Ctrl* ctrl = abs2d_iface->GetCtrl();
				ASSERT(ctrl);
				
				TODO // Move Geom2DComponent content to ParallelLib
				#if 0
				Rect cw_rect = cw.GetStoredRect();
				sz = cw_rect.GetSize();
				
				// Geom2DComponent might not have calculated frame yet
				if (sz.IsEmpty()) {
					TopWindow* tw = ctrl->GetTopWindow();
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
				
				#if 1
				DrawCommand* it = begin;
				int i = 0;
				bool has_cmd = false;
				while (it) {
					LOG(i++ << ": " << it->ToString());
					if (!has_cmd && it->type != 0)
						has_cmd = true;
					it = it->next;
				}
				ASSERT(has_cmd);
				#endif
				
				DrawCommandImageRenderer::FindBegin(begin);
		
				dbg_win_id = 0;
				while (begin) {
					begin = ProcessWindow(b, begin);
					dbg_win_id++;
				}
				
				if (dbg_info)
					Panic("stop flood");
				
				#endif
			}
		}
	}
}

bool HandleVideoBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	Format fmt = out.GetFormat();
	if (fmt.IsProg()) {
		if (IsScreenMode()) {
			if (wins && screen_id < wins->GetScreenCount()) {
				ProgPainter& pp = pd.GetPainter();
				InternalPacketData& data = out.SetData<InternalPacketData>();
				data.ptr = pp.GetBegin();
			}
			else {
				ASSERT_(0, "no screen");
				return false;
			}
		}
		else {
			if (binders.GetCount() == 1) {
				Binder& b = binders.Top();
				
				DrawCommand *begin = 0, *end = 0;
				b.iface->RenderProg(begin, end);
				
				InternalPacketData& data = out.SetData<InternalPacketData>();
				data.ptr = begin;
			}
			else if (binders.GetCount() > 1) {
				TODO // join multiple draw command vectors from binders to one
			}
			else {
				ASSERT_(0, "no binders");
				return false;
			}
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

void HandleVideoBase::AddBinders() {
	for (Binder& b : binders)
		if (!b.abs_iface)
			AddBinderActive(b);
}

void HandleVideoBase::AddBinderActive(Binder& b) {
	TODO
	#if 0
	Handle::DefaultGuiAppComponent* gui = CastPtr<Handle::DefaultGuiAppComponent>(b.iface);
	if (gui) {
		Handle::Geom2DComponentRef cw = gui->GetEntity()->Find<Handle::Geom2DComponent>();
		if (cw)
			AddWindow3D(b, *cw);
	}
	#endif
}

void HandleVideoBase::AddBinder(BinderIfaceVideo* iface) {
	Binder& b = binders.Add();
	b.iface = iface;
	
	if (active)
		active->AddBinderActive(b);
}

void HandleVideoBase::RemoveBinder(BinderIfaceVideo* iface) {
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
	
	TODO
	#if 0
	if (active) {
		Handle::DefaultGuiAppComponent* gui = CastPtr<Handle::DefaultGuiAppComponent>(iface);
		if (gui) {
			Handle::Geom2DComponentRef cw = gui->GetEntity()->Find<Handle::Geom2DComponent>();
			if (cw)
				active->RemoveWindow3D(b, *cw);
		}
	}
	#endif
}

#if 0
void HandleVideoBase::AddWindow3D(Binder& b, Handle::Geom2DComponent& cw) {
	ASSERT(!b.win_entity);
	
	Handle::PoolRef pool = ents->GetEngine().Get<Handle::EntityStore>()->GetRoot();
	b.win_entity = &*pool->Create<Handle::Window3D>();
	
	Handle::Geom2DComponentLinkRef linked_win = b.win_entity->Get<Handle::Geom2DComponentLink>();
	linked_win->Link(&cw);
}

void HandleVideoBase::RemoveWindow3D(Binder& b, Handle::Geom2DComponent& cw) {
	if (b.win_entity) {
		Handle::Geom2DComponentLinkRef linked_win = b.win_entity->Find<Handle::Geom2DComponentLink>();
		if (linked_win) {
			linked_win->Unlink(&cw);
			b.win_entity->Destroy();
		}
	}
}
#endif

DrawCommand* HandleVideoBase::ProcessWindow(Binder& b, DrawCommand* begin) {
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

void HandleVideoBase::ProcessWindowCommands(Binder& b, DrawCommand* begin, DrawCommand* end) {
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
	
	TODO
	#if 0
	if (!b.win_inited) {
		Handle::ModelComponentRef mdl = b.win_entity->Find<Handle::ModelComponent>();
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

#endif



#if 0
Callback1<HandleOglBase*> HandleOglBase::WhenInitialize;


HandleOglBase::HandleOglBase() {
	
}

bool HandleOglBase::Initialize(const Script::WorldState& ws) {
	
	if (!WhenInitialize) {
		LOG("HandleOglBase::Initialize: internal error: expected ecs system to prepare this");
		return false;
	}
	
	WhenInitialize(this);
	
	return true;
}

bool HandleOglBase::PostInitialize() {
	return true;
}

void HandleOglBase::Uninitialize() {
	
}

bool HandleOglBase::IsReady(PacketIO& io) {
	dword iface_sink_mask = iface.GetSinkMask();
	bool b =
		io.active_sink_mask == iface_sink_mask &&
		io.full_src_mask == 0;
	RTLOG("HandleOglBase::IsReady: " << (b ? "true" : "false") << " (" << io.nonempty_sinks << ", " << io.sink.GetCount() << ", " << HexStr(iface_sink_mask) << ", " << HexStr(io.active_sink_mask) << ")");
	return b;
}

bool HandleOglBase::Recv(int sink_ch, const Packet& in) {
	TODO
}

bool HandleOglBase::end(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	TODO
}

void HandleOglBase::AddBinder(BinderIfaceOgl* iface) {
	VectorFindAdd(binders, iface);
}

void HandleOglBase::RemoveBinder(BinderIfaceOgl* iface) {
	VectorRemoveKey(binders, iface);
}
#endif


NAMESPACE_PARALLEL_END

