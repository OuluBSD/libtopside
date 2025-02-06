#include "ToolCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


ImageGenTool::ImageGenTool() {
	images.tool = this;
	editor.tool = this;
	
	Add(tabs.SizePos());
	tabs.Add(hsplit.SizePos(), t_("Show"));
	tabs.Add(edit.SizePos(), t_("Edit"));
	
	// Main
	hsplit.Horz() << main << list;
	hsplit.SetPos(8000);
	
	int bw = 120;
	int bw2 = bw/2;
	int barh = 30;
	main.Add(prompt.HSizePos(0,4*bw).TopPos(1,barh-2));
	main.Add(translate.RightPos(3*bw,bw).TopPos(1,barh-2));
	main.Add(count.RightPos(2*bw,bw).TopPos(1,barh-2));
	main.Add(upload.RightPos(bw,bw).TopPos(1,barh-2));
	main.Add(generate.RightPos(0,bw).TopPos(1,barh-2));
	main.Add(images.HSizePos().VSizePos(barh,0));
	
	prompt.SetData("An armchair in the shape of an avocado");
	count.MinMax(1, 4);
	count.SetData(1);
	translate.SetLabel(t_("Translate"));
	generate.SetLabel(t_("Generate"));
	upload.SetLabel(t_("Upload"));
	translate << THISBACK1(Translate, false);
	generate << THISBACK(Generate);
	upload << THISBACK(Upload);
	
	list.AddColumn(t_("Prompt"));
	list.AddColumn(t_("Preview"));
	list.SetLineCy(64);
	list.ColumnWidths("1 6");
	list.WhenCursor << THISBACK(OnListCursor);
	
	LoadRecent();
	
	
	
	// Edit
	edit.Add(prompt1.HSizePos(0,6*bw).TopPos(1,barh-2));
	edit.Add(translate1.RightPos(5*bw,bw).TopPos(1,barh-2));
	edit.Add(mode.RightPos(4*bw+bw2,bw2).TopPos(1,barh-2));
	edit.Add(color.RightPos(4*bw,bw2).TopPos(1,barh-2));
	edit.Add(width.RightPos(3*bw,bw).TopPos(1,barh-2));
	edit.Add(upload1.RightPos(2*bw,bw).TopPos(1,barh-2));
	edit.Add(generate1.RightPos(bw,bw).TopPos(1,barh-2));
	edit.Add(variate.RightPos(0,bw).TopPos(1,barh-2));
	edit.Add(editor_frame.HSizePos().VSizePos(barh,0));
	
	colors.Add({t_("White"), White()});
	colors.Add({t_("Red"), LtRed()});
	colors.Add({t_("Violet"), Color(255, 0, 255)});
	colors.Add({t_("Yellow"), Color(255, 254, 0)});
	colors.Add({t_("Orange"), Color(255, 153, 0)});
	colors.Add({t_("Brown"), Color(255, 50, 0)});
	// Currently red channel is drawn to alpha, so red must be 255
	//colors.Add({t_("Green"), LtGreen()});
	//colors.Add({t_("Blue"), LtBlue()});
	
	for (auto& t : colors)
		color.Add(t.a);
	color.SetIndex(0);
	color.WhenAction << [=]() {
		editor.brush_clr = colors[color.GetIndex()].b;
		editor.RewriteMaskColor();
		editor.Refresh();
	};
	editor.brush_clr = colors[0].b;
	
	
	mode.Add(t_("Draw"));
	mode.Add(t_("Erase"));
	mode.SetIndex(0);
	mode.WhenAction << [=](){
		editor.mode = mode.GetIndex();
		editor.Refresh();
	};
	
	
	width.MinMax(1, 512);
	width.SetData(10);
	width.WhenAction << [=](){
		editor.brush_sz = width.GetData();
		editor.Refresh();
	};
	
	
	translate1.SetLabel(t_("Translate"));
	generate1.SetLabel(t_("Generate"));
	upload1.SetLabel(t_("Upload"));
	variate.SetLabel(t_("Variate"));
	translate1 << THISBACK1(Translate, true);
	generate1 << THISBACK(GenerateFromEditor);
	upload1 << THISBACK(Upload);
	variate << THISBACK(VariateFromEditor);
	
	vsb.Vert();
	vsb.SetTotal(page_side);
	vsb.SetLine(30);
	vsb.Set(256);
	vsb.SetPage(1024);
	
	hsb.Horz();
	hsb.SetTotal(page_side);
	hsb.SetLine(30);
	hsb.Set(256);
	hsb.SetPage(1024);
	
	editor_frame.Add(editor.SizePos());
	//editor_frame.AddFrame(vsb);
	//editor_frame.AddFrame(hsb);
	
}

