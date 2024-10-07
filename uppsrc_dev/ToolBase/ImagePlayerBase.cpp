#include "ToolBase.h"
#include <Task/Task.h>


BEGIN_TEXTLIB_NAMESPACE


void PreviewDisplay::Paint(Draw& w, const Rect& r, const Value& q,
	                       Color ink, Color paper, dword style) const
{
	Image img = q;
	w.DrawRect(r, paper);
	w.DrawImage(r.left,r.top,img);
}



ImagePlayerBase::ImagePlayerBase() {
	Add(hsplit.VSizePos().HSizePos());
	
	hsplit.Horz() << list << player;
	
	list.AddColumn(t_("Sort-value"));
	list.AddColumn(t_("Part"));
	list.AddColumn(t_("Image"));
	list.AddColumn(t_("Prompt"));
	list.ColumnWidths("1 2 2 5");
	list.SetLineCy(64);
	
	player.Add(img.HSizePos(5,0).VSizePos(5,30));
	player.Add(play.LeftPos(1,58).BottomPos(1,28));
	player.Add(stop.LeftPos(61,58).BottomPos(1,28));
	player.Add(slider.HSizePos(120,1).BottomPos(1,28));
	play.SetLabel(t_("Play"));
	stop.SetLabel(t_("Stop"));
	slider.MinMax(0,1);
	slider.SetData(0);
	play.WhenAction << THISBACK(Play);
	stop.WhenAction << THISBACK(Stop);
	
}

void ImagePlayerBase::Data() {
	if (!is_inited) {
		Init();
		is_inited = true;
	}
	
	DataPlayer();
}

void ImagePlayerBase::DataList() {
	for(int i = 0; i < items.GetCount(); i++) {
		Item& item = items[i];
		list.Set(i, 0, item.sort_value);
		list.Set(i, 1, item.part);
		list.Set(i, 2, item.preview);
		list.Set(i, 3, item.prompt);
		list.SetDisplay(i, 2, Single<PreviewDisplay>());
	}
	list.SetCount(items.GetCount());
	
	int len = items.Top().time + 5;
	slider.MinMax(0, len);
	slider.SetData(0);
}

void ImagePlayerBase::DataPlayer() {
	if (items.IsEmpty())
		return;
	
	if (playing)
		DataPlayerImage();
}

void ImagePlayerBase::DataPlayerImage() {
	if (!playing)
		return;
	
	double time = ts.Seconds();
	slider.SetData((int)time);
	bool found = false;
	for (int i = items.GetCount()-1; i >= 0; i--) {
		const Item& item = items[i];
		if (item.time >= 0 && item.time <= time) {
			if (cur_item != &item) {
				cur_item = &item;
				img.SetImage(i, item.prompt, item.full, item.time);
				found = true;
			}
			break;
		}
	}
	if (!found) {
		img.SetTime((int)time);
	}
}

void ImagePlayerBase::Play() {
	playing = true;
	cur_item = 0;
	ts.Reset();
	tc.Set(-200, THISBACK(DataPlayerImage));
}

void ImagePlayerBase::Stop() {
	tc.Kill();
	playing = false;
}

void ImagePlayerBase::Init() {
	
}

void ImagePlayerBase::CreateSingleImage() {
	
}

void ImagePlayerBase::CreateAllImages() {
	
}

void ImagePlayerBase::MakeSingleImage() {
	if (!list.IsCursor())
		return;
	int cur = list.GetCursor();
	const Item& item = items[cur];
	String prompt = item.prompt;
	
	EditorPtrs& p = GetPointers();
	if(!p.component || !p.entity)
		return;
	
	
	
	{
		TaskMgr& m = TaskMgr::Single();
		m.CreateImage(prompt, 1, THISBACK1(OnPromptImage, cur));
	}
}

void ImagePlayerBase::MakeAllImages() {
	
}

void ImagePlayerBase::OnPromptImage(Array<Image>& images, int i) {
	if (i >= 0 && i < items.GetCount() && images.GetCount() >= 1) {
		Item& item = items[i];
		item.full = images[0];
		item.preview = Rescale(item.full, Size(64,64));
	}
	PostCallback(THISBACK(DataList));
}






ImagePlayerCtrl::ImagePlayerCtrl() {
	
}

void ImagePlayerCtrl::SetImage(int i, String prompt, const Image& img, int time) {
	this->img_no = i;
	this->prompt = prompt;
	this->img = img;
	this->time = time;
	Refresh();
}

void ImagePlayerCtrl::SetTime(int time) {
	this->time = time;
	Refresh();
}

void ImagePlayerCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	d.DrawRect(sz, GrayColor());
	
	int side = min(sz.cx, sz.cy);
	Rect vid;
	if (sz.cy >= sz.cx)
		vid = RectC(0, (sz.cy - side) / 2, side, side);
	else
		vid = RectC((sz.cx - side) / 2, 0, side, side);
	
	d.DrawRect(vid, Black());
	
	if (img_no >= 0) {
		Font fnt = SansSerif(20).Bold();
		String no = IntStr(img_no);
		
		d.DrawText(5,5, no, fnt, Black());
		d.DrawText(3,3, no, fnt, White());
	}
	
	if (!prompt.IsEmpty()) {
		Font fnt = SansSerif(14);
		int text_rows = prompt.GetCount() / 50;
		for(int i = 0; i < text_rows; i++) {
			String part = prompt.Mid(i*50, 50);
			int y = sz.cy - (text_rows - i) * 16;
			Size txt_sz = GetTextSize(part, fnt);
			int x = (sz.cx - txt_sz.cx) / 2;
			d.DrawText(x, y, part, fnt, Black());
			d.DrawText(x-2, y-2, part, fnt, White());
		}
	}
	
	if (!img.IsEmpty()) {
		Size vid_sz(side, side);
		int x = vid.left;
		int y = vid.top;
		Image rescaled = CachedRescale(img, vid_sz);
		d.DrawImage(x,y,rescaled);
	}
	
	if (time >= 0) {
		Font fnt = SansSerif(20).Bold();
		int min = time / 60;
		int sec = time % 60;
		String str = Format("%d:%02d", min, sec);
		Size tsz = GetTextSize(str, fnt);
		int x = sz.cx - tsz.cx;
		int y = 3;
		d.DrawText(x, y, str, fnt, Black());
		d.DrawText(x-2, y-2, str, fnt, White());
	}
}


END_TEXTLIB_NAMESPACE

