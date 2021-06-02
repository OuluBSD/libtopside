#ifndef _LayoutCtrl_Element_h_
#define _LayoutCtrl_Element_h_

NAMESPACE_LAYOUT_BEGIN

class Document;
typedef const Document ConstDocument;

class Element : public Object, public Pte<Element> {
	
protected:
	friend class BlockBox;
	friend class LineBox;
	friend class HtmlTag;
	friend class ElTable;
	friend class Document;
	
	Box*						box = NULL;
	Position					pos;
	Margins						margins;
	Margins						padding;
	Margins						borders;
	bool						skip = 0;
	
public:
	RTTI_DECL1(Element, Object)
	Element();
	
	Element* GetParentElement() const {return CastPtr<Element>(GetParent());}
	ConstDocument* GetDocument() const;
	Document* GetDocument();
	

	int							Left()						const;
	int							Right()						const;
	int							Top()						const;
	int							Bottom()					const;
	int							Height()					const;
	int							Width()						const;

	int							ContentMarginsTop()			const;
	int							ContentMarginsBottom()		const;
	int							ContentMarginsLeft()		const;
	int							ContentMarginsRight()		const;

	int							MarginTop()					const;
	int							MarginBottom()				const;
	int							MarginLeft()				const;
	int							MarginRight()				const;
	Margins						GetMargins()				const;

	int							PaddingTop()				const;
	int							PaddingBottom()				const;
	int							PaddingLeft()				const;
	int							PaddingRight()				const;
	Margins						GetPaddings()				const;

	int							BorderTop()					const;
	int							BorderBottom()				const;
	int							BorderLeft()				const;
	int							BorderRight()				const;
	Margins						GetBorders()				const;

	bool						InNormalFlow()				const;
	RGBA						GetColor(const String& prop_name, bool inherited, const RGBA& DefColor = RGBA());
	bool						IsInLineBox()				const;
	Position					GetPlacement()				const;
	bool						CollapseTopMargin()			const;
	bool						CollapseBottomMargin()		const;
	bool						IsPositioned()				const;

	bool						Skip();
	void						Skip(bool val);
	bool						IsVisible() const;
	int							CalcWidth(int defVal) const;
	int							GetInlineShiftLeft();
	int							GetInlineShiftRight();

	virtual Element*			SelectOne(const String& Selector);
	virtual Element*			SelectOne(const CssSelector& Selector);

	virtual int					Render(int x, int y, int max_width, bool second_pass = false);
	virtual int					RenderInline(Element* container, int max_width);
	virtual int					PlaceElement(Element* el, int max_width);
	virtual void				CalcOutlines( int higher_width );
	virtual void				CalcAutoMargins(int higher_width);
	virtual void				ApplyVerticalAlign();
	virtual bool				FetchPositioned();
	virtual void				RenderPositioned(RenderType rt = RenderAll);

	virtual bool				AppendChild(Element* el);

	virtual String				GetTagName() const;
	virtual void				SetTagName(const String& tag);
	virtual void				SetData(const WString& data);
	virtual ElementFloat		GetFloat() const;
	virtual VerticalAlign		GetVerticalAlign() const;
	virtual ElementClear		GetClear() const;
	virtual size_t				GetChildrenCount() const;
	virtual Element*			GetChild(int idx);
	virtual Overflow			GetOverflow() const;

	virtual CssLength			GetCssLeft() const;
	virtual CssLength			GetCssRight() const;
	virtual CssLength			GetCssTop() const;
	virtual CssLength			GetCssBottom() const;
	virtual CssOffsets			GetCssOffsets() const;
	virtual CssLength			GetCssWidth() const;
	virtual void				SetCssWidth(CssLength& w);
	virtual CssLength			GetCssHeight() const;

