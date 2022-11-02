#ifndef _AudioCtrl_Slider_h_
#define _AudioCtrl_Slider_h_


NAMESPACE_TOPSIDE_BEGIN


class AudioSlider : public Ctrl {
	String name;
	int value, min, max, diff;
	Color bg;
public:
	RTTI_DECL1(AudioSlider, Ctrl)
	AudioSlider();
	
	void Set(String name, int value, int min, int max);
	
	virtual void Paint(Draw& w);
};


NAMESPACE_TOPSIDE_END


#endif
