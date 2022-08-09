#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


VideoImportCtrl::VideoImportCtrl(Edit3D* e) {
	owner = e;
	
	Add(hsplit.SizePos());
	hsplit.Horz().SetPos(1000) << list << tabs;
	
	list.AddColumn("");
	list.NoHeader();
	
	tabs.Add(kp.SizePos(), "Keypoints");
	tabs.Add(tri.SizePos(), "Triangles");
	tabs.Add(w.SizePos(), "World");
	tabs.WhenAction << THISBACK(OnTab);
	
	kp.Add(kp.hsplit.SizePos());
	kp.hsplit.Horz(kp.st, kp.vsplit);
	kp.vsplit.Vert(kp.rends[0], kp.rends[1]);
	for(int i = 0; i < 2; i++)
		kp.rends[i].owner = e;
	kp.rends[0].SetCameraSource(CAMSRC_VIDEOIMPORT_FOCUS);
	kp.rends[0].SetViewMode(VIEWMODE_XZ);
	kp.rends[1].SetCameraSource(CAMSRC_VIDEOIMPORT_PROGRAM);
	kp.rends[1].SetViewMode(VIEWMODE_PERSPECTIVE);
	kp.st.owner = this;
	
	tri.Add(tri.hsplit.SizePos());
	tri.hsplit.Horz(tri.st, tri.vsplit);
	tri.vsplit.Vert(tri.rends[0], tri.rends[1]);
	for(int i = 0; i < 2; i++)
		tri.rends[i].owner = e;
	tri.rends[0].SetCameraSource(CAMSRC_VIDEOIMPORT_FOCUS);
	tri.rends[0].SetViewMode(VIEWMODE_XZ);
	tri.rends[1].SetCameraSource(CAMSRC_VIDEOIMPORT_PROGRAM);
	tri.rends[1].SetViewMode(VIEWMODE_PERSPECTIVE);
	tri.st.owner = this;
	
	w.Add(w.grid.SizePos());
	w.grid.SetGridSize(2,2);
	for(int i = 0; i < 4; i++)
		w.grid.Add(w.rends[i].SizePos());
	for(int i = 0; i < 4; i++) {
		w.rends[i].owner = e;
		w.rends[i].SetCameraSource(i < 3 ? CAMSRC_VIDEOIMPORT_FOCUS : CAMSRC_VIDEOIMPORT_PROGRAM);
		w.rends[i].SetViewMode((ViewMode)i);
	}
	
	list <<= THISBACK(Data);
	list.SetCursor(0);
	//SetView(VIEW_KEYPOINTS);
}

void VideoImportCtrl::Data() {
	StagedVirtualStereoUncamera& uncam = owner->video.uncam;
	if (list.IsCursor()) {
		int i = list.GetCursor();
		//UncameraFrame& frame = uncam.frames[i];
		owner->anim.position = i;
	}
	
	RefreshRenderers();
}

void VideoImportCtrl::DataList() {
	StagedVirtualStereoUncamera& uncam = owner->video.uncam;
	for(int i = 0; i < uncam.frames.GetCount(); i++) {
		list.Set(i, 0, i);
	}
	list.SetCount(uncam.frames.GetCount());
	if (!list.IsCursor())
		list.SetCursor(0);
}

void VideoImportCtrl::RefreshRenderers() {
	switch (tabs.Get()) {
		case 0:
			kp.st.Refresh();
			for(int i = 0; i < 2; i++)
				kp.rends[i].Refresh();
			break;
		case 1:
			tri.st.Refresh();
			for(int i = 0; i < 2; i++)
				tri.rends[i].Refresh();
			break;
		case 2:
			for(int i = 0; i < 4; i++)
				w.rends[i].Refresh();
			break;
	}
}

void VideoImportCtrl::OnTab() {
	
}

void VideoImportCtrl::Update(double dt) {
	StagedVirtualStereoUncamera& uncam = owner->video.uncam;
	
	if (uncam.frames.GetCount() != list.GetCount())
		DataList();
	
}










VideoImportImageCtrl::VideoImportImageCtrl() {
	
}

void VideoImportImageCtrl::Paint(Draw& w) {
	Size sz = GetSize();
	
	Color bg = owner->owner->conf.background_clr;
	
	w.DrawRect(sz, bg);
	
	
}

