#ifndef _OpenLib_HolographicRenderer_h_
#define _OpenLib_HolographicRenderer_h_


NAMESPACE_TOPSIDE_BEGIN


class HolographicRenderer :
	public System<HolographicRenderer>
{
	
public:
	void Visit(RuntimeVisitor& vis) override {}
	SYS_RTTI(HolographicRenderer)
	SYS_CTOR(HolographicRenderer);
	
	
};


NAMESPACE_TOPSIDE_END


#endif
