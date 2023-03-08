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
	
	void CreateGeom3DComponent();
	void UpdateFromTransform3D();
	void FocusEvent();
	void RunInMachine();
	void OpenMain();
	int Run();
	
};


NAMESPACE_TOPSIDE_END


#endif