	virtual void				SetAttr(const String& name, const String& val);
	virtual String				GetAttr(const String& name, const String& def = "");
	virtual int					GetAttrCount() {return 0;}
	virtual String				GetAttrKey(int i) {return "";}
	virtual String				GetAttrValue(int i) {return "";}
	
	
	virtual void				ApplyStylesheet(const Css& Stylesheet);
	virtual void				RefreshStyles();
	virtual bool				IsWhiteSpace();
	virtual bool				IsBody() const;
	virtual bool				IsBreak() const;
	virtual int					GetBaseLine();
	virtual bool				OnMouseOver();
	virtual bool				OnMouseLeave();
	virtual bool				OnMouseLeftDown();
	virtual bool				OnMouseLeftUp();
	virtual void				OnClick();
	virtual bool				FindStylesChanges(Vector<Position>& redraw_boxes, int x, int y);
	virtual String				GetCursor();
	virtual void				InitFont();
	virtual bool				IsPointInside(int x, int y);
	virtual bool				SetPseudoClass(const String& pclass, bool add);
	virtual bool				IsReplaced() const;
	virtual int					LineHeight() const;
	virtual WhiteSpace			GetWhiteSpace() const;
	virtual StyleDisplay		GetDisplay() const;
	virtual Visibility			GetVisibility() const;
	virtual ElementPosition	GetElementPosition(CssOffsets* offsets = 0) const;
	virtual void				GetInLineBoxes(Vector<Position>& Boxes);
	virtual void				ParseStyles(bool is_reparse = false);
	virtual void				Paint(Draw& hdc, int x, int y, const Position& clip);
	virtual void				DrawBackground( Draw& hdc, int x, int y, const Position& clip );
	virtual String				GetStyleProperty(const String& name, bool inherited, const String& def = "");
	virtual uint32				GetFont(FontMetrics* fm = 0);
	virtual int					GetFontSize() const;
	virtual void				GetText(WString& text);
	virtual void				ParseAttributes();
	virtual int					Select(const CssSelector& selector, bool apply_pseudo = true);
	virtual int					Select(const CssElementSelector& selector, bool apply_pseudo = true);
	virtual Element*			FindAncestor(const CssSelector& selector, bool apply_pseudo = true, bool* is_pseudo = 0);
	virtual bool				IsAncestor(Element* el);
	virtual Element*			FindAdjacentSibling(Element* el, const CssSelector& selector, bool apply_pseudo = true, bool* is_pseudo = 0);
	virtual Element*			FindSibling(Element* el, const CssSelector& selector, bool apply_pseudo = true, bool* is_pseudo = 0);
	virtual bool				IsFirstChildInline(const Element* el);
	virtual bool				IsLastChildInline(const Element* el);
	virtual bool				HaveInlineChild();
	virtual void				GetContentSize(Size& sz, int max_width);
	virtual void				Init();
	virtual bool				IsFloatsHolder() const;
	virtual int					GetFloatsHeight(ElementFloat el_float = FloatNone) const;
	virtual int					GetLeftFloatsHeight() const;
	virtual int					GetRightGloatsHeight() const;
	virtual int					GetLineLeft(int y);
	virtual int					GetLineRight(int y, int def_right);
	virtual void				GetLineLeftRight(int y, int def_right, int& ln_left, int& ln_right);
	virtual void				AddFloat(Element* el, int x, int y);
	virtual void				UpdateFloats(int dy, Element* higher);
	virtual void				AddPositioned(Element* el);
	virtual int					FindNextLineTop(int top, int width, int def_right);
	virtual int					GetZIndex() const;
	virtual void				DrawStackingContext(Draw& hdc, int x, int y, const Position& clip, bool with_positioned);
	virtual void				DrawChildren(Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex );
	virtual bool				IsNthChild(Element* el, int num, int off, bool of_type);
	virtual bool				IsNthLastChild(Element* el, int num, int off, bool of_type);
	virtual bool				IsOnlyChild(Element* el, bool of_type);
	virtual bool				GetPredefinedHeight(int& p_height) const;
	virtual void				CalcDocumentSize(UPP::Size& sz, int x = 0, int y = 0);
	virtual void				GetRedrawBox(Position& pos, int x = 0, int y = 0);
	virtual void				AddStyle(Style* st);
	virtual Element*			GetElementByPoint(int x, int y, int client_x, int client_y);
	virtual Element*			GetChildByPoint(int x, int y, int client_x, int client_y, DrawFlag flag, int zindex);
	virtual Background*			GetBackground(bool own_only = false);
	
	
	virtual int					GetStylePropertyCount() {return 0;}
	virtual String				GetStylePropertyKey(int i) {return "";}
	virtual String				GetStylePropertyValue(int i) {return "";}
	
