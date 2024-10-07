#ifndef _ToolCtrl_ImageAspectFixerTool_h_
#define _ToolCtrl_ImageAspectFixerTool_h_


BEGIN_TEXTLIB_NAMESPACE


class AspectFixer;


class ImageAspectFixerTool : public ToolAppCtrl {
	Splitter vsplit;
	WithImageAspectForm<Ctrl> form;
	ImageViewerCtrl from, to;
	String path;
	Image src_image;
	AspectFixer* af_ptr = 0;
	
	Vector<String> queue;
	
	void OpenFile(String path);
	
	Event<> WhenReady;
	
public:
	typedef ImageAspectFixerTool CLASSNAME;
	ImageAspectFixerTool();
	
	void Data() override;
	void ToolMenu(Bar& bar) override;
	void OnQueueSelect();
	void Do(int fn);
	void PostDo(int fn) {PostCallback(THISBACK1(Do, fn));}
	void QueueProcess(int cursor);
	
};



END_TEXTLIB_NAMESPACE


#endif
