#ifndef _EcsLib_WindowSystem_h_
#define _EcsLib_WindowSystem_h_

#if HAVE_WINDOWSYSTEM

NAMESPACE_OULU_BEGIN


class WindowSystem : public System<WindowSystem>, public Windows {
	Ref<EntityStore> ents;
	//Shader simple_shader;
	
public:
	WindowSystem(Machine& m);
	
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
