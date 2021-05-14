#ifndef _EcsLib_WindowSystem_h_
#define _EcsLib_WindowSystem_h_

#if HAVE_WINDOWSYSTEM

NAMESPACE_OULU_BEGIN


class WindowSystem : public System<WindowSystem>, public Windows {
	Ref<EntityStore> ents;
	//Shader simple_shader;
	
	void Visit(RuntimeVisitor& vis) override {
		vis & ents;
	}
	
public:
	SYS_CTOR(WindowSystem);
	
	static constexpr const char* POOL_NAME = "windows";
	
	PoolRef GetPool() const {return GetMachine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
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


NAMESPACE_OULU_END


#endif
#endif