void ImageGenTool::Data() {
	
	DataRecent();
	
	// Ruins startup
	#if 0
	if (list.GetCount() && !list.IsCursor()) {
		list.SetCursor(0);
		OnListCursor();
	}
	#endif
}

void ImageGenTool::ToolMenu(Bar& bar) {
	if (tabs.Get() == 0) {
		bar.Add(t_("Translate"), AppImg::Part(), THISBACK1(Translate, 0)).Key(K_F5);
		bar.Add(t_("Upload"), AppImg::Part(), THISBACK(Upload)).Key(K_F6);
		bar.Add(t_("Generate"), AppImg::Part(), THISBACK(Generate)).Key(K_F7);
	}
	else {
		bar.Add(t_("Translate"), AppImg::Part(), THISBACK1(Translate, 1)).Key(K_F5);
		bar.Add(t_("Upload"), AppImg::Part(), THISBACK(Upload)).Key(K_F6);
		bar.Add(t_("Generate from editor"), AppImg::Part(), THISBACK(GenerateFromEditor)).Key(K_F7);
		bar.Add(t_("Variate from editor"), AppImg::Part(), THISBACK(VariateFromEditor)).Key(K_F8);
	}
}

void ImageGenTool::OnListCursor() {
	if (!list.IsCursor())
		return;
	int c = recents.GetCount();
	int i = list.GetCursor();
	int j = c-1-i;
	
	const Recent& r = recents[j];
	
	GenerateArgs(r.prompt, r.n);
}

void ImageGenTool::Generate() {
	int n = count.GetData();
	String prompt_str = prompt.GetData();
	GenerateArgs(prompt_str, n);
}

void ImageGenTool::GenerateArgs(String prompt_str, int n) {
	{
		TaskMgr& m = TaskMgr::Single();
		m.CreateImage(prompt_str, n, THISBACK2(OnImageReady, prompt_str, n), 0, THISBACK(EnableAll));
	}
	
	list.Disable();
	count.Disable();
	prompt.Disable();
	generate.Disable();
	upload.Disable();
}

void ImageGenTool::OnImageReady(Array<Image>& imgs, String prompt, int n) {
	images.lock.Enter();
	images.images <<= imgs;
	images.lock.Leave();
	
	AddRecent(imgs, prompt, n);
	
	PostCallback(THISBACK2(OnImageReadyGui, prompt, n));
}

void ImageGenTool::OnImageReadyGui(String prompt_str, int n) {
	Refresh();
	
	count.SetData(n);
	prompt.SetData(prompt_str);
	
	PostCallback(THISBACK(EnableAll));
}

void ImageGenTool::AddRecent(Array<Image>& imgs, String prompt, int n) {
	hash_t hash;
	{
		CombineHash ch;
		for (Image& img : imgs)
			ch << img.GetHashValue();
		hash = ch;
	}
	
	for (Recent& r : recents) {
		if (r.hash == hash)
			return;
	}
	
	Recent& recent = recents.Add();
	recent.prompt = prompt;
	recent.hash = hash;
	recent.n = n;
	{
		int side = 64;
		int recent_preview_h = side;
		int recent_preview_w = imgs.GetCount() * recent_preview_h;
		Size sz(recent_preview_w, recent_preview_h);
		Size rescale_sz(side, side);
		ImageDraw id(sz);
		id.DrawRect(sz, White());
		
		for(int i = 0; i < imgs.GetCount(); i++) {
			Image& img = imgs[i];
			int x = i * side;
			id.DrawImage(x, 0, Rescale(img, rescale_sz));
		}
		recent.preview = id;
	}
	
	StoreRecent();
	PostCallback(THISBACK(DataRecent));
}

