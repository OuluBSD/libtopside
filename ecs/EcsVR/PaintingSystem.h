#ifndef _EcsVR_PaintingSystem_h_
#define _EcsVR_PaintingSystem_h_

NAMESPACE_ECS_BEGIN


class PaintingInteractionSystemHolo :
	public PaintingInteractionSystemBase
{
public:
	RTTI_DECL1(PaintingInteractionSystemHolo, PaintingInteractionSystemBase)
	PaintingInteractionSystemHolo(Engine& e) : PaintingInteractionSystemBase(e) {}
	
	
protected:
	void Update(double dt) override;
	void Register(const LinkedList<EntityRef>& entities) override;
	
	void OnSourcePressed(const SpatialInteractionSourceEventArgs& args) override;
	void OnSourceUpdated(const SpatialInteractionSourceEventArgs& args) override;
	void OnSourceReleased(const SpatialInteractionSourceEventArgs& args) override;
	
};


NAMESPACE_ECS_END

#endif
