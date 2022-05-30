#include "EcsLib.h"

NAMESPACE_ECS_BEGIN


void Renderable::Initialize() {
	Engine& e = GetEngine();
	RenderingSystemRef rend = e.TryGet<RenderingSystem>();
	if (rend)
		rend->AddRenderable(AsRef<ComponentBase>());
}

void Renderable::Uninitialize() {
	Engine& e = GetEngine();
	RenderingSystemRef rend = e.TryGet<RenderingSystem>();
	if (rend)
		rend->RemoveRenderable(AsRef<ComponentBase>());
}



bool RenderingSystem::Initialize() {
	return true;
}


#ifdef flagSDL2
void RenderingSystem::Attach(String key, Parallel::BufferT<SdlSwGfx>* b) {
	if (key != "ecs") {
		RTLOG("RenderingSystem::Attach: warning: skipping unrelated key '" << key << "'");
		return;
	}
	
	TODO
	/*ASSERT(!sdl_sw_buf);
	if (sdl_sw_buf) sdl_sw_buf->RemoveBinder(this);
	
	ASSERT(b);
	b->AddBinder(this);
	sdl_sw_buf = b;*/
}
#ifdef flagOGL
void RenderingSystem::Attach(String key, Parallel::BufferT<SdlOglGfx>* b) {
	if (key != "ecs") {
		RTLOG("RenderingSystem::Attach: warning: skipping unrelated key '" << key << "'");
		return;
	}
	
	TODO
	/*ASSERT(!buf);
	if (sdl_ogl_buf) sdl_ogl_buf->RemoveBinder(this);
	
	ASSERT(b);
	b->AddBinder(this);
	sdl_ogl_buf = b;*/
}
#endif
#endif

void RenderingSystem::AddViewable(ViewableRef v) {
	ASSERT(v);
	ArrayFindAdd(views, v);
}

void RenderingSystem::RemoveViewable(ViewableRef v) {
	ASSERT(v);
	ArrayRemoveKey(views, v);
}

void RenderingSystem::AddRenderable(RenderableRef b) {
	ASSERT(b);
	ArrayFindAdd(rends, b);
}

void RenderingSystem::RemoveRenderable(RenderableRef b) {
	ASSERT(b);
	ArrayRemoveKey(rends, b);
}

void RenderingSystem::AddModel(ModelComponentRef m) {
	ASSERT(m);
	ArrayFindAdd(models, m);
}

void RenderingSystem::RemoveModel(ModelComponentRef m) {
	ASSERT(m);
	ArrayRemoveKey(models, m);
}

void RenderingSystem::AddCamera(CameraBase& c) {
	VectorFindAdd(cams, &c);
}

void RenderingSystem::RemoveCamera(CameraBase& c) {
	VectorRemoveKey(cams, &c);
}

void RenderingSystem::Start() {
	
}

void RenderingSystem::Update(double dt) {
	
	//if (state.IsEmpty()) {
	if (!state) {
		Serial::Machine& mach = Serial::GetActiveMachine();
		SpaceStoreRef ents = mach.Get<SpaceStore>();
		
		#ifdef flagSCREEN
		RefT_Atom<X11SwFboProg> x11_fbo = ents->GetRoot()->FindDeep<X11SwFboProg>();
		if (!state && x11_fbo) {
			state = &x11_fbo->data.accel_state;
		}
		#ifdef flagOGL
		RefT_Atom<X11OglFboProg> x11_ogl_fbo = ents->GetRoot()->FindDeep<X11OglFboProg>();
		if (!state && x11_ogl_fbo) {
			state = &x11_ogl_fbo->data.accel_state;
		}
		#ifdef flagSDL2
		RefT_Atom<SdlOglFboProg> sdl2_ogl_fbo = ents->GetRoot()->FindDeep<SdlOglFboProg>();
		if (!state && sdl2_ogl_fbo) {
			state = &sdl2_ogl_fbo->data.accel_state;
		}
		#endif
		#endif
		#endif
		#ifdef flagVR
		/*#ifdef flagOGL
		RefT_Atom<X11OglHoloFboProg> x11_holo_ogl_fbo = ents->GetRoot()->FindDeep<X11OglHoloFboProg>();
		if (!state && x11_holo_ogl_fbo) {
			state = &x11_holo_ogl_fbo->data.accel_state;
		}
		#endif*/
		#endif
		//GfxDataState& ds = FboAtomT<X11SwGfx>::data.accel_state
		if (!state) TODO
	}
	
	for (ModelComponentRef& m : models) {
		
		m->Load(*state);
		
	}
	
	for (CameraBase* cb : cams) {
		
		cb->Load(*state);
		
	}
}

void RenderingSystem::Stop() {
	
}

void RenderingSystem::Uninitialize() {
	ASSERT_(rends.IsEmpty(), "RenderingSystem must be added to Engine before EntityStore");
	
	/*if (buf) {
		buf->RemoveBinder(this);
		buf = 0;
	}*/
}

void RenderingSystem::Render(GfxDataState& data) {
	//DUMPC(rends);
	
	TODO
	
	/*for (RenderableRef& rend : rends) {
		rend->cb(data);
	}
	
	for (ViewableRef& view : views) {
		view->cb(data);
	}*/
	
}


NAMESPACE_ECS_END
