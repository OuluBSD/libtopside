#ifndef _EcsLib_AudioSystem_h_
#define _EcsLib_AudioSystem_h_


NAMESPACE_OULU_BEGIN


class AudioSystem : public System<AudioSystem> {
	Ref<EntityStore> ents;
	Vector<AudioSource*> audios;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
    using System::System;
	
	void AddAudioSource(AudioSource& src);
	void RemoveAudioSource(AudioSource& src);
	
};

template <class T> void AddAudioSource(T& o) {
	Ref<AudioSystem> sys = o.GetEntity().GetMachine().template Get<AudioSystem>();
	if (sys)
		sys	-> AddAudioSource(o);
}

template <class T> void RemoveAudioSource(T& o) {
	Ref<AudioSystem> sys = o.GetEntity().GetMachine().template Get<AudioSystem>();
	if (sys)
		sys	-> RemoveAudioSource(o);
}


NAMESPACE_OULU_END


#endif
