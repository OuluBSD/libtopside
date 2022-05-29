#ifndef _AtomLocal_Generated_h_
#define _AtomLocal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagVR
class SpatialInteractionSA : public SpatialInteractionAtom {

public:
	RTTI_DECL1(SpatialInteractionSA, SpatialInteractionAtom)
	COPY_PANIC(SpatialInteractionSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("vr.spatial.interaction")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagVR
using SpatialInteractionSARef = Ref<SpatialInteractionSA, AtomParent>;
#endif

}

}



#endif
