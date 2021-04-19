#ifndef _AudioCtrl_AudioSourceCtrl_h_
#define _AudioCtrl_AudioSourceCtrl_h_

NAMESPACE_OULU_BEGIN

class AudioSourceCtrl : public InterfaceCtrl {
	StaticRect s;
	
public:
	typedef AudioSourceCtrl CLASSNAME;
	AudioSourceCtrl();
	
	void SetInterface(ComponentBase& c, InterfaceBase& b) override;
	
};

NAMESPACE_OULU_END

#endif
