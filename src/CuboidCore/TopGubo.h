#ifndef _GuboCore_TopGubo_h_
#define _GuboCore_TopGubo_h_

NAMESPACE_UPP

class TopGubo :
	public Gubo,
	public AbsoluteWindowProxy
{
	
public:
	RTTI_DECL1(TopGubo, Gubo)
	TopGubo();
	virtual ~TopGubo() {}
	
	void CreateCoreWindow();
	void UpdateFromTransform3D();
	
	void SetFrameRect(const Rect& r) override;
	Gubo* GetWindowGubo() override;
	
	
};

END_UPP_NAMESPACE

#endif
