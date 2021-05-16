#ifndef _AudioCtrl_AudioSourceCtrl_h_
#define _AudioCtrl_AudioSourceCtrl_h_

NAMESPACE_TOPSIDE_BEGIN

class AudioSourceCtrl : public InterfaceCtrl {
	StaticRect s;
	
public:
	typedef AudioSourceCtrl CLASSNAME;
	AudioSourceCtrl();
	
	void SetInterface(ComponentBaseRef c, ExchangeProviderBaseRef b) override;
	
};

NAMESPACE_TOPSIDE_END

#endif
