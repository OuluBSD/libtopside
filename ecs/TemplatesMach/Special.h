#ifndef _TemplatesMach_Special_h_
#define _TemplatesMach_Special_h_

#if 0

NAMESPACE_ECS_BEGIN


class AVMediaProxy : public Media {
public:
	Audio* aud = 0;
	Video* vid = 0;

public:
	RTTI_DECL1(AVMediaProxy, Media)

	AVMediaProxy() = default;

	void Set(Audio& a, Video& v) {aud = &a; vid = &v;}
	Audio& GetAudio() override {return *aud;}
	Video& GetVideo() override {return *vid;}

	void			Exchange(MediaEx& e) override;
	int				GetQueueSize() const override;
	MediaFormat		GetFormat() const override;
	bool			IsQueueFull() const override;
	
};



NAMESPACE_ECS_END

#endif
#endif
