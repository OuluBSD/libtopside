#ifndef _AudioCtrl_AudioView_h_
#define _AudioCtrl_AudioView_h_

#include <AudioCore/AudioCore.h>
#include <OuluCtrl/OuluCtrl.h>

NAMESPACE_OULU_BEGIN
using namespace Upp;

class AudioCtrl;
class AudioViewCtrl;

class AudioWindowCtrl : public Ctrl {
	
protected:
	friend class AudioViewCtrl;
	AudioViewCtrl* viewctrl;
	int offset;
	int window;
	int channel;
	
public:
	AudioWindowCtrl();
	
};

class AudioPlotCtrl : public AudioWindowCtrl {
	
	
public:
	AudioPlotCtrl();
	
	virtual void Paint(Draw& d);
	
};


class AudioHeatmapCtrl : public AudioWindowCtrl {
	
	Image render;
	
public:
	AudioHeatmapCtrl();
	
	virtual void Paint(Draw& d);
	
};

class AudioViewCtrl : public Ctrl {
	
protected:
	friend class AudioPlotCtrl;
	friend class AudioHeatmapCtrl;
	
	Record* file = NULL;
	
	Splitter plot_split, hmap_split;
	Array<AudioPlotCtrl> plots;
	Array<AudioHeatmapCtrl> hmaps;
	
public:
	typedef AudioViewCtrl CLASSNAME;
	AudioViewCtrl();
	
	void RefreshData();
	void SetView(int type);
	
};

NAMESPACE_OULU_END

#endif
