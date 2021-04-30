#ifndef _EcsLib_EventSystem_h_
#define _EcsLib_EventSystem_h_


NAMESPACE_OULU_BEGIN

class EventSystem : public System<EventSystem> {
	Ref<EntityStore> ents;
	
	Vector<ControllerSource*> outputs;
	Vector<MidiSource*> midis;
	
public:
	EventSystem(Machine& m);
	
	void Add(ControllerSource* out);
	void Remove(ControllerSource* out);
	void Add(MidiSource* out);
	void Remove(MidiSource* out);
	
    const Vector<ControllerSource*>& GetSources() const {return outputs;}
    const Vector<MidiSource*>& GetMidiSources() const {return midis;}
	
protected:
	friend class Font;
	friend class CoreWindow;
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    
};


NAMESPACE_OULU_END


#endif
