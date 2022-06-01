#ifndef _EcsVR_PaintingSystem_h_
#define _EcsVR_PaintingSystem_h_

NAMESPACE_ECS_BEGIN


class PaintingInteractionSystemHolo :
	public PaintingInteractionSystemBase
{
public:
	ECS_SYS_CTOR(PaintingInteractionSystemHolo);
	
	
protected:
	void Update(double dt) override;
	void Register(const LinkedList<EntityRef>& entities) override;
};


NAMESPACE_ECS_END

#endif
