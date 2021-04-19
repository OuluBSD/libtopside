#ifndef _AudioCtrl_Slider_h_
#define _AudioCtrl_Slider_h_


NAMESPACE_OULU_BEGIN


class AudioSlider : public Ctrl {
	String name;
	int value, min, max, diff;
	Color bg;
public:
	AudioSlider();
	
	void Set(String name, int value, int min, int max);
	
	virtual void Paint(Draw& w);
};


NAMESPACE_OULU_END


#endif
