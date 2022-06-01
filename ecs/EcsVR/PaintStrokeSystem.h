#ifndef _EcsVR_PaintStrokeSystem_h_
#define _EcsVR_PaintStrokeSystem_h_

NAMESPACE_ECS_BEGIN


class PaintStrokeSystemHolo :
	public PaintStrokeSystemBase,
	public HolographicScopeBinder
{
public:
	RTTI_DECL2(PaintStrokeSystem, PaintStrokeSystemBase, HolographicScopeBinder)
	ECS_SYS_CTOR(PaintStrokeSystem);
	SYS_DEF_VISIT
	~PaintStrokeSystem() = default;
	
protected:
	bool Initialize() override;
	
};


NAMESPACE_ECS_END

#endif
