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
	
}

void WebcamCV::MainBar(Bar& bar) {
	bar.Sub("Input", [=](Bar& bar) {
		
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

void WebcamCV::SelectDemo() {
	if (list.IsCursor())
		OpenDemo(list.GetCursor());
	frame_i = 0;
}

void WebcamCV::Data() {
	
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
		case DEMO_YAPE06:		Tick(Yape06); break;
		case DEMO_YAPE:			Tick(Yape); break;
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
		int out_x = sz.cx / 2;
		id.DrawImage(0, y, in);
		id.DrawImage(out_x, y, out);
		
		if (lines) {
			for (ColorLine& l : *lines) {
				id.DrawLine(
					out_x + l.a.x * scale,
					y     + l.a.y * scale,
					out_x + l.b.x * scale,
					y     + l.b.y * scale,
					1, l.clr);
			}
		}
		
		if (points) {
			for (Point& p : *points) {
				id.DrawRect(
					out_x + p.x * scale - 1,
					y     + p.y * scale - 1,
					3, 3, Color(0,255,0));
			}
		}
		
		if (rects) {
			for (const BBox& b : *rects) {
				Point tl(out_x + b.x * scale, y + b.y * scale);
				Point tr(out_x + (b.x + b.width) * scale, y + b.y * scale);
				Point bl(out_x + b.x * scale, y + (b.y + b.height) * scale);
				Point br(out_x + (b.x + b.width) * scale, y + (b.y + b.height) * scale);
				Color clr(0,255,0);
				id.DrawLine(tl, tr, 1, clr);
				id.DrawLine(tr, br, 1, clr);
				id.DrawLine(br, bl, 1, clr);
				id.DrawLine(bl, tl, 1, clr);
			}
		}
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
	if (frame_i++ == 0)
		proc.InitDefault();
	proc.Process();
	rend.output = proc.GetOutput();
	rend.lines = &proc.lines;
	rend.points = &proc.points;
	rend.rects = &proc.rects;
}

void ImageProcBase::OutputFromGray(const ByteMat& gray) {
	ASSERT(gray.channels == 1 && gray.cols == sz.cx && gray.rows == sz.cy);
	output.SetSize(sz.cx, sz.cy, 4);
    ASSERT(!gray.IsEmpty());
	if (gray.IsEmpty())
		return;
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

void ImageProcBase::OutputFromXY(const DMatrix<int>& img_gxgy) {
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

void ImageProcBase::RenderCorners(const Vector<Keypoint>& corners, ByteMat& out) {
	int count = corners.GetCount();
	int step = sz.cx;
	
	out.SetSize(sz.cx, sz.cy, 4);
	memset(out.data.Begin(), 0, out.data.GetCount());
	uint32* img = (uint32*)(byte*)out.data.Begin();
	
    uint32 pix = (0xff << 24) | (0x00 << 16) | (0xff << 8) | 0x00;
    for(int i=0; i < count; ++i)
    {
        const auto& c = corners[i];
        int off = (c.x + c.y * step);
        img[off] = pix;
        img[off-1] = pix;
        img[off+1] = pix;
        img[off-step] = pix;
        img[off+step] = pix;
    }
}

void ImageProcBase::RenderCorners(const ByteMat& bg, const ByteMat* mini_img, const Vector<Keypoint>& corners, ByteMat& out) {
	ASSERT(bg.cols == sz.cx && bg.rows == sz.cy);
	int count = corners.GetCount();
	int step = sz.cx;
	
	OutputFromGray(bg);
	
	if (mini_img && mini_img->cols > 0 && mini_img->cols <= bg.cols) {
		RGBA* img = (RGBA*)output.data.Begin();
		const byte* bg_img = (byte*)mini_img->data.Begin();
		for (int y = 0; y < mini_img->rows; y++) {
			for (int x = 0; x < mini_img->cols; x++) {
				img->r = img->g = img->b = *bg_img++;
				img->a = 255;
				img++;
			}
			img += output.cols - mini_img->cols;
		}
	}
	
	uint32* img = (uint32*)(byte*)output.data.Begin();
    for(int i=0; i < count; ++i)
    {
        uint32 pix = 0xff << 24 | 0xff << 16;
        const auto& c = corners[i];
        int off = (c.x + c.y * step);
        img[off] = pix;
        img[off-1] = pix;
        img[off+1] = pix;
        img[off-step] = pix;
        img[off+step] = pix;
    }
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