void ImageGenTool::StoreRecent() {
	String dir = ConfigFile("recent");
	RealizeDirectory(dir);
	for(int i = 0; i < recents.GetCount(); i++) {
		Recent& r = recents[i];
		if (r.tmp_stored)
			continue;
		
		String filename = IntStr(i) + ".bin";
		String path = AppendFileName(dir, filename);
		StoreToFile(r, path);
		r.tmp_stored = true;
	}
}

void ImageGenTool::LoadRecent() {
	String dir = ConfigFile("recent");
	RealizeDirectory(dir);
	recents.Clear();
	for(int i = 0; i < 10000; i++) {
		String filename = IntStr(i) + ".bin";
		String path = AppendFileName(dir, filename);
		if (!FileExists(path))
			break;
		
		Recent& r = recents.Add();
		LoadFromFile(r, path);
		r.tmp_stored = true;
	}
	PostCallback(THISBACK(DataRecent));
}

void ImageGenTool::DataRecent() {
	int c = recents.GetCount();
	for(int i = 0; i < c; i++) {
		int j = c-1-i;
		const Recent& recent = recents[i];
		list.Set(j, 0, recent.prompt);
		list.Set(j, 1, recent.preview);
		list.SetDisplay(j, 1, Single<PreviewDisplay>());
	}
	list.SetCount(c);
}

void ImageGenTool::GenerateFromEditor() {
	{
		String prompt_str = prompt1.GetData();
		if (prompt_str.IsEmpty()) {
			PromptOK(t_("Prompt string is empty"));
			return;
		}
		if (editor.image.IsEmpty()) {
			PromptOK(t_("Image is empty"));
			return;
		}
		if (editor.mask.IsEmpty()) {
			PromptOK(t_("Mask is empty"));
			return;
		}
		
		int n = count.GetData();
		
		TaskMgr& m = TaskMgr::Single();
		m.GetEditImage(editor.image, editor.mask, prompt_str, n, THISBACK2(OnEditReady, prompt_str, n), THISBACK(EnableAll));
	}
	
	mode.Disable();
	color.Disable();
	translate1.Disable();
	prompt1.Disable();
	generate1.Disable();
	upload1.Disable();
	variate.Disable();
}

void ImageGenTool::VariateFromEditor() {
	{
		String prompt_str = prompt1.GetData();
		// Prompt is optional
		if (prompt_str.IsEmpty()) {
			prompt_str = "variation";
		}
		prompt_str += " " + IntStr64(Random64());
		
		if (editor.image.IsEmpty()) {
			PromptOK(t_("Image is empty"));
			return;
		}
		
		int n = count.GetData();
		
		TaskMgr& m = TaskMgr::Single();
		m.VariateImage(editor.image, n, THISBACK2(OnEditReady, prompt_str, n), THISBACK(EnableAll));
	}
	
	mode.Disable();
	color.Disable();
	translate1.Disable();
	prompt1.Disable();
	generate1.Disable();
	upload1.Disable();
	variate.Disable();
}

void ImageGenTool::GetEditImage(const Image& img, String prompt, int use_current_prompt) {
	if (use_current_prompt == 1)
		prompt = this->prompt.GetData();
	else if (use_current_prompt == 2)
		prompt = this->prompt1.GetData();
	
	prompt1.SetData(prompt);
	tabs.Set(1);
	
	editor.SetImage(img);
	
}

void ImageGenTool::OnEditReadyGui(String prompt, int n) {
	Refresh();
	
	tabs.Set(0);
	
	this->count.SetData(n);
	this->prompt.SetData(prompt);
	this->prompt1.SetData(prompt);
	
	PostCallback(THISBACK(EnableAll));
}

void ImageGenTool::EnableAll() {
	list.Enable();
	count.Enable();
	prompt.Enable();
	generate.Enable();
	upload.Enable();
	
	mode.Enable();
	color.Enable();
	translate1.Enable();
	prompt1.Enable();
	generate1.Enable();
	upload1.Enable();
	variate.Enable();
}

void ImageGenTool::OnEditReady(Array<Image>& imgs, String prompt, int n) {
	images.lock.Enter();
	images.images <<= imgs;
	images.lock.Leave();
	
	AddRecent(imgs, prompt, n);
	
	PostCallback(THISBACK2(OnEditReadyGui, prompt, n));
}