	virtual Element*			GetAsElement()				{return this;}
};



inline int Element::Right() const
{
	return Left() + Width();
}

inline int Element::Left() const
{
	return pos.Left() - MarginLeft() - padding.left - borders.left;
}

inline int Element::Top() const
{
	return pos.Top() - MarginTop() - padding.top - borders.top;
}

inline int Element::Bottom() const
{
	return Top() + Height();
}

inline int Element::Height() const
{
	return pos.height + MarginTop() + MarginBottom() + padding.Height() + borders.Height();
}

inline int Element::Width() const
{
	return pos.width + MarginLeft() + MarginRight() + padding.Width() + borders.Width();
}

inline int Element::ContentMarginsTop() const
{
	return MarginTop() + padding.top + borders.top;
}

inline int Element::ContentMarginsBottom() const
{
	return MarginBottom() + padding.bottom + borders.bottom;
}

inline int Element::ContentMarginsLeft() const
{
	return MarginLeft() + padding.left + borders.left;
}

inline int Element::ContentMarginsRight() const
{
	return MarginRight() + padding.right + borders.right;
}

inline Margins Element::GetPaddings()	const
{
	return padding;
}

inline Margins Element::GetBorders()	const
{
	return borders;
}

inline int Element::PaddingTop() const
{
	return padding.top;
}

inline int Element::PaddingBottom() const
{
	return padding.bottom;
}

inline int Element::PaddingLeft() const
{
	return padding.left;
}

inline int Element::PaddingRight() const
{
	return padding.right;
}

inline bool Element::InNormalFlow() const
{
	if(GetElementPosition() != ElementPositionAbsolute && GetDisplay() != DisplayNone)
	{
		return true;
	}
	return false;
}

inline int Element::BorderTop() const
{
	return borders.top;
}

inline int Element::BorderBottom() const
{
	return borders.bottom;
}

inline int Element::BorderLeft() const
{
	return borders.left;
}

inline int Element::BorderRight() const
{
	return borders.right;
}

inline bool Element::Skip()
{
	return skip;
}

inline void Element::Skip(bool val)
{
	skip = val;
}

inline int Element::MarginTop() const
{
	return margins.top;
}

inline int Element::MarginBottom() const
{
	return margins.bottom;
}

inline int Element::MarginLeft() const
{
	return margins.left;
}

inline int Element::MarginRight() const
{
	return margins.right;
}

inline Margins Element::GetMargins() const
{
	Margins ret;
	ret.left	= MarginLeft();
	ret.right	= MarginRight();
	ret.top		= MarginTop();
	ret.bottom	= MarginBottom();

	return ret;
}

inline bool Element::IsPositioned()	const
{
	return (GetElementPosition() > ElementPositionStatic);
}

inline bool Element::IsVisible() const
{
	return !(skip || GetDisplay() == DisplayNone || GetVisibility() != VisibilityVisible);
}

class HtmlTag : public Element {
	
protected:
	Vector<One<Box> >		boxes;
	String					id;
	String					class_;
	String					tag;
	Style					style;
	StrMap					attrs;
	VerticalAlign			vertical_align;
	TextAlign				text_align;
	StyleDisplay			display;
	ListStyleType			list_style_type;
	ListStylePosition		list_style_position;
	WhiteSpace				white_space;
	ElementFloat			float_;
	ElementClear			clear;
	Vector<FloatedBox>		floats_left;
	Vector<FloatedBox>		floats_right;
	ElementsVector			positioned;
	Background				bg;
	ElementPosition			el_position;
	int						line_height = 0;
	bool					lh_predefined = 0;
	StringVector			pseudo_classes;
	Array<UsedSelector>		used_styles;
	
	uint32					font = 0;
	int						font_size = 0;
	FontMetrics				font_metrics;

	CssMargins				css_margins;
	CssMargins				css_padding;
	CssBorders				css_borders;
	CssLength				css_width;
	CssLength				css_height;
	CssLength				css_min_width;
	CssLength				css_min_height;
	CssLength				css_max_width;
	CssLength				css_max_height;
	CssOffsets				css_offsets;
	CssLength				css_text_indent;

