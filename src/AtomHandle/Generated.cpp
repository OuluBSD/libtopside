#include "AtomHandle.h"

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagSCREEN
String HandleProgEvents::GetAction() {
	return "center.events.prog.ecs";
}

AtomTypeCls HandleProgEvents::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::ECS_PROG_EVENTS;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,RECEIPT),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	return t;
}

LinkTypeCls HandleProgEvents::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void HandleProgEvents::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HandleEventsBase>(this);
}

AtomTypeCls HandleProgEvents::GetType() const {
	return GetAtomType();
}
#endif


#if defined flagSCREEN
String PipeProgVideo::GetAction() {
	return "center.video.prog.pipe";
}

AtomTypeCls PipeProgVideo::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::PIPE_PROG_VIDEO;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,PROG),0);
	return t;
}

LinkTypeCls PipeProgVideo::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void PipeProgVideo::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HandleVideoBase>(this);
}

AtomTypeCls PipeProgVideo::GetType() const {
	return GetAtomType();
}
#endif


#if defined flagSCREEN
String HandleProgVideo::GetAction() {
	return "center.video.prog.ecs";
}

AtomTypeCls HandleProgVideo::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::ECS_PROG_VIDEO;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	return t;
}

LinkTypeCls HandleProgVideo::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void HandleProgVideo::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HandleVideoBase>(this);
}

AtomTypeCls HandleProgVideo::GetType() const {
	return GetAtomType();
}
#endif


}

}