void ImageGenTool::OnBrushSizeChange(int zdelta) {
	int cur = editor.brush_sz;
	if (zdelta < 0) {
		if (cur > 1) {
			cur /= 2;
			editor.brush_sz = cur;
			editor.Refresh();
			width.SetData(cur);
		}
	}
	else {
		if (cur < 512) {
			cur *= 2;
			editor.brush_sz = cur;
			editor.Refresh();
			width.SetData(cur);
		}
	}
}

void ImageGenTool::OnBrushColorChange(int zdelta) {
	int i = color.GetIndex();
	if (zdelta < 0) {
		if (i+1 < colors.GetCount()) {
			color.SetIndex(i+1);
			editor.brush_clr = colors[i+1].b;
			editor.RewriteMaskColor();
			editor.Refresh();
		}
	}
	else {
		if (i-1 >= 0) {
			color.SetIndex(i-1);
			editor.brush_clr = colors[i-1].b;
			editor.RewriteMaskColor();
			editor.Refresh();
		}
	}
}

void ImageGenTool::SaveImageAs(Image img) {
	String file = SelectFileSaveAs("*.jpg\n*.png\n*.*");
	
	JPGEncoder jpg;
	jpg.Quality(100);
	jpg.SaveFile(file, img);
}

void ImageGenTool::Upload() {
	String path = SelectFileOpen("*.jpg\n*.png\n*.*");
	
	Image img = StreamRaster::LoadFileAny(path);
	if (!img.IsEmpty()) {
		tabs.Set(1);
		editor.SetImage(img);
	}
}

void ImageGenTool::Translate(bool editor) {
	String prompt_str = (editor ? prompt1 : prompt).GetData();
	
	{
		String orig_lng = "FI-FI"; //GetCurrentLanguageString().Left(5);
		String trans_lng = "EN-US";
		TaskMgr& m = TaskMgr::Single();
		m.Translate(orig_lng, prompt_str, trans_lng, THISBACK1(PostOnTranslateReady, editor));
	}
}

void ImageGenTool::OnTranslateReady(String s, bool editor) {
	(editor ? prompt1 : prompt).SetData(s);
}











GeneratedImages::GeneratedImages() {
	
}

void GeneratedImages::Paint(Draw& d) {
	Size sz = GetSize();
	d.DrawRect(sz, Color(221, 222, 229));
	
	lock.Enter();
	rects.Clear();
	int c = images.GetCount();
	if (c) {
		int w = min(sz.cx / c, sz.cy);
		int off = 5;
		int w_total = w * c;
		int left_off = (sz.cx - w_total) / 2;
		
		for(int i = 0; i < images.GetCount(); i++) {
			int side = w - 2*off;
			if (side <= 0)
				continue;
			
			Size isz(side, side);
			Image orig_img = images[i];
			if (orig_img.IsEmpty())
				continue;
			Image img = CachedRescale(orig_img, isz, FILTER_BILINEAR);
			
			int x = left_off + i*w + off;
			int y = sz.cy / 2 - side / 2;
			
			d.DrawImage(x, y, img);
			
			rects.Add(RectC(x, y, side, side));
		}
		
	}
	lock.Leave();
}

void GeneratedImages::RightDown(Point p, dword keyflags) {
	for(int i = 0; i < rects.GetCount(); i++) {
		const Rect& r = rects[i];
		if (r.Contains(p)) {
			MenuBar::Execute(THISBACK1(ImageMenu, i));
		}
	}
}

void GeneratedImages::ImageMenu(Bar& bar, int i) {
	if (i < 0 || i >= images.GetCount())
		return;
	bar.Add(t_("Edit image"), [=]() {
		if (tool) tool->GetEditImage(images[i], "", 1);
	});
	bar.Add(t_("Save image as"), [=]() {
		if (tool) tool->SaveImageAs(images[i]);
	});
}










EditImage::EditImage() {
	brush_clr = LtRed();
	
}

