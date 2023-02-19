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
	t.sub = SubAtomCls::HANDLE_PROG_EVENTS;
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
String CenterProgPipe::GetAction() {
	return "center.video.prog.pipe";
}

AtomTypeCls CenterProgPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::CENTER_PROG_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,PROG),0);
	return t;
}

LinkTypeCls CenterProgPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void CenterProgPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HandleVideoBase>(this);
}

AtomTypeCls CenterProgPipe::GetType() const {
	return GetAtomType();
}
#endif


#if defined flagSCREEN
String OglProgPipe::GetAction() {
	return "ogl.prog.pipe";
}

AtomTypeCls OglProgPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::OGL_PROG_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(OGL,ORDER),0);
	t.AddOut(VD(OGL,PROG),0);
	return t;
}

LinkTypeCls OglProgPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void OglProgPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HandleVideoBase>(this);
}

AtomTypeCls OglProgPipe::GetType() const {
	return GetAtomType();
}
#endif


#if defined flagSCREEN
String HandleProgVideo::GetAction() {
	return "center.video.prog.ecs";
}

AtomTypeCls HandleProgVideo::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::HANDLE_PROG_VIDEO;
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

