#ifndef _EcsCore_AudioSystem_h_
#define _EcsCore_AudioSystem_h_


NAMESPACE_OULU_BEGIN


class AudioSystem : public System<AudioSystem> {
	Ref<EntityStore> ents;
	Vector<AudioSourceRef> srcs;
	Vector<AudioSinkRef> sinks;
	Vector<AudioExchangePointRef> expts;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
    using System::System;
	
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