Rect VideoImportImageCtrl::DrawStereoImages(Draw& d) {
	Size sz = GetSize();
	
	int frame_i = owner->owner->anim.position;
	if (frame_i < 0 || frame_i >= owner->owner->video.uncam.frames.GetCount())
		return Rect(0,0,0,0);
	
	UncameraFrame& frame = owner->owner->video.uncam.frames[frame_i];
	if (frame.l_img.IsEmpty() || frame.r_img.IsEmpty())
		return Rect(0,0,0,0);
	
	Size orig_img_sz = frame.l_img.GetSize();
	int img_h = sz.cy / 2;
	float factor = (float)img_h / (float)orig_img_sz.cy;
	Size new_sz = orig_img_sz * factor;
	
	Image l_img = CachedRescale(frame.l_img, new_sz, FILTER_NEAREST);
	Image r_img = CachedRescale(frame.r_img, new_sz, FILTER_NEAREST);
	
	int x_off = (sz.cx - new_sz.cx) * 0.5;
	d.DrawImage(x_off, 0, l_img);
	d.DrawImage(x_off, img_h, r_img);
	
	return RectC(x_off, 0, new_sz.cx, new_sz.cy);
}





KeypointImageCtrl::KeypointImageCtrl() {
	clr = LtRed();
}

void KeypointImageCtrl::Paint(Draw& w) {
	VideoImportImageCtrl::Paint(w);
	
	Rect r = DrawStereoImages(w);
	if (r.Width() == 0)
		return;
	
	int frame_i = owner->owner->anim.position;
	UncameraFrame& frame = owner->owner->video.uncam.frames[frame_i];
	
	Size sz = GetSize();
	Size orig_img_sz = frame.l_img.GetSize();
	int img_h = sz.cy / 2;
	float factor = (float)img_h / (float)orig_img_sz.cy;
	
	float x_off = r.left;
	for(const Descriptor& d : frame.l_dimg.GetDescriptors()) {
		float y = factor * d.y;
		float x = x_off + factor * d.x;
		
		w.DrawRect(x,y,1,1,clr);
	}
	
	for(const Descriptor& d : frame.r_dimg.GetDescriptors()) {
		float y = img_h + factor * d.y;
		float x = x_off + factor * d.x;
		
		w.DrawRect(x,y,1,1,clr);
	}
	
}




TriangleImageCtrl::TriangleImageCtrl() {
	clr = LtRed();
}

void TriangleImageCtrl::Paint(Draw& w) {
	VideoImportImageCtrl::Paint(w);
	
	Rect r = DrawStereoImages(w);
	if (r.Width() == 0)
		return;
	
	int frame_i = owner->owner->anim.position;
	UncameraFrame& frame = owner->owner->video.uncam.frames[frame_i];
	
	Size sz = GetSize();
	Size orig_img_sz = frame.l_img.GetSize();
	int img_h = sz.cy / 2;
	float factor = (float)img_h / (float)orig_img_sz.cy;
	
	float x_off = r.left;
	for(const TrackedTriangle& tt : frame.tracked_triangles) {
		float y0 = factor * tt.a->l->y;
		float x0 = x_off + factor * tt.a->l->x;
		float y1 = factor * tt.b->l->y;
		float x1 = x_off + factor * tt.b->l->x;
		float y2 = factor * tt.c->l->y;
		float x2 = x_off + factor * tt.c->l->x;
		
		w.DrawLine(x0, y0, x1, y1, 1, clr);
		w.DrawLine(x1, y1, x2, y2, 1, clr);
		w.DrawLine(x2, y2, x0, y0, 1, clr);
	}
	
	for(const TrackedTriangle& tt : frame.tracked_triangles) {
		float y0 = img_h + factor * tt.a->r->y;
		float x0 = x_off + factor * tt.a->r->x;
		float y1 = img_h + factor * tt.b->r->y;
		float x1 = x_off + factor * tt.b->r->x;
		float y2 = img_h + factor * tt.c->r->y;
		float x2 = x_off + factor * tt.c->r->x;
		
		w.DrawLine(x0, y0, x1, y1, 1, clr);
		w.DrawLine(x1, y1, x2, y2, 1, clr);
		w.DrawLine(x2, y2, x0, y0, 1, clr);
	}
	
}





NAMESPACE_TOPSIDE_END
