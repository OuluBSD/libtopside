#ifndef _ToolBase_ImagePlayerBase_h_
#define _ToolBase_ImagePlayerBase_h_



BEGIN_TEXTLIB_NAMESPACE


struct PreviewDisplay : Display {
	virtual void Paint(Draw& w, const Rect& r, const Value& q,
		               Color ink, Color paper, dword style) const;
};

class ImagePlayerCtrl : public Ctrl {
	int img_no = -1;
	String prompt;
	Image img;
	int time = -1;
	
public:
	typedef ImagePlayerCtrl CLASSNAME;
	ImagePlayerCtrl();
	
	void SetImage(int i, String prompt, const Image& img, int time);
	void SetTime(int time);
	void Paint(Draw& d) override;
	
};

class ImagePlayerBase : public ToolAppCtrl {
	Splitter hsplit;
	ArrayCtrl list;
	Ctrl player;
	ImagePlayerCtrl img;
	Button play, stop;
	SliderCtrl slider;
	bool is_inited = false;
	
	bool playing = false;
	TimeStop ts;
	TimeCallback tc;
	
protected:
	
	struct Item : Moveable<Item> {
		int time = 0;
		String sort_value;
		String part;
		Image preview, full;
		String filename;
		String prompt;
	};
	Array<Item> items;
	const Item* cur_item = 0;
	
public:
	typedef ImagePlayerBase CLASSNAME;
	ImagePlayerBase();
	
	void Data() override;
	virtual void Init();
	
	void CreateSingleImage();
	void CreateAllImages();
	void DataList();
	void DataPlayer();
	void DataPlayerImage();
	void MakeSingleImage();
	void MakeAllImages();
	void Play();
	void Stop();
	void OnPromptImage(Array<Image>& images, int i);
	
};



END_TEXTLIB_NAMESPACE


#endif
