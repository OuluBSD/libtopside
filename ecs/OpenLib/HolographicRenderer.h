#ifndef _OpenLib_HolographicRenderer_h_
#define _OpenLib_HolographicRenderer_h_


NAMESPACE_OULU_BEGIN


class HolographicRenderer :
	public System<HolographicRenderer>
{
	
public:
	void Visit(RuntimeVisitor& vis) override {}
	SYS_CTOR(HolographicRenderer);
	
	
};


NAMESPACE_OULU_END


#endif
