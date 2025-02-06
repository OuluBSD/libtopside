#include "ToolCtrl.h"
#include <TextLib/TextLib.h>


BEGIN_TEXTLIB_NAMESPACE


ImageAspectFixerTool::ImageAspectFixerTool() {
	Add(vsplit.SizePos());
	
	CtrlLayout(form);
	
	vsplit.Vert() << form << from << to;
	vsplit.SetPos(2000,0);
	vsplit.SetPos(2000+4000,1);
	
	form.width.SetData(1920);
	form.height.SetData(1080);
	form.extra_height.SetData(0);
	form.extra_width.SetData(0);
	
	form.load <<= THISBACK1(Do, 0);
	form.process <<= THISBACK1(Do, 1);
	form.load_dir <<= THISBACK1(Do, 3);
	form.process_all <<= THISBACK1(Do, 4);
	form.queue <<= THISBACK(OnQueueSelect);
	form.queue.AddColumn("Name");
	
}

void ImageAspectFixerTool::Data() {
	
	for(int i = 0; i < queue.GetCount(); i++) {
		form.queue.Set(i, 0, GetFileName(queue[i]));
	}
	INHIBIT_CURSOR(form.queue);
	form.queue.SetCount(queue.GetCount());
	if (!form.queue.IsCursor() && form.queue.GetCount())
		form.queue.SetCursor(0);
	
}

void ImageAspectFixerTool::OnQueueSelect() {
	if (!form.queue.IsCursor())
		return;
	int c = form.queue.GetCursor();
	if (c >= 0 && c < queue.GetCount())
		OpenFile(queue[c]);
}

void ImageAspectFixerTool::ToolMenu(Bar& bar) {
	bar.Add(t_("Load image"), AppImg::BlueRing(), THISBACK1(Do, 0)).Key(K_F4);
	bar.Add(t_("Start process"), AppImg::RedRing(), THISBACK1(Do, 1)).Key(K_F5);
	bar.Separator();
	bar.Add(t_("Load directory"), AppImg::BlueRing(), THISBACK1(Do, 3)).Key(K_F6);
	bar.Add(t_("Process all"), AppImg::RedRing(), THISBACK1(Do, 4)).Key(K_F7);
	
}

void ImageAspectFixerTool::Do(int fn) {
	
	if (fn == 0) {
		FileSelNative sel;
		
		if (path.GetCount())
			sel.ActiveDir(GetFileDirectory(path));
		sel.Type("PNG", "*.png");
		sel.Type("JPEG", "*.jpg");
		if (sel.ExecuteOpen( "Select image file")) {
			path = sel.Get();
			OpenFile(path);
		}
	}
	else if (fn == 1) {
		if (src_image.IsEmpty())
			return;
		
		int w = form.width.GetData();
		int h = form.height.GetData();
		int w_extra = form.extra_width.GetData();
		int h_extra = form.extra_height.GetData();
		TODO
		#if 0
		AspectFixer& af = AspectFixer::Get(src_image, w, h, w_extra, h_extra);
		af_ptr = &af;
		af.WhenIntermediate = THISBACK1(PostDo, 2);
		af.WhenReady << Proxy(WhenReady);
		af.Start();
		#endif
	}
	else if (fn == 2) {
		TODO
		#if 0
		if (!af_ptr) return;
		to.SetImage(af_ptr->intermediate);
		form.safe_prompt.SetData(af_ptr->safe_prompt);
		form.prompt.SetData(af_ptr->prompt);
		#endif
	}
	else if (fn == 3) {
		FileSelNative sel;
		queue.Clear();
		
		if (path.GetCount())
			sel.ActiveDir(GetFileDirectory(path));
		sel.Type("PNG", "*.png");
		sel.Type("JPEG", "*.jpg");
		if (sel.ExecuteOpen( "Select image file in a directory")) {
			path = sel.Get();
			if (FileExists(path)) {
				String dir = GetFileDirectory(path);
				String ext = GetFileExt(path);
				FindFile ff;
				if (ff.Search(AppendFileName(dir, "*" + ext))) do {
					String path = ff.GetPath();
					queue << path;
				}
				while (ff.Next());
				
				PostCallback(THISBACK(Data));
				if (queue.GetCount())
					PostCallback(THISBACK1(OpenFile, queue[0]));
			}
		}
	}
	else if (fn == 4) {
		QueueProcess(0);
	}
}

void ImageAspectFixerTool::OpenFile(String path) {
	if (FileExists(path)) {
		src_image = StreamRaster::LoadFileAny(path);
		from.SetImage(src_image);
		form.path.SetData(path);
		
		Size sz = src_image.GetSize();
		form.orig_sz.SetData(Format("%d x %d", sz.cx, sz.cy));
		form.prompt.Clear();
		form.safe_prompt.Clear();
	}
}

void ImageAspectFixerTool::QueueProcess(int cursor) {
	if (cursor < 0 || cursor >= queue.GetCount())
		return;
	
	String path = queue[cursor];
	String title = GetFileTitle(path);
	String dir = GetFileDirectory(path);
	String extended_dir = AppendFileName(dir, "extended");
	RealizeDirectory(extended_dir);
	String dst_path = AppendFileName(extended_dir, title + ".png");
	
	if (FileExists(dst_path)) {
		LOG("#" + IntStr(cursor) + ": Skipping existing file: " + dst_path);
		PostCallback(THISBACK1(QueueProcess, cursor+1));
		return;
	}
	
	OpenFile(path);
	
	WhenReady = [this, cursor, dst_path]() {
		TODO
		#if 0
		PNGEncoder enc;
		enc.SaveFile(dst_path, af_ptr->result);
		#endif
		
		PostCallback(THISBACK1(QueueProcess, cursor+1));
	};
	
	Do(1);
}


END_TEXTLIB_NAMESPACE
