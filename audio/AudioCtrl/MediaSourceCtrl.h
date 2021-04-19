#ifndef _AudioCtrl_MediaSourceCtrl_h_
#define _AudioCtrl_MediaSourceCtrl_h_

NAMESPACE_OULU_BEGIN

class MediaSourceCtrl : public InterfaceCtrl {
	AudioSourceCtrl audio;
	
public:
	typedef MediaSourceCtrl CLASSNAME;
	MediaSourceCtrl();
	
	void SetInterface(ComponentBase& c, InterfaceBase& b) override;
	
};

NAMESPACE_OULU_END

#endif
