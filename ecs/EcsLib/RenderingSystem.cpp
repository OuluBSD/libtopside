#include "EcsLib.h"


#if 0

NAMESPACE_TOPSIDE_BEGIN




RenderingSystem::RenderingSystem(Machine& m) : RefScopeParent<RefParent1<Machine>>(m) {
	invalid = 0;
	vscreen_sz = Size(800,600);
}

bool RenderingSystem::Initialize() {
	
	return true;
}

void RenderingSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void RenderingSystem::Update(double dt) {

	for (DisplaySourceRef src : srcs) {
		DisplayStream& stream = src->GetStream(DisCtx);
		int buf_sz = stream.GetDisplay().GetQueueSize();
		bool buffer_full = buf_sz >= 2;
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render) {
			#if DEBUG_DISPLAY_PIPE
			DISPLAYLOG("begin source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->BeginStream(DisCtx);
		}
	}
	
	for (DisplayExchangePointRef expt : expts) {
		DisplaySourceRef src = expt->Source();
		off32 begin_offset = expt->GetOffset();
		
		expt->SetOffset(begin_offset);
		expt->Update(dt);
		
		off32 end_offset = expt->GetOffset();
		src->SetOffset(begin_offset, end_offset);
		
		#if DEBUG_DISPLAY_PIPE
		off32 diff = off32::GetDifference(begin_offset, end_offset);
		if (diff) {
			auto sink = expt->Sink();
			DISPLAYLOG("sink " << HexStr((size_t)&*sink) << "<" << sink->GetConfigString() << "> consumed " << diff.ToString());
		}
		#endif
	}
	
	for (DisplaySourceRef src :srcs) {
		const auto& cfg = src->Cfg();
		if (cfg.begin_offset != cfg.end_offset) {
			#if DEBUG_DISPLAY_PIPE
			DISPLAYLOG("end source " << HexStr((size_t)&*src) << "<" << src->GetConfigString() << ">");
			#endif
			
			src->EndStream(DisCtx);
		}
	}
}

void RenderingSystem::Stop() {
	
}

void RenderingSystem::Uninitialize() {
	
	//Close();
	
}

void RenderingSystem::Add(DisplaySourceRef src) {
	srcs.FindAdd(src);
	
	Ref<RegistrySystem> reg = GetMachine().TryGet<RegistrySystem>();
	if (reg)
		src->SetTitle(reg->GetAppName());
}

void RenderingSystem::Remove(DisplaySourceRef src) {
	srcs.RemoveKey(src);
}

void RenderingSystem::Add(DisplaySinkRef r) {
	sinks.FindAdd(src);
}

void RenderingSystem::Add(DisplayExchangePointRef r) {
	expts.FindAdd(src);
}

void RenderingSystem::Remove(DisplaySinkRef r) {
	sinks.RemoveKey(src);
}

void RenderingSystem::Remove(DisplayExchangePointRef r) {
	expts.RemoveKey(src);
}




NAMESPACE_TOPSIDE_END

#endif
