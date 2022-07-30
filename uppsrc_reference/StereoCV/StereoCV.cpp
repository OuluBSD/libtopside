#include "StereoCV.h"

NAMESPACE_TOPSIDE_BEGIN


StereoCV::StereoCV() {
	Title("StereoCV");
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
	
	type = DEMO_POINTCLOUD;
	
	tc.Set(-20, THISBACK(Data));
}

StereoCV::~StereoCV() {
	flag.Stop();
	
}

bool StereoCV::ConnectDebugVideo() {
	if (!client.ConnectTcp("127.0.0.1", 7776))
		return false;
	
	flag.Start(1);
	Thread::Start(THISBACK(FrameDownloader));
	return true;
}

void StereoCV::FrameDownloader() {
	
	while (client.IsOpen() && flag.IsRunning()) {
		if (!client.CallSocket(NET_LATEST_BRIGHT_FRAME, THISBACK(GetFrame)))
			break;
	}
	
	flag.DecreaseRunning();
}

void StereoCV::GetFrame(TcpSocket& sock) {
	Size sz;
	int size = 0;
	sock.Get(&sz.cx, sizeof(sz.cx));
	sock.Get(&sz.cy, sizeof(sz.cy));
	sock.Get(&size, sizeof(size));
	tmp_data.SetCount(size);
	sock.Get(tmp_data.Begin(), size);
	
	bool has_stereo = size >= (sz.cx * sz.cy * 2);
	
	ImageBuffer ib(Size(sz.cx * (has_stereo ? 2 : 1), sz.cy));
	RGBA* it = ib.Begin();
	RGBA* end = ib.End();
	const byte* src = tmp_data.Begin();
	
	int cx2 = sz.cx * 2;
	
	for(int y = 0; y < sz.cy; y++) {
		for(int x = 0; x < cx2; x++) {
			byte b = *src++;
			it->r = b;
			it->g = b;
			it->b = b;
			it->a = 255;
			it++;
		}
	}
	Image img = ib;
	hash_t new_hash = img.GetHashValue();
	hash_t old_hash = latest_bright.GetHashValue();
	
	lock.Enter();
	latest_bright = img;
	lock.Leave();
	
	
	if (!export_path.IsEmpty() && new_hash != old_hash) {
		JPGEncoder enc;
		enc.Quality(95);
		String filename = IntStr(img_i++) + ".jpg";
		String filepath = AppendFileName(export_path, filename);
		enc.SaveFile(filepath, img);
	}
}

void StereoCV::MainBar(Bar& bar) {
	bar.Sub("Input", [=](Bar& bar) {
		
	});
}

void StereoCV::OpenDemo(int i) {
	type = i;
}

String StereoCV::GetDemoName(int i) {
	switch (i) {
		case DEMO_POINTCLOUD: return "Pointcloud";
	}
	return "Invalid id";
}

void StereoCV::Export(String path) {
	export_path = path;
}

void StereoCV::SelectDemo() {
	if (list.IsCursor())
		OpenDemo(list.GetCursor());
	frame_i = 0;
}

void StereoCV::Data() {
	
	switch (type) {
		case DEMO_POINTCLOUD:	Tick(pointcloud); break;
	};
	
	rend.Refresh();
}

void StereoCV::Renderer::Paint(Draw& d) {
	Size sz = GetSize();
	ImageDraw id(sz);
	id.DrawRect(sz, Color(227, 227, 227));
	
	bool draw_out = false;
	
	if (!input.IsEmpty()) {
		Size in_sz = input.GetSize();
		double scale = (double)sz.cx * 0.5 / in_sz.cx;
		Size rend_sz = in_sz * scale;
		
		Image in = CachedRescale(input, rend_sz, FILTER_NEAREST);
		
		int y = (sz.cy - in_sz.cy) / 2;
		int out_x = sz.cx / 2;
		id.DrawImage(0, y, in);
		
		if (draw_out) {
			Image out = CachedRescale(output, rend_sz, FILTER_NEAREST);
			id.DrawImage(out_x, y, out);
		}
		
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
bool StereoCV::HaveEnoughVideoData() {
	return true;
}

const VideoInputFrame& StereoCV::GetVideo() {
	static VideoInputFrame f;
	return f;
}

VideoOutputFrame& StereoCV::GetOutputFrame() {
	static VideoOutputFrame f;
	return f;
}*/


Image StereoCV::NewFrame() {
	lock.Enter();
	rend.input = latest_bright;
	lock.Leave();
	
	return rend.input;
}

void StereoCV::Tick(ImageProcBase& proc) {
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
	int len = out.data.GetCount();
	
    uint32 pix = (0xff << 24) | (0x00 << 16) | (0xff << 8) | 0x00;
    for(int i=0; i < count; ++i)
    {
        const auto& c = corners[i];
        int off = (c.x + c.y * step);
        img[off] = pix;
        int o0 = off-1 >= 0 ? off-1 : off;
        int o1 = off+1 < len ? off+1 : off;
        int o2 = off-step >= 0 ? off-step : off;
        int o3 = off+step < len ? off+step : off;
		img[o0] = pix;
		img[o1] = pix;
		img[o2] = pix;
		img[o3] = pix;
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
	
	StereoCV wc;
	
	if (!wc.ConnectDebugVideo())
		return;
	
	const auto& c = CommandLine();
	if (c.GetCount() && DirectoryExists(c[0]))
		wc.Export(c[0]);
	
	wc.Run();
}
