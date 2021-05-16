#ifndef _EcsLib_EventSystem_h_
#define _EcsLib_EventSystem_h_


NAMESPACE_TOPSIDE_BEGIN

class EventSystem : public System<EventSystem> {
	Ref<EntityStore> ents;
	LinkedList<ControllerSourceRef> outputs;
	LinkedList<MidiSourceRef> midis;
	
	void Visit(RuntimeVisitor& vis) override {
		vis & ents
			&& outputs
			&& midis;
	}
public:
	SYS_CTOR(EventSystem);
	
	void Add(ControllerSourceRef out);
	void Remove(ControllerSourceRef out);
	void Add(MidiSourceRef out);
	void Remove(MidiSourceRef out);
	
    const LinkedList<ControllerSourceRef>&	GetSources() const		{return outputs;}
    const LinkedList<MidiSourceRef>&		GetMidiSources() const	{return midis;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
};


NAMESPACE_TOPSIDE_END


#endif
