#ifndef _WebcamCV_WebcamCV_h_
#define _WebcamCV_WebcamCV_h_

#include <ComputerVision/ComputerVision.h>
#include <LocalCtrl/LocalCtrl.h>


NAMESPACE_TOPSIDE_BEGIN


class WebcamCV : public TopWindow {
	Splitter hsplit;
	ArrayCtrl list;
	ParentCtrl demo_view;
	TimeCallback tc;
	Mutex lock;
	VideoDeviceManager vidmgr, openmgr;
	MenuBar menu;
	int type = -1;
	VideoDevice* open_dev = 0;
	VideoCaptureDevice* open_cap = 0;
	const VideoInputStream* stream = 0;
	
	void TickGrayscale();
	
	bool HaveEnoughVideoData();
	const VideoInputFrame& GetVideo();
	VideoOutputFrame& GetOutputFrame();
	void MainBar(Bar& bar);
	
public:
	typedef WebcamCV CLASSNAME;
	WebcamCV();
	~WebcamCV();
	
	enum {
		DEMO_GRAYSCALE,
		
		DEMO_COUNT
	};
	
	void OpenDemo(int i);
	String GetDemoName(int i);
	
	void OpenFile();
	void OpenVideoCapture(int dev, int cap, int fmt, int res);
	void CloseInput();
	void SelectDemo();
	void Data();
	
	
};


NAMESPACE_TOPSIDE_END

#endif
