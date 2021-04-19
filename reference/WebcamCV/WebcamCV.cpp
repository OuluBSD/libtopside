#include "WebcamCV.h"

NAMESPACE_OULU_BEGIN


WebcamCV::WebcamCV() {
	Title("WebcamCV");
	Sizeable().MaximizeBox();
	
	Add(hsplit.SizePos());
	hsplit.Horz() << list << demo_view;
	hsplit.SetPos(2000);
	
	AddFrame(menu);
	menu.Set(THISFN(MainBar));
	
	list.AddColumn("Name");
	for(int i = 0; i < DEMO_COUNT; i++) {
		list.Set(i, 0, GetDemoName(i));
	}
	list.SetCursor(0);
	list <<= THISBACK(SelectDemo);
	SelectDemo();
	
	vidmgr.Refresh();
	PostCallback(THISBACK4(OpenVideoCapture, 0, 0, 0, 0));
	
	tc.Set(-20, THISBACK(Data));
}

WebcamCV::~WebcamCV() {
	CloseInput();
}

void WebcamCV::MainBar(Bar& bar) {
	bar.Sub("Input", [=](Bar& bar) {
		bar.Add("Open file", THISBACK(OpenFile));
		bar.Separator();
		
		if (!open_dev)
			vidmgr.Refresh(); // don't refresh while video input is open (buggy currently)
		
		for(int i = 0; i < vidmgr.GetCount(); i++) {
			VideoDevice& dev = vidmgr[i];
			for(int j = 0; j < dev.GetCaptureCount(); j++) {
				VideoCaptureDevice& cap = dev.GetCapture(j);
				
				String name = dev.GetDescription();
				if (dev.GetCaptureCount() > 1)
					 name += " :" + IntStr(j);
				
				bar.Sub(name, [=,&cap](Bar& bar) {
					for(int k = 0; k < cap.GetFormatCount(); k++) {
						const VideoFormat& fmt = cap.GetFormat(k);
						for(int l = 0; l < fmt.GetResolutionCount(); l++) {
							const auto& res = fmt.GetResolution(l);
							Size sz = res.GetSize();
							String s = fmt.GetDescription() + " " + sz.ToString();
							bar.Add(s, THISBACK4(OpenVideoCapture, i, j, k, l));
						}
					}
				});
			}
		}
	});
}

void WebcamCV::OpenDemo(int i) {
	lock.Enter();
	
	if (i == DEMO_GRAYSCALE) {
		
		
	}
	else {
		LOG("error: couldn't open demo id " << i);
	}
	
	lock.Leave();
}

String WebcamCV::GetDemoName(int i) {
	switch (i) {
		case DEMO_GRAYSCALE: return "Grayscale";
	}
	return "Invalid id";
}

void WebcamCV::OpenFile() {
	
}

void WebcamCV::CloseInput() {
	if (open_dev) {
		if (open_cap && stream)
			open_cap->Close();
		stream = 0;
		open_cap = 0;
		open_dev = 0;
	}
}

void WebcamCV::OpenVideoCapture(int dev_i, int cap_i, int fmt_i, int res_i) {
	if (dev_i < 0 || cap_i < 0 || fmt_i < 0 || res_i < 0) return;
	
	CloseInput();
	
	openmgr.Refresh();
	
	if (dev_i >= openmgr.GetCount()) return;
	VideoDevice& dev = openmgr[dev_i];
	
	if (cap_i >= dev.GetCaptureCount()) return;
	VideoCaptureDevice& cap = dev.GetCapture(cap_i);
	
	if (fmt_i >= cap.GetFormatCount()) return;
	const VideoFormat& fmt = cap.GetFormat(fmt_i);
	
	if (res_i >= fmt.GetResolutionCount()) return;
	const VideoFormatResolution& res = fmt.GetResolution(res_i);
	
	open_dev = &dev;
	open_cap = &cap;
	
	if (cap.Open(fmt_i, res_i)) {
		stream = &cap.GetStream();
	
	}
}

void WebcamCV::SelectDemo() {
	if (list.IsCursor())
		OpenDemo(list.GetCursor());
}

void WebcamCV::Data() {
	if (open_cap)
		open_cap->Read();
	
	lock.Enter();
	
	if (type == DEMO_GRAYSCALE)
		TickGrayscale();
	
	lock.Leave();
}

bool WebcamCV::HaveEnoughVideoData() {
	return true;
}

const VideoInputFrame& WebcamCV::GetVideo() {
	static VideoInputFrame f;
	return f;
}

VideoOutputFrame& WebcamCV::GetOutputFrame() {
	static VideoOutputFrame f;
	return f;
}

	

NAMESPACE_OULU_END



GUI_APP_MAIN {
	using namespace Oulu;
	
	SetCoutLog();
	
	
	WebcamCV().Run();
}
