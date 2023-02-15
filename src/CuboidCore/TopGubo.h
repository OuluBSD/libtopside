#ifndef _GuboCore_TopGubo_h_
#define _GuboCore_TopGubo_h_


NAMESPACE_TOPSIDE_BEGIN


class TopGubo :
	public Gubo
{
	
public:
	RTTI_DECL1(TopGubo, Gubo)
	TopGubo();
	virtual ~TopGubo() {}
	
	void CreateGeom2DComponent();
	void UpdateFromTransform3D();
	
	
};


NAMESPACE_TOPSIDE_END


#endif
