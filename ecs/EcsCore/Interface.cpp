#include "EcsCore.h"

NAMESPACE_TOPSIDE_BEGIN

/*

void InterfaceBase::DbgChk(InterfaceBase* b) {
	for(auto c: b->conns) {
		ComponentBase* cb = c->AsComponentBase();
		ASSERT(cb->GetEntityPtr());
	}
}

void InterfaceBase::RemoveConnection(InterfaceBase* b) {
	int i=0;
	for(auto c: conns) {
		if(c==b) {
			Unlink0(b);
			b->Unlink0(this);
			conns.Remove(i);
			break;
		}
		i++;
	}
}






String InterfaceBase::GetComponentBaseTypeString(ComponentBase* base) {
	return base->GetType().CleanDemangledName();
}*/


/*void DisplaySource::SetTitle(String s) {
	for (Ref<DisplaySink> sink : GetConnections())
		sink->SetTitle(s);
}*/





#if 0
#ifdef flagDEBUG
void InterfaceDebugPrint(TypeId type, String s) {
	if (type != typeid(RouteSource)) {
		LOG(s);
	}
}
#endif
#endif


/*void AudioSource::DefaultEmitAudioSource(double dt, int sink_limit) {
	const auto& sinks = AudioSource::GetConnections();
	if (sink_limit >= 0) {
		//for(int i = 0; i < sinks.GetCount(); i++) {LOG(i << ": " << sinks[i]->AsComponentBase()->GetType().DemangledName());}
		ASSERT_(sinks.GetCount() <= sink_limit,
			"Only the support for single audio sink is implemented currently");
		int i = 0;
		for(Ref<AudioSink> c : sinks) {
			if (i++ >= sink_limit)
				break;
			c->RecvAudio(*this, dt);
		}
	}
	else {
		for(Ref<AudioSink> c : sinks)
			c->RecvAudio(*this, dt);
	}
}*/










#if 0
void ActionSink::OnLink(Source src, Cookie src_c, Cookie sink_c) {
	TODO
	/*ActionSource* src = dynamic_cast<ActionSource*>(iface);
	ASSERT(src);
	return src ? OnLinkActionSource(*src) : 0;*/
}
#endif

NAMESPACE_TOPSIDE_END

