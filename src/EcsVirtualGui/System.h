#ifndef _EcsVirtualGui_System_h_
#define _EcsVirtualGui_System_h_


NAMESPACE_ECS_BEGIN


class VirtualGuiSystem : public System<VirtualGuiSystem> {
	Ecs::VirtualGui gui;
	
	
	
public:
	SYS_RTTI(VirtualGuiSystem)
	ECS_SYS_CTOR_(VirtualGuiSystem), gui(this) {}
	SYS_DEF_VISIT
	
protected:
	friend class Font;
	friend class Geom2DComponent;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
	
};



NAMESPACE_ECS_END

#endif
