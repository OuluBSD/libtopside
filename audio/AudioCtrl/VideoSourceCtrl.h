#ifndef _AudioCtrl_VideoSourceCtrl_h_
#define _AudioCtrl_VideoSourceCtrl_h_

NAMESPACE_TOPSIDE_BEGIN

class VideoSourceCtrl : public InterfaceCtrl {
	AudioSourceCtrl audio;
	
public:
	typedef VideoSourceCtrl CLASSNAME;
	VideoSourceCtrl();
	
	void SetInterface(ComponentBaseRef c, ExchangeProviderBaseRef b) override;
	
};

NAMESPACE_TOPSIDE_END

#endif
