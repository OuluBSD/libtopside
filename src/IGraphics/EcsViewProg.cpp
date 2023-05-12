#include "IGraphics.h"

#include <EcsLib/EcsLib.h>

NAMESPACE_PARALLEL_BEGIN


EcsViewProg::EcsViewProg() {
	
}


void EcsViewProg::Initialize() {
	
}


void EcsViewProg::Uninitialize() {
	
}


bool EcsViewProg::Arg(const String& key, const String& value) {
	
	return true;
}


bool EcsViewProg::Render(Draw& fb) {
	GfxStateDraw* sd = CastPtr<GfxStateDraw>(&fb);
	ASSERT(sd);
	
	GfxDataState& state = sd->GetState();
	ASSERT(state.mach);
	
	Machine& mach = *state.mach;
	Ecs::Engine& eng = mach.GetEngine();
	
	Ecs::RenderingSystemRef rend = eng.Get<Ecs::RenderingSystem>();
	ASSERT(rend);
	
	rend->Render(state);
	
	return true;
}


NAMESPACE_PARALLEL_END
