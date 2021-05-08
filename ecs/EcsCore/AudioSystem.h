#ifndef _EcsCore_AudioSystem_h_
#define _EcsCore_AudioSystem_h_


NAMESPACE_OULU_BEGIN


class AudioSystem : public System<AudioSystem> {
	Ref<EntityStore> ents;
	LinkedList<AudioSourceRef> srcs;
	LinkedList<AudioSinkRef> sinks;
	LinkedList<AudioExchangePointRef> expts;
	
	void Visit(RuntimeVisitor& vis) override {
		vis & ents
			&& srcs
			&& sinks
			&& expts;
	}
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
    SYS_CTOR(AudioSystem)
	
	void Add(AudioSourceRef src);
	void Add(AudioSinkRef sink);
	void Add(AudioExchangePointRef sink);
	void Remove(AudioSourceRef src);
	void Remove(AudioSinkRef sink);
	void Remove(AudioExchangePointRef sink);
	
	static Callback WhenUninit;
	
};



NAMESPACE_OULU_END


#endif
