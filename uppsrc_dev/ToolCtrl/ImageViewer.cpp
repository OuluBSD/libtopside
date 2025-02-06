#include "ToolCtrl.h"


BEGIN_TEXTLIB_NAMESPACE


ImageViewerCtrl::ImageViewerCtrl() {
	
}

void ImageViewerCtrl::Paint(Draw& d) {
	Size sz = GetSize();
	
	d.DrawRect(sz, Black());
	
	if (!img.IsEmpty()) {
		Size orig_sz = img.GetSize();
		double orig_ratio = (double)orig_sz.cx / orig_sz.cy;
		double new_ratio = (double)sz.cx / sz.cy;
		Size new_sz;
		if (orig_ratio < new_ratio) {
			new_sz.cy = sz.cy;
			new_sz.cx = (int)(sz.cy * orig_ratio);
		}
		else {
			new_sz.cx = sz.cx;
			new_sz.cy = (int)(sz.cx / orig_ratio);
		}
		
		Image scaled_img = CachedRescale(img, new_sz, FILTER_BILINEAR);
		
		if (orig_ratio < new_ratio) {
			int off = (sz.cx - new_sz.cx) / 2;
			d.DrawImage(off,0,scaled_img);
		}
		else {
			int off = (sz.cy - new_sz.cy) / 2;
			d.DrawImage(0,off,scaled_img);
		}
	}
}

void ImageViewerCtrl::SetImage(const Image& i) {
	img = i;
	PostCallback([this](){Refresh();});
}

void ImageViewerCtrl::Clear() {
	img.Clear();
	PostCallback([this](){Refresh();});
}

void ImageViewerCtrl::Menu(Bar& menu) {
	menu.Add("Save Image as", [this]() {
		String file = SelectFileSaveAs("*.jpg\n*.*");
		
		if (file.GetCount()) {
			JPGEncoder jpg;
			jpg.Quality(100);
			jpg.SaveFile(file, img);
		}
	});
	menu.Add("Copy image to clipboard", [this]() {
		WriteClipboardImage(img);
	});
}

void ImageViewerCtrl::RightDown(Point p, dword keyflags) {
	MenuBar::Execute(THISBACK(Menu));
}


END_TEXTLIB_NAMESPACE
