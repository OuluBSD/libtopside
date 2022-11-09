#ifndef _DesktopSuite_System_h_
#define _DesktopSuite_System_h_

NAMESPACE_ECS_BEGIN


class DesktopSuiteSystem : public System<DesktopSuiteSystem> {
	Array<TopWindow> apps;
	
	
protected:
    bool Initialize() override;
    bool Arg(String key, Object value) override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
public:
	SYS_RTTI(DesktopSuiteSystem)
    ECS_SYS_CTOR(DesktopSuiteSystem)
	void Visit(RuntimeVisitor& vis) override;
	~DesktopSuiteSystem() {ASSERT(apps.IsEmpty());}
	
	
};


NAMESPACE_ECS_END

#endif
