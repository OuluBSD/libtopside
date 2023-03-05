#ifndef _GuboCore_TopSurface_h_
#define _GuboCore_TopSurface_h_


NAMESPACE_TOPSIDE_BEGIN



class TopSurface :
	public Surface,
	public Absolute2DProxy
{
	
public:
	RTTI_DECL2(TopSurface, Surface, Absolute2DProxy)
	TopSurface();
	virtual ~TopSurface() {}
	
	void CreateGeom2DComponent();
	void UpdateFromTransform2D();
	void RunInMachine();
	
	//Surface* GetSurface() override;
	
	
};


NAMESPACE_TOPSIDE_END


#endif
