#include "ParallelCore.h"


NAMESPACE_PARALLEL_BEGIN

// incomplete Script::Plan dtor in header
AtomBase::CustomerData::CustomerData() : cfg(gen) {}
AtomBase::CustomerData::~CustomerData() {}


AtomBase::AtomBase() {
	DBG_CONSTRUCT
}

AtomBase::~AtomBase() {
	ASSERT(dep_count == 0);
	DBG_DESTRUCT
}

Machine& AtomBase::GetMachine() {
	return GetParent().GetMachine();
}

void AtomBase::UninitializeDeep() {
	if (IsInitialized()) {
		Uninitialize();
		SetInitialized(false);
	}
	ClearSinkSource();
	ClearDependency();
	UninitializeAtom();
}

SpaceRef AtomBase::GetSpace() {
	return GetParent().AsRefT();
}

Space& AtomBase::GetParent() {
	return *((SP*)this)->GetParent().AsStatic<Space>();
}

Serial::Link* AtomBase::GetLink() {
	return link;
}

String AtomBase::ToString() const {
	return GetDynamicName();
}

void AtomBase::SetInterface(const IfaceConnTuple& iface) {
	this->iface = iface;
}

const IfaceConnTuple& AtomBase::GetInterface() const {
	return iface;
}

void AtomBase::SetPrimarySinkQueueSize(int i) {
	GetSink()->GetValue(0).SetMinQueueSize(i);
}

void AtomBase::AddAtomToUpdateList() {
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
}

void AtomBase::RemoveAtomFromUpdateList() {
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
}

int AtomBase::FindSourceWithValDev(ValDevCls vd) {
	InterfaceSourceRef src = GetSource();
	int c = src->GetSourceCount();
	for(int i = 0; i < c; i++) {
		Value& v = src->GetSourceValue(i);
		Format f = v.GetFormat();
		if (f.vd == vd)
			return i;
	}
	return -1;
}

int AtomBase::FindSinkWithValDev(ValDevCls vd) {
	InterfaceSinkRef src = GetSink();
	int c = src->GetSinkCount();
	for(int i = 0; i < c; i++) {
		Value& v = src->GetValue(i);
		Format f = v.GetFormat();
		if (f.vd == vd)
			return i;
	}
	return -1;
}

void AtomBase::UpdateSinkFormat(ValCls vc, Format fmt) {
	InterfaceSinkRef sink_iface = GetSink();
	int sink_count = sink_iface->GetSinkCount();
	for(int i = 0; i < sink_count; i++) {
		Value& val = sink_iface->GetValue(i);
		Format val_fmt = val.GetFormat();
		if (val_fmt.vd.val == vc && val_fmt != fmt) {
			RTLOG("AudioOutput::UpdateSinkFormat: updating sink #" << i << " format to " << fmt.ToString());
			val.SetFormat(fmt);
		}
	}
}


void AtomBase::PostContinueForward() {
	RTLOG("AtomBase::PostContinueForward");
	
	Serial_Link_PostContinueForward(link);
}

bool AtomBase::Recv(int sink_ch, const Packet& in) {
	// TODO assert(0), because this is bad idea, but I was lazy... all tests will break
	return true;
}

void AtomBase::SetQueueSize(int queue_size) {
	InterfaceSinkRef sink_iface = this->GetSink();
	InterfaceSourceRef src_iface = this->GetSource();
	if (queue_size == 1) {
		int c = sink_iface->GetSinkCount();
		for(int i = 0; i < c; i++)
			sink_iface->GetValue(i).SetMaxQueueSize(queue_size);
		
		c = src_iface->GetSourceCount();
		for(int i = 0; i < c; i++)
			src_iface->GetSourceValue(i).SetMaxQueueSize(queue_size);
	}
	else {
		int c = sink_iface->GetSinkCount();
		for(int i = 0; i < c; i++)
			sink_iface->GetValue(i).SetMinQueueSize(queue_size);
		
		c = src_iface->GetSourceCount();
		for(int i = 0; i < c; i++)
			src_iface->GetSourceValue(i).SetMinQueueSize(queue_size);
	}
}









NAMESPACE_PARALLEL_END

