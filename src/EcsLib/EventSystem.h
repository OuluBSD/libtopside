#ifndef _EcsLib_EventSystem_h_
#define _EcsLib_EventSystem_h_


NAMESPACE_ECS_BEGIN
using namespace Parallel;


class EventSystem :
	public System<EventSystem>,
	public BinderIfaceEvents
{
	//Serial::EcsEventsBase* serial = 0;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    void Dispatch(const CtrlEvent& state) override {TODO}
    
public:
	using Base = System<EventSystem>;
	RTTI_DECL2(EventSystem, Base, BinderIfaceEvents)
    ECS_SYS_CTOR(EventSystem)
	SYS_DEF_VISIT
	
	//void Attach(Serial::EcsEventsBase* b);
	
};

using EventSystemRef = Ref<EventSystem>;


NAMESPACE_ECS_END

#endif
