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
	
	void Add(AudioSource* src);
	void Remove(AudioSource* src);
	
};



NAMESPACE_OULU_END


#endif
