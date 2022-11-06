#ifndef _EcsLocal_WindowSystem_h_
#define _EcsLocal_WindowSystem_h_

#if HAVE_WINDOWSYSTEM

NAMESPACE_ECS_BEGIN


class WindowSystem :
	public System<WindowSystem>
{
	Ref<EntityStore> ents;
	Size vdesktop_sz;
	EnvStateRef env;
	WindowManager wm;
	
	void Visit(RuntimeVisitor& vis) override {
		vis.VisitThis<System<WindowSystem>>(this);
		vis & ents;
	}
	
public:
	SYS_RTTI(WindowSystem)
	typedef WindowSystem CLASSNAME; \
	WindowSystem(Engine& m);
	
	static constexpr const char* POOL_NAME = "windows";
	
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
	void Invalidate();
	
	void SetDesktopSize(Size sz);
	
	int GetScreenCount() const {return wm.GetScreenCount();}
	Windows& GetScreen(int i) {return wm.GetScreen(i);}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
};


using WindowSystemRef = Ref<WindowSystem>;


NAMESPACE_ECS_END

#endif
#endif