	Overflow				overflow;
	Visibility				visibility;
	int						z_index = 0;
	BoxSizing				box_sizing;

	IntIntCache				cahe_line_left;
	IntIntCache				cahe_line_right;

	TableGrid				grid;
	CssLength				css_border_spacing_x;
	CssLength				css_border_spacing_y;
	int						border_spacing_x = 0;
	int						border_spacing_y = 0;
	BorderCollapse			borderCollapse;

	void Reset();
public:
	HtmlTag();
	~HtmlTag();
	

	virtual int					Render(int x, int y, int max_width, bool second_pass = false);

	virtual int					RenderInline(Element* container, int max_width);
	virtual int					PlaceElement(Element* el, int max_width);
	virtual bool				FetchPositioned();
	virtual void				RenderPositioned(RenderType rt = RenderAll);

	int							NewBox( Element* el, int max_width );

	int							GetClearedTop( Element* el, int line_top );
	int							FinishLastBox(bool end_of_render = false);

	virtual bool				AppendChild(Element* el);
	virtual String				GetTagName() const;
	virtual void				SetTagName(const String& tag);
	virtual void				SetData(const WString& data);
	virtual ElementFloat		GetFloat() const;
	virtual VerticalAlign		GetVerticalAlign() const;
	virtual CssLength			GetCssLeft() const;
	virtual CssLength			GetCssRight() const;
	virtual CssLength			GetCssTop() const;
	virtual CssLength			GetCssBottom() const;
	virtual CssLength			GetCssWidth() const;
	virtual CssOffsets			GetCssOffsets() const;
	virtual void				SetCssWidth(CssLength& w);
	virtual CssLength			GetCssHeight() const;
	virtual ElementClear		GetClear() const;
	virtual size_t				GetChildrenCount() const;
	virtual Element*			GetChild(int idx);
	virtual ElementPosition		GetElementPosition(CssOffsets* offsets = 0) const;
	virtual Overflow			GetOverflow() const;

	virtual void				SetAttr(const String& name, const String& val);
	virtual String				GetAttr(const String& name, const String& def = "");
	
	virtual int					GetAttrCount() {return attrs.GetCount();}
	virtual String				GetAttrKey(int i) {return attrs.GetKey(i);}
	virtual String				GetAttrValue(int i) {return attrs[i];}
	
	virtual void				ApplyStylesheet(const Css& Stylesheet);
	virtual void				RefreshStyles();

	virtual bool				IsWhiteSpace();
	virtual bool				IsBody() const;
	virtual bool				IsBreak() const;
	virtual int					GetBaseLine();
	virtual bool				OnMouseOver();
	virtual bool				OnMouseLeave();
	virtual bool				OnMouseLeftDown();
	virtual bool				OnMouseLeftUp();
	virtual void				OnClick();
	virtual bool				FindStylesChanges(Vector<Position>& redraw_boxes, int x, int y);
	virtual String				GetCursor();
	virtual void				InitFont();
	virtual bool				SetPseudoClass(const String& pclass, bool add);
	virtual bool				IsReplaced() const;
	virtual int					LineHeight() const;
	virtual WhiteSpace			GetWhiteSpace() const;
	virtual StyleDisplay		GetDisplay() const;
	virtual Visibility			GetVisibility() const;
	virtual void				ParseStyles(bool is_reparse = false);
	virtual void				Paint(Draw& hdc, int x, int y, const Position& clip);
	virtual void				DrawBackground( Draw& hdc, int x, int y, const Position& clip );

	virtual String				GetStyleProperty(const String& name, bool inherited, const String& def = "");
	virtual uint32				GetFont(FontMetrics* fm = 0);
	virtual int					GetFontSize() const;

	ElementsVector&				Children();
	virtual void				CalcOutlines( int higher_width );
	virtual void				CalcAutoMargins(int higher_width);

	virtual int					Select(const CssSelector& Selector, bool apply_pseudo = true);
	virtual int					Select(const CssElementSelector& Selector, bool apply_pseudo = true);

	virtual Element*			SelectOne(const String& Selector);
	virtual Element*			SelectOne(const CssSelector& Selector);

