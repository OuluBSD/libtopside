#ifndef _GuboCore_TopGubo_h_
#define _GuboCore_TopGubo_h_

NAMESPACE_UPP

class TopGubo :
	public Gubo,
	public Absolute3DProxy
{
	
public:
	RTTI_DECL2(TopGubo, Gubo, Absolute3DProxy)
	TopGubo();
	virtual ~TopGubo() {}
	
	void CreateGeom2DComponent();
	void UpdateFromTransform3D();
	
	Gubo* GetGubo() override;
	
	
};

END_UPP_NAMESPACE

#endif
