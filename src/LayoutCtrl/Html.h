#ifndef _LayoutCtrl_Html_h_
#define _LayoutCtrl_Html_h_

NAMESPACE_LAYOUT_BEGIN

struct ListMarker
{
	String			image;
	String			baseurl;
	ListStyleType	marker_type;
	RGBA			color;
	Position		pos;
	int				list_id = 0;
	uint32			font = 0;
};


class HtmlRenderer : public Ctrl {
	RTTI_DECL1_(HtmlRenderer, Ctrl)
	
protected:
	friend class HtmlCtrl;
	
	struct Piece : Moveable<Piece> {
		Image img;
		Rect rect;
	};
	Vector<Piece> pieces;
	Mutex lock;
	int xscroll = 0, yscroll = 0;
	Color bg;
	
	virtual void Paint(Draw& d);
	
};

class HtmlCtrl : public ParentCtrl {
	RTTI_DECL1_(HtmlCtrl, ParentCtrl)
	
private:
	HtmlRenderer renderer;
	ScrollBar vscroll, hscroll;
	
	String html, addr;
	
	Document doc;
	bool init_ready = false;
	
	Document master_doc;
	Css master_css;
	One<MediaQueryList> media;
	Color bg_color;
	
	Vector<ElScript*> scripts;
	
	static Array<Font> _fonts;
	
	enum {IDLE, PAINT, RENDER, INIT};
	int process = 0;
	SpinLock process_lock;
	Mutex process_lock_run;
	
	
	void ImageReady(ResourceQuery* res, int cache_id, bool render_on_ready);
	void CssReady(ResourceQuery* res, int cache_id);
	void ProcessAtLeast(int i) {process_lock.Enter(); process = max(process, i); process_lock.Leave();}
	int GetProcessAtLeast() {int i; process_lock.Enter(); i = process; process_lock.Leave(); return i;}
	void SetScrollTotal(int h, int w) {vscroll.SetTotal(h); hscroll.SetTotal(w);}
	
public:
	typedef HtmlCtrl CLASSNAME;
	HtmlCtrl();
	~HtmlCtrl();
	
	virtual void Layout();
	virtual void MouseWheel(Point, int zdelta, dword);
	virtual bool Key(dword key, int);
	
	void		OnScroll();
	void		Process();
	void		SetHtml(String html, String addr);
	Element*	CreateElement(HtmlNode& n);
	Css&		MasterCss() {return master_css;}
	
	void		AddScript(ElScript* script);
	void		SetBackgroundColor(Color c) {bg_color = c; renderer.bg = c;}
	
	virtual uint32		CreateFont(const String& faceName, int size, int weight, FontStyle italic, unsigned int decoration, FontMetrics* fm);
	virtual void		DeleteFont(uint32 hFont);
	virtual int			TextWidth(const WString& text, uint32 hFont);
	virtual void		DrawText(Draw& hdc, const WString& text, uint32 hFont, RGBA color, const Position& pos, bool centered=false);
	virtual void		FillRect(Draw& hdc, const Position& pos, const RGBA color, const CssBorderRadius& radius);
	
	virtual int			PtPx(int pt) const;
	virtual int			GetDefaultFontSize() const;
	virtual String		GetDefaultFontName() const;
	virtual void		DrawListMarker(Draw& hdc, const ListMarker& marker);
	virtual void		LoadImage(const String& src, const String& baseurl, bool render_on_ready);
	virtual void		GetImageSize(const String& src, const String& baseurl, UPP::Size& sz);
	virtual void		GetImageSize(int cache_id, Size& sz);
	virtual void		DrawImage(Draw& hdc, const String& src, const String& baseurl, const Position& pos);
	virtual void		DrawBackground(Draw& hdc, const BackgroundPaint& bg);
	virtual void		DrawBorders(Draw& hdc, const Borders& Borders, const Position& draw_pos, bool root);

	virtual	void		TransformText(WString& text, TextTransform tt);
	virtual void		SetClip(Draw& d, const Position& pos, const BorderRadiuses& bdr_radius, bool valid_x, bool valid_y);
	virtual void		DelClip(Draw& d);
	virtual Element*	CreateElement(const String& tag_name, const StrMap& attributes, Document* doc);
	virtual void		GetMediaFeatures(MediaFeatures& media);
	
	virtual	void		SetCaption(const WString& caption);
	virtual	void		SetBaseUrl(const String& base_url);
	virtual void		Link(Document* doc, Element* el);
	virtual void		OnAnchorClick(const String& url, Element* el);
	virtual	void		SetCursor(const String& cursor);
	virtual void		ImportCss(String& text, const String& url, String& baseurl);
	virtual void		GetClientRect(Position& client) const;
		
	
	
	Callback1<WString>	WhenCaption;
	Callback1<String>	WhenLoadAddress;
	
protected:
	
	virtual void		DrawEllipse(Draw& hdc, int x, int y, int width, int height, const RGBA& color, double line_width);
	virtual void		FillEllipse(Draw& hdcr, int x, int y, int width, int height, const RGBA& color);
	virtual void		RoundedRectangle( Draw& hdc, const Position &pos, const BorderRadiuses &radius, RGBA color );
};

class BrowserCtrl : public ParentCtrl {
	RTTI_DECL1_(BrowserCtrl, ParentCtrl)
	
private:
	static const int button_h = 30;
	
	Button prev, next, home, refresh, stop;
	int button_count = 0;
	EditString addr;
	HtmlCtrl html;
	
	void AddButton(Button& b, Image img, Callback cb);
	
public:
	typedef BrowserCtrl CLASSNAME;
	BrowserCtrl();
	
	void Previous();
	void Next();
	void Home();
	void Refresh();
	void Stop();
	void Go();
	void SetResourcePage(ResourceQuery* res);
	
	void SetAddress(String addr) {this->addr.SetData(addr); Go();}
	void SetAddressText(String addr) {this->addr.SetData(addr);}
};

NAMESPACE_LAYOUT_END


#endif
