#ifndef _EcsLib_EventSystem_h_
#define _EcsLib_EventSystem_h_


NAMESPACE_OULU_BEGIN

class EventSystem : public System<EventSystem> {
	Ref<EntityStore> ents;
	
	Vector<ControllerSource*> outputs;
	Vector<MidiSource*> midis;
	
public:
	EventSystem(Machine& m);
	
	void AddControllable(ControllerSource& out);
	void RemoveControllable(ControllerSource& out);
	void AddMidi(MidiSource& out);
	void RemoveMidi(MidiSource& out);
	
    const Vector<ControllerSource*>& GetSources() const {return outputs;}
    const Vector<MidiSource*>& GetMidiSources() const {return midis;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(float dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
};

template <class T> void AddControllable(T& o) {
	Ref<EventSystem> sys = o.GetEntity().GetMachine().template Get<EventSystem>();
	if (sys)
		sys	-> AddControllable(o);
}

template <class T> void RemoveControllable(T& o) {
	Ref<EventSystem> sys = o.GetEntity().GetMachine().template Get<EventSystem>();
	if (sys)
		sys	-> RemoveControllable(o);
}

template <class T> void AddMidi(T& o) {
	Ref<EventSystem> sys = o.GetEntity().GetMachine().template Get<EventSystem>();
	if (sys)
		sys	-> AddMidi(o);
}

template <class T> void RemoveMidi(T& o) {
	Ref<EventSystem> sys = o.GetEntity().GetMachine().template Get<EventSystem>();
	if (sys)
		sys	-> RemoveMidi(o);
}

NAMESPACE_OULU_END


#endif