void EditImage::Paint(Draw& d) {
	Size sz = GetRect().GetSize();
	d.DrawRect(sz, Color(221, 222, 229));
	
	{
		int w = min(sz.cx, sz.cy);
		int off = 5;
		int w_total = w;
		int left_off = (sz.cx - w_total) / 2;
		
		{
			int side = w - 2*off;
			int x = left_off + off;
			int y = sz.cy / 2 - side / 2;
			
			if (side <= 0 || image.IsEmpty())
				return;
			
			Size isz(side, side);
			img_rect = RectC(x, y, side, side);
			
			Image rescaled = CachedRescale(image, isz, FILTER_BILINEAR);
			d.DrawImage(x, y, rescaled);
			
			if (!mask.IsEmpty()) {
				Image mask_rescaled = CachedRescale(mask, isz, FILTER_BILINEAR);
				d.DrawImage(x, y, mask_rescaled);
			}
		}
	}
	
	{
		int w = this->brush_sz;
		Rect r(
			last_mouse.x - w,
			last_mouse.y - w,
			last_mouse.x + w,
			last_mouse.y + w);
		d.DrawEllipse(r, brush_clr);
	}
}

void EditImage::MouseWheel(Point p, int zdelta, dword keyflags) {
	/*if (keyflags & K_SHIFT)
		tool->hsb.Wheel(zdelta);
	else
		tool->vsb.Wheel(zdelta);*/
	if (keyflags & K_SHIFT)
		tool->OnBrushColorChange(zdelta);
	else
		tool->OnBrushSizeChange(zdelta);
	
}

void EditImage::MouseMove(Point p, dword keyflags) {
	last_mouse = p;
	DrawMask(p, keyflags);
}

void EditImage::DrawMask(Point p, dword keyflags) {
	if (drawing && !image.IsEmpty()) {
		Size sz = image.GetSize();
		ImageDraw id(sz);
		id.DrawRect(sz, Black());
		id.Alpha().DrawRect(sz, Black());
		if (!mask.IsEmpty()) {
			id.DrawImage(0,0,mask);
			id.Alpha().DrawImage(0,0,mask);
		}
		double ratio = img_rect.Width() / (double)sz.cx;
		
		int x = (int)((p.x - img_rect.left) / ratio);
		int y = (int)((p.y - img_rect.top) / ratio);
		int w = (int)(this->brush_sz / ratio);
		Rect r(
			x - w,
			y - w,
			x + w,
			y + w);
			
		int mode = this->mode;
		
		if (keyflags & K_CTRL)
			mode = !mode;
		
		if (mode == PAINT) {
			id.DrawEllipse(r, brush_clr);
			id.Alpha().DrawEllipse(r, White());
		}
		else if (mode == ERASE) {
			id.DrawEllipse(r, Black());
			id.Alpha().DrawEllipse(r, Black());
		}
		
		mask = id;
	}
	
	Refresh();
}

void EditImage::SetImage(const Image& img) {
	if (img.IsEmpty())
		return;
	
	Size sz(1024, 1024);
	image = Rescale(img, sz);
	
	// Make mask image
	{
		RGBA light, dark;
		light.r = brush_clr.GetR();
		light.g = brush_clr.GetG();
		light.b = brush_clr.GetB();
		light.a = 255;
		dark.r = 0;
		dark.g = 0;
		dark.b = 0;
		dark.a = 0;
		
		ImageBuffer ib(sz);
		const RGBA* src = image.Begin();
		RGBA* it = ib.Begin();
		RGBA* end = ib.End();
		while (it != end) {
			if (src->a == 0) {
				*it = light;
			}
			else {
				*it = dark;
			}
			it++;
			src++;
		}
		mask = ib;
	}
	
	Refresh();
}

void EditImage::LeftDown(Point p, dword keyflags) {
	drawing = true;
	
	DrawMask(p, keyflags);
}

void EditImage::LeftUp(Point p, dword keyflags) {
	drawing = false;
	
}

void EditImage::MouseLeave() {
	drawing = false;
	
}

void EditImage::RewriteMaskColor() {
	if (!image.IsEmpty() && !mask.IsEmpty() && mask.GetSize() == image.GetSize()) {
		Size sz = image.GetSize();
		ImageBuffer ib(sz);
		
		RGBA light, dark;
		light.r = brush_clr.GetR();
		light.g = brush_clr.GetG();
		light.b = brush_clr.GetB();
		light.a = 255;
		dark.r = 0;
		dark.g = 0;
		dark.b = 0;
		dark.a = 0;
		
		const RGBA* it = mask.Begin();
		const RGBA* end = mask.End();
		RGBA* dst = ib.Begin();
		while (it != end) {
			*dst = it->a ? light : dark;
			it++;
			dst++;
		}
		mask = ib;
	}
}


END_TEXTLIB_NAMESPACE
