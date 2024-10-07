#ifndef _TextCtrl_ImageViewer_h_
#define _TextCtrl_ImageViewer_h_


BEGIN_TEXTLIB_NAMESPACE


class ImageViewerCtrl : public Ctrl {
	Image img;
	
public:
	typedef ImageViewerCtrl CLASSNAME;
	ImageViewerCtrl();
	
	void Paint(Draw& d) override;
	void SetImage(const Image& i);
	void Clear();
	void Menu(Bar& menu);
	void RightDown(Point p, dword keyflags) override;

};


END_TEXTLIB_NAMESPACE


#endif
