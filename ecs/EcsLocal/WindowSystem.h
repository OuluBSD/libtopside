#ifndef _EcsLocal_WindowSystem_h_
#define _EcsLocal_WindowSystem_h_

#if HAVE_WINDOWSYSTEM

NAMESPACE_ECS_BEGIN


class WindowSystem :
	public System<WindowSystem>,
	public Windows
{
	Ref<EntityStore> ents;
	Size vdesktop_sz;
	//Shader simple_shader;
	
	void Visit(RuntimeVisitor& vis) override {
		vis.VisitThis<System<WindowSystem>>(this);
		vis.VisitThis<Windows>(this);
		vis & ents;
	}
	
public:
	SYS_RTTI(WindowSystem)
	ECS_SYS_CTOR(WindowSystem);
	
	static constexpr const char* POOL_NAME = "windows";
	
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
	void Invalidate();
	
	void SetDesktopSize(Size sz);
	
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    void CloseWindow(CoreWindow& cw) override;
    
    
};


NAMESPACE_ECS_END


#endif
#endif