	virtual Element*			FindAncestor(const CssSelector& Selector, bool apply_pseudo = true, bool* is_pseudo = 0);
	virtual Element*			FindAdjacentSibling(Element* el, const CssSelector& Selector, bool apply_pseudo = true, bool* is_pseudo = 0);
	virtual Element*			FindSibling(Element* el, const CssSelector& Selector, bool apply_pseudo = true, bool* is_pseudo = 0);
	virtual void				GetText(WString& text);
	virtual void				ParseAttributes();

	virtual bool				IsFirstChildInline(const Element* el);
	virtual bool				IsLastChildInline(const Element* el);
	virtual bool				HaveInlineChild();
	virtual void				GetContentSize(Size& sz, int max_width);
	virtual void				Init();
	virtual void				GetInLineBoxes(Vector<Position>& Boxes);
	virtual bool				IsFloatsHolder() const;
	virtual int					GetFloatsHeight(ElementFloat el_float = FloatNone) const;
	virtual int					GetLeftFloatsHeight() const;
	virtual int					GetRightGloatsHeight() const;
	virtual int					GetLineLeft(int y);
	virtual int					GetLineRight(int y, int def_right);
	virtual void				GetLineLeftRight(int y, int def_right, int& ln_left, int& ln_right);
	virtual void				AddFloat(Element* el, int x, int y);
	virtual void				UpdateFloats(int dy, Element* higher);
	virtual void				AddPositioned(Element* el);
	virtual int					FindNextLineTop(int top, int width, int def_right);
	virtual void				ApplyVerticalAlign();
	virtual void				DrawChildren( Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex );
	virtual int					GetZIndex() const;
	virtual void				DrawStackingContext(Draw& hdc, int x, int y, const Position& clip, bool with_positioned);
	virtual void				CalcDocumentSize(UPP::Size& sz, int x = 0, int y = 0);
	virtual void				GetRedrawBox(Position& pos, int x = 0, int y = 0);
	virtual void				AddStyle(Style* st);
	virtual Element*			GetElementByPoint(int x, int y, int client_x, int client_y);
	virtual Element*			GetChildByPoint(int x, int y, int client_x, int client_y, DrawFlag flag, int zindex);

	virtual bool				IsNthChild(Element* el, int num, int off, bool of_type);
	virtual bool				IsNthLastChild(Element* el, int num, int off, bool of_type);
	virtual bool				IsOnlyChild(Element* el, bool of_type);
	virtual Background*			GetBackground(bool own_only = false);
	
	virtual int					GetStylePropertyCount();
	virtual String				GetStylePropertyKey(int i);
	virtual String				GetStylePropertyValue(int i);
	
	
protected:
	void						DrawChildrenBox(Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex);
	void						DrawChildrenTable(Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex);
	int							RenderBox(int x, int y, int max_width, bool second_pass = false);
	int							RenderTable(int x, int y, int max_width, bool second_pass = false);
	int							FixLineWidth(int max_width, ElementFloat flt);
	void						ParseBackground();
	void						InitBackgroundPaint( Position pos, BackgroundPaint &bg_paint, Background* bg );
	void						DrawListMarker( Draw& hdc, const Position &pos );
	void						ParseNthChildParams( String param, int &num, int &off );
	void						RemoveBeforeAfter();
	Element*					GetElementBefore();
	Element*					GetElementAfter();
};


class ElAnchor : public HtmlTag {
public:
	ElAnchor();

	virtual void	OnClick();
	virtual void	ApplyStylesheet(const Css& Stylesheet);
};


class ElBase : public HtmlTag {
public:
	ElBase();

	virtual void	ParseAttributes();
};

class ElBeforeAfterBase : public HtmlTag {
	void	AddText(const WString& txt);
	void	AddFunction(const String& fnc, const String& params);
	wchar ConvertEscape(const WString& txt);
	wchar ConvertEscape(const String& txt);
	
public:
	ElBeforeAfterBase(bool before);

	virtual void AddStyle(Style* st);
	virtual void ApplyStylesheet(const Css& Stylesheet);
};

