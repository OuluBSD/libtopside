#ifndef _GuboCore_TopGubo_h_
#define _GuboCore_TopGubo_h_

NAMESPACE_UPP

class TopGubo :
	public Gubo,
	public Absolute3DProxy
{
	
public:
	RTTI_DECL1(TopGubo, Gubo)
	TopGubo();
	virtual ~TopGubo() {}
	
	void CreateGeom2DComponent();
	void UpdateFromTransform3D();
	
	void SetFrameCubf(const Cubf& r) override;
	Gubo* GetGubo() override;
	
	
};

END_UPP_NAMESPACE

#endif
