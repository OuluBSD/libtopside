#include "AtomEcs.h"

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagSCREEN
String EcsProgVideo::GetAction() {
	return "center.video.prog.ecs";
}

AtomTypeCls EcsProgVideo::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::ECS_PROG_VIDEO;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,PROG),0);
	return t;
}

LinkTypeCls EcsProgVideo::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void EcsProgVideo::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<EcsVideoBase>(this);
}

AtomTypeCls EcsProgVideo::GetType() const {
	return GetAtomType();
}
#endif


}

}

