#include "WebcamCV.h"

NAMESPACE_TOPSIDE_BEGIN


WebcamCV::WebcamCV() {
	Title("WebcamCV");
	Sizeable().MaximizeBox();
	
	Add(hsplit.SizePos());
	hsplit.Horz() << list << demo_view;
	hsplit.SetPos(2000);
	
	demo_view.Add(rend.SizePos());
	
	AddFrame(menu);
	menu.Set(THISFN(MainBar));
	
	list.AddColumn("Name");
	for(int i = 0; i < DEMO_COUNT; i++) {
		list.Set(i, 0, GetDemoName(i));
	}
	list.SetCursor(0);
	list <<= THISBACK(SelectDemo);
	SelectDemo();
	
	//vidmgr.Refresh();
	//PostCallback(THISBACK4(OpenVideoCapture, 0, 0, 0, 0));
	
	type = DEMO_GRAYSCALE;
	
	tc.Set(-20, THISBACK(Data));
}

WebcamCV::~WebcamCV() {
	CloseInput();
}

void WebcamCV::MainBar(Bar& bar) {
	bar.Sub("Input", [=](Bar& bar) {
		bar.Add("Open file", THISBACK(OpenFile));
		bar.Separator();
		
		/*
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
		}*/
	});
}

void WebcamCV::OpenDemo(int i) {
	type = i;
}

String WebcamCV::GetDemoName(int i) {
	switch (i) {
		case DEMO_GRAYSCALE: return "Grayscale";
		case DEMO_BOXBLUR: return "BoxBlur";
		case DEMO_GAUSSIANBLUR: return "GaussianBlur";
		case DEMO_PYRDOWN: return "PyramidDownsample";
		case DEMO_SCHARR: return "Scharr";
		case DEMO_SOBEL: return "Sobel";
		case DEMO_SOBELEDGE: return "SobelEdge";
		case DEMO_EQHIST: return "EqualizeHistogram";
		case DEMO_CANNY: return "CannyEdge";
		case DEMO_WARPAFF: return "WarpAffine";
		case DEMO_WARPPERS: return "WarpPerspective";
		case DEMO_VIDSTAB: return "VideoStabilizer";
		case DEMO_FASTCOR: return "FastCorners";
		case DEMO_YAPE06: return "Yape06";
		case DEMO_YAPE: return "Yape";
		case DEMO_ORB: return "Orb";
		case DEMO_OPTFLOWLK: return "OpticalFlowLK";
		case DEMO_BBF: return "Bbf";
		case DEMO_HAAR: return "Haar";
	}
	return "Invalid id";
}

void WebcamCV::LoadImageSeries(String dir) {
	new_imgs.Clear();
	
	LOG("WebcamCV::LoadImageSeries: loading images from directory: " << dir);
	
	for(int i = 0;; i++) {
		String name = Format("Image %02d.bmp", i);
		String path = AppendFileName(dir, name);
		if (!FileExists(path))
			break;
		
		Image img = StreamRaster::LoadFileAny(path);
		if (img.IsEmpty()) {
			LOG("WebcamCV::LoadImageSeries: error: could not open file: " << path);
			break;
		}
		
		new_imgs << img;
		
		#ifdef flagDEBUG
		if (i == 5)
			break;
		#endif
	}
	
	LOG("WebcamCV::LoadImageSeries: loaded " << new_imgs.GetCount() << " images");
	
}

void WebcamCV::OpenFile() {
	
}

void WebcamCV::CloseInput() {
	/*if (open_dev) {
		if (open_cap && stream)
			open_cap->Close();
		stream = 0;
		open_cap = 0;
		open_dev = 0;
	}*/
}

void WebcamCV::OpenVideoCapture(int dev_i, int cap_i, int fmt_i, int res_i) {
	/*if (dev_i < 0 || cap_i < 0 || fmt_i < 0 || res_i < 0) return;
	
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
	
	}*/
}

void WebcamCV::SelectDemo() {
	if (list.IsCursor())
		OpenDemo(list.GetCursor());
}

