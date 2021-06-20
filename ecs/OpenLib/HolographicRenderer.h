#ifndef _OpenLib_HolographicRenderer_h_
#define _OpenLib_HolographicRenderer_h_


NAMESPACE_TOPSIDE_BEGIN


class HolographicRenderer :
	public System<HolographicRenderer>
{
	
public:
	COMP_DEF_VISIT
	SYS_RTTI(HolographicRenderer)
	SYS_CTOR(HolographicRenderer);
	SYS_DEF_VISIT
	
};


NAMESPACE_TOPSIDE_END


#endif
