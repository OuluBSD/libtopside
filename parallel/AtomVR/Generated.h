#ifndef _AtomVR_Generated_h_
#define _AtomVR_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagVR && defined flagOGL
class X11OglHoloFboProg : public X11OglHoloFboBase {

public:
	RTTI_DECL1(X11OglHoloFboProg, X11OglHoloFboBase)
	COPY_PANIC(X11OglHoloFboProg)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.holo.fbo.program")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagVR && defined flagOGL
using X11OglHoloFboProgRef = Ref<X11OglHoloFboProg, AtomParent>;
#endif

}

}



#endif
