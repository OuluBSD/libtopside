#ifndef _ToolCtrl_ImageGenTool_h_
#define _ToolCtrl_ImageGenTool_h_


BEGIN_TEXTLIB_NAMESPACE


class ImageGenTool;


class GeneratedImages : public Ctrl {
	
	
public:
	typedef GeneratedImages CLASSNAME;
	GeneratedImages();
	
	void Paint(Draw& d) override;
	void RightDown(Point p, dword keyflags) override;
	void ImageMenu(Bar& bar, int i);
	
	Mutex lock;
	Array<Image> images;
	Vector<Rect> rects;
	
	ImageGenTool* tool = 0;
	
};

class EditImage : public Ctrl {
	
	
public:
	typedef EditImage CLASSNAME;
	EditImage();
	
	void Paint(Draw& d) override;
	void MouseWheel(Point p, int zdelta, dword keyflags) override;
	void SetImage(const Image& img);
	void MouseMove(Point p, dword keyflags) override;
	void LeftDown(Point p, dword keyflags) override;
	void LeftUp(Point p, dword keyflags) override;
	void MouseLeave() override;
	void DrawMask(Point p, dword keyflags);
	void RewriteMaskColor();
	
	
	enum {
		PAINT,
		ERASE
	};
	
	Size sz;
	Image image;
	Image mask;
	int brush_sz = 10;
	int mode = PAINT;
	Point last_mouse;
	Color brush_clr;
	bool drawing = false;
	Rect img_rect;
	
	ImageGenTool* tool = 0;
	
};

class ImageGenTool : public ToolAppCtrl {
	TabCtrl tabs;
	
	
	// Show
	Splitter hsplit;
	ArrayCtrl list;
	
	Ctrl main;
	EditString prompt;
	EditIntSpin count;
	Button upload, generate, translate;
	GeneratedImages images;
	
	struct Recent : Moveable<Recent> {
		String prompt;
		Image preview;
		hash_t hash;
		int n;
		
		bool tmp_stored = false;
		void Serialize(Stream& s) {s % prompt % preview % hash % n;}
	};
	Vector<Recent> recents;
	
	void StoreRecent();
	void LoadRecent();
	void DataRecent();
	
	
	
	// Edit
protected:
	friend class EditImage;
	static const int page_side = 1024+512;
	Ctrl edit;
	EditString prompt1;
	DropList mode;
	DropList color;
	EditIntSpin width;
	Button upload1, generate1, variate, translate1;
	Ctrl editor_frame;
	EditImage editor;
	ScrollBar vsb, hsb;
	Vector<Tuple<String,Color>> colors;
	
public:
	typedef ImageGenTool CLASSNAME;
	ImageGenTool();
	
	void Data() override;
	void ToolMenu(Bar& bar) override;
	void Generate();
	void GenerateFromEditor();
	void VariateFromEditor();
	void GenerateArgs(String prompt, int n);
	void EnableAll();
	void Upload();
	void OnListCursor();
	void OnImageReadyGui(String prompt, int n);
	void OnImageReady(Array<Image>& imgs, String prompt, int n);
	void AddRecent(Array<Image>& imgs, String prompt, int n);
	void GetEditImage(const Image& img, String prompt, int use_current_prompt);
	void OnBrushSizeChange(int zdelta);
	void OnBrushColorChange(int zdelta);
	void SaveImageAs(Image img);
	void Translate(bool editor);
	void OnTranslateReady(String s, bool editor);
	void PostOnTranslateReady(String s, bool editor) {PostCallback(THISBACK2(OnTranslateReady, s, editor));}
	void OnEditReadyGui(String prompt, int n);
	void OnEditReady(Array<Image>& imgs, String prompt, int n);
	
};


END_TEXTLIB_NAMESPACE


#endif
