#ifndef _AtomEcs_Generated_h_
#define _AtomEcs_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagSCREEN
class EcsProgVideo : public EcsVideoBase {

public:
	RTTI_DECL1(EcsProgVideo, EcsVideoBase)
	COPY_PANIC(EcsProgVideo)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.prog.ecs")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
using EcsProgVideoRef = Ref<EcsProgVideo, AtomParent>;
#endif

}

}



#endif
