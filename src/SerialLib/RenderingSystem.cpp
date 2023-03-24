#include "SerialLib.h"

#if 0

#if (defined flagPOSIX && defined flagSCREEN && defined flagOGL)
NAMESPACE_PARALLEL_BEGIN
GfxAccelAtom<X11OglGfx>& Get_ScrX11Ogl_Ogl(One<ScrX11Ogl::NativeSinkDevice>& dev);
NAMESPACE_PARALLEL_END
#endif

NAMESPACE_TOPSIDE_BEGIN
using namespace Serial;


#ifdef flagSDL2
void RenderingSystem::Attach(String key, Parallel::BufferT<SdlSwGfx>* b) {
	if (key != "ecs") {
		RTLOG("RenderingSystem::Attach: warning: skipping unrelated key '" << key << "'");
		return;
	}
	
	TODO
	
}
#ifdef flagOGL
void RenderingSystem::Attach(String key, Parallel::BufferT<SdlOglGfx>* b) {
	if (key != "ecs") {
		RTLOG("RenderingSystem::Attach: warning: skipping unrelated key '" << key << "'");
		return;
	}
	
	TODO
	
}
#endif
#endif

ModelRef RenderingSystem::GetAddModelFile(String path) {
	int i = model_cache.Find(path);
	if (i >= 0)
		return model_cache[i].GetModel();
	ModelLoader& l = model_cache.Add(path);
	l.LoadModel(path);
	return l.GetModel();
}



bool RenderingSystem::Initialize() {
	return true;
}

void RenderingSystem::Start() {
	
}

void RenderingSystem::Update(double dt) {
	time += dt;
	
	if (is_dummy)
		return;
	
	if (!state) {
		Serial::Machine& mach = Serial::GetActiveMachine();
		SpaceStoreRef ents = mach.Get<SpaceStore>();
		
		#if (defined flagPOSIX && defined flagSCREEN)
		RefT_Atom<X11SwFboProg> x11_fbo = ents->GetRoot()->FindDeep<X11SwFboProg>();
		if (!state && x11_fbo) {
			state = &x11_fbo->data;
		}
		#ifdef flagOGL
		RefT_Atom<X11OglFboProg> x11_ogl_fbo = ents->GetRoot()->FindDeep<X11OglFboProg>();
		if (!state && x11_ogl_fbo) {
			state = &x11_ogl_fbo->data;
		}
		RefT_Atom<X11OglSinkDevice> x11_ogl_sink = ents->GetRoot()->FindDeep<X11OglSinkDevice>();
		if (!state && x11_ogl_sink) {
			state = &Get_ScrX11Ogl_Ogl(x11_ogl_sink->dev).GetBuffer().GetState();
		}
		#endif
		#endif
		
		#ifdef flagSDL2
		#ifdef flagOGL
		RefT_Atom<SdlOglFboProg> sdl2_ogl_fbo = ents->GetRoot()->FindDeep<SdlOglFboProg>();
		if (!state && sdl2_ogl_fbo) {
			state = &sdl2_ogl_fbo->data;
		}
		#endif
		#endif
		#ifdef flagVR
		
		#endif
		if (!state) return;
	}
	
	#if 1
	double phase_time = 3.0;
	float f = time / phase_time;
	float f2 = 1 - fabs(2 * f - 1);
	float angle = f * (2.0 * M_PI);
	state->light_dir = vec3 {sin(angle), 0.0, cos(angle)};
	#endif
	
	LOG("RenderingSystem::Update: TODO");
	
	for (Gu::GuboManager* scope : gubo_scopes) {
		scope->Load(*state);
	}
	
}

void RenderingSystem::Stop() {
	
}

void RenderingSystem::Uninitialize() {
	
}

void RenderingSystem::Attach(Gu::GuboManager* b) {
	VectorFindAdd(gubo_scopes, b);
}

NAMESPACE_TOPSIDE_END

#endif
