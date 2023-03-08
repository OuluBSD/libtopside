#ifndef _GuboCore_TopSurface_h_
#define _GuboCore_TopSurface_h_


NAMESPACE_TOPSIDE_BEGIN



class TopSurface :
	public Surface
{
	
public:
	RTTI_DECL1(TopSurface, Surface)
	TopSurface();
	virtual ~TopSurface() {}
	
	void CreateGeom2DComponent();
	void UpdateFromTransform2D();
	void Run();
	void RunInMachine();
	void FocusEvent();
	
	//Surface* GetSurface() override;
	
	
};


NAMESPACE_TOPSIDE_END


#endif