class ElBefore : public ElBeforeAfterBase {
public:
	ElBefore() : ElBeforeAfterBase(true) {}
};

class ElAfter : public ElBeforeAfterBase {
public:
	ElAfter() : ElBeforeAfterBase(false) {}
};

class ElBody : public HtmlTag {
public:
	ElBody();
	
	virtual bool IsBody()  const;
	virtual void ParseAttributes();
};


class ElBreak : public HtmlTag {
public:
	ElBreak();

	virtual bool	IsBreak() const;
};

class ElCdata : public Element {
	WString	text;
public:
	ElCdata();

	virtual void	GetText(WString& text);
	virtual void	SetData(const WString& data);
};

class ElComment : public Element {
	WString	text;
public:
	ElComment();

	virtual void	GetText(WString& text);
	virtual void	SetData(const WString& data);
};


class ElDiv : public HtmlTag {
public:
	ElDiv();
	
	virtual void ParseAttributes();
};

class ElFont : public HtmlTag {
public:
	ElFont();
	
	virtual void ParseAttributes();
};

class ElImage : public HtmlTag {
	String	src;
	int		cache_id;
	
public:
	ElImage();

	virtual int		LineHeight() const;
	virtual bool	IsReplaced() const;
	virtual int		Render(int x, int y, int max_width, bool second_pass = false);
	virtual void	ParseAttributes();
	virtual void	ParseStyles(bool is_reparse = false);
	virtual void	Paint(Draw& hdc, int x, int y, const Position& clip);
	virtual void	GetContentSize(Size& sz, int max_width);
};

class ElLink : public HtmlTag {

protected:
	virtual void	ParseAttributes();
	
public:
	ElLink();
};

class ElPara : public HtmlTag {
public:
	ElPara();

	virtual void	ParseAttributes();
};

class ElScript : public Element {
	WString text;
	String type;
public:
	ElScript();

	virtual void			ParseAttributes();
	virtual bool			AppendChild(Element* el);
	virtual String			GetTagName() const;
	virtual void			SetAttr(const String& name, const String& val);
	
	const WString& GetContent() const {return text;}
	
};

class ElText : public Element {
protected:
	WString			text;
	WString			transformed_text;
	Size			size;
	TextTransform	text_transform;
	bool			use_transformed;
	bool			draw_spaces;
	
public:
	ElText(const WString& text);

	virtual void				GetText(WString& text);
	virtual String				GetStyleProperty(const String& name, bool inherited, const String& def = "");
	virtual void				ParseStyles(bool is_reparse);
	virtual int					GetBaseLine();
	virtual void				Paint(Draw& hdc, int x, int y, const Position& clip);
	virtual int					LineHeight() const;
	virtual uint32				GetFont(FontMetrics* fm = 0);
	virtual StyleDisplay		GetDisplay() const;
	virtual WhiteSpace			GetWhiteSpace() const;
	virtual ElementPosition		GetElementPosition(CssOffsets* offsets = 0) const;
	virtual CssOffsets			GetCssOffsets() const;

protected:
	virtual void				GetContentSize(Size& sz, int max_width);
};

class ElSpace : public ElText {
public:
	ElSpace(const WString& text);

	virtual bool	IsWhiteSpace();
	virtual bool	IsBreak() const;
};

class ElStyle : public Element {
	ElementsVector		children;
public:
	ElStyle();
	
	virtual void			ParseAttributes();
	virtual bool			AppendChild(Element* el);
	virtual String			GetTagName() const;
};


struct col_info
{
	int		width;
	bool	is_auto;
};

class ElTable : public HtmlTag {
public:
	ElTable();

	virtual bool	AppendChild(Element* el);
	virtual void	ParseStyles(bool is_reparse = false);
	virtual void	ParseAttributes();
};

class ElTd : public HtmlTag {
public:
	ElTd();

	virtual void ParseAttributes();
};

class ElTitle : public HtmlTag {
protected:
	virtual void	ParseAttributes();
public:
	ElTitle();

};

class ElTr : public HtmlTag {
public:
	ElTr();

	virtual void	ParseAttributes();
	virtual void	GetInLineBoxes(Vector<Position>& Boxes);
};


NAMESPACE_LAYOUT_END

#endif
