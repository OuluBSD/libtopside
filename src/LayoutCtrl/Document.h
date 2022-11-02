#ifndef _LayoutCtrl_Document_h_
#define _LayoutCtrl_Document_h_

NAMESPACE_LAYOUT_BEGIN

class HtmlCtrl;

class Document : public Object {
	
	FontsMap					fonts;
	Vector<CssText>				css;
	Css							styles;
	RGBA						def_color;
	UPP::Size					size;
	Vector<Position>			fixed_boxes;
	Vector<MediaQueryList*>		media_lists;
	Element*					over_element;
	ElementsVector				tabular_elements;
	MediaFeatures				media;
	
	String						addr, base_addr;
	HtmlCtrl*					ctrl = NULL;
	Css*						user_styles = NULL;
	
	
	uint32 AddFont(String name, int size, const String& weight, const String& Style, const String& decoration, FontMetrics* fm);
	void CreateNode(HtmlNode& n, Object& o);
	bool UpdateMediaLists(const MediaFeatures& features);
	void FixTablesLayout();
	void FixTableChildren(Element* el_ptr, StyleDisplay disp, const String& disp_str);
	void FixTableParent(Element* el_ptr, StyleDisplay disp, const String& disp_str);
	
public:
	RTTI_DECL1(Document, Object)
	Document(HtmlCtrl* ctrl) : ctrl(ctrl) {}
	
	bool			Init(String html, String address);
	void			SetBaseUrl(String url) {base_addr = url;}
	Element*		CreateElement(HtmlNode& n);
	HtmlCtrl&		GetHtmlCtrl() {return *ctrl;}
	const HtmlCtrl&	GetHtmlCtrl() const {return *ctrl;}
	Element*		GetRoot() {if (Object::GetCount() == 0) return NULL; return At(0).As<Element>();}
	String			GetBaseUrl() const {return base_addr;}
	uint32			GetFont(String name, int size, const String& weight, const String& Style, const String& decoration, FontMetrics* fm);
	int				Render(int max_width, RenderType rt = RenderAll);
	void			Paint(Draw& hdc, int x, int y, const Position& clip);
	RGBA			GetDefColor()	{ return def_color; }
	int				CvtUnits(const String& str, int fontSize, bool* is_percent = 0) const;
	int				CvtUnits(CssLength& val, int fontSize, int size = 0) const;
	int				Width() const;
	int				Height() const;
	void			AddStylesheet(const String& str, const String& baseurl, const String& media);
	bool			OnMouseOver(int x, int y, int client_x, int client_y, Vector<Position>& redraw_boxes, Element** el_sel=0);
	bool			OnMouseLeftDown(int x, int y, int client_x, int client_y, Vector<Position>& redraw_boxes);
	bool			OnMouseLeftUp(int x, int y, int client_x, int client_y, Vector<Position>& redraw_boxes);
	bool			OnMouseLeave(Vector<Position>& redraw_boxes);
	Element*		CreateElement(const String& tag_name, const StrMap& attributes);
	Element*		Root();
	void			GetFixedBoxes(Vector<Position>& fixed_boxes);
	void			AddFixedBox(const Position& pos);
	void			AddMediaList(MediaQueryList* list);
	bool			MediaChanged();
	void			AddTabular(Element* el) {tabular_elements.Add(el);}
};

typedef const Document ConstDocument;

NAMESPACE_LAYOUT_END

#endif
