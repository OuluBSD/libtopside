#ifndef _EcsCore_VideoSystem_h_
#define _EcsCore_VideoSystem_h_


NAMESPACE_OULU_BEGIN


class VideoSystem : public System<VideoSystem> {
	Ref<EntityStore> ents;
	Vector<VideoSourceRef> srcs;
	Vector<VideoSinkRef> sinks;
	Vector<VideoExchangePointRef> expts;
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
    SYS_CTOR(VideoSystem)
	
	void Add(VideoSourceRef src);
	void Add(VideoSinkRef sink);
	void Add(VideoExchangePointRef sink);
	void Remove(VideoSourceRef src);
	void Remove(VideoSinkRef sink);
	void Remove(VideoExchangePointRef sink);
	
	static Callback WhenUninit;
	
};



NAMESPACE_OULU_END


#endif