void WebcamCV::Data() {
	/*if (open_cap)
		open_cap->Read();*/
	
	if (new_imgs.GetCount())
		Swap(new_imgs, imgs);
	
	
	switch (type) {
		case DEMO_GRAYSCALE:	Tick(grayscale); break;
		case DEMO_BOXBLUR:		Tick(boxblur); break;
		case DEMO_GAUSSIANBLUR:	Tick(gaussblur); break;
		case DEMO_PYRDOWN:		Tick(pyrdown); break;
		case DEMO_SCHARR:		Tick(scharr); break;
		case DEMO_SOBEL:		Tick(sobel); break;
		case DEMO_SOBELEDGE:	Tick(sobeledge); break;
		case DEMO_EQHIST:		Tick(eqhist); break;
		case DEMO_CANNY:		Tick(canny); break;
		case DEMO_WARPAFF:		Tick(warpaff); break;
		case DEMO_WARPPERS:		Tick(warppers); break;
		case DEMO_VIDSTAB:		Tick(vidstab); break;
		case DEMO_FASTCOR:		Tick(fastcor); break;
		case DEMO_YAPE06:		Tick(yape06); break;
		case DEMO_YAPE:			Tick(yape); break;
		case DEMO_ORB:			Tick(orb); break;
		case DEMO_OPTFLOWLK:	Tick(optflowlk); break;
		case DEMO_BBF:			Tick(bbf); break;
		case DEMO_HAAR:			Tick(haar); break;
	};
	
	rend.Refresh();
}

void WebcamCV::Renderer::Paint(Draw& d) {
	Size sz = GetSize();
	ImageDraw id(sz);
	id.DrawRect(sz, Color(227, 227, 227));
	
	if (!input.IsEmpty()) {
		Size in_sz = input.GetSize();
		double scale = (double)sz.cx * 0.5 / in_sz.cx;
		Size rend_sz = in_sz * scale;
		
		Image in = CachedRescale(input, rend_sz, FILTER_NEAREST);
		Image out = CachedRescale(output, rend_sz, FILTER_NEAREST);
		
		int y = (sz.cy - in_sz.cy) / 2;
		id.DrawImage(0, y, in);
		id.DrawImage(sz.cx / 2, y, out);
	}
	
	d.DrawImage(0,0,id);
}

/*
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
}*/


Image WebcamCV::NewFrame() {
	if (imgs.IsEmpty())
		return Image();
	
	if (img_i >= imgs.GetCount())
		img_i = 0;
	
	rend.input = imgs[img_i++];
	return rend.input;
}

void WebcamCV::Tick(ImageProcBase& proc) {
	proc.SetInput(NewFrame());
	proc.Process();
	rend.output = proc.GetOutput();
}

void ImageProcBase::OutputFromGray(const ByteMat& gray) {
    output.SetSize(sz.cx, sz.cy, 4);
    ASSERT(output.data.GetCount() == gray.data.GetCount() * 4);
    byte* it = output.data.Begin();
    for (byte g : gray.data) {
        it[0] = g;
        it[1] = g;
        it[2] = g;
        it[3] = 255;
        it+=4;
    }
}

void ImageProcBase::OutputFromXY(const matrix_t<int>& img_gxgy) {
    ASSERT(img_gxgy.cols == sz.cx && img_gxgy.rows == sz.cy);
    output.SetSize(sz.cx, sz.cy, 4);
    byte* out = output.data.Begin();
    const int* in = img_gxgy.data.Begin();
    const int* end = img_gxgy.data.End();
    
    while (in != end) {
        byte gx = abs(in[0] >> 2)&0xff;
        byte gy = abs(in[1] >> 2)&0xff;
        byte pix = (((int)gx + (int)gy)>>2)&0xff;
        out[0] = gy;
        out[1] = 0;
        out[2] = gx;
        out[3] = pix;
        
        in += 2;
        out += 4;
    }
}

void ImageProcBase::SetInput(Image i) {
	sz = i.GetSize();
	const RGBA* it = i.Begin();
	int len = sz.cx * sz.cy * 4;
	input.SetSize(sz.cx, sz.cy, 4);
	memcpy(input.data.Begin(), it, len);
}

Image ImageProcBase::GetOutput() const {
	int len = sz.cx*sz.cy*4;
	ASSERT(output.data.GetCount() == len);
	if (sz.IsEmpty() || output.data.GetCount() != len)
		return Image();
	ImageBuffer ib(sz);
	RGBA* it = ib.Begin();
	memcpy(it, output.data.Begin(), len);
	return ib;
}


NAMESPACE_TOPSIDE_END



GUI_APP_MAIN {
	using namespace TS;
	
	SetCoutLog();
	
	WebcamCV wc;
	
	const auto& cmds = CommandLine();
	if (!cmds.IsEmpty())
		wc.LoadImageSeries(cmds[0]);
	
	wc.Run();
}
