#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN

#define OVERLAY_EMPTY_FUNC			{}
#define OVERLAY_RETURN_FUNC(ret)	{return ret;}





Element::Element()  {
	box = 0;
	skip = false;
}

ConstDocument* Element::GetDocument() const {return CastPtr<ConstDocument>(GetTopParent());}
Document* Element::GetDocument() {return CastPtr<Document>(GetTopParent());}

bool Element::IsPointInside( int x, int y )
{
	if(GetDisplay() != DisplayInline && GetDisplay() != DisplayTableRow)
	{
		Position pos = this->pos;
		pos += padding;
		pos += borders;
		if(pos.IsPointInside(x, y))
		{
			return true;
		}
		else
		{
			return false;
		}
	} else
	{
		Vector<Position> Boxes;
		GetInLineBoxes(Boxes);
		for(Vector<Position>::Iterator Box = Boxes.Begin(); Box != Boxes.End(); Box++)
		{
			if(Box->IsPointInside(x, y))
			{
				return true;
			}
		}
	}
	return false;
}

RGBA Element::GetColor( const String& prop_name, bool inherited, const RGBA& DefColor )
{
	String clrstr = GetStyleProperty(prop_name, inherited, "");
	if(!clrstr.GetCount()) {
		return DefColor;
	}
	return RGBAFromString(clrstr);
}

Position Element::GetPlacement() const
{
	Position pos = this->pos;
	Element* cur_el = GetParentElement();
	while(cur_el)
	{
		pos.x += cur_el->pos.x;
		pos.y += cur_el->pos.y;
		cur_el = cur_el->GetParentElement();
	}
	return pos;
}

bool Element::IsInLineBox() const
{
	StyleDisplay d = GetDisplay();
	if(	d == DisplayInline ||
		d == DisplayInlineBlock ||
		d == DisplayInlineText)
	{
		return true;
	}
	return false;
}

bool Element::CollapseTopMargin() const
{
	if(!borders.top && !padding.top && InNormalFlow() && GetFloat() == FloatNone && margins.top >= 0 && GetParent()->Is<Element>())
	{
		return true;
	}
	return false;
}

bool Element::CollapseBottomMargin() const
{
	if(!borders.bottom && !padding.bottom && InNormalFlow() && GetFloat() == FloatNone && margins.bottom >= 0 && GetParent()->Is<Element>())
	{
		return true;
	}
	return false;
}

bool Element::GetPredefinedHeight(int& p_height) const
{
	CssLength h = GetCssHeight();
	if(h.IsPredefined())
	{
		p_height = pos.height;
		return false;
	}
	if(h.Units() == CssUnitsPercentage)
	{
		if(!GetParent()->Is<Element>())
		{
			Position client_pos;
			GetDocument()->GetHtmlCtrl().GetClientRect(client_pos);
			p_height = h.CalcPercent(client_pos.height);
			return true;
		} else
		{
			int ph = 0;
			if(GetParentElement()->GetPredefinedHeight(ph))
			{
				p_height = h.CalcPercent(ph);
				p_height -= ContentMarginsTop() + ContentMarginsBottom();
				return true;
			} else
			{
				p_height = pos.height;
				return false;
			}
		}
	}
	p_height = GetDocument()->CvtUnits(h, GetFontSize());
	return true;
}

void Element::CalcDocumentSize( UPP::Size& sz, int x /*= 0*/, int y /*= 0*/ )
{
	if(IsVisible())
	{
		sz.cx	= max(sz.cx,	x + Right());
		sz.cy	= max(sz.cy,	y + Bottom());
	}
}

void Element::GetRedrawBox(Position& pos, int x /*= 0*/, int y /*= 0*/)
{
	if(IsVisible())
	{
		int p_left		= min(pos.Left(),	x + pos.Left() - padding.left - borders.left);
		int p_right		= max(pos.Right(), x + pos.Right() + padding.left + borders.left);
		int p_top		= min(pos.Top(), y + pos.Top() - padding.top - borders.top);
		int p_bottom	= max(pos.Bottom(), y + pos.Bottom() + padding.bottom + borders.bottom);

		pos.x = p_left;
		pos.y = p_top;
		pos.width	= p_right - p_left;
		pos.height	= p_bottom - p_top;
	}
}

int Element::CalcWidth(int defVal) const
{
	CssLength w = GetCssWidth();
	if(w.IsPredefined())
	{
		return defVal;
	}
	if(w.Units() == CssUnitsPercentage)
	{
		if(!GetParent()->Is<Element>())
		{
			Position client_pos;
			GetDocument()->GetHtmlCtrl().GetClientRect(client_pos);
			return w.CalcPercent(client_pos.width);
		} else
		{
			int pw = GetParentElement()->CalcWidth(defVal);
			pw = w.CalcPercent(pw);
			pw -= ContentMarginsRight() + ContentMarginsLeft();
			return pw;
		}
	}
	return 	GetDocument()->CvtUnits(w, GetFontSize());
}

bool Element::IsAncestor( Element* el )
{
	Element* el_higher = GetParentElement();
	while(el_higher && el_higher != el)
	{
		el_higher = el_higher->GetParentElement();
	}
	if(el_higher)
	{
		return true;
	}
	return false;
}

int Element::GetInlineShiftLeft()
{
	int ret = 0;

	if(GetParentElement()->GetDisplay() == DisplayInline)
	{
		StyleDisplay disp = GetDisplay();

		if(disp == DisplayInlineText || disp == DisplayInlineBlock)
		{
			Element* higher = GetParentElement();
			Element* el = this;
			while(higher && higher->GetDisplay() == DisplayInline)
			{
				if( higher->IsFirstChildInline(el) )
				{
					ret += higher->PaddingLeft() + higher->BorderLeft() + higher->MarginLeft();
				}
				el = higher;
				
				higher = higher->GetParentElement();
			}
		}
	}

	return ret;
}

int Element::GetInlineShiftRight()
{
	int ret = 0;

	if(GetParentElement()->GetDisplay() == DisplayInline)
	{
		StyleDisplay disp = GetDisplay();

		if(disp == DisplayInlineText || disp == DisplayInlineBlock)
		{
			Element* higher = GetParentElement();
			Element* el = this;
			while(higher && higher->GetDisplay() == DisplayInline)
			{
				if( higher->IsLastChildInline(el) )
				{
					ret += higher->PaddingRight() + higher->BorderRight() + higher->MarginRight();
				}
				el = higher;
				higher = higher->GetParentElement();
			}
		}
	}

	return ret;
}

void Element::CalcAutoMargins(int higher_width)							OVERLAY_EMPTY_FUNC
Background* Element::GetBackground(bool own_only)				OVERLAY_RETURN_FUNC(0)
Element* Element::GetElementByPoint( int x, int y, int client_x, int client_y )	OVERLAY_RETURN_FUNC(0)
Element* Element::GetChildByPoint( int x, int y, int client_x, int client_y, DrawFlag flag, int zindex ) OVERLAY_RETURN_FUNC(0)
void Element::GetLineLeftRight( int y, int def_right, int& ln_left, int& ln_right ) OVERLAY_EMPTY_FUNC
void Element::AddStyle( Style* st )						OVERLAY_EMPTY_FUNC
Element* Element::SelectOne( const CssSelector& Selector ) OVERLAY_RETURN_FUNC(0)
Element* Element::SelectOne( const String& Selector )		OVERLAY_RETURN_FUNC(0)
Element* Element::FindAdjacentSibling( Element* el, const CssSelector& Selector, bool apply_pseudo /*= true*/, bool* is_pseudo /*= 0*/ ) OVERLAY_RETURN_FUNC(0)
Element* Element::FindSibling( Element* el, const CssSelector& Selector, bool apply_pseudo /*= true*/, bool* is_pseudo /*= 0*/ ) OVERLAY_RETURN_FUNC(0)
bool Element::IsNthLastChild( Element* el, int num, int off, bool of_type )			OVERLAY_RETURN_FUNC(false)
bool Element::IsNthChild( Element* el, int num, int off, bool of_type )				OVERLAY_RETURN_FUNC(false)
bool Element::IsOnlyChild(Element* el, bool of_type)					OVERLAY_RETURN_FUNC(false)
Overflow Element::GetOverflow() const							OVERLAY_RETURN_FUNC(OverflowVisible)
void Element::DrawChildren( Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex ) OVERLAY_EMPTY_FUNC
void Element::DrawStackingContext( Draw& hdc, int x, int y, const Position& clip, bool with_positioned ) OVERLAY_EMPTY_FUNC
void Element::RenderPositioned(RenderType rt)							OVERLAY_EMPTY_FUNC
int Element::GetZIndex() const											OVERLAY_RETURN_FUNC(0)
bool Element::FetchPositioned()											OVERLAY_RETURN_FUNC(false)
Visibility Element::GetVisibility() const						OVERLAY_RETURN_FUNC(VisibilityVisible)
void Element::ApplyVerticalAlign()										OVERLAY_EMPTY_FUNC
void Element::SetCssWidth( CssLength& w )								OVERLAY_EMPTY_FUNC
Element* Element::GetChild( int idx )									OVERLAY_RETURN_FUNC(0)
size_t Element::GetChildrenCount() const								OVERLAY_RETURN_FUNC(0)
void Element::CalcOutlines( int higher_width )							OVERLAY_EMPTY_FUNC
CssLength Element::GetCssWidth() const						OVERLAY_RETURN_FUNC(CssLength())
CssLength Element::GetCssHeight() const						OVERLAY_RETURN_FUNC(CssLength())
ElementClear Element::GetClear() const						OVERLAY_RETURN_FUNC(ClearNone)
CssLength Element::GetCssLeft() const						OVERLAY_RETURN_FUNC(CssLength())
CssLength Element::GetCssRight() const						OVERLAY_RETURN_FUNC(CssLength())
CssLength Element::GetCssTop() const							OVERLAY_RETURN_FUNC(CssLength())
CssLength Element::GetCssBottom() const						OVERLAY_RETURN_FUNC(CssLength())
CssOffsets Element::GetCssOffsets() const					OVERLAY_RETURN_FUNC(CssOffsets())
VerticalAlign Element::GetVerticalAlign() const				OVERLAY_RETURN_FUNC(VABaseline)
int Element::PlaceElement( Element* el, int max_width )					OVERLAY_RETURN_FUNC(0)
int Element::RenderInline( Element* container, int max_width )			OVERLAY_RETURN_FUNC(0)
void Element::AddPositioned( Element* el )									OVERLAY_EMPTY_FUNC
int Element::FindNextLineTop( int top, int width, int def_right )		OVERLAY_RETURN_FUNC(0)
ElementFloat Element::GetFloat() const						OVERLAY_RETURN_FUNC(FloatNone)
void Element::AddFloat( Element* el, int x, int y )						OVERLAY_EMPTY_FUNC
void Element::UpdateFloats( int dy, Element* higher )					OVERLAY_EMPTY_FUNC
int Element::GetLineLeft( int y )										OVERLAY_RETURN_FUNC(0)
int Element::GetLineRight( int y, int def_right )						OVERLAY_RETURN_FUNC(def_right)
int Element::GetLeftFloatsHeight() const								OVERLAY_RETURN_FUNC(0)
int Element::GetRightGloatsHeight() const								OVERLAY_RETURN_FUNC(0)
int Element::GetFloatsHeight(ElementFloat el_float) const				OVERLAY_RETURN_FUNC(0)
bool Element::IsFloatsHolder() const									OVERLAY_RETURN_FUNC(false)
void Element::GetContentSize( Size& sz, int max_width )					OVERLAY_EMPTY_FUNC
void Element::Init()														OVERLAY_EMPTY_FUNC
int Element::Render( int x, int y, int max_width, bool second_pass )		OVERLAY_RETURN_FUNC(0)
bool Element::AppendChild( Element* el )						OVERLAY_RETURN_FUNC(false)
String Element::GetTagName() const						OVERLAY_RETURN_FUNC("")
void Element::SetTagName( const String& tag )							OVERLAY_EMPTY_FUNC
void Element::SetData( const WString& data )								OVERLAY_EMPTY_FUNC
void Element::SetAttr( const String& name, const String& val )			OVERLAY_EMPTY_FUNC
void Element::ApplyStylesheet( const Css& Stylesheet )			OVERLAY_EMPTY_FUNC
void Element::RefreshStyles()											OVERLAY_EMPTY_FUNC
void Element::OnClick()													OVERLAY_EMPTY_FUNC
void Element::InitFont()													OVERLAY_EMPTY_FUNC
void Element::GetInLineBoxes( Vector<Position>& Boxes )					OVERLAY_EMPTY_FUNC
void Element::ParseStyles( bool is_reparse /*= false*/ )					OVERLAY_EMPTY_FUNC
String Element::GetAttr( const String& name, const String& def /*= 0*/ )	OVERLAY_RETURN_FUNC(def)
bool Element::IsWhiteSpace()											OVERLAY_RETURN_FUNC(false)
bool Element::IsBody() const												OVERLAY_RETURN_FUNC(false)
bool Element::IsBreak() const											OVERLAY_RETURN_FUNC(false)
int Element::GetBaseLine()												OVERLAY_RETURN_FUNC(0)
bool Element::OnMouseOver()												OVERLAY_RETURN_FUNC(false)
bool Element::OnMouseLeave()											OVERLAY_RETURN_FUNC(false)
bool Element::OnMouseLeftDown()											OVERLAY_RETURN_FUNC(false)
bool Element::OnMouseLeftUp()												OVERLAY_RETURN_FUNC(false)
bool Element::FindStylesChanges( Vector<Position>& redraw_boxes, int x, int y )	OVERLAY_RETURN_FUNC(false)
String Element::GetCursor()							OVERLAY_RETURN_FUNC("")
WhiteSpace Element::GetWhiteSpace() const					OVERLAY_RETURN_FUNC(WhiteSpaceNormal)
StyleDisplay Element::GetDisplay() const							OVERLAY_RETURN_FUNC(DisplayNone)
bool Element::SetPseudoClass( const String& pclass, bool add )			OVERLAY_RETURN_FUNC(false)
ElementPosition Element::GetElementPosition(CssOffsets* offsets) const	OVERLAY_RETURN_FUNC(ElementPositionStatic)
bool Element::IsReplaced() const										OVERLAY_RETURN_FUNC(false)
int Element::LineHeight() const											OVERLAY_RETURN_FUNC(0)
void Element::Paint( Draw& hdc, int x, int y, const Position& clip )	OVERLAY_EMPTY_FUNC
void Element::DrawBackground( Draw& hdc, int x, int y, const Position& clip )	OVERLAY_EMPTY_FUNC
String Element::GetStyleProperty( const String& name, bool inherited, const String& def /*= 0*/ )	OVERLAY_RETURN_FUNC("")
uint32 Element::GetFont( FontMetrics* fm /*= 0*/ )						OVERLAY_RETURN_FUNC(0)
int Element::GetFontSize()	const										OVERLAY_RETURN_FUNC(0)
void Element::GetText( WString& text )									OVERLAY_EMPTY_FUNC
void Element::ParseAttributes()											OVERLAY_EMPTY_FUNC
int Element::Select( const CssSelector& Selector, bool apply_pseudo)		OVERLAY_RETURN_FUNC(SelectNoMatch)
int Element::Select( const CssElementSelector& Selector, bool apply_pseudo /*= true*/ )	OVERLAY_RETURN_FUNC(SelectNoMatch)
Element* Element::FindAncestor( const CssSelector& Selector, bool apply_pseudo, bool* is_pseudo)	OVERLAY_RETURN_FUNC(0)
bool Element::IsFirstChildInline( const Element* el )					OVERLAY_RETURN_FUNC(false)
bool Element::IsLastChildInline( const Element* el )					OVERLAY_RETURN_FUNC(false)
bool Element::HaveInlineChild()											OVERLAY_RETURN_FUNC(false)








HtmlTag::HtmlTag() {Reset();}

HtmlTag::~HtmlTag() {
	for(int i = 0; i < boxes.GetCount(); i++)
		boxes[i].Clear();
}

void HtmlTag::Reset()
{
	box_sizing				= BoxSizingContentBox;
	z_index					= 0;
	overflow				= OverflowVisible;
	box						= 0;
	text_align				= TextAlignLeft;
	el_position				= ElementPositionStatic;
	display					= DisplayInline;
	vertical_align			= VABaseline;
	list_style_type			= ListStyleTypeNone;
	list_style_position		= ListStylepositionOutside;
	float_					= FloatNone;
	clear					= ClearNone;
	font					= 0;
	font_size				= 0;
	white_space				= WhiteSpaceNormal;
	lh_predefined			= false;
	line_height				= 0;
	visibility				= VisibilityVisible;
	border_spacing_x		= 0;
	border_spacing_y		= 0;
	borderCollapse			= BorderCollapseSeparate;
}

bool HtmlTag::AppendChild( Element* el )
{
	if(el)
	{
		el->MoveTo(*this);
		return true;
	}
	return false;
}

String HtmlTag::GetTagName() const
{
	return tag;
}

void HtmlTag::SetAttr( const String& name, const String& val ) {
	if(name.GetCount() && val.GetCount()) {
		String tmp;
		for(size_t i = 0; i < name.GetCount(); i++)
		{
			tmp.Cat( ToLower(name[i]) );
		}
		attrs.GetAdd(tmp) = val;
	}
}

String HtmlTag::GetAttr( const String& name, const String& def )
{
	int i = attrs.Find(name);
	if (i != -1)
		return attrs[i];
	return def;
}

Element* HtmlTag::SelectOne( const String& selector )
{
	CssSelector sel(NULL);
	sel.Parse(selector);

	return SelectOne(sel);
}

Element* HtmlTag::SelectOne( const CssSelector& selector )
{
	if(Select(selector))
	{
		return this;
	}
	
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if (el) {
			Element* res = el->SelectOne(selector);
			if(res)
				return res;
		}
	}
	return 0;
}

void HtmlTag::ApplyStylesheet( const Css& stylesheet )
{
	RemoveBeforeAfter();

	for (int i = 0; i < stylesheet.Selectors().GetCount(); i++) {
		ASSERT(!stylesheet.Selectors()[i].IsEmpty());
		const CssSelector& sel = *stylesheet.Selectors()[i];
		
		int apply = Select(sel, false);

		if(apply != SelectNoMatch)
		{
			UsedSelector* us = new UsedSelector(&sel, false);
			used_styles.Add(us);

			if(sel.IsMediaValid())
			{
				if(apply & SelectMatchPseudoClass)
				{
					if(Select(sel, true))
					{
						AddStyle(sel.style);
						us->used = true;
					}
				} else if(apply & SelectMatchWithAfter)
				{
					Element* el = GetElementAfter();
					if(el)
						el->AddStyle(sel.style);
				} else if(apply & SelectMatchWithBefore)
				{
					Element* el = GetElementBefore();
					if(el)
						el->AddStyle(sel.style);
				} else
				{
					AddStyle(sel.style);
					us->used = true;
				}
			}
		}
	}

	for (int j = 0; j < Object::GetCount(); j++)
	{
		Element* el = Object::At(j).As<Element>();
		if(el && el->GetDisplay() != DisplayInlineText) {
			el->ApplyStylesheet(stylesheet);
		}
	}
}

void HtmlTag::GetContentSize( Size& sz, int max_width )
{
	sz.cy	= 0;
	if(display == DisplayBlock)
	{
		sz.cx	= max_width;
	} else
	{
		sz.cx	= 0;
	}
}

void HtmlTag::Paint( Draw& hdc, int x, int y, const Position& clip )
{
	Position pos = this->pos;
	pos.x	+= x;
	pos.y	+= y;

	DrawBackground(hdc, x, y, clip);

	if(display == DisplayListItem && list_style_type != ListStyleTypeNone)
	{
		if(overflow > OverflowVisible)
		{
			Position border_box = pos;
			border_box += padding;
			border_box += borders;

			BorderRadiuses bdr_radius = css_borders.radius.CalcPercents(border_box.width, border_box.height);

			bdr_radius -= borders;
			bdr_radius -= padding;

			GetDocument()->GetHtmlCtrl().SetClip(hdc, pos, bdr_radius, true, true);
		}

		DrawListMarker(hdc, pos);

		if(overflow > OverflowVisible)
		{
			GetDocument()->GetHtmlCtrl().DelClip(hdc);
		}
	}
}

uint32 HtmlTag::GetFont(FontMetrics* fm)
{
	if(fm)
	{
		*fm = font_metrics;
	}
	return font;
}
	

String HtmlTag::GetStyleProperty( const String& name, bool inherited, const String& def /*= 0*/ )
{
	String ret = style.GetProperty(name);
	bool pass_higher = false;
	
	
	Element* higher = GetParentElement();
	if(higher) {
	
	
		if(ret.GetCount() && !CompareNoCase(ret, "inherit"))
		{
			pass_higher = true;
		} else if(!ret.GetCount() && inherited)
		{
			pass_higher = true;
		}
	}
	if (pass_higher)
	{
			ret = higher->GetStyleProperty(name, inherited, def);
	}

	if(!ret.GetCount())
	{
		return def;
	}

	return ret;
}

int HtmlTag::GetStylePropertyCount() {
	return style.GetCount();
}

String HtmlTag::GetStylePropertyKey(int i) {
	return style.GetKey(i);
}

String HtmlTag::GetStylePropertyValue(int i) {
	return style.GetValue(i);
}

void HtmlTag::ParseStyles(bool is_reparse)
{
	id		= GetAttr("id", "");
	class_	= GetAttr("class", "");

	String style = GetAttr("style");
	
	if(style.GetCount()) {
		this->style.Add(style, "");
	}

	InitFont();

	el_position	= (ElementPosition)		ValueIndex(GetStyleProperty("Position",		false,	"static"),		ElementPositionStrings,	ElementPositionFixed);
	text_align	= (TextAlign)			ValueIndex(GetStyleProperty("text-align",	true,	"left"),		TextAlignStrings,			TextAlignLeft);
	overflow	= (Overflow)			ValueIndex(GetStyleProperty("Overflow",		false,	"visible"),		OverflowStrings,			OverflowVisible);
	white_space	= (WhiteSpace)			ValueIndex(GetStyleProperty("white-space",	true,	"normal"),		WhiteSpaceStrings,		WhiteSpaceNormal);
	display		= (StyleDisplay)		ValueIndex(GetStyleProperty("display",		false,	"inline"),		StyleDisplayStrings,		DisplayInline);
	visibility	= (Visibility)			ValueIndex(GetStyleProperty("Visibility",	true,	"visible"),		VisibilityStrings,			VisibilityVisible);
	box_sizing	= (BoxSizing)			ValueIndex(GetStyleProperty("Box-sizing",	false,	"content-box"),	BoxSizingStrings,			BoxSizingContentBox);

	if(el_position != ElementPositionStatic)
	{
		String val = GetStyleProperty("z-index", false, "");
		if(val.GetCount())
		{
			z_index = StrInt(val);
		}
	}

	String va	= GetStyleProperty("vertical-align", true,	"baseline");
	vertical_align = (VerticalAlign) ValueIndex(va, VerticalAlignStrings, VABaseline);

	String fl	= GetStyleProperty("float", false,	"none");
	float_ = (ElementFloat) ValueIndex(fl, ElementFloatStrings, FloatNone);

	clear = (ElementClear) ValueIndex(GetStyleProperty("clear", false, "none"), ElementClearStrings, ClearNone);
	
	Document* doc = GetDocument();
	
	if (float_ != FloatNone)
	{
		// reset display in to block for floating elements
		if (display != DisplayNone)
		{
			display = DisplayBlock;
		}
	}
	else if (display == DisplayTable ||
		display == DisplayTableCaption ||
		display == DisplayTableCell ||
		display == DisplayTableColumn ||
		display == DisplayTableColumnGroup ||
		display == DisplayTableFooterGroup ||
		display == DisplayTableHeaderGroup ||
		display == DisplayTableRow ||
		display == DisplayTableRowGroup)
	{
		doc->AddTabular(this);
	}
	// fix inline Boxes with absolute/fixed Positions
	else if (display != DisplayNone && IsInLineBox())
	{
		if (el_position == ElementPositionAbsolute || el_position == ElementPositionFixed)
		{
			display = DisplayBlock;
		}
	}

	css_text_indent.FromString(	GetStyleProperty("text-indent",	true,	"0"),	"0");

	css_width.FromString(			GetStyleProperty("width",			false, "auto"), "auto");
	css_height.FromString(		GetStyleProperty("height",			false, "auto"), "auto");

	doc->CvtUnits(css_width,	font_size);
	doc->CvtUnits(css_height,	font_size);

	css_min_width.FromString(		GetStyleProperty("min-width",		false,	"0"));
	css_min_height.FromString(	GetStyleProperty("min-height",		false,	"0"));

	css_max_width.FromString(		GetStyleProperty("max-width",		false,	"none"),	"none");
	css_max_height.FromString(	GetStyleProperty("max-height",		false,	"none"),	"none");
	
	doc->CvtUnits(css_min_width,	font_size);
	doc->CvtUnits(css_min_height,	font_size);

	css_offsets.left.FromString(		GetStyleProperty("left",				false,	"auto"), "auto");
	css_offsets.right.FromString(		GetStyleProperty("right",				false,	"auto"), "auto");
	css_offsets.top.FromString(		GetStyleProperty("top",				false,	"auto"), "auto");
	css_offsets.bottom.FromString(	GetStyleProperty("bottom",			false,	"auto"), "auto");

	doc->CvtUnits(css_offsets.left,		font_size);
	doc->CvtUnits(css_offsets.right,	font_size);
	doc->CvtUnits(css_offsets.top,		font_size);
	doc->CvtUnits(css_offsets.bottom,	font_size);

	css_margins.left.FromString(		GetStyleProperty("margin-left",			false,	"0"), "auto");
	css_margins.right.FromString(		GetStyleProperty("margin-right",		false,	"0"), "auto");
	css_margins.top.FromString(		GetStyleProperty("margin-top",			false,	"0"), "auto");
	css_margins.bottom.FromString(	GetStyleProperty("margin-bottom",		false,	"0"), "auto");

	css_padding.left.FromString(		GetStyleProperty("padding-left",		false,	"0"), "");
	css_padding.right.FromString(		GetStyleProperty("padding-right",		false,	"0"), "");
	css_padding.top.FromString(		GetStyleProperty("padding-top",			false,	"0"), "");
	css_padding.bottom.FromString(	GetStyleProperty("padding-bottom",		false,	"0"), "");

	css_borders.left.width.FromString(	GetStyleProperty("border-left-width",		false,	"medium"), BorderWidthStrings);
	css_borders.right.width.FromString(	GetStyleProperty("border-right-width",		false,	"medium"), BorderWidthStrings);
	css_borders.top.width.FromString(		GetStyleProperty("border-top-width",		false,	"medium"), BorderWidthStrings);
	css_borders.bottom.width.FromString(	GetStyleProperty("border-bottom-width",		false,	"medium"), BorderWidthStrings);

	css_borders.left.color = RGBAFromString(GetStyleProperty("border-left-color",	false,	""));
	css_borders.left.style = (BorderStyle) ValueIndex(GetStyleProperty("border-left-style", false, "none"), BorderStyleStrings, BorderStyleNone);

	css_borders.right.color = RGBAFromString(GetStyleProperty("border-right-color",	false,	""));
	css_borders.right.style = (BorderStyle) ValueIndex(GetStyleProperty("border-right-style", false, "none"), BorderStyleStrings, BorderStyleNone);

	css_borders.top.color = RGBAFromString(GetStyleProperty("border-top-color",	false,	""));
	css_borders.top.style = (BorderStyle) ValueIndex(GetStyleProperty("border-top-style", false, "none"), BorderStyleStrings, BorderStyleNone);

	css_borders.bottom.color = RGBAFromString(GetStyleProperty("border-bottom-color",	false,	""));
	css_borders.bottom.style = (BorderStyle) ValueIndex(GetStyleProperty("border-bottom-style", false, "none"), BorderStyleStrings, BorderStyleNone);

	css_borders.radius.top_left_x.FromString(GetStyleProperty("border-top-left-radius-x", false, "0"));
	css_borders.radius.top_left_y.FromString(GetStyleProperty("border-top-left-radius-y", false, "0"));

	css_borders.radius.top_right_x.FromString(GetStyleProperty("border-top-right-radius-x", false, "0"));
	css_borders.radius.top_right_y.FromString(GetStyleProperty("border-top-right-radius-y", false, "0"));

	css_borders.radius.bottom_right_x.FromString(GetStyleProperty("border-bottom-right-radius-x", false, "0"));
	css_borders.radius.bottom_right_y.FromString(GetStyleProperty("border-bottom-right-radius-y", false, "0"));

	css_borders.radius.bottom_left_x.FromString(GetStyleProperty("border-bottom-left-radius-x", false, "0"));
	css_borders.radius.bottom_left_y.FromString(GetStyleProperty("border-bottom-left-radius-y", false, "0"));

	doc->CvtUnits(css_borders.radius.bottom_left_x,			font_size);
	doc->CvtUnits(css_borders.radius.bottom_left_y,			font_size);
	doc->CvtUnits(css_borders.radius.bottom_right_x,			font_size);
	doc->CvtUnits(css_borders.radius.bottom_right_y,			font_size);
	doc->CvtUnits(css_borders.radius.top_left_x,				font_size);
	doc->CvtUnits(css_borders.radius.top_left_y,				font_size);
	doc->CvtUnits(css_borders.radius.top_right_x,				font_size);
	doc->CvtUnits(css_borders.radius.top_right_y,				font_size);

	doc->CvtUnits(css_text_indent,								font_size);

	margins.left		= doc->CvtUnits(css_margins.left,		font_size);
	margins.right		= doc->CvtUnits(css_margins.right,		font_size);
	margins.top		= doc->CvtUnits(css_margins.top,		font_size);
	margins.bottom	= doc->CvtUnits(css_margins.bottom,	font_size);

	padding.left		= doc->CvtUnits(css_padding.left,		font_size);
	padding.right		= doc->CvtUnits(css_padding.right,		font_size);
	padding.top		= doc->CvtUnits(css_padding.top,		font_size);
	padding.bottom	= doc->CvtUnits(css_padding.bottom,	font_size);

	borders.left		= doc->CvtUnits(css_borders.left.width,	font_size);
	borders.right		= doc->CvtUnits(css_borders.right.width,	font_size);
	borders.top		= doc->CvtUnits(css_borders.top.width,		font_size);
	borders.bottom	= doc->CvtUnits(css_borders.bottom.width,	font_size);

	CssLength line_height;
	line_height.FromString(GetStyleProperty("line-height",	true,	"normal"), "normal");
	if(line_height.IsPredefined())
	{
		this->line_height = font_metrics.height;
		lh_predefined = true;
	} else if(line_height.Units() == CssUnitsNone)
	{
		this->line_height = (int) (line_height.GetValue() * font_size);
		lh_predefined = false;
	} else
	{
		this->line_height =  doc->CvtUnits(line_height,	font_size, font_size);
		lh_predefined = false;
	}


	if(display == DisplayListItem)
	{
		String list_type = GetStyleProperty("list-style-type", true, "disc");
		list_style_type = (ListStyleType) ValueIndex(list_type, ListStyleTypeStrings, ListStyleTypeDisc);

		String list_pos = GetStyleProperty("list-style-position", true, "outside");
		list_style_position = (ListStylePosition) ValueIndex(list_pos, ListStylepositionStrings, ListStylepositionOutside);

		String list_image = GetStyleProperty("list-style-image", true, "");
		
		if(list_image.GetCount() && list_image[0])
		{
			String url;
			Css::ParseCssUrl(list_image, url);

			String list_image_baseurl = GetStyleProperty("list-style-image-baseurl", true, "");
			doc->GetHtmlCtrl().LoadImage(url, list_image_baseurl, true);
		}

	}

	ParseBackground();

	if(!is_reparse)
	{
		for(int i = 0; i < Object::GetCount(); i++) {
			Element* el = Object::At(i).As<Element>();
			if (el)
				el->ParseStyles();
		}
	}
}

int HtmlTag::Render( int x, int y, int max_width, bool second_pass )
{
	if (display == DisplayTable || display == DisplayInlineTable)
	{
		return RenderTable(x, y, max_width, second_pass);
	}

	return RenderBox(x, y, max_width, second_pass);
}

bool HtmlTag::IsWhiteSpace()
{
	return false;
}

int HtmlTag::GetFontSize() const
{
	return font_size;
}

int HtmlTag::GetBaseLine()
{
	if(IsReplaced())
	{
		return 0;
	}
	int bl = 0;
	if(!boxes.IsEmpty())
	{
		bl = LAST(boxes)->Baseline() + ContentMarginsBottom();
	}
	return bl;
}

void HtmlTag::Init()
{
	if (display == DisplayTable || display == DisplayInlineTable)
	{
		grid.Clear();

		GoInsideTable		table_selector;
		TableRowsSelector	row_selector;
		TableCellsSelector	cell_selector;

		ElementsIterator row_iter(this, &table_selector, &row_selector);

		Element* row = row_iter.Next(false);
		while (row)
		{
			grid.BeginRow(row);

			ElementsIterator cell_iter(row, &table_selector, &cell_selector);
			Element* cell = cell_iter.Next();
			while (cell)
			{
				grid.AddCell(cell);

				cell = cell_iter.Next(false);
			}
			row = row_iter.Next(false);
		}

		grid.Finish();
	}
	else
	{
		//remove white spaces
		int i = 0;
		while (i < Object::GetCount())
		{
			Element* el = At(i).As<Element>();
			if (el && el->IsWhiteSpace())
			{
				i++;
				while ( i < Object::GetCount())
				{
					Element* el = At(i).As<Element>();
					if (el && !el->IsWhiteSpace()) break;
					Object::Remove(i);
				}
			}
			else
			{
				i++;
			}
		}
	}

	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if (el)
			el->Init();
	}
}

int HtmlTag::Select(const CssSelector& selector, bool apply_pseudo)
{
	int right_res = Select(selector.right, apply_pseudo);
	if(right_res == SelectNoMatch)
	{
		return SelectNoMatch;
	}
	if(selector.left)
	{
		Element* higher = GetParentElement();
		if(!higher)
		{
			return SelectNoMatch;
		}
		switch(selector.combinator)
		{
		case CombinatorDescendant:
			{
				bool is_pseudo = false;
				Element* res = FindAncestor(*selector.left, apply_pseudo, &is_pseudo);
				if(!res)
				{
					return SelectNoMatch;
				} else
				{
					if(is_pseudo)
					{
						right_res |= SelectMatchPseudoClass;
					}
				}
			}
			break;
		case CombinatorChild:
			{
				int res = higher->Select(*selector.left, apply_pseudo);
				if(res == SelectNoMatch)
				{
					return SelectNoMatch;
				} else
				{
					if(right_res != SelectMatchPseudoClass)
					{
						right_res |= res;
					}
				}
			}
			break;
		case CombinatorAdjacentSibling:
			{
				bool is_pseudo = false;
				Element* res =  higher->FindAdjacentSibling(this, *selector.left, apply_pseudo, &is_pseudo);
				if(!res)
				{
					return SelectNoMatch;
				} else
				{
					if(is_pseudo)
					{
						right_res |= SelectMatchPseudoClass;
					}
				}
			}
			break;
		case CombinatorGeneralSibling:
			{
				bool is_pseudo = false;
				Element* res =  higher->FindSibling(this, *selector.left, apply_pseudo, &is_pseudo);
				if(!res)
				{
					return SelectNoMatch;
				} else
				{
					if(is_pseudo)
					{
						right_res |= SelectMatchPseudoClass;
					}
				}
			}
			break;
		default:
			right_res = SelectNoMatch;
		}
	}
	return right_res;
}

int HtmlTag::Select(const CssElementSelector& selector, bool apply_pseudo)
{
	//LOG("HtmlTag::Select " << selector.tag);
	if(!selector.tag.IsEmpty() && selector.tag != "*")
	{
		if(selector.tag != tag)
		{
			return SelectNoMatch;
		}
	}

	int res = SelectMatch;
	
	for(CssAttributeSelector::vector::ConstIterator i = selector.attrs.Begin(); i != selector.attrs.End(); i++)
	{
		String attr_value = GetAttr(i->attribute);
		switch(i->condition)
		{
		case SelectExists:
			if(!attr_value.GetCount())
			{
				return SelectNoMatch;
			}
			break;
		case SelectEqual:
			if (!attr_value.GetCount()) {
				return SelectNoMatch;
			}
			else {
				if(i->attribute == "class")
				{
					StringVector tokens1;
					SplitString(attr_value, tokens1, " ");
					StringVector tokens2;
					SplitString(i->val, tokens2, " ");
					bool found = true;
					for(StringVector::Iterator str1 = tokens2.Begin(); str1 != tokens2.End() && found; str1++)
					{
						bool f = false;
						for(StringVector::Iterator str2 = tokens1.Begin(); str2 != tokens1.End() && !f; str2++)
						{
							if( !CompareNoCase(*str1, *str2) )
							{
								f = true;
							}
						}
						if(!f)
						{
							found = false;
						}
					}
					if(!found)
					{
						return SelectNoMatch;
					}
				} else
				{
					if( CompareNoCase(i->val, attr_value) )
					{
						return SelectNoMatch;
					}
				}
			}
			break;
		case SelectContainStr:
			if(!attr_value.GetCount())
			{
				return SelectNoMatch;
			}
			else if(attr_value.Find(i->val) == -1)
			{
				return SelectNoMatch;
			}
			break;
		case SelectStartStr:
			if(!attr_value.GetCount())
			{
				return SelectNoMatch;
			} else if(attr_value.Compare(i->val))
			{
				return SelectNoMatch;
			}
			break;
		case SelectEndStr:
			if(!attr_value.GetCount())
			{
				return SelectNoMatch;
			}
			else if(attr_value.Compare(i->val))
			{
				String s = attr_value.Mid(attr_value.GetCount() - i->val.GetCount() - 1);
				if(s < attr_value)
				{
					return SelectNoMatch;
				}
				if(i->val != s)
				{
					return SelectNoMatch;
				}
			}
			break;
		case SelectPseudoElement:
			if(i->val == "after")
			{
				res |= SelectMatchWithAfter;
			} else if(i->val == "before")
			{
				res |= SelectMatchWithBefore;
			} else
			{
				return SelectNoMatch;
			}
			break;
		case SelectPseudoClass:
			if(apply_pseudo)
			{
				Element* higher = GetParentElement();
				
				if(!higher) return SelectNoMatch;

				String selector_param;
				String	selector_name;

				int begin	= FindFirstOf(i->val, '(');
				int end		= (begin == -1) ? -1 : FindCloseBracket(i->val, begin);
				if(begin != -1 && end != -1)
				{
					selector_param = i->val.Mid(begin + 1, end - begin - 1);
				}
				if(begin != -1)
				{
					selector_name = i->val.Mid(0, begin);
					Trim(selector_name);
				} else
				{
					selector_name = i->val;
				}

				int selector = ValueIndex(selector_name, PseudoClassStrings);
				
				switch(selector)
				{
				case PseudoClassOnlyChild:
					if( !higher->IsOnlyChild(this, false) )
					{
						return SelectNoMatch;
					}
					break;
				case PseudoClassOnlyOfType:
					if( !higher->IsOnlyChild(this, true) )
					{
						return SelectNoMatch;
					}
					break;
				case PseudoClassFirstChild:
					if( !higher->IsNthChild(this, 0, 1, false) )
					{
						return SelectNoMatch;
					}
					break;
				case PseudoClassFirstOfType:
					if( !higher->IsNthChild(this, 0, 1, true) )
					{
						return SelectNoMatch;
					}
					break;
				case PseudoClassLastChild:
					if( !higher->IsNthLastChild(this, 0, 1, false) )
					{
						return SelectNoMatch;
					}
					break;
				case PseudoClassLastOfType:
					if( !higher->IsNthLastChild(this, 0, 1, true) )
					{
						return SelectNoMatch;
					}
					break;
				case PseudoClassNthChild:
				case PseudoClassNthOfType:
				case PseudoClassNthLastChild:
				case PseudoClassNthLastOfType:
					{
						if(selector_param.IsEmpty()) return SelectNoMatch;

						int num = 0;
						int off = 0;

						ParseNthChildParams(selector_param, num, off);
						if(!num && !off) return SelectNoMatch;
						switch(selector)
						{
						case PseudoClassNthChild:
							if( !higher->IsNthChild(this, num, off, false) )
							{
								return SelectNoMatch;
							}
							break;
						case PseudoClassNthOfType:
							if( !higher->IsNthChild(this, num, off, true) )
							{
								return SelectNoMatch;
							}
							break;
						case PseudoClassNthLastChild:
							if( !higher->IsNthLastChild(this, num, off, false) )
							{
								return SelectNoMatch;
							}
							break;
						case PseudoClassNthLastOfType:
							if( !higher->IsNthLastChild(this, num, off, true) )
							{
								return SelectNoMatch;
							}
							break;
						}

					}
					break;
				case PseudoClassNot:
					{
						CssElementSelector sel;
						sel.Parse(selector_param);
						if(Select(sel, apply_pseudo))
						{
							return SelectNoMatch;
						}
					}
					break;
				default:
					if(UPP::Find(pseudo_classes.Begin(), pseudo_classes.End(), i->val, StdEqual<String>() ) == pseudo_classes.End())
					{
						return SelectNoMatch;
					}
					break;
				}
			} else
			{
				res |= SelectMatchPseudoClass;
			}
			break;
		}
	}
	return res;
}

Element* HtmlTag::FindAncestor( const CssSelector& selector, bool apply_pseudo, bool* is_pseudo )
{
	Element* higher = GetParentElement();
	if(!higher)
	{
		return 0;
	}
	int res = higher->Select(selector, apply_pseudo);
	if(res != SelectNoMatch)
	{
		if(is_pseudo)
		{
			if(res & SelectMatchPseudoClass)
			{
				*is_pseudo = true;
			} else
			{
				*is_pseudo = false;
			}
		}
		return higher;
	}
	if (higher == this)
		return 0;
	return higher->FindAncestor(selector, apply_pseudo, is_pseudo);
}

int HtmlTag::GetFloatsHeight(ElementFloat el_float) const
{
	if(IsFloatsHolder())
	{
		int h = 0;

		bool process = false;

		for(FloatedBox::vector::ConstIterator i = floats_left.Begin(); i != floats_left.End(); i++)
		{
			process = false;
			switch(el_float)
			{
			case FloatNone:
				process = true;
				break;
			case FloatLeft:
				if(i->clear_floats == ClearLeft || i->clear_floats == ClearBoth)
				{
					process = true;
				}
				break;
			case FloatRight:
				if(i->clear_floats == ClearRight || i->clear_floats == ClearBoth)
				{
					process = true;
				}
				break;
			}
			if(process)
			{
				if(el_float == FloatNone)
				{
					h = max(h, i->pos.Bottom());
				} else
				{
					h = max(h, i->pos.Top());
				}
			}
		}


		for(FloatedBox::vector::ConstIterator i = floats_right.Begin(); i != floats_right.End(); i++)
		{
			process = false;
			switch(el_float)
			{
			case FloatNone:
				process = true;
				break;
			case FloatLeft:
				if(i->clear_floats == ClearLeft || i->clear_floats == ClearBoth)
				{
					process = true;
				}
				break;
			case FloatRight:
				if(i->clear_floats == ClearRight || i->clear_floats == ClearBoth)
				{
					process = true;
				}
				break;
			}
			if(process)
			{
				if(el_float == FloatNone)
				{
					h = max(h, i->pos.Bottom());
				} else
				{
					h = max(h, i->pos.Top());
				}
			}
		}

		return h;
	}
	int h = GetParentElement()->GetFloatsHeight(el_float);
	return h - pos.y;
}

int HtmlTag::GetLeftFloatsHeight() const
{
	if(IsFloatsHolder())
	{
		int h = 0;
		if(!floats_left.IsEmpty())
		{
			for(FloatedBox::vector::ConstIterator el = floats_left.Begin(); el != floats_left.End(); el++)
			{
				h = max(h, el->pos.Bottom());
			}
		}
		return h;
	}
	int h = GetParentElement()->GetLeftFloatsHeight();
	return h - pos.y;
}

int HtmlTag::GetRightGloatsHeight() const
{
	if(IsFloatsHolder())
	{
		int h = 0;
		if(!floats_right.IsEmpty())
		{
			for(FloatedBox::vector::ConstIterator el = floats_right.Begin(); el != floats_right.End(); el++)
			{
				h = max(h, el->pos.Bottom());
			}
		}
		return h;
	}
	int h = GetParentElement()->GetRightGloatsHeight();
	return h - pos.y;
}

int HtmlTag::GetLineLeft( int y )
{
	if(IsFloatsHolder())
	{
		if(cahe_line_left.is_valid && cahe_line_left.hash == y)
		{
			return cahe_line_left.val;
		}

		int w = 0;
		for(FloatedBox::vector::Iterator el = floats_left.Begin(); el != floats_left.End(); el++)
		{
			if(y >= el->pos.Top() && y < el->pos.Bottom())
			{
				w = max(w, el->pos.Right());
				if(w < el->pos.Right())
				{
					break;
				}
			}
		}
		cahe_line_left.SetValue(y, w);
		return w;
	}
	int w = GetParentElement()->GetLineLeft(y + pos.y);
	if(w < 0)
	{
		w = 0;
	}
	return w - (w ? pos.x : 0);
}

int HtmlTag::GetLineRight( int y, int def_right )
{
	if(IsFloatsHolder())
	{
		if(cahe_line_right.is_valid && cahe_line_right.hash == y)
		{
			if(cahe_line_right.is_default)
			{
				return def_right;
			} else
			{
				return min(cahe_line_right.val, def_right);
			}
		}

		int w = def_right;
		cahe_line_right.is_default = true;
		for(FloatedBox::vector::Iterator el = floats_right.Begin(); el != floats_right.End(); el++)
		{
			if(y >= el->pos.Top() && y < el->pos.Bottom())
			{
				w = min(w, el->pos.Left());
				cahe_line_right.is_default = false;
				if(w > el->pos.Left())
				{
					break;
				}
			}
		}
		cahe_line_right.SetValue(y, w);
		return w;
	}
	int w = GetParentElement()->GetLineRight(y + pos.y, def_right + pos.x);
	return w - pos.x;
}


void HtmlTag::GetLineLeftRight( int y, int def_right, int& ln_left, int& ln_right )
{
	if(IsFloatsHolder())
	{
		ln_left		= GetLineLeft(y);
		ln_right	= GetLineRight(y, def_right);
	} else
	{
		GetParentElement()->GetLineLeftRight(y + pos.y, def_right + pos.x, ln_left, ln_right);
		ln_right -= pos.x;

		if(ln_left < 0)
		{
			ln_left = 0;
		} else if(ln_left)
		{
			ln_left -= pos.x;
		}
	}
}

int HtmlTag::FixLineWidth( int max_width, ElementFloat flt )
{
	int ret_width = 0;
	if(!boxes.IsEmpty())
	{
		ElementsVector els;
		LAST(boxes)->GetElements(els);
		bool was_cleared = false;
		if(!els.IsEmpty() && els[0]->GetClear() != ClearNone)
		{
			if(els[0]->GetClear() == ClearBoth)
			{
				was_cleared = true;
			} else
			{
				if(	(flt == FloatLeft	&& els[0]->GetClear() == ClearLeft) ||
					(flt == FloatRight	&& els[0]->GetClear() == ClearRight) )
				{
					was_cleared = true;
				}
			}
		}

		if(!was_cleared)
		{
			REMOVELAST(boxes);

			for(ElementsVector::Iterator i = els.Begin(); i != els.End(); i++)
			{
				int rw = PlaceElement((*i), max_width);
				if(rw > ret_width)
				{
					ret_width = rw;
				}
			}
		} else
		{
			int line_top = 0;
			if(LAST(boxes)->GetType() == BOX_LINE)
			{
				line_top = LAST(boxes)->Top();
			} else
			{
				line_top = LAST(boxes)->Bottom();
			}

			int line_left	= 0;
			int line_right	= max_width;
			GetLineLeftRight(line_top, max_width, line_left, line_right);

			if(LAST(boxes)->GetType() == BOX_LINE)
			{
				if(boxes.GetCount() == 1 && list_style_type != ListStyleTypeNone && list_style_position == ListStylepositionInside)
				{
					int sz_font = GetFontSize();
					line_left += sz_font;
				}

				if(css_text_indent.GetValue() != 0)
				{
					bool LineBox_found = false;
					for(Vector<One<Box> >::Iterator iter = boxes.Begin(); iter != boxes.End(); iter++)
					{
						if((*iter)->GetType() == BOX_LINE)
						{
							LineBox_found = true;
							break;
						}
					}
					if(!LineBox_found)
					{
						line_left += css_text_indent.CalcPercent(max_width);
					}
				}

			}

			ElementsVector els;
			LAST(boxes)->NewWidth(line_left, line_right, els);
			for(ElementsVector::Iterator i = els.Begin(); i != els.End(); i++)
			{
				int rw = PlaceElement((*i), max_width);
				if(rw > ret_width)
				{
					ret_width = rw;
				}
			}
		}
	}

	return ret_width;
}

void HtmlTag::AddFloat( Element* el, int x, int y )
{
	if(IsFloatsHolder())
	{
		FloatedBox fb;
		fb.pos.x		= el->Left() + x;
		fb.pos.y		= el->Top()  + y;
		fb.pos.width	= el->Width();
		fb.pos.height	= el->Height();
		fb.float_side	= el->GetFloat();
		fb.clear_floats	= el->GetClear();
		fb.el			= el;

		if(fb.float_side == FloatLeft)
		{
			if(floats_left.IsEmpty())
			{
				floats_left.Add(fb);
			} else
			{
				bool inserted = false;
				for (int i = 0; i < floats_left.GetCount(); i++)
				{
					FloatedBox& ifb = floats_left[i];
					if(fb.pos.Right() > ifb.pos.Right())
					{
						floats_left.Insert(i, fb);
						inserted = true;
						break;
					}
				}
				if(!inserted)
				{
					floats_left.Add(fb);
				}
			}
			cahe_line_left.invalidate();
		} else if(fb.float_side == FloatRight)
		{
			if(floats_right.IsEmpty())
			{
				floats_right.Add(fb);
			} else
			{
				bool inserted = false;
				for (int i = 0; i < floats_right.GetCount(); i++)
				{
					FloatedBox& ifb = floats_right[i];
					if(fb.pos.Left() < ifb.pos.Left())
					{
						floats_right.Insert(i, fb);
						inserted = true;
						break;
					}
				}
				if(!inserted)
				{
					floats_right.Add(fb);
				}
			}
			cahe_line_right.invalidate();
		}
	} else
	{
		GetParentElement()->AddFloat(el, x + pos.x, y + pos.y);
	}
}

int HtmlTag::FindNextLineTop( int top, int width, int def_right )
{
	if(IsFloatsHolder())
	{
		int new_top = top;
		IntVector points;

		for(FloatedBox::vector::Iterator el = floats_left.Begin(); el != floats_left.End(); el++)
		{
			if(el->pos.Top() >= top)
			{
				if(UPP::Find(points.Begin(), points.End(), el->pos.Top(), StdEqual<int>()) == points.End())
				{
					points.Add(el->pos.Top());
				}
			}
			if(el->pos.Bottom() >= top)
			{
				if(UPP::Find(points.Begin(), points.End(), el->pos.Bottom(), StdEqual<int>()) == points.End())
				{
					points.Add(el->pos.Bottom());
				}
			}
		}

		for(FloatedBox::vector::Iterator el = floats_right.Begin(); el != floats_right.End(); el++)
		{
			if(el->pos.Top() >= top)
			{
				if(UPP::Find(points.Begin(), points.End(), el->pos.Top(), StdEqual<int>()) == points.End())
				{
					points.Add(el->pos.Top());
				}
			}
			if(el->pos.Bottom() >= top)
			{
				if(UPP::Find(points.Begin(), points.End(), el->pos.Bottom(), StdEqual<int>()) == points.End())
				{
					points.Add(el->pos.Bottom());
				}
			}
		}

		if(!points.IsEmpty())
		{
			Sort(points, StdLess<int>() );
			new_top = LAST(points);

			for(IntVector::Iterator i = points.Begin(); i != points.End(); i++)
			{
				int pos_left	= 0;
				int pos_right	= def_right;
				GetLineLeftRight((*i), def_right, pos_left, pos_right);

				if(pos_right - pos_left >= width)
				{
					new_top = (*i);
					break;
				}
			}
		}
		return new_top;
	}
	int new_top = GetParentElement()->FindNextLineTop(top + pos.y, width, def_right + pos.x);
	return new_top - pos.y;
}

void HtmlTag::ParseBackground()
{
	// parse background-color
	bg.color		= GetColor("background-color", false, RGBAZero());
	
	
	// Late body background color change
	if (bg.color.a > 0 && CastPtr<ElBody>(this))
		GetDocument()->GetHtmlCtrl().SetBackgroundColor(bg.color);
	
	
	// parse background-position
	String str = GetStyleProperty("background-position", false, "0% 0%");

	if(str.GetCount())
	{
		StringVector res;
		SplitString(str, res, " \t");
		if(res.GetCount() > 0)
		{
			if(res.GetCount() == 1)
			{
				if( ValueInList(res[0], "left;right;center"))
				{
					bg.position.x.FromString(res[0], "left;right;center");
					bg.position.y.SetValue(50, CssUnitsPercentage);
				} else if( ValueInList(res[0], "top;bottom;center"))
				{
					bg.position.y.FromString(res[0], "top;bottom;center");
					bg.position.x.SetValue(50, CssUnitsPercentage);
				} else
				{
					bg.position.x.FromString(res[0], "left;right;center");
					bg.position.y.SetValue(50, CssUnitsPercentage);
				}
			} else
			{
				if(ValueInList(res[0], "left;right"))
				{
					bg.position.x.FromString(res[0], "left;right;center");
					bg.position.y.FromString(res[1], "top;bottom;center");
				} else if(ValueInList(res[0], "top;bottom"))
				{
					bg.position.x.FromString(res[1], "left;right;center");
					bg.position.y.FromString(res[0], "top;bottom;center");
				} else if(ValueInList(res[1], "left;right"))
				{
					bg.position.x.FromString(res[1], "left;right;center");
					bg.position.y.FromString(res[0], "top;bottom;center");
				}else if(ValueInList(res[1], "top;bottom"))
				{
					bg.position.x.FromString(res[0], "left;right;center");
					bg.position.y.FromString(res[1], "top;bottom;center");
				} else
				{
					bg.position.x.FromString(res[0], "left;right;center");
					bg.position.y.FromString(res[1], "top;bottom;center");
				}
			}

			if(bg.position.x.IsPredefined())
			{
				switch(bg.position.x.PreDefine())
				{
				case 0:
					bg.position.x.SetValue(0, CssUnitsPercentage);
					break;
				case 1:
					bg.position.x.SetValue(100, CssUnitsPercentage);
					break;
				case 2:
					bg.position.x.SetValue(50, CssUnitsPercentage);
					break;
				}
			}
			if(bg.position.y.IsPredefined())
			{
				switch(bg.position.y.PreDefine())
				{
				case 0:
					bg.position.y.SetValue(0, CssUnitsPercentage);
					break;
				case 1:
					bg.position.y.SetValue(100, CssUnitsPercentage);
					break;
				case 2:
					bg.position.y.SetValue(50, CssUnitsPercentage);
					break;
				}
			}
		} else
		{
			bg.position.x.SetValue(0, CssUnitsPercentage);
			bg.position.y.SetValue(0, CssUnitsPercentage);
		}
	} else
	{
		bg.position.y.SetValue(0, CssUnitsPercentage);
		bg.position.x.SetValue(0, CssUnitsPercentage);
	}

	str = GetStyleProperty("background-size", false, "auto");

	if(str.GetCount())
	{
		StringVector res;
		SplitString(str, res, " \t");
		if(!res.IsEmpty())
		{
			bg.position.width.FromString(res[0], BackgroundSizeStrings);
			if(res.GetCount() > 1)
			{
				bg.position.height.FromString(res[1], BackgroundSizeStrings);
			} else
			{
				bg.position.height.PreDefine(BackgroundSizeAuto);
			}
		} else
		{
			bg.position.width.PreDefine(BackgroundSizeAuto);
			bg.position.height.PreDefine(BackgroundSizeAuto);
		}
	}

	Document* doc = GetDocument();
	doc->CvtUnits(bg.position.x,			font_size);
	doc->CvtUnits(bg.position.y,			font_size);
	doc->CvtUnits(bg.position.width,		font_size);
	doc->CvtUnits(bg.position.height,	font_size);

	// parse BackgroundAttachment
	bg.attachment = (BackgroundAttachment) ValueIndex(
		GetStyleProperty("background-attachment", false, "scroll"),
		BackgroundAttachmentStrings,
		BackgroundAttachmentScroll);

	// parse BackgroundAttachment
	bg.repeat = (BackgroundRepeat) ValueIndex(
		GetStyleProperty("background-repeat", false, "repeat"),
		BackgroundRepeatStrings,
		BackgroundRepeatRepeat);

	// parse background_clip
	bg.clip = (BackgroundBox) ValueIndex(
		GetStyleProperty("background-clip", false, "border-box"),
		BackgroundBoxStrings,
		BackgroundBoxBorder);

	// parse background_origin
	bg.origin = (BackgroundBox) ValueIndex(
		GetStyleProperty("background-origin", false, "padding-box"),
		BackgroundBoxStrings,
		BackgroundBoxContent);

	// parse background-image
	Css::ParseCssUrl(GetStyleProperty("background-image", false, ""), bg.image);
	bg.baseurl = GetStyleProperty("background-image-baseurl", false, "");

	if(!bg.image.IsEmpty() && bg.cache_id == -1)
	{
		String base_url;
		if (bg.baseurl.GetCount())
			base_url = bg.baseurl;
		else
			base_url = GetDocument()->GetBaseUrl();
		
		doc->GetHtmlCtrl().LoadImage(bg.image, base_url, true);
		
		bg.cache_id = GetResourceCache().FindObject(bg.image, base_url);
	}
}

void HtmlTag::AddPositioned( Element* el )
{
	Element* higher = GetParentElement();
	
	if( el_position != ElementPositionStatic || (!higher) )
	{
		positioned.Add(el);
	} else
	{
		higher->AddPositioned(el);
	}
}

void HtmlTag::CalcOutlines( int higher_width )
{
	padding.left	= css_padding.left.CalcPercent(higher_width);
	padding.right	= css_padding.right.CalcPercent(higher_width);

	borders.left	= css_borders.left.width.CalcPercent(higher_width);
	borders.right	= css_borders.right.width.CalcPercent(higher_width);

	margins.left	= css_margins.left.CalcPercent(higher_width);
	margins.right	= css_margins.right.CalcPercent(higher_width);

	margins.top		= css_margins.top.CalcPercent(higher_width);
	margins.bottom	= css_margins.bottom.CalcPercent(higher_width);

	padding.top		= css_padding.top.CalcPercent(higher_width);
	padding.bottom	= css_padding.bottom.CalcPercent(higher_width);
}

void HtmlTag::CalcAutoMargins(int higher_width)
{
	if (GetElementPosition() != ElementPositionAbsolute && (display == DisplayBlock || display == DisplayTable))
	{
		if (css_margins.left.IsPredefined() && css_margins.right.IsPredefined())
		{
			int el_width = pos.width + borders.left + borders.right + padding.left + padding.right;
			if (el_width <= higher_width)
			{
				margins.left = (higher_width - el_width) / 2;
				margins.right = (higher_width - el_width) - margins.left;
			}
			else
			{
				margins.left = 0;
				margins.right = 0;
			}
		}
		else if (css_margins.left.IsPredefined() && !css_margins.right.IsPredefined())
		{
			int el_width = pos.width + borders.left + borders.right + padding.left + padding.right + margins.right;
			margins.left = higher_width - el_width;
			if (margins.left < 0) margins.left = 0;
		}
		else if (!css_margins.left.IsPredefined() && css_margins.right.IsPredefined())
		{
			int el_width = pos.width + borders.left + borders.right + padding.left + padding.right + margins.left;
			margins.right = higher_width - el_width;
			if (margins.right < 0) margins.right = 0;
		}
	}
}

void HtmlTag::ParseAttributes()
{
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if (el)
			el->ParseAttributes();
	}
}

void HtmlTag::GetText( WString& text )
{
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if (el)
			el->GetText(text);
	}
}

bool HtmlTag::IsBody()  const
{
	return false;
}

void HtmlTag::SetData( const WString& data )
{

}

void HtmlTag::GetInLineBoxes( Vector<Position>& boxes )
{
	Box* old_box = 0;
	Position pos;for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if(el && !el->Skip())
		{
			if(el->box)
			{
				if(el->box != old_box)
				{
					if(old_box)
					{
						if(boxes.IsEmpty())
						{
							pos.x		-= padding.left + borders.left;
							pos.width	+= padding.left + borders.left;
						}
						boxes.Add(pos);
					}
					old_box		= el->box;
					pos.x		= el->Left() + el->MarginLeft();
					pos.y		= el->Top() - padding.top - borders.top;
					pos.width	= 0;
					pos.height	= 0;
				}
				pos.width	= el->Right() - pos.x - el->MarginRight() - el->MarginLeft();
				pos.height	= max(pos.height, el->Height() + padding.top + padding.bottom + borders.top + borders.bottom);
			} else if(el->GetDisplay() == DisplayInline)
			{
				Vector<Position> sub_boxes;
				el->GetInLineBoxes(sub_boxes);
				if(!sub_boxes.IsEmpty())
				{
					//sub_boxes.rbegin()->width += el->MarginRight();
					sub_boxes[sub_boxes.GetCount()-1].width += el->MarginRight();
					if(boxes.IsEmpty())
					{
						if(padding.left + borders.left > 0)
						{
							Position padding_box = (*sub_boxes.Begin());
							padding_box.x		-= padding.left + borders.left + el->MarginLeft();
							padding_box.width	= padding.left + borders.left + el->MarginLeft();
							boxes.Add(padding_box);
						}
					}

					sub_boxes[sub_boxes.GetCount()-1].width += el->MarginRight();
					
					boxes.Append(sub_boxes);
				}
			}
		}
	}
	if(pos.width || pos.height)
	{
		if(boxes.IsEmpty())
		{
			pos.x		-= padding.left + borders.left;
			pos.width	+= padding.left + borders.left;
		}
		boxes.Add(pos);
	}
	if(!boxes.IsEmpty())
	{
		if(padding.right + borders.right > 0)
		{
			//Position padding_box = (*boxes.rbegin());
			Position padding_box = (boxes[boxes.GetCount()-1]);
			padding_box.x		+= padding_box.width;
			padding_box.width	= padding.right + borders.right;
			boxes.Add(padding_box);
		}
	}
}

bool HtmlTag::OnMouseOver()
{
	bool ret = false;

	Element* el = this;
	while(el)
	{
		if(el->SetPseudoClass("hover", true))
		{
			ret = true;
		}
		el = el->GetParentElement();
	}

	return ret;
}

bool HtmlTag::FindStylesChanges( Vector<Position>& redraw_boxes, int x, int y )
{
	if(display == DisplayInlineText)
	{
		return false;
	}

	bool ret = false;
	bool apply = false;
	for (Array<UsedSelector>::Iterator iter = used_styles.Begin(); iter != used_styles.End() && !apply; iter++)
	{
		if(iter->selector->IsMediaValid())
		{
			int res = Select(*(iter->selector), true);
			if( (res == SelectNoMatch && iter->used) || (res == SelectMatch && !iter->used) )
			{
				apply = true;
			}
		}
	}

	if(apply)
	{
		if(display == DisplayInline ||  display == DisplayTableRow)
		{
			Vector<Position> Boxes;
			GetInLineBoxes(Boxes);
			for(Vector<Position>::Iterator pos = Boxes.Begin(); pos != Boxes.End(); pos++)
			{
				pos->x	+= x;
				pos->y	+= y;
				redraw_boxes.Add(*pos);
			}
		} else
		{
			Position pos = this->pos;
			if(el_position != ElementPositionFixed)
			{
				pos.x += x;
				pos.y += y;
			}
			pos += padding;
			pos += borders;
			redraw_boxes.Add(pos);
		}

		ret = true;
		RefreshStyles();
		ParseStyles();
	}
	
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if (el && !el->Skip())
		{
			if(el_position != ElementPositionFixed)
			{
				if(el->FindStylesChanges(redraw_boxes, x + pos.x, y + pos.y))
				{
					ret = true;
				}
			} else
			{
				if(el->FindStylesChanges(redraw_boxes, pos.x, pos.y))
				{
					ret = true;
				}
			}
		}
	}
	return ret;
}

bool HtmlTag::OnMouseLeave()
{
	bool ret = false;

	Element* el = this;
	while(el)
	{
		if(el->SetPseudoClass("hover", false))
		{
			ret = true;
		}
		if(el->SetPseudoClass("active", false))
		{
			ret = true;
		}
		el = el->GetParentElement();
	}

	return ret;
}

bool HtmlTag::OnMouseLeftDown()
{
    bool ret = false;

    Element* el = this;
    while (el)
    {
        if (el->SetPseudoClass("active", true))
        {
            ret = true;
        }
        el = el->GetParentElement();
    }

    return ret;
}

bool HtmlTag::OnMouseLeftUp()
{
	bool ret = false;

    Element* el = this;
    while (el)
    {
        if (el->SetPseudoClass("active", false))
        {
            ret = true;
        }
        el = el->GetParentElement();
    }

    OnClick();

	return ret;
}

void HtmlTag::OnClick()
{
	if(GetParentElement())
	{
		GetParentElement()->OnClick();
	}
}

String HtmlTag::GetCursor()
{
	return GetStyleProperty("cursor", true, "");
}

static const int FontSize_table[8][7] =
{
	{ 9,    9,     9,     9,    11,    14,    18},
	{ 9,    9,     9,    10,    12,    15,    20},
	{ 9,    9,     9,    11,    13,    17,    22},
	{ 9,    9,    10,    12,    14,    18,    24},
	{ 9,    9,    10,    13,    16,    20,    26},
	{ 9,    9,    11,    14,    17,    21,    28},
	{ 9,   10,    12,    15,    17,    23,    30},
	{ 9,   10,    13,    16,    18,    24,    32}
};


void HtmlTag::InitFont()
{
	// Initialize font size
	String str = GetStyleProperty("font-size", false, "");

	int higher_sz = 0;
	Document* doc = GetDocument();
	Element* higher = GetParentElement();
	
	int doc_font_size = doc->GetHtmlCtrl().GetDefaultFontSize();
	if(higher)
	{
		higher_sz = higher->GetFontSize();
	} else
	{
		higher_sz = doc_font_size;
	}


	if(!str.GetCount())
	{
		font_size = higher_sz;
	} else
	{
		font_size = higher_sz;

		CssLength sz;
		sz.FromString(str, FontSizeStrings);
		if(sz.IsPredefined())
		{
			int idx_in_table = doc_font_size - 9;
			if(idx_in_table >= 0 && idx_in_table <= 7)
			{
				if(sz.PreDefine() >= FontSizeXXSmall && sz.PreDefine() <= FontSizeXXLarge)
				{
					font_size = FontSize_table[idx_in_table][sz.PreDefine()];
				} else
				{
					font_size = doc_font_size;
				}
			} else			
			{
				switch(sz.PreDefine())
				{
				case FontSizeXXSmall:
					font_size = doc_font_size * 3 / 5;
					break;
				case FontSizeXSmall:
					font_size = doc_font_size * 3 / 4;
					break;
				case FontSizeSmall:
					font_size = doc_font_size * 8 / 9;
					break;
				case FontSizeLarge:
					font_size = doc_font_size * 6 / 5;
					break;
				case FontSizeXLarge:
					font_size = doc_font_size * 3 / 2;
					break;
				case FontSizeXXLarge:
					font_size = doc_font_size * 2;
					break;
				default:
					font_size = doc_font_size;
					break;
				}
			}
		} else
		{
			if(sz.Units() == CssUnitsPercentage)
			{
				font_size = sz.CalcPercent(higher_sz);
			} else if(sz.Units() == CssUnitsNone)
			{
				font_size = higher_sz;
			} else
			{
				font_size = doc->CvtUnits(sz, higher_sz);
			}
		}
	}

	// Initialize font
	String name			= GetStyleProperty("font-family",		true,	"inherit");
	String weight		= GetStyleProperty("font-weight",		true,	"normal");
	String style		= GetStyleProperty("font-style",		true,	"normal");
	String decoration	= GetStyleProperty("text-decoration",	true,	"none");

	font = doc->GetFont(name, font_size, weight, style, decoration, &font_metrics);
	
	if (font > 1000){
		font = doc->GetFont(name, font_size, weight, style, decoration, &font_metrics);
		Panic("errorz here");
	}
}

bool HtmlTag::IsBreak() const
{
	return false;
}

void HtmlTag::SetTagName( const String& tag )
{
	this->tag.Clear();
	for(int i = 0; i < tag.GetCount(); i++) {
		this->tag.Cat( ToLower(tag[i]) );
	}
}

void HtmlTag::DrawBackground( Draw& hdc, int x, int y, const Position& clip )
{
	Position pos = this->pos;
	pos.x	+= x;
	pos.y	+= y;

	Position el_pos = pos;
	el_pos += padding;
	el_pos += borders;

	Document* doc = GetDocument();
	
	if(display != DisplayInline && display != DisplayTableRow)
	{
		if(el_pos.DoesIntersect(clip))
		{
			Background* bg = GetBackground();
			if(bg)
			{
				BackgroundPaint bg_paint;
				InitBackgroundPaint(pos, bg_paint, bg);

				doc->GetHtmlCtrl().DrawBackground(hdc, bg_paint);
			}
			Position border_box = pos;
			border_box += padding;
			border_box += borders;

			Borders bdr = css_borders;
			bdr.radius = css_borders.radius.CalcPercents(border_box.width, border_box.height);

			doc->GetHtmlCtrl().DrawBorders(hdc, bdr, border_box, GetParentElement() ? false : true);
		}
	} else
	{
		Background* bg = GetBackground();

		Vector<Position> Boxes;
		GetInLineBoxes(Boxes);

		BackgroundPaint bg_paint;
		Position content_box;

		for(Vector<Position>::Iterator Box = Boxes.Begin(); Box != Boxes.End(); Box++)
		{
			Box->x	+= x;
			Box->y	+= y;

			if(Box->DoesIntersect(clip))
			{
				content_box = *Box;
				content_box -= borders;
				content_box -= padding;

				if(bg)
				{
					InitBackgroundPaint(content_box, bg_paint, bg);
				}

				CssBorders bdr;

				// set left Borders radius for the first Box
				if(Box == Boxes.Begin())
				{
					bdr.radius.bottom_left_x	= css_borders.radius.bottom_left_x;
					bdr.radius.bottom_left_y	= css_borders.radius.bottom_left_y;
					bdr.radius.top_left_x		= css_borders.radius.top_left_x;
					bdr.radius.top_left_y		= css_borders.radius.top_left_y;
				}

				// set right Borders radius for the last Box
				if(Box == Boxes.End() -1)
				{
					bdr.radius.bottom_right_x	= css_borders.radius.bottom_right_x;
					bdr.radius.bottom_right_y	= css_borders.radius.bottom_right_y;
					bdr.radius.top_right_x		= css_borders.radius.top_right_x;
					bdr.radius.top_right_y		= css_borders.radius.top_right_y;
				}

				
				bdr.top		= css_borders.top;
				bdr.bottom	= css_borders.bottom;
				if(Box == Boxes.Begin())
				{
					bdr.left	= css_borders.left;
				}
				if(Box == Boxes.End()-1)
				{
					bdr.right	= css_borders.right;
				}


				if(bg)
				{
					bg_paint.border_radius = bdr.radius.CalcPercents(bg_paint.border_box.width, bg_paint.border_box.width);
					doc->GetHtmlCtrl().DrawBackground(hdc, bg_paint);
				}
				Borders b = bdr;
				b.radius = bdr.radius.CalcPercents(Box->width, Box->height);
				doc->GetHtmlCtrl().DrawBorders(hdc, b, *Box, false);
			}
		}
	}
}

int HtmlTag::RenderInline( Element* container, int max_width )
{
	int ret_width = 0;
	int rw = 0;
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = Object::At(i).As<Element>();
		if (el) {
			rw = container->PlaceElement( el, max_width );
			if(rw > ret_width)
			{
				ret_width = rw;
			}
		}
	}
	return ret_width;
}

int HtmlTag::PlaceElement( Element* el, int max_width )
{
	if(el->GetDisplay() == DisplayNone) return 0;

	if(el->GetDisplay() == DisplayInline)
	{
		return el->RenderInline(this, max_width);
	}

	ElementPosition el_position = el->GetElementPosition();

	if(el_position == ElementPositionAbsolute || el_position == ElementPositionFixed)
	{
		int line_top = 0;
		if(!boxes.IsEmpty())
		{
			if(LAST(boxes)->GetType() == BOX_LINE)
			{
				line_top = LAST(boxes)->Top();
				if(!LAST(boxes)->IsEmpty())
				{
					line_top += LineHeight();
				}
			} else
			{
				line_top = LAST(boxes)->Bottom();
			}
		}

		el->Render(0, line_top, max_width);
		el->pos.x	+= el->ContentMarginsLeft();
		el->pos.y	+= el->ContentMarginsTop();

		return 0;
	}

	int ret_width = 0;

	switch(el->GetFloat())
	{
	case FloatLeft:
		{
			int line_top = 0;
			if(!boxes.IsEmpty())
			{
				if(LAST(boxes)->GetType() == BOX_LINE)
				{
					line_top = LAST(boxes)->Top();
				} else
				{
					line_top = LAST(boxes)->Bottom();
				}
			}
			line_top		= GetClearedTop(el, line_top);
			int line_left	= 0;
			int line_right	= max_width;
			GetLineLeftRight(line_top, max_width, line_left, line_right);

			el->Render(line_left, line_top, line_right);
			if(el->Right() > line_right)
			{
				int new_top = FindNextLineTop(el->Top(), el->Width(), max_width);
				el->pos.x = GetLineLeft(new_top) + el->ContentMarginsLeft();
				el->pos.y = new_top + el->ContentMarginsTop();
			}
			AddFloat(el, 0, 0);
			ret_width = FixLineWidth(max_width, FloatLeft);
			if(!ret_width)
			{
				ret_width = el->Right();
			}
		}
		break;
	case FloatRight:
		{
			int line_top = 0;
			if(!boxes.IsEmpty())
			{
				if(LAST(boxes)->GetType() == BOX_LINE)
				{
					line_top = LAST(boxes)->Top();
				} else
				{
					line_top = LAST(boxes)->Bottom();
				}
			}
			line_top		= GetClearedTop(el, line_top);
			int line_left	= 0;
			int line_right	= max_width;
			GetLineLeftRight(line_top, max_width, line_left, line_right);

			el->Render(0, line_top, line_right);

			if(line_left + el->Width() > line_right)
			{
				int new_top = FindNextLineTop(el->Top(), el->Width(), max_width);
				el->pos.x = GetLineRight(new_top, max_width) - el->Width() + el->ContentMarginsLeft();
				el->pos.y = new_top + el->ContentMarginsTop();
			} else
			{
				el->pos.x = line_right - el->Width() + el->ContentMarginsLeft();
			}
			AddFloat(el, 0, 0);
			ret_width = FixLineWidth(max_width, FloatRight);

			if(!ret_width)
			{
				line_left	= 0;
				line_right	= max_width;
				GetLineLeftRight(line_top, max_width, line_left, line_right);

				ret_width = ret_width + (max_width - line_right);
			}
		}
		break;
	default:
		{
			int line_top = 0;
			if(!boxes.IsEmpty())
			{
				line_top = LAST(boxes)->Top();
			}
			int line_left	= 0;
			int line_right	= max_width;
			GetLineLeftRight(line_top, max_width, line_left, line_right);

			switch(el->GetDisplay())
			{
			case DisplayInlineBlock:
				ret_width = el->Render(line_left, line_top, line_right);
				break;
			case DisplayBlock:		
				if(el->IsReplaced() || el->IsFloatsHolder())
				{
					el->pos.width		= el->GetCssWidth().CalcPercent(line_right - line_left);
					el->pos.height		= el->GetCssHeight().CalcPercent(el->GetParentElement() ?  el->GetParentElement()->pos.height : 0);
				}
				el->CalcOutlines(line_right - line_left);
				break;
			case DisplayInlineText:
				{
					UPP::Size sz;
					el->GetContentSize(sz, line_right);
					el->pos = sz;
				}
				break;
			default:
				ret_width = 0;
				break;
			}

			bool add_box = true;
			if(!boxes.IsEmpty())
			{
				if(LAST(boxes)->CanHold(el, white_space))
				{
					add_box = false;
				}
			}
			if(add_box)
			{
				line_top = NewBox(el, max_width);
			} else if(!boxes.IsEmpty())
			{
				line_top = LAST(boxes)->Top();
			}

			line_left	= 0;
			line_right	= max_width;
			GetLineLeftRight(line_top, max_width, line_left, line_right);

			if(!el->IsInLineBox())
			{
				if(boxes.GetCount() == 1)
				{
					if(CollapseTopMargin())
					{
						int shift = el->MarginTop();
						if(shift >= 0)
						{
							line_top -=shift;
							LAST(boxes)->SetYShift(-shift);
						}
					}
				} else
				{
					int shift = 0;
					int prev_margin = boxes[boxes.GetCount() - 2]->BottomMargin();

					if(prev_margin > el->MarginTop())
					{
						shift = el->MarginTop();
					} else
					{
						shift = prev_margin;
					}
					if(shift >= 0)
					{
						line_top -= shift;
						LAST(boxes)->SetYShift(-shift);
					}
				}
			}

			switch(el->GetDisplay())
			{
			case DisplayTable:
			case DisplayListItem:
				ret_width = el->Render(line_left, line_top, line_right - line_left);
				break;
			case DisplayBlock:
			case DisplayTableCell:
			case DisplayTableCaption:
			case DisplayTableRow:
				if(el->IsReplaced() || el->IsFloatsHolder())
				{
					ret_width = el->Render(line_left, line_top, line_right - line_left) + line_left + (max_width - line_right);
				} else
				{
					ret_width = el->Render(0, line_top, max_width);
				}
				break;
			default:
				ret_width = 0;
				break;
			}

			LAST(boxes)->AddElement(el);

			if(el->IsInLineBox() && !el->Skip())
			{
				ret_width = el->Right() + (max_width - line_right);
			}
		}
		break;
	}

	return ret_width;
}

bool HtmlTag::SetPseudoClass( const String& pclass, bool add )
{
	bool ret = false;
	if(add)
	{
		if(UPP::Find(pseudo_classes.Begin(), pseudo_classes.End(), pclass, StdEqual<String>()) == pseudo_classes.End())
		{
			pseudo_classes.Add(pclass);
			ret = true;
		}
	} else
	{
		int pi = -1;
		for(int i = 0; i < pseudo_classes.GetCount(); i++) {
			if (pseudo_classes[i] == pclass)
				pi = i;
		}
		if(pi != -1)
		{
			pseudo_classes.Remove(pi);
			ret = true;
		}
	}
	return ret;
}

int HtmlTag::LineHeight() const
{
	return line_height;
}

bool HtmlTag::IsReplaced() const
{
	return false;
}

int HtmlTag::FinishLastBox(bool end_of_render)
{
	int line_top = 0;

	if(!boxes.IsEmpty())
	{
		LAST(boxes)->Finish(end_of_render);

		if(LAST(boxes)->IsEmpty())
		{
			line_top = LAST(boxes)->Top();
			REMOVELAST(boxes);
		}

		if(!boxes.IsEmpty())
		{
			line_top = LAST(boxes)->Bottom();
		}
	}
	return line_top;
}

int HtmlTag::NewBox( Element* el, int max_width )
{
	int line_top	= GetClearedTop(el, FinishLastBox());

	int line_left	= 0;
	int line_right	= max_width;
	GetLineLeftRight(line_top, max_width, line_left, line_right);

	if(el->IsInLineBox() || el->IsFloatsHolder())
	{
		if(el->Width() > line_right - line_left)
		{
			line_top	= FindNextLineTop(line_top, el->Width(), max_width);
			line_left	= 0;
			line_right	= max_width;
			GetLineLeftRight(line_top, max_width, line_left, line_right);
		}
	}

	int first_line_margin = 0;
	if(boxes.IsEmpty() && list_style_type != ListStyleTypeNone && list_style_position == ListStylepositionInside)
	{
		int sz_font = GetFontSize();
		first_line_margin = sz_font;
	}

	if(el->IsInLineBox())
	{
		int text_indent = 0;
		if(css_text_indent.GetValue() != 0)
		{
			bool LineBox_found = false;
			for(Vector<One<Box> >::Iterator iter = boxes.Begin(); iter != boxes.End(); iter++)
			{
				if((*iter)->GetType() == BOX_LINE)
				{
					LineBox_found = true;
					break;
				}
			}
			if(!LineBox_found)
			{
				text_indent = css_text_indent.CalcPercent(max_width);
			}
		}

		FontMetrics fm;
		GetFont(&fm);
		LineBox* lb = new LineBox(line_top, line_left + first_line_margin + text_indent, line_right, LineHeight(), fm, text_align);
		boxes.Add() = lb;
	} else
	{
		BlockBox* bb = new BlockBox(line_top, line_left, line_right);
		boxes.Add() = bb;
	}

	return line_top;
}

int HtmlTag::GetClearedTop( Element* el, int line_top )
{
	switch(el->GetClear())
	{
	case ClearLeft:
		{
			int fh = GetLeftFloatsHeight();
			if(fh && fh > line_top)
			{
				line_top = fh;
			}
		}
		break;
	case ClearRight:
		{
			int fh = GetRightGloatsHeight();
			if(fh && fh > line_top)
			{
				line_top = fh;
			}
		}
		break;
	case ClearBoth:
		{
			int fh = GetFloatsHeight();
			if(fh && fh > line_top)
			{
				line_top = fh;
			}
		}
		break;
	default:
		if(el->GetFloat() != FloatNone)
		{
			int fh = GetFloatsHeight(el->GetFloat());
			if(fh && fh > line_top)
			{
				line_top = fh;
			}
		}
		break;
	}
	return line_top;
}

StyleDisplay HtmlTag::GetDisplay() const
{
	return display;
}

ElementFloat HtmlTag::GetFloat() const
{
	return float_;
}

bool HtmlTag::IsFloatsHolder() const
{
	if(	display == DisplayInlineBlock ||
		display == DisplayTableCell ||
		!GetParentElement() ||
		IsBody() ||
		float_ != FloatNone ||
		el_position == ElementPositionAbsolute ||
		el_position == ElementPositionFixed ||
		overflow > OverflowVisible)
	{
		return true;
	}
	return false;
}

bool HtmlTag::IsFirstChildInline( const Element* el )
{
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* e = Object::At(i).As<Element>();
		if (e) {
			if(!e->IsWhiteSpace())
			{
				if(el == e)
				{
					return true;
				}
				if(e->GetDisplay() == DisplayInline)
				{
					if(e->HaveInlineChild())
					{
						return false;
					}
				} else
				{
					return false;
				}
			}
		}
	}
	return false;
}

bool HtmlTag::IsLastChildInline( const Element* el )
{
	for(int i = Object::GetCount()-1; i >= 0; i--) {
		Element* e = Object::At(i).As<Element>();
		if (e) {
			if(!e->IsWhiteSpace())
			{
				if(el == e)
				{
					return true;
				}
				if(e->GetDisplay() == DisplayInline)
				{
					if(e->HaveInlineChild())
					{
						return false;
					}
				} else
				{
					return false;
				}
			}
		}
	}
	return false;
}

WhiteSpace HtmlTag::GetWhiteSpace() const
{
	return white_space;
}

VerticalAlign HtmlTag::GetVerticalAlign() const
{
	return vertical_align;
}

CssLength HtmlTag::GetCssLeft() const
{
	return css_offsets.left;
}

CssLength HtmlTag::GetCssRight() const
{
	return css_offsets.right;
}

CssLength HtmlTag::GetCssTop() const
{
	return css_offsets.top;
}

CssLength HtmlTag::GetCssBottom() const
{
	return css_offsets.bottom;
}


CssOffsets HtmlTag::GetCssOffsets() const
{
	return css_offsets;
}

ElementClear HtmlTag::GetClear() const
{
	return clear;
}

CssLength HtmlTag::GetCssWidth() const
{
	return css_width;
}

CssLength HtmlTag::GetCssHeight() const
{
	return css_height;
}

size_t HtmlTag::GetChildrenCount() const
{
	return Object::GetCount();
}

Element* HtmlTag::GetChild( int idx )
{
	return At(idx).As<Element>();
}

void HtmlTag::SetCssWidth( CssLength& w )
{
	css_width = w;
}

void HtmlTag::ApplyVerticalAlign()
{
	if(!boxes.IsEmpty())
	{
		int add = 0;
		int content_height	= LAST(boxes)->Bottom();

		if(pos.height > content_height)
		{
			switch(vertical_align)
			{
			case VAMiddle:
				add = (pos.height - content_height) / 2;
				break;
			case VABottom:
				add = pos.height - content_height;
				break;
			default:
				add = 0;
				break;
			}
		}

		if(add)
		{
			for(size_t i = 0; i < boxes.GetCount(); i++)
			{
				boxes[i]->SetYShift(add);
			}
		}
	}
}

ElementPosition HtmlTag::GetElementPosition(CssOffsets* offsets) const
{
	if(offsets && el_position != ElementPositionStatic)
	{
		*offsets = css_offsets;
	}
	return el_position;
}

void HtmlTag::InitBackgroundPaint( Position pos, BackgroundPaint &bg_paint, Background* bg )
{
	if(!bg) return;

	bg_paint = *bg;
	Position content_box	= pos;
	Position padding_box	= pos;
	padding_box += padding;
	Position border_box		= padding_box;
	border_box += borders;

	switch(bg->clip)
	{
	case BackgroundBoxPadding:
		bg_paint.clip_box = padding_box;
		break;
	case BackgroundBoxContent:
		bg_paint.clip_box = content_box;
		break;
	default:
		bg_paint.clip_box = border_box;
		break;
	}

	switch(bg->origin)
	{
	case BackgroundBoxBorder:
		bg_paint.origin_box = border_box;
		break;
	case BackgroundBoxContent:
		bg_paint.origin_box = content_box;
		break;
	default:
		bg_paint.origin_box = padding_box;
		break;
	}

	if(!bg_paint.image.IsEmpty())
	{
		GetDocument()->GetHtmlCtrl().GetImageSize(bg_paint.image, bg_paint.baseurl, bg_paint.image_size);
		
		if(bg_paint.image_size.cx && bg_paint.image_size.cy)
		{
			UPP::Size img_new_sz = bg_paint.image_size;
			double img_ar_width		= (double) bg_paint.image_size.cx / (double) bg_paint.image_size.cy;
			double img_ar_height	= (double) bg_paint.image_size.cy / (double) bg_paint.image_size.cx;


			if(bg->position.width.IsPredefined())
			{
				switch(bg->position.width.PreDefine())
				{
				case BackgroundSizeContain:
					if( (int) ((double) bg_paint.origin_box.width * img_ar_height) <= bg_paint.origin_box.height )
					{
						img_new_sz.cx = bg_paint.origin_box.width;
						img_new_sz.cy	= (int) ((double) bg_paint.origin_box.width * img_ar_height);
					} else
					{
						img_new_sz.cy = bg_paint.origin_box.height;
						img_new_sz.cx	= (int) ((double) bg_paint.origin_box.height * img_ar_width);
					}
					break;
				case BackgroundSizeCover:
					if( (int) ((double) bg_paint.origin_box.width * img_ar_height) >= bg_paint.origin_box.height )
					{
						img_new_sz.cx = bg_paint.origin_box.width;
						img_new_sz.cy	= (int) ((double) bg_paint.origin_box.width * img_ar_height);
					} else
					{
						img_new_sz.cy = bg_paint.origin_box.height;
						img_new_sz.cx	= (int) ((double) bg_paint.origin_box.height * img_ar_width);
					}
					break;
					break;
				case BackgroundSizeAuto:
					if(!bg->position.height.IsPredefined())
					{
						img_new_sz.cy	= bg->position.height.CalcPercent(bg_paint.origin_box.height);
						img_new_sz.cx	= (int) ((double) img_new_sz.cy * img_ar_width);
					}
					break;
				}
			} else
			{
				img_new_sz.cx = bg->position.width.CalcPercent(bg_paint.origin_box.width);
				if(bg->position.height.IsPredefined())
				{
					img_new_sz.cy = (int) ((double) img_new_sz.cx * img_ar_height);
				} else
				{
					img_new_sz.cy = bg->position.height.CalcPercent(bg_paint.origin_box.height);
				}
			}

			bg_paint.image_size = img_new_sz;
			bg_paint.position_x = bg_paint.origin_box.x + (int) bg->position.x.CalcPercent(bg_paint.origin_box.width - bg_paint.image_size.cx);
			bg_paint.position_y = bg_paint.origin_box.y + (int) bg->position.y.CalcPercent(bg_paint.origin_box.height - bg_paint.image_size.cy);
		}

	}
	bg_paint.border_radius	= css_borders.radius.CalcPercents(border_box.width, border_box.height);;
	bg_paint.border_box		= border_box;
	bg_paint.is_root		= GetParentElement() ? false : true;
}

Visibility HtmlTag::GetVisibility() const
{
	return visibility;
}

void HtmlTag::DrawListMarker( Draw& hdc, const Position &pos )
{
	ListMarker lm;

	String list_image = GetStyleProperty("list-style-image", true, "");
	Size img_size(0,0);
	//if(list_image)
	if(list_image.GetCount())
	{
		Css::ParseCssUrl(list_image, lm.image);
		lm.baseurl = GetStyleProperty("list-style-image-baseurl", true, "");
		GetDocument()->GetHtmlCtrl().GetImageSize(lm.image, lm.baseurl, img_size);
	} else
	{
		lm.baseurl.Clear();
	}

	int ln_height	= LineHeight();
	int sz_font		= GetFontSize();
	lm.pos.x		= pos.x;
	lm.pos.width	= sz_font	- sz_font * 2 / 3;
	lm.pos.height	= sz_font	- sz_font * 2 / 3;
	lm.pos.y		= pos.y		+ ln_height / 2 - lm.pos.height / 2;

	if(img_size.cx && img_size.cy)
	{
		if(lm.pos.y + img_size.cy > pos.y + pos.height)
		{
			lm.pos.y = pos.y + pos.height - img_size.cy;
		}
		if(img_size.cx > lm.pos.width)
		{
			lm.pos.x -= img_size.cx - lm.pos.width;
		}

		lm.pos.width	= img_size.cx;
		lm.pos.height	= img_size.cy;
	}
	if(list_style_position == ListStylepositionOutside)
	{
		lm.pos.x -= sz_font;
	}
	if (list_style_type == ListStyleTypeDecimal) {
		Element* el = GetParent()->As<Element>();
		if (el) {
			lm.list_id = GetParent()->FindPos(this) + 1;
			lm.font = GetParentElement()->GetFont();
		}
	}

	lm.color = GetColor("color", true, Black());
	lm.marker_type = list_style_type;
	GetDocument()->GetHtmlCtrl().DrawListMarker(hdc, lm);
}

void HtmlTag::DrawChildren( Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex )
{
	if (display == DisplayTable || display == DisplayInlineTable)
	{
		DrawChildrenTable(hdc, x, y, clip, flag, zindex);
	}
	else
	{
		DrawChildrenBox(hdc, x, y, clip, flag, zindex);
	}
}

bool HtmlTag::FetchPositioned()
{
	bool ret = false;

	positioned.Clear();

	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = Object::At(i).As<Element>();
		if (!el) continue;
		
		if(el->GetElementPosition() != ElementPositionStatic)
		{
			AddPositioned(el);
		}
		if(!ret && (el->GetElementPosition() == ElementPositionAbsolute || el->GetElementPosition() == ElementPositionFixed))
		{
			ret = true;
		}
		if(el->FetchPositioned())
		{
			ret = true;
		}
	}
	return ret;
}

int HtmlTag::GetZIndex() const
{
	return z_index;
}

void HtmlTag::RenderPositioned(RenderType rt)
{
	Position wnd_position;
	GetDocument()->GetHtmlCtrl().GetClientRect(wnd_position);

	ElementPosition el_position;
	Element* el;
	bool process;
	for(ElementsVector::Iterator abs_el = positioned.Begin(); abs_el != positioned.End(); abs_el++)
	{
		el = (*abs_el);
		el_position = el->GetElementPosition();

		process = false;
		if(el->GetDisplay() != DisplayNone)
		{
			if(el_position == ElementPositionAbsolute)
			{
				if(rt != RenderFixedOnly)
				{
					process = true;
				}
			} else if(el_position == ElementPositionFixed)
			{
				if(rt != RenderNoFixed)
				{
					process = true;
				}
			}
		}

		if(process)
		{
			int higher_height	= 0;
			int higher_width	= 0;
			int client_x		= 0;
			int client_y		= 0;
			if(el_position == ElementPositionFixed)
			{
				higher_height	= wnd_position.height;
				higher_width	= wnd_position.width;
				client_x		= wnd_position.Left();
				client_y		= wnd_position.Top();
			} else
			{
				if(el->GetParentElement())
				{
					higher_height	= el->GetParentElement()->Height();
					higher_width	= el->GetParentElement()->Width();
				}
			}

			CssLength	css_left	= el->GetCssLeft();
			CssLength	css_right	= el->GetCssRight();
			CssLength	css_top		= el->GetCssTop();
			CssLength	css_bottom	= el->GetCssBottom();

			bool need_render = false;

			CssLength el_w = el->GetCssWidth();
			CssLength el_h = el->GetCssHeight();

            int new_width = -1;
            int new_height = -1;
			if(el_w.Units() == CssUnitsPercentage && higher_width)
			{
                new_width = el_w.CalcPercent(higher_width);
                if(el->pos.width != new_width)
				{
					need_render = true;
                    el->pos.width = new_width;
				}
			}

			if(el_h.Units() == CssUnitsPercentage && higher_height)
			{
                new_height = el_h.CalcPercent(higher_height);
                if(el->pos.height != new_height)
				{
					need_render = true;
                    el->pos.height = new_height;
				}
			}

			bool cvt_x = false;
			bool cvt_y = false;

			if(el_position == ElementPositionFixed)
			{
				if(!css_left.IsPredefined() || !css_right.IsPredefined())
				{
					if(!css_left.IsPredefined() && css_right.IsPredefined())
					{
						el->pos.x = css_left.CalcPercent(higher_width) + el->ContentMarginsLeft();
					} else if(css_left.IsPredefined() && !css_right.IsPredefined())
					{
						el->pos.x = higher_width - css_right.CalcPercent(higher_width) - el->pos.width - el->ContentMarginsRight();
					} else
					{
						el->pos.x		= css_left.CalcPercent(higher_width) + el->ContentMarginsLeft();
						el->pos.width	= higher_width - css_left.CalcPercent(higher_width) - css_right.CalcPercent(higher_width) - (el->ContentMarginsLeft() + el->ContentMarginsRight());
						need_render = true;
					}
				}

				if(!css_top.IsPredefined() || !css_bottom.IsPredefined())
				{
					if(!css_top.IsPredefined() && css_bottom.IsPredefined())
					{
						el->pos.y = css_top.CalcPercent(higher_height) + el->ContentMarginsTop();
					} else if(css_top.IsPredefined() && !css_bottom.IsPredefined())
					{
						el->pos.y = higher_height - css_bottom.CalcPercent(higher_height) - el->pos.height - el->ContentMarginsBottom();
					} else
					{
						el->pos.y			= css_top.CalcPercent(higher_height) + el->ContentMarginsTop();
						el->pos.height	= higher_height - css_top.CalcPercent(higher_height) - css_bottom.CalcPercent(higher_height) - (el->ContentMarginsTop() + el->ContentMarginsBottom());
						need_render = true;
					}
				}
			} else 
			{
				if(!css_left.IsPredefined() || !css_right.IsPredefined())
				{
					if(!css_left.IsPredefined() && css_right.IsPredefined())
					{
						el->pos.x = css_left.CalcPercent(higher_width) + el->ContentMarginsLeft() - padding.left;
					} else if(css_left.IsPredefined() && !css_right.IsPredefined())
					{
						el->pos.x = pos.width + padding.right - css_right.CalcPercent(higher_width) - el->pos.width - el->ContentMarginsRight();
					} else
					{
						el->pos.x		= css_left.CalcPercent(higher_width) + el->ContentMarginsLeft() - padding.left;
						el->pos.width	= pos.width + padding.left + padding.right - css_left.CalcPercent(higher_width) - css_right.CalcPercent(higher_width) - (el->ContentMarginsLeft() + el->ContentMarginsRight());
                        if (new_width != -1)
                        {
                            el->pos.x += (el->pos.width - new_width) / 2;
                            el->pos.width = new_width;
                        }
                        need_render = true;
					}
					cvt_x = true;
				}

				if(!css_top.IsPredefined() || !css_bottom.IsPredefined())
				{
					if(!css_top.IsPredefined() && css_bottom.IsPredefined())
					{
						el->pos.y = css_top.CalcPercent(higher_height) + el->ContentMarginsTop() - padding.top;
					} else if(css_top.IsPredefined() && !css_bottom.IsPredefined())
					{
						el->pos.y = pos.height + padding.bottom - css_bottom.CalcPercent(higher_height) - el->pos.height - el->ContentMarginsBottom();
					} else
					{
						el->pos.y			= css_top.CalcPercent(higher_height) + el->ContentMarginsTop() - padding.top;
						el->pos.height	= pos.height + padding.top + padding.bottom - css_top.CalcPercent(higher_height) - css_bottom.CalcPercent(higher_height) - (el->ContentMarginsTop() + el->ContentMarginsBottom());
                        if (new_height != -1)
                        {
                            el->pos.y += (el->pos.height - new_height) / 2;
                            el->pos.height = new_height;
                        }
                        need_render = true;
					}
					cvt_y = true;
				}
			}

			if(cvt_x || cvt_y)
			{
				int offset_x = 0;
				int offset_y = 0;
				Element* cur_el = el->GetParentElement();
				while(cur_el && cur_el != this)
				{
					offset_x += cur_el->pos.x;
					offset_y += cur_el->pos.y;
					cur_el = cur_el->GetParentElement();
				}
				if(cvt_x)	el->pos.x -= offset_x;
				if(cvt_y)	el->pos.y -= offset_y;
			}

			if(need_render)
			{
				Position pos = el->pos;
				el->Render(el->Left(), el->Top(), el->Width(), true);
				el->pos = pos;
			}

			if(el_position == ElementPositionFixed)
			{
				Position fixed_pos;
				el->GetRedrawBox(fixed_pos);
				GetDocument()->AddFixedBox(fixed_pos);
			}
		}

		el->RenderPositioned();
	}

	if(!positioned.IsEmpty())
	{
		Sort(positioned, ElementZIndexSort());
	}
}

void HtmlTag::DrawStackingContext( Draw& hdc, int x, int y, const Position& clip, bool with_positioned )
{
	if(!IsVisible()) return;

	ArrayMap<int, bool> zindexes;
	if(with_positioned)
	{
		for(ElementsVector::Iterator i = positioned.Begin(); i != positioned.End(); i++)
		{
			zindexes.GetAdd((*i)->GetZIndex()) = false;
		}

		for (int i = 0; i < zindexes.GetCount(); i++)
		{
			int j = zindexes.GetKey(i);
			if(j < 0)
			{
				//DrawChildren(hdc, x, y, clip, DrawPositioned, idx->first);
				DrawChildren(hdc, x, y, clip, DrawPositioned, j);
			}
		}
	}
	DrawChildren(hdc, x, y, clip, DrawBlock, 0);
	DrawChildren(hdc, x, y, clip, DrawFloats, 0);
	DrawChildren(hdc, x, y, clip, DrawInlines, 0);
	if(with_positioned)
	{
		for (int i = 0; i < zindexes.GetCount(); i++)
		{
			int j = zindexes.GetKey(i);
			if(j == 0)
			{
				DrawChildren(hdc, x, y, clip, DrawPositioned, j);
			}
		}

		for (int i = 0; i < zindexes.GetCount(); i++)
		{
			int j = zindexes.GetKey(i);
			if(j > 0)
			{
				DrawChildren(hdc, x, y, clip, DrawPositioned, j);
			}
		}
	}
}

Overflow HtmlTag::GetOverflow() const
{
	return overflow;
}

bool HtmlTag::IsNthChild( Element* el, int num, int off, bool of_type )
{
	int idx = 1;
	for (int i = 0; i < Object::GetCount(); i++) {
		Element* e = At(i).As<Element>();
		
		if(e && e->GetDisplay() != DisplayInlineText)
		{
			if( (!of_type) || (of_type && !el->GetTagName().Compare(e->GetTagName())) )
			{
				if(el == e)
				{
					if(num != 0)
					{
						if((idx - off) >= 0 && (idx - off) % num == 0)
						{
							return true;
						}

					} else if(idx == off)
					{
						return true;
					}
					return false;
				}
				idx++;
			}
			if(el == e) break;
		}
	}
	return false;
}

bool HtmlTag::IsNthLastChild( Element* el, int num, int off, bool of_type )
{
	int idx = 1;
	for (int i = Object::GetCount()-1; i >= 0; i--) {
		Element* child = At(i).As<Element>();
		
		if(child->GetDisplay() != DisplayInlineText)
		{
			if( !of_type || (of_type && !el->GetTagName().Compare(child->GetTagName())) )
			{
				if(el == child)
				{
					if(num != 0)
					{
						if((idx - off) >= 0 && (idx - off) % num == 0)
						{
							return true;
						}

					} else if(idx == off)
					{
						return true;
					}
					return false;
				}
				idx++;
			}
			if(el == child) break;
		}
	}
	return false;
}

void HtmlTag::ParseNthChildParams( String param, int &num, int &off )
{
	if(param == "odd")
	{
		num = 2;
		off = 1;
	} else if(param == "even")
	{
		num = 2;
		off = 0;
	} else
	{
		StringVector tokens;
		SplitString(param, tokens, " n", "n");

		String s_num;
		String s_off;

		String s_int;
		for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
		{
			if((*tok) == "n")
			{
				s_num = s_int;
				s_int.Clear();
			} else
			{
				s_int += (*tok);
			}
		}
		s_off = s_int;

		num = StrInt(s_num);
		off = StrInt(s_off);
	}
}

void HtmlTag::CalcDocumentSize( UPP::Size& sz, int x /*= 0*/, int y /*= 0*/ )
{
	if(IsVisible() && el_position != ElementPositionFixed)
	{
		Element::CalcDocumentSize(sz, x, y);

		if(overflow == OverflowVisible)
		{
			for (int i = 0; i < Object::GetCount(); i++) {
				Element* el = At(i).As<Element>();
				if (el)
					el->CalcDocumentSize(sz, x + pos.x, y + pos.y);
			}
		}

		// root element (<html>) must to cover entire window
		if(!GetParentElement())
		{
			Position client_pos;
			GetDocument()->GetHtmlCtrl().GetClientRect(client_pos);
			pos.height = max(sz.cy, client_pos.height) - ContentMarginsTop() - ContentMarginsBottom();
			pos.width	 = max(sz.cx, client_pos.width) - ContentMarginsLeft() - ContentMarginsRight();
		}
	}
}


void HtmlTag::GetRedrawBox(Position& pos, int x /*= 0*/, int y /*= 0*/)
{
	if(IsVisible())
	{
		Element::GetRedrawBox(pos, x, y);

		if(overflow == OverflowVisible)
		{
			for (int i = 0; i < Object::GetCount(); i++) {
				Element* el = At(i).As<Element>();
				if(el && el->GetElementPosition() != ElementPositionFixed)
				{
					el->GetRedrawBox(pos, x + pos.x, y + pos.y);
				}
			}
		}
	}
}

Element* HtmlTag::FindAdjacentSibling( Element* el, const CssSelector& Selector, bool apply_pseudo /*= true*/, bool* is_pseudo /*= 0*/ )
{
	Element* ret = 0;
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* e = At(i).As<Element>();
		if(e->GetDisplay() != DisplayInlineText)
		{
			if(e == el)
			{
				if(ret)
				{
					int res = ret->Select(Selector, apply_pseudo);
					if(res != SelectNoMatch)
					{
						if(is_pseudo)
						{
							if(res & SelectMatchPseudoClass)
							{
								*is_pseudo = true;
							} else
							{
								*is_pseudo = false;
							}
						}
						return ret;
					}
				}
				return 0;
			} else
			{
				ret = e;
			}
		}
	}
	return 0;
}

Element* HtmlTag::FindSibling( Element* el, const CssSelector& Selector, bool apply_pseudo /*= true*/, bool* is_pseudo /*= 0*/ )
{
	Element* ret = 0;
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* e = At(i).As<Element>();
		if(e->GetDisplay() != DisplayInlineText)
		{
			if(e == el)
			{
				return ret;
			} else if(!ret)
			{
				int res = e->Select(Selector, apply_pseudo);
				if(res != SelectNoMatch)
				{
					if(is_pseudo)
					{
						if(res & SelectMatchPseudoClass)
						{
							*is_pseudo = true;
						} else
						{
							*is_pseudo = false;
						}
					}
					ret = e;
				}
			}
		}
	}
	return 0;
}

bool HtmlTag::IsOnlyChild( Element* el, bool of_type )
{
	int child_count = 0;
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* child = At(i).As<Element>();
		if(child->GetDisplay() != DisplayInlineText)
		{
			if( !of_type || (of_type && !el->GetTagName().Compare(child->GetTagName())) )
			{
				child_count++;
			}
			if(child_count > 1) break;
		}
	}
	if(child_count > 1)
	{
		return false;
	}
	return true;
}

void HtmlTag::UpdateFloats( int dy, Element* higher )
{
	if(IsFloatsHolder())
	{
		bool reset_cache = false;
		for (int i = floats_left.GetCount() - 1; i >= 0; i--)
		{
			FloatedBox& fb = floats_left[i];
			if(fb.el->IsAncestor(higher))
			{
				reset_cache	= true;
				fb.pos.y	+= dy;
			}
		}
		if(reset_cache)
		{
			cahe_line_left.invalidate();
		}
		reset_cache = false;
		for (int i = floats_right.GetCount() - 1; i >= 0; i--) {
			FloatedBox& fb = floats_right[i];
			if(fb.el->IsAncestor(higher))
			{
				reset_cache	= true;
				//fb->pos.y	+= dy;
				fb.pos.y	+= dy;
			}
		}
		if(reset_cache)
		{
			cahe_line_right.invalidate();
		}
	} else
	{
		GetParentElement()->UpdateFloats(dy, higher);
	}
}

void HtmlTag::RemoveBeforeAfter()
{
	if(Object::GetCount())
	{
		Element* el = Find<Element>();
		if(el && !el->GetTagName().Compare("::before") )
		{
			Object::Remove(el);
		}
	}
	if(Object::GetCount())
	{
		Element* el = ReverseFind<Element>();
		if(el && !el->GetTagName().Compare("::after") )
		{
			Object::Remove(el);
		}
	}
}

Element* HtmlTag::GetElementBefore()
{
	Element* el = Find<Element>();
	if(el)
	{
		if( !el->GetTagName().Compare("::before") )
		{
			return el;
		}
	}
	el = new ElBefore();
	el->MoveTo(*this);
	return el;
}

Element* HtmlTag::GetElementAfter()
{
	Element* el = ReverseFind<Element>();
	if(el)
	{
		if( !el->GetTagName().Compare("::after") )
		{
			return el;
		}
	}
	el = new ElAfter();
	el->MoveTo(*this);
	return el;
}

void HtmlTag::AddStyle( Style* st )
{
	style.Combine(*st);
}

bool HtmlTag::HaveInlineChild()
{
	if(Object::GetCount())
	{
		for(int i = 0; i < Object::GetCount(); i++) {
			Element* el = At(i).As<Element>();
			if(el && !el->IsWhiteSpace())
				return true;
		}
	}
	return false;
}

void HtmlTag::RefreshStyles()
{
	RemoveBeforeAfter();

	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if(el && el->GetDisplay() != DisplayInlineText)
			el->RefreshStyles();
	}

	style.Clear();

	for(Array<UsedSelector>::Iterator sel = used_styles.Begin(); sel != used_styles.End(); sel++)
	{
		UsedSelector* usel = &*sel;
		usel->used = false;

		if(usel->selector->IsMediaValid())
		{
			int apply = Select(*usel->selector, false);

			if(apply != SelectNoMatch)
			{
				if(apply & SelectMatchPseudoClass)
				{
					if(Select(*usel->selector, true))
					{
						AddStyle(usel->selector->style);
						usel->used = true;
					}
				} else if(apply & SelectMatchWithAfter)
				{
					Element* el = GetElementAfter();
					if(el)
					{
						el->AddStyle(usel->selector->style);
					}
				} else if(apply & SelectMatchWithBefore)
				{
					Element* el = GetElementBefore();
					if(el)
					{
						el->AddStyle(usel->selector->style);
					}
				} else
				{
					AddStyle(usel->selector->style);
					usel->used = true;
				}
			}
		}
	}
}

Element* HtmlTag::GetChildByPoint(int x, int y, int client_x, int client_y, DrawFlag flag, int zindex)
{
	Element* ret = 0;

	if(overflow > OverflowVisible)
	{
		if(!pos.IsPointInside(x, y))
		{
			return ret;
		}
	}

	Position pos = this->pos;
	pos.x	= x - pos.x;
	pos.y	= y - pos.y;

	for (int i = Object::GetCount() - 1; i >= 0; i--)
	{
		Element* el = At(i).As<Element>();
		Element* iter = el;

		if(el && el->IsVisible() && el->GetDisplay() != DisplayInlineText)
		{
			switch(flag)
			{
			case DrawPositioned:
				if(el->IsPositioned() && el->GetZIndex() == zindex)
				{
					if(el->GetElementPosition() == ElementPositionFixed)
					{
						ret = el->GetElementByPoint(client_x, client_y, client_x, client_y);
						if(!ret && iter->IsPointInside(client_x, client_y))
						{
							ret = iter;
						}
					} else
					{
						ret = el->GetElementByPoint(pos.x, pos.y, client_x, client_y);
						if(!ret && iter->IsPointInside(pos.x, pos.y))
						{
							ret = iter;
						}
					}
					el = 0;
				}
				break;
			case DrawBlock:
				if(!el->IsInLineBox() && el->GetFloat() == FloatNone && !el->IsPositioned())
				{
					if(el->IsPointInside(pos.x, pos.y))
					{
						ret = el;
					}
				}
				break;
			case DrawFloats:
				if(el->GetFloat() != FloatNone && !el->IsPositioned())
				{
					ret = el->GetElementByPoint(pos.x, pos.y, client_x, client_y);

					if(!ret && iter->IsPointInside(pos.x, pos.y))
					{
						ret = iter;
					}
					el = 0;
				}
				break;
			case DrawInlines:
				if(el->IsInLineBox() && el->GetFloat() == FloatNone && !el->IsPositioned())
				{
					if(el->GetDisplay() == DisplayInlineBlock)
					{
						ret = el->GetElementByPoint(pos.x, pos.y, client_x, client_y);
						el = 0;
					}
					if(!ret && iter->IsPointInside(pos.x, pos.y))
					{
						ret = iter;
					}
				}
				break;
			default:
				break;
			}

			if(el && !el->IsPositioned())
			{
				if(flag == DrawPositioned)
				{
					Element* child = el->GetChildByPoint(pos.x, pos.y, client_x, client_y, flag, zindex);
					if(child)
					{
						ret = child;
					}
				} else
				{
					if(	el->GetFloat() == FloatNone &&
						el->GetDisplay() != DisplayInlineBlock)
					{
						Element* child = el->GetChildByPoint(pos.x, pos.y, client_x, client_y, flag, zindex);
						if(child)
						{
							ret = child;
						}
					}
				}
			}
		}
	}

	return ret;
}

Element* HtmlTag::GetElementByPoint( int x, int y, int client_x, int client_y )
{
	if(!IsVisible()) return 0;

	Element* ret = 0;

	ArrayMap<int, bool> zindexes;

	for(ElementsVector::Iterator i = positioned.Begin(); i != positioned.End(); i++)
	{
		zindexes[(*i)->GetZIndex()];
	}

	for (int i = 0; i < zindexes.GetCount(); i++)
	{
		int j = zindexes.GetKey(i);
		if (j > 0)
		{
			ret = GetChildByPoint(x, y, client_x, client_y, DrawPositioned, j);
		}
	}
	if(ret) return ret;

	for (int i = 0; i < zindexes.GetCount(); i++)
	{
		int j = zindexes.GetKey(i);
		if (j > 0)
		{
			ret = GetChildByPoint(x, y, client_x, client_y, DrawPositioned, j);
		}
	}
	if(ret) return ret;

	ret = GetChildByPoint(x, y, client_x, client_y, DrawInlines, 0);
	if(ret) return ret;

	ret = GetChildByPoint(x, y, client_x, client_y, DrawFloats, 0);
	if(ret) return ret;

	ret = GetChildByPoint(x, y, client_x, client_y, DrawBlock, 0);
	if(ret) return ret;


	for (int i = 0; i < zindexes.GetCount() && !ret; i++)
	{
		int j = zindexes.GetKey(i);
		if (j < 0)
		{
			ret = GetChildByPoint(x, y, client_x, client_y, DrawPositioned, j);
		}
	}
	if(ret) return ret;

	if(el_position == ElementPositionFixed)
	{
		if(IsPointInside(client_x, client_y))
		{
			ret = this;
		}
	} else
	{
		if(IsPointInside(x, y))
		{
			ret = this;
		}
	}

	return ret;
}

Background* HtmlTag::GetBackground(bool own_only)
{
	if(own_only)
	{
		// return own background with check for empty one
		if(bg.image.IsEmpty() && !bg.color.a)
		{
			return 0;
		}
		return &bg;
	}

	if(bg.image.IsEmpty() && !bg.color.a)
	{
		// if this is root element (<html>) try to get background from body
		if(!GetParentElement())
		{
			for (int i = 0; i < Object::GetCount(); i++) {
				Element* el = At(i).As<Element>();
				if(el && el->IsBody() )
				{
					// return own body background
					return el->GetBackground(true);
				}
			}
		}
		return 0;
	}
	
	if(IsBody())
	{
		if(!GetParentElement()->GetBackground(true))
		{
			// higher of body will draw background for body
			return 0;
		}
	}
	
	if(bg.cache_id == -1 && !bg.image.IsEmpty()) {
		String base_url;
		if (bg.baseurl.GetCount())
			base_url = bg.baseurl;
		else
			base_url = GetDocument()->GetBaseUrl();
		
		bg.cache_id = GetResourceCache().FindObject(bg.image, base_url);
	}

	return &bg;
}

int HtmlTag::RenderBox(int x, int y, int max_width, bool second_pass /*= false*/)
{
	int higher_width = max_width;
	Element* higher = GetParentElement();
	
	CalcOutlines(higher_width);

	pos.Clear();
	pos.MoveTo(x, y);

	pos.x += ContentMarginsLeft();
	pos.y += ContentMarginsTop();

	int ret_width = 0;

	DefValue<int>	block_width(0);

	if (display != DisplayTableCell && !css_width.IsPredefined())
	{
		int w = CalcWidth(higher_width);
		if (box_sizing == BoxSizingBorderBox)
		{
			w -= padding.left + borders.left + padding.right + borders.right;
		}
		ret_width = max_width = block_width = w;
	}
	else
	{
		if (max_width)
		{
			max_width -= ContentMarginsLeft() + ContentMarginsRight();
		}
	}

	// check for max-width
	if (!css_max_width.IsPredefined())
	{
		int mw = GetDocument()->CvtUnits(css_max_width, font_size, higher_width);
		if (box_sizing == BoxSizingBorderBox)
		{
			mw -= padding.left + borders.left + padding.right + borders.right;
		}
		if (max_width > mw)
		{
			max_width = mw;
		}
	}

	floats_left.Clear();
	floats_right.Clear();
	boxes.Clear();
	cahe_line_left.invalidate();
	cahe_line_right.invalidate();

	Element* el;
	ElementPosition el_position;

	int block_height = 0;

	pos.height = 0;

	if (GetPredefinedHeight(block_height))
	{
		pos.height = block_height;
	}

	for (int i = 0; i < Object::GetCount(); i++) {
		el = At(i).As<Element>();
		if (el) {
			el_position = el->GetElementPosition();
			if ((el_position == ElementPositionAbsolute || el_position == ElementPositionFixed) && second_pass) continue;
	
			int rw = PlaceElement(el, max_width);
			if (rw > ret_width)
			{
				ret_width = rw;
			}
		}
	}

	FinishLastBox(true);

	if (block_width.IsDefault() && IsInLineBox())
	{
		pos.width = ret_width;
	}
	else
	{
		pos.width = max_width;
	}
	CalcAutoMargins(higher_width);

	if (!boxes.IsEmpty())
	{
		if (CollapseTopMargin())
		{
			int old_top = margins.top;
			margins.top = max(boxes[0]->TopMargin(), margins.top);
			if (margins.top != old_top)
			{
				UpdateFloats(margins.top - old_top, this);
			}
		}
		if (CollapseBottomMargin())
		{
			margins.bottom = max(LAST(boxes)->BottomMargin(), margins.bottom);
			pos.height = LAST(boxes)->Bottom() - LAST(boxes)->BottomMargin();
		}
		else
		{
			pos.height = LAST(boxes)->Bottom();
		}
	}

	// add the floats height to the block height
	if (IsFloatsHolder())
	{
		int floats_height = GetFloatsHeight();
		if (floats_height > pos.height)
		{
			pos.height = floats_height;
		}
	}

	// calculate the final Position

	pos.MoveTo(x, y);
	pos.x += ContentMarginsLeft();
	pos.y += ContentMarginsTop();

	if (GetPredefinedHeight(block_height))
	{
		pos.height = block_height;
	}

	int min_height = 0;
	if (!css_min_height.IsPredefined() && css_min_height.Units() == CssUnitsPercentage)
	{
		if (higher)
		{
			if (higher->GetPredefinedHeight(block_height))
			{
				min_height = css_min_height.CalcPercent(block_height);
			}
		}
	}
	else
	{
		min_height = (int)css_min_height.GetValue();
	}
	if (min_height != 0 && box_sizing == BoxSizingBorderBox)
	{
		min_height -= padding.top + borders.top + padding.bottom + borders.bottom;
		if (min_height < 0) min_height = 0;
	}

	if (display == DisplayListItem)
	{
		String list_image = GetStyleProperty("list-style-image", true, "");
		//if (list_image)
		if (list_image.GetCount())
		{
			String url;
			Css::ParseCssUrl(list_image, url);

			Size sz;
			String list_image_baseurl = GetStyleProperty("list-style-image-baseurl", true, "");
			GetDocument()->GetHtmlCtrl().GetImageSize(url, list_image_baseurl, sz);
			if (min_height < sz.cy)
			{
				min_height = sz.cy;
			}
		}

	}

	if (min_height > pos.height)
	{
		pos.height = min_height;
	}

	int min_width = css_min_width.CalcPercent(higher_width);

	if (min_width != 0 && box_sizing == BoxSizingBorderBox)
	{
		min_width -= padding.left + borders.left + padding.right + borders.right;
		if (min_width < 0) min_width = 0;
	}

	if (min_width != 0)
	{
		if (min_width > pos.width)
		{
			pos.width = min_width;
		}
		if (min_width > ret_width)
		{
			ret_width = min_width;
		}
	}

	ret_width += ContentMarginsLeft() + ContentMarginsRight();

	// re-render with new width
	if (ret_width < max_width && !second_pass && higher)
	{
		if (display == DisplayInlineBlock ||
			css_width.IsPredefined() &&
			(float_ != FloatNone ||
			display == DisplayTable ||
			el_position == ElementPositionAbsolute ||
			el_position == ElementPositionFixed
			)
			)
		{
			Render(x, y, ret_width, true);
			pos.width = ret_width - (ContentMarginsLeft() + ContentMarginsRight());
		}
	}

	return ret_width;
}

int HtmlTag::RenderTable(int x, int y, int max_width, bool second_pass /*= false*/)
{
	int higher_width = max_width;
	Element* higher = GetParentElement();
	
	CalcOutlines(higher_width);

	pos.Clear();
	pos.MoveTo(x, y);

	pos.x += ContentMarginsLeft();
	pos.y += ContentMarginsTop();

	DefValue<int>	block_width(0);

	if (!css_width.IsPredefined())
	{
		max_width = block_width = CalcWidth(higher_width - (ContentMarginsLeft() + ContentMarginsRight()));
	}
	else
	{
		if (max_width)
		{
			max_width -= ContentMarginsLeft() + ContentMarginsRight();
		}
	}

	// Calculate table spacing
	int table_width_spacing = 0;
	if (borderCollapse == BorderCollapseSeparate)
	{
		table_width_spacing = border_spacing_x * (grid.GetColsCount() + 1);
	}
	else
	{
		table_width_spacing = 0;

		if (grid.GetColsCount())
		{
			table_width_spacing -= min(BorderLeft(), grid.Column(0).border_left);
			table_width_spacing -= min(BorderRight(), grid.Column(grid.GetColsCount() - 1).border_right);
		}

		for (int col = 1; col < grid.GetColsCount(); col++)
		{
			table_width_spacing -= min(grid.Column(col).border_left, grid.Column(col - 1).border_right);
		}
	}


	// Calculate the minimum content width (MCW) of each cell: the formatted content may span any number of lines but may not Overflow the cell Box. 
	// If the specified 'width' (W) of the cell is greater than MCW, W is the minimum cell width. A value of 'auto' means that MCW is the minimum 
	// cell width.
	// 
	// Also, calculate the "maximum" cell width of each cell: formatting the content without breaking lines other than where explicit line breaks occur.

	if (grid.GetColsCount() == 1 && !block_width.IsDefault())
	{
		for (int row = 0; row < grid.GetRowsCount(); row++)
		{
			TableCell* cell = grid.Cell(0, row);
			if (cell && cell->el)
			{
				cell->min_width = cell->max_width = cell->el->Render(0, 0, max_width - table_width_spacing);
				cell->el->pos.width = cell->min_width - cell->el->ContentMarginsLeft() - cell->el->ContentMarginsRight();
			}
		}
	}
	else
	{
		for (int row = 0; row < grid.GetRowsCount(); row++)
		{
			for (int col = 0; col < grid.GetColsCount(); col++)
			{
				TableCell* cell = grid.Cell(col, row);
				if (cell && cell->el)
				{
					if (!grid.Column(col).css_width.IsPredefined() && grid.Column(col).css_width.Units() != CssUnitsPercentage)
					{
						int css_w = grid.Column(col).css_width.CalcPercent(block_width);
						int el_w = cell->el->Render(0, 0, css_w);
						cell->min_width = cell->max_width = max(css_w, el_w);
						cell->el->pos.width = cell->min_width - cell->el->ContentMarginsLeft() - cell->el->ContentMarginsRight();
					}
					else
					{
						// calculate minimum content width
						cell->min_width = cell->el->Render(0, 0, 1);
						// calculate maximum content width
						cell->max_width = cell->el->Render(0, 0, max_width - table_width_spacing);
					}
				}
			}
		}
	}

	// For each column, determine a maximum and minimum column width from the cells that span only that column. 
	// The minimum is that required by the cell with the largest minimum cell width (or the column 'width', whichever is larger). 
	// The maximum is that required by the cell with the largest maximum cell width (or the column 'width', whichever is larger).

	for (int col = 0; col < grid.GetColsCount(); col++)
	{
		grid.Column(col).max_width = 0;
		grid.Column(col).min_width = 0;
		for (int row = 0; row < grid.GetRowsCount(); row++)
		{
			if (grid.Cell(col, row)->colspan <= 1)
			{
				grid.Column(col).max_width = max(grid.Column(col).max_width, grid.Cell(col, row)->max_width);
				grid.Column(col).min_width = max(grid.Column(col).min_width, grid.Cell(col, row)->min_width);
			}
		}
	}

	// For each cell that spans more than one column, increase the minimum widths of the columns it spans so that together, 
	// they are at least as wide as the cell. Do the same for the maximum widths. 
	// If possible, widen all spanned columns by approximately the same amount.

	for (int col = 0; col < grid.GetColsCount(); col++)
	{
		for (int row = 0; row < grid.GetRowsCount(); row++)
		{
			if (grid.Cell(col, row)->colspan > 1)
			{
				int max_total_width = grid.Column(col).max_width;
				int min_total_width = grid.Column(col).min_width;
				for (int col2 = col + 1; col2 < col + grid.Cell(col, row)->colspan; col2++)
				{
					max_total_width += grid.Column(col2).max_width;
					min_total_width += grid.Column(col2).min_width;
				}
				if (min_total_width < grid.Cell(col, row)->min_width)
				{
					grid.DistributeMinWidth(grid.Cell(col, row)->min_width - min_total_width, col, col + grid.Cell(col, row)->colspan - 1);
				}
				if (max_total_width < grid.Cell(col, row)->max_width)
				{
					grid.DistributeMaxWidth(grid.Cell(col, row)->max_width - max_total_width, col, col + grid.Cell(col, row)->colspan - 1);
				}
			}
		}
	}

	// If the 'table' or 'inline-table' element's 'width' property has a computed value (W) other than 'auto', the used width is the 
	// greater of W, CAPMIN, and the minimum width required by all the columns plus cell spacing or Borders (MIN). 
	// If the used width is greater than MIN, the extra width should be distributed over the columns.
	//
	// If the 'table' or 'inline-table' element has 'width: auto', the used width is the greater of the table's containing block width, 
	// CAPMIN, and MIN. However, if either CAPMIN or the maximum width required by the columns plus cell spacing or Borders (MAX) is 
	// less than that of the containing block, use max(MAX, CAPMIN).


	int table_width = 0;
	int min_table_width = 0;
	int max_table_width = 0;

	if (!block_width.IsDefault())
	{
		table_width = grid.CalcTableWidth(block_width - table_width_spacing, false, min_table_width, max_table_width);
	}
	else
	{
		table_width = grid.CalcTableWidth(max_width - table_width_spacing, true, min_table_width, max_table_width);
	}

	min_table_width += table_width_spacing;
	max_table_width += table_width_spacing;
	table_width += table_width_spacing;
	grid.CalcHorizPos(borders, borderCollapse, border_spacing_x);

	bool row_span_found = false;

	// render cells with computed width
	for (int row = 0; row < grid.GetRowsCount(); row++)
	{
		grid.Row(row).height = 0;
		for (int col = 0; col < grid.GetColsCount(); col++)
		{
			TableCell* cell = grid.Cell(col, row);
			if (cell->el)
			{
				int span_col = col + cell->colspan - 1;
				if (span_col >= grid.GetColsCount())
				{
					span_col = grid.GetColsCount() - 1;
				}
				int cell_width = grid.Column(span_col).right - grid.Column(col).left;

				if (cell->el->pos.width != cell_width - cell->el->ContentMarginsLeft() - cell->el->ContentMarginsRight())
				{
					cell->el->Render(grid.Column(col).left, 0, cell_width);
					cell->el->pos.width = cell_width - cell->el->ContentMarginsLeft() - cell->el->ContentMarginsRight();
				}
				else
				{
					cell->el->pos.x = grid.Column(col).left + cell->el->ContentMarginsLeft();
				}

				if (cell->rowspan <= 1)
				{
					grid.Row(row).height = max(grid.Row(row).height, cell->el->Height());
				}
				else
				{
					row_span_found = true;
				}

			}
		}
	}

	if (row_span_found)
	{
		for (int col = 0; col < grid.GetColsCount(); col++)
		{
			for (int row = 0; row < grid.GetRowsCount(); row++)
			{
				TableCell* cell = grid.Cell(col, row);
				if (cell->el)
				{
					int span_row = row + cell->rowspan - 1;
					if (span_row >= grid.GetRowsCount())
					{
						span_row = grid.GetRowsCount() - 1;
					}
					if (span_row != row)
					{
						int h = 0;
						for (int i = row; i <= span_row; i++)
						{
							h += grid.Row(i).height;
						}
						if (h < cell->el->Height())
						{
							grid.Row(span_row).height += cell->el->Height() - h;
						}
					}
				}
			}
		}
	}


	int unconstrained_table_height = 0;

	// compute vertical size inferred by cells
	for (int row = 0; row < grid.GetRowsCount(); row++)
	{
		unconstrained_table_height += grid.Row(row).height;
	}

	unconstrained_table_height += border_spacing_y * (grid.GetRowsCount() + 1);

	int extra_row_height = 0;
	int minimum_table_height = max(css_height.CalcPercent(higher ? higher->pos.height : 0), css_min_height.CalcPercent(higher ? higher->pos.height : 0));

	if(minimum_table_height > unconstrained_table_height)
	{
		extra_row_height = (minimum_table_height - unconstrained_table_height) / grid.GetRowsCount();

		for (int row = 0; row < grid.GetRowsCount(); row++)
		{
			grid.Row(row).height += extra_row_height;
		}
	}

	grid.CalcVertPos(borders, borderCollapse, border_spacing_y);

	int table_height = 0;

	// place cells vertically
	for (int col = 0; col < grid.GetColsCount(); col++)
	{
		for (int row = 0; row < grid.GetRowsCount(); row++)
		{
			TableCell* cell = grid.Cell(col, row);
			if (cell->el)
			{
				int span_row = row + cell->rowspan - 1;
				if (span_row >= grid.GetRowsCount())
				{
					span_row = grid.GetRowsCount() - 1;
				}
				cell->el->pos.y = grid.Row(row).top + cell->el->ContentMarginsTop();
				cell->el->pos.height = grid.Row(span_row).bottom - grid.Row(row).top - cell->el->ContentMarginsTop() - cell->el->ContentMarginsBottom();
				table_height = max(table_height, grid.Row(span_row).bottom);
				cell->el->ApplyVerticalAlign();
			}
		}
	}

	if (borderCollapse == BorderCollapseCollapse)
	{
		if (grid.GetRowsCount())
		{
			table_height -= min(BorderBottom(), grid.Row(grid.GetRowsCount() - 1).border_bottom);
		}
	}
	else
	{
		table_height += border_spacing_y;
	}

	pos.width = table_width;

	CalcAutoMargins(higher_width);

	pos.MoveTo(x, y);
	pos.x += ContentMarginsLeft();
	pos.y += ContentMarginsTop();
	pos.width = table_width;
	pos.height = table_height;

	return max_table_width;
}

void HtmlTag::DrawChildrenBox(Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex)
{
	Position pos = this->pos;
	pos.x += x;
	pos.y += y;

	if (overflow > OverflowVisible)
	{
		Position border_box = pos;
		border_box += padding;
		border_box += borders;

		BorderRadiuses bdr_radius = css_borders.radius.CalcPercents(border_box.width, border_box.height);

		bdr_radius -= borders;
		bdr_radius -= padding;

		GetDocument()->GetHtmlCtrl().SetClip(hdc, pos, bdr_radius, true, true);
	}

	Position browser_wnd;
	GetDocument()->GetHtmlCtrl().GetClientRect(browser_wnd);
	
	
	for(int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();

		if (el && el->IsVisible())
		{
			switch (flag)
			{
			case DrawPositioned:
				if (el->IsPositioned() && el->GetZIndex() == zindex)
				{
					if (el->GetElementPosition() == ElementPositionFixed)
					{
						el->Paint(hdc, browser_wnd.x, browser_wnd.y, clip);
						el->DrawStackingContext(hdc, browser_wnd.x, browser_wnd.y, clip, true);
					}
					else
					{
						el->Paint(hdc, pos.x, pos.y, clip);
						el->DrawStackingContext(hdc, pos.x, pos.y, clip, true);
					}
					el = 0;
				}
				break;
			case DrawBlock:
				if (!el->IsInLineBox() && el->GetFloat() == FloatNone && !el->IsPositioned())
				{
					el->Paint(hdc, pos.x, pos.y, clip);
				}
				break;
			case DrawFloats:
				if (el->GetFloat() != FloatNone && !el->IsPositioned())
				{
					el->Paint(hdc, pos.x, pos.y, clip);
					el->DrawStackingContext(hdc, pos.x, pos.y, clip, false);
					el = 0;
				}
				break;
			case DrawInlines:
				if (el->IsInLineBox() && el->GetFloat() == FloatNone && !el->IsPositioned())
				{
					el->Paint(hdc, pos.x, pos.y, clip);
					if (el->GetDisplay() == DisplayInlineBlock)
					{
						el->DrawStackingContext(hdc, pos.x, pos.y, clip, false);
						el = 0;
					}
				}
				break;
			default:
				break;
			}

			if (el)
			{
				if (flag == DrawPositioned)
				{
					if (!el->IsPositioned())
					{
						el->DrawChildren(hdc, pos.x, pos.y, clip, flag, zindex);
					}
				}
				else
				{
					if (el->GetFloat() == FloatNone &&
						el->GetDisplay() != DisplayInlineBlock &&
						!el->IsPositioned())
					{
						el->DrawChildren(hdc, pos.x, pos.y, clip, flag, zindex);
					}
				}
			}
		}
	}

	if (overflow > OverflowVisible)
	{
		GetDocument()->GetHtmlCtrl().DelClip(hdc);
	}
}

void HtmlTag::DrawChildrenTable(Draw& hdc, int x, int y, const Position& clip, DrawFlag flag, int zindex)
{
	Position pos = this->pos;
	pos.x += x;
	pos.y += y;
	for (int row = 0; row < grid.GetRowsCount(); row++)
	{
		if (flag == DrawBlock)
		{
			grid.Row(row).el_row->DrawBackground(hdc, pos.x, pos.y, clip);
		}
		for (int col = 0; col < grid.GetColsCount(); col++)
		{
			TableCell* cell = grid.Cell(col, row);
			if (cell->el)
			{
				if (flag == DrawBlock)
				{
					cell->el->Paint(hdc, pos.x, pos.y, clip);
				}
				cell->el->DrawChildren(hdc, pos.x, pos.y, clip, flag, zindex);
			}
		}
	}
}








ElAnchor::ElAnchor() {
}

void ElAnchor::OnClick()
{
	String href = GetAttr("href");
	if (href.GetCount()) {
		GetDocument()->GetHtmlCtrl().OnAnchorClick(href, this);
	}
}

void ElAnchor::ApplyStylesheet( const Css& stylesheet )
{
	if( GetAttr("href").GetCount() ) {
		pseudo_classes.Add("link");
	}
	HtmlTag::ApplyStylesheet(stylesheet);
}







ElBase::ElBase()
{
	
}

void ElBase::ParseAttributes()
{
	String href = GetAttr("href");
	if (href.GetCount())
		GetDocument()->GetHtmlCtrl().SetBaseUrl(href);
}











ElBeforeAfterBase::ElBeforeAfterBase(bool before)
{
	if(before)
	{
		SetTagName("::before");
	} else
	{
		SetTagName("::after");
	}
}

void ElBeforeAfterBase::AddStyle( Style* st )
{
	HtmlTag::AddStyle(st);

	WString content = GetStyleProperty("content", false, "").ToWString();
	if(!content.IsEmpty())
	{
		int idx = ValueIndex(content, ContentPropertyString);
		if(idx < 0)
		{
			WString fnc;
			int i = 0;
			while(i < content.GetCount() && i != -1)
			{
				if(content[i] == '"')
				{
					fnc.Clear();
					i++;
					int pos = content.Find('"', i);
					WString txt;
					if(pos == -1)
					{
						txt = content.Mid(i);
						i = -1;
					} else
					{
						txt = content.Mid(i, pos - i);
						i = pos + 1;
					}
					AddText(txt);
				} else if(content[i] == '(')
				{
					i++;
					Trim(fnc);
					LowerCase(fnc);
					int pos = content.Find(')', i);
					WString params;
					if(pos == -1)
					{
						params = content.Mid(i);
						i = -1;
					} else
					{
						params = content.Mid(i, pos - i);
						i = pos + 1;
					}
					AddFunction(fnc.ToString(), params.ToString());
					fnc.Clear();
				} else
				{
					fnc.Cat(content[i]);
					i++;
				}
			}
		}
	}
}

void ElBeforeAfterBase::AddText( const WString& txt )
{
	WString word_;
	WString esc;
	for(int i = 0; i < txt.GetCount(); i++)
	{
		if( (txt[i] == ' ') || (txt[i] == '\t') || (txt[i] == '\\' && !esc.IsEmpty()) )
		{
			if(esc.IsEmpty())
			{
				if(!word_.IsEmpty())
				{
					Element* el = new ElText(word_);
					AppendChild(el);
					word_.Clear();
				}

				Element* el = new ElSpace(txt.Mid(i, 1));
				AppendChild(el);
			} else
			{
				word_ += ConvertEscape(esc.Mid(1));
				esc.Clear();
				if(txt[i] == '\\')
				{
					esc += txt[i];
				}
			}
		} else
		{
			if(!esc.IsEmpty() || txt[i] == '\\')
			{
				esc += txt[i];
			} else
			{
				word_ += txt[i];
			}
		}
	}

	if(!esc.IsEmpty())
	{
		word_ += ConvertEscape(esc.Mid(1));
	}
	if(!word_.IsEmpty())
	{
		Element* el = new ElText(word_);
		AppendChild(el);
		word_.Clear();
	}
}

void ElBeforeAfterBase::AddFunction( const String& fnc, const String& params )
{
	int idx = ValueIndex(fnc, "attr;counter;url");
	switch(idx)
	{
	// attr
	case 0:
		{
			String p_name = params;
			Trim(p_name);
			LowerCase(p_name);
			String attr_value = GetAttr(p_name);
			if (attr_value.GetCount())
				AddText(attr_value.ToWString());
			
		}
		break;
	// counter
	case 1:
		break;
	// url
	case 2:
		{
			String p_url = params;
			Trim(p_url);
			if(!p_url.IsEmpty())
			{
				if(p_url[0] == '\'' || p_url[0] == '\"')
				{
					p_url.Remove(0, 1);
				}
			}
			if(!p_url.IsEmpty())
			{
				if(p_url[p_url.GetCount() - 1] == '\'' || p_url[p_url.GetCount() - 1] == '\"')
				{
					p_url.Remove(p_url.GetCount() - 1, 1);
				}
			}
			if(!p_url.IsEmpty())
			{
				Element* el = new ElImage();
				el->SetAttr("src", p_url);
				el->SetAttr("style", "display:inline-block");
				el->SetTagName("img");
				AppendChild(el);
				el->ParseAttributes();
			}
		}
		break;
	}
}

wchar ElBeforeAfterBase::ConvertEscape( const WString& txt )
{
	return HexInt(txt.ToString());
}

wchar ElBeforeAfterBase::ConvertEscape( const String& txt )
{
	return HexInt(txt);
}

void ElBeforeAfterBase::ApplyStylesheet( const Css& Stylesheet )
{

}












ElBody::ElBody()
{
}

bool ElBody::IsBody()  const
{
	return true;
}

void ElBody::ParseAttributes()
{
	String str;

	str = GetAttr("bgcolor");
	if (str.GetCount())
	{
		style.AddProperty("background-color", str, "", false);
	}
	
	Color clr = GetColor("background-color", true, White());
	GetDocument()->GetHtmlCtrl().SetBackgroundColor(clr);

	HtmlTag::ParseAttributes();
}











ElBreak::ElBreak()
{

}

bool ElBreak::IsBreak() const
{
	return true;
}










ElCdata::ElCdata()
{
	skip = true;
}

void ElCdata::GetText( WString& text )
{
	text += this->text;
}

void ElCdata::SetData( const WString& data )
{
	//if(data) {
	if(data.GetCount()) {
		text += data;
	}
}







ElComment::ElComment()
{
	skip = true;
}

void ElComment::GetText( WString& text )
{
	text += this->text;
}

void ElComment::SetData( const WString& data )
{
	//if(data){
	if(data.GetCount()){
		text += data;
	}
}




ElDiv::ElDiv()
{

}

void ElDiv::ParseAttributes()
{
	String str = GetAttr("align");
	if(str.GetCount()) {
		style.AddProperty("text-align", str, "", false);
	}
	HtmlTag::ParseAttributes();
}









ElFont::ElFont()
{

}

void ElFont::ParseAttributes()
{
	String str = GetAttr("color");
	if(str.GetCount()) {
		style.AddProperty("color", str, "", false);
	}

	str = GetAttr("face");
	if(str.GetCount()){
		style.AddProperty("font-face", str, "", false);
	}

	str = GetAttr("color");
	if(str.GetCount()){
		
		int sz = StrInt(str);
		if(sz <= 1)
		{
			style.AddProperty("font-size", "x-small", "", false);
		} else if(sz >= 6)
		{
			style.AddProperty("font-size", "xx-large", "", false);
		} else
		{
			switch(sz)
			{
			case 2:
				style.AddProperty("font-size", "small", "", false);
				break;
			case 3:
				style.AddProperty("font-size", "medium", "", false);
				break;
			case 4:
				style.AddProperty("font-size", "large", "", false);
				break;
			case 5:
				style.AddProperty("font-size", "x-large", "", false);
				break;
			}
		}
	}

	HtmlTag::ParseAttributes();
}










ElImage::ElImage()
{
	display = DisplayInlineBlock;
	cache_id = -1;
}

void ElImage::GetContentSize( Size& sz, int max_width )
{
	GetDocument()->GetHtmlCtrl().GetImageSize(src, "", sz);
}

int ElImage::LineHeight() const
{
	return Height();
}

bool ElImage::IsReplaced() const
{
	return true;
}

int ElImage::Render( int x, int y, int max_width, bool second_pass )
{
	int higher_width = max_width;

	CalcOutlines(higher_width);

	pos.MoveTo(x, y);

	UPP::Size sz;
	GetDocument()->GetHtmlCtrl().GetImageSize(src, "", sz);

	pos.width		= sz.cx;
	pos.height	= sz.cy;

	if(css_height.IsPredefined() && css_width.IsPredefined())
	{
		pos.height	= sz.cy;
		pos.width		= sz.cx;

		// check for max-height
		if(!css_max_width.IsPredefined())
		{
			int max_width = GetDocument()->CvtUnits(css_max_width, font_size, higher_width);
			if(pos.width > max_width)
			{
				pos.width = max_width;
			}
			if(sz.cx)
			{
				pos.height = (int) ((float) pos.width * (float) sz.cy / (float)sz.cx);
			} else
			{
				pos.height = sz.cy;
			}
		}

		// check for max-height
		if(!css_max_height.IsPredefined())
		{
			int max_height = GetDocument()->CvtUnits(css_max_height, font_size);
			if(pos.height > max_height)
			{
				pos.height = max_height;
			}
			if(sz.cy)
			{
				pos.width = (int) (pos.height * (float)sz.cx / (float)sz.cy);
			} else
			{
				pos.width = sz.cx;
			}
		}
	} else if(!css_height.IsPredefined() && css_width.IsPredefined())
	{
		if (!GetPredefinedHeight(pos.height))
		{
			pos.height = (int)css_height.GetValue();
		}

		// check for max-height
		if(!css_max_height.IsPredefined())
		{
			int max_height = GetDocument()->CvtUnits(css_max_height, font_size);
			if(pos.height > max_height)
			{
				pos.height = max_height;
			}
		}

		if(sz.cy)
		{
			pos.width = (int) (pos.height * (float)sz.cx / (float)sz.cy);
		} else
		{
			pos.width = sz.cx;
		}
	} else if(css_height.IsPredefined() && !css_width.IsPredefined())
	{
		pos.width = (int) css_width.CalcPercent(higher_width);

		// check for max-width
		if(!css_max_width.IsPredefined())
		{
			int max_width = GetDocument()->CvtUnits(css_max_width, font_size, higher_width);
			if(pos.width > max_width)
			{
				pos.width = max_width;
			}
		}

		if(sz.cx)
		{
			pos.height = (int) ((float) pos.width * (float) sz.cy / (float)sz.cx);
		} else
		{
			pos.height = sz.cy;
		}
	} else
	{
		pos.width		= (int) css_width.CalcPercent(higher_width);
		pos.height	= 0;
		if (!GetPredefinedHeight(pos.height))
		{
			pos.height = (int)css_height.GetValue();
		}

		// check for max-height
		if(!css_max_height.IsPredefined())
		{
			int max_height = GetDocument()->CvtUnits(css_max_height, font_size);
			if(pos.height > max_height)
			{
				pos.height = max_height;
			}
		}

		// check for max-height
		if(!css_max_width.IsPredefined())
		{
			int max_width = GetDocument()->CvtUnits(css_max_width, font_size, higher_width);
			if(pos.width > max_width)
			{
				pos.width = max_width;
			}
		}
	}

	CalcAutoMargins(higher_width);

	pos.x	+= ContentMarginsLeft();
	pos.y += ContentMarginsTop();

	return pos.width + ContentMarginsLeft() + ContentMarginsRight();
}

void ElImage::ParseAttributes()
{
	src = GetAttr("src", "");

	String attr_height = GetAttr("height");
	if(attr_height.GetCount()) {
		style.AddProperty("height", attr_height, "", false);
	}
	String attr_width = GetAttr("width");
	if (attr_width.GetCount()) {
		style.AddProperty("width", attr_width, "", false);
	}
}

void ElImage::Paint( Draw& hdc, int x, int y, const Position& clip )
{
	Position pos = this->pos;
	pos.x += x;
	pos.y += y;

	Position el_pos = pos;
	el_pos += padding;
	el_pos += borders;

	// draw standard background here
	if (el_pos.DoesIntersect(clip))
	{
		Background* bg = GetBackground();
		if (bg)
		{
			BackgroundPaint bg_paint;
			InitBackgroundPaint(pos, bg_paint, bg);

			GetDocument()->GetHtmlCtrl().DrawBackground(hdc, bg_paint);
		}
	}

	// draw image as background
	if(pos.DoesIntersect(clip))
	{
		BackgroundPaint bg;
		bg.cache_id				= cache_id;
		if (cache_id == -1)
			bg.image			= src;
		bg.clip_box				= pos;
		bg.origin_box			= pos;
		bg.border_box			= pos;
		bg.border_box			+= padding;
		bg.border_box			+= borders;
		bg.repeat				= BackgroundRepeatNoRepeat;
		bg.image_size.cx		= pos.width;
		bg.image_size.cy		= pos.height;
		bg.border_radius		= css_borders.radius.CalcPercents(bg.border_box.width, bg.border_box.height);
		bg.position_x			= pos.x;
		bg.position_y			= pos.y;
		GetDocument()->GetHtmlCtrl().DrawBackground(hdc, bg);
	}

	// draw Borders
	if (el_pos.DoesIntersect(clip))
	{
		Position border_box = pos;
		border_box += padding;
		border_box += borders;

		Borders bdr = css_borders;
		bdr.radius = css_borders.radius.CalcPercents(border_box.width, border_box.height);

		GetDocument()->GetHtmlCtrl().DrawBorders(hdc, bdr, border_box, GetParentElement() ? false : true);
	}
}

void ElImage::ParseStyles( bool is_reparse /*= false*/ )
{
	HtmlTag::ParseStyles(is_reparse);

	if(!src.IsEmpty() && cache_id == -1)
	{
		if(!css_height.IsPredefined() && !css_width.IsPredefined())
		{
			GetDocument()->GetHtmlCtrl().LoadImage(src, "", true);
		} else
		{
			GetDocument()->GetHtmlCtrl().LoadImage(src, "", false);
		}
		cache_id = GetResourceCache().FindObject(src, ""/*GetDocument()->GetBaseUrl()*/);
	}
}












ElLink::ElLink()
{

}

void ElLink::ParseAttributes()
{
	bool processed = false;

	String rel = GetAttr("rel");
	if(rel.GetCount() && !rel.Compare("stylesheet"))
	{
		String media	= GetAttr("media");
		String href		= GetAttr("href");
		if(href.GetCount())
		{
			String css_text;
			String css_baseurl;
			GetDocument()->GetHtmlCtrl().ImportCss(css_text, href, css_baseurl);
			if(!css_text.IsEmpty())
			{
				GetDocument()->AddStylesheet(css_text, css_baseurl, media);
				processed = true;
			}
		}
	}

	if(!processed)
	{
		GetDocument()->GetHtmlCtrl().Link(GetDocument(), this);
	}
}











ElPara::ElPara(  )
{
}

void ElPara::ParseAttributes()
{
	String str = GetAttr("align");
	if(str.GetCount())
	{
		style.AddProperty("text-align", str, "", false);
	}

	HtmlTag::ParseAttributes();
}









ElScript::ElScript(  )
{
}

void ElScript::SetAttr(const String& name, const String& val) {
	if (name == "type") {
		type = val;
	}
}

void ElScript::ParseAttributes()
{
	if (type == "text/c++") {
		HtmlCtrl& page = GetDocument()->GetHtmlCtrl();
		page.AddScript(this);
	}
}

bool ElScript::AppendChild( Element* el )
{
	el->GetText(text);
	return true;
}

String ElScript::GetTagName() const
{
	return "script";
}









ElSpace::ElSpace( const WString& text) : ElText(text)
{
}

bool ElSpace::IsWhiteSpace()
{
	WhiteSpace ws = GetWhiteSpace();
	if(	ws == WhiteSpaceNormal || 
		ws == WhiteSpaceNowrap ||
		ws == WhiteSpacePreLine )
	{
		return true;
	}
	return false;
}

bool ElSpace::IsBreak() const
{
	WhiteSpace ws = GetWhiteSpace();
	if(	ws == WhiteSpacePre ||
		ws == WhiteSpacePreLine ||
		ws == WhiteSpacePreWrap)
	{
		if(text == WString(L"\n"))
		{
			return true;
		}
	}
	return false;
}








ElStyle::ElStyle( ) 
{

}

void ElStyle::ParseAttributes()
{
	WString text;

	for(ElementsVector::Iterator iter = children.Begin(); iter != children.End(); iter++)
	{
		(*iter)->GetText(text);
	}
	
	GetDocument()->AddStylesheet( text.ToString() , "",  GetAttr("media"));
}

bool ElStyle::AppendChild( Element* el )
{
	children.Add(el);
	return true;
}

String ElStyle::GetTagName() const
{
	return "Style";
}









ElTable::ElTable( )
{
	border_spacing_x	= 0;
	border_spacing_y	= 0;
	borderCollapse	= BorderCollapseSeparate;
}


bool ElTable::AppendChild( Element* el )
{
	if(!el)	return false;
	if(!el->GetTagName().Compare("tbody") || !el->GetTagName().Compare("thead") || !el->GetTagName().Compare("tfoot"))
	{
		return HtmlTag::AppendChild(el);
	}
	return false;
}

void ElTable::ParseStyles(bool is_reparse)
{
	HtmlTag::ParseStyles(is_reparse);

	borderCollapse = (BorderCollapse) ValueIndex(GetStyleProperty("border-collapse", true, "separate"), BorderCollapseStrings, BorderCollapseSeparate);

	if(borderCollapse == BorderCollapseSeparate)
	{
		css_border_spacing_x.FromString(GetStyleProperty("-litehtml-border-spacing-x", true, "0px"));
		css_border_spacing_y.FromString(GetStyleProperty("-litehtml-border-spacing-y", true, "0px"));

		int fntsz = GetFontSize();
		Document* doc = GetDocument();
		border_spacing_x = doc->CvtUnits(css_border_spacing_x, fntsz);
		border_spacing_y = doc->CvtUnits(css_border_spacing_y, fntsz);
	} else
	{
		border_spacing_x	= 0;
		border_spacing_y	= 0;
		padding.bottom	= 0;
		padding.top		= 0;
		padding.left		= 0;
		padding.right		= 0;
		css_padding.bottom.SetValue(0, CssUnitsPx);
		css_padding.top.SetValue(0, CssUnitsPx);
		css_padding.left.SetValue(0, CssUnitsPx);
		css_padding.right.SetValue(0, CssUnitsPx);
	}
}

void ElTable::ParseAttributes()
{
	String str = GetAttr("width");
	if(str.GetCount())
	{
		style.AddProperty("width", str, "", false);
	}

	str = GetAttr("align");
	if(str.GetCount())
	{
		int align = ValueIndex(str, "left;center;right");
		switch(align)
		{
		case 1:
			style.AddProperty("margin-left", "auto", "", false);
			style.AddProperty("margin-right", "auto", "", false);
			break;
		case 2:
			style.AddProperty("margin-left", "auto", "", false);
			style.AddProperty("margin-right", "0", "", false);
			break;
		}
	}

	str = GetAttr("cellspacing");
	if(str.GetCount())
	{
		String val = str;
		val += " ";
		val += str;
		style.AddProperty("border-spacing", val, "", false);
	}
	
	str = GetAttr("border");
	if(str.GetCount())
	{
		style.AddProperty("border-width", str, "", false);
	}

	str = GetAttr("bgcolor");
	if (str.GetCount())
	{
		style.AddProperty("background-color", str, "", false);
	}

	HtmlTag::ParseAttributes();
}














ElTd::ElTd(  )
{

}

void ElTd::ParseAttributes()
{
	String str = GetAttr("width");
	if(str.GetCount())
	{
		style.AddProperty("width", str, "", false);
	}
	str = GetAttr("background");
	if(str.GetCount())
	
	{
		String url = "url('";
		url += str;
		url += "')";
		style.AddProperty("background-image", url, "", false);
	}
	str = GetAttr("align");
	if(str.GetCount())
	{
		style.AddProperty("text-align", str, "", false);
	}

	str = GetAttr("bgcolor");
	if (str.GetCount())
	{
		style.AddProperty("background-color", str, "", false);
	}

	str = GetAttr("valign");
	if(str.GetCount())
	{
		style.AddProperty("vertical-align", str, "", false);
	}
	HtmlTag::ParseAttributes();
}












ElText::ElText( const WString& text )
{
	this->text		= text;
	text_transform	= TextTransformNone;
	use_transformed	= false;
	draw_spaces		= true;
}

void ElText::GetContentSize( Size& sz, int max_width )
{
	sz = size;
}

void ElText::GetText( WString& text )
{
	text += this->text;
}

String ElText::GetStyleProperty( const String& name, bool inherited, const String& def /*= 0*/ )
{
	if(inherited)
	{
		Element* e = GetParentElement();
		if (!e) return def;
		return e->GetStyleProperty(name, inherited, def);
	}
	return def;
}

void ElText::ParseStyles(bool is_reparse)
{
	text_transform	= (TextTransform)	ValueIndex(GetStyleProperty("text-transform", true,	"none"),	TextTransformStrings,	TextTransformNone);
	if(text_transform != TextTransformNone)
	{
		transformed_text	= text;
		use_transformed = true;
		GetDocument()->GetHtmlCtrl().TransformText(transformed_text, text_transform);
	}

	if(IsWhiteSpace())
	{
		transformed_text = " ";
		use_transformed = true;
	} else
	{
		if(text == WString(L"\t"))
		{
			transformed_text = "    ";
			use_transformed = true;
		}
		if(text == WString(L"\n") || text == WString(L"\r"))
		{
			transformed_text = "";
			use_transformed = true;
		}
	}
	
	
	FontMetrics fm;
	Element* e = GetParentElement();
	
	uint32 font	= e->GetFont(&fm);
	if (font >= 1000) {
		font	= e->GetFont(&fm);
		Panic("errorz here");
	}


	if(IsBreak())
	{
		size.cy	= 0;
		size.cx	= 0;
	} else
	{
		size.cy	= fm.height;
		size.cx	= GetDocument()->GetHtmlCtrl().TextWidth(use_transformed ? transformed_text : text, font);
	}
	
	draw_spaces = fm.draw_spaces;

	
}

int ElText::GetBaseLine()
{
	return GetParentElement()->GetBaseLine();
}

void ElText::Paint( Draw& hdc, int x, int y, const Position& clip )
{
	if(IsWhiteSpace() && !draw_spaces)
	{
		return;
	}

	Position pos = this->pos;
	pos.x	+= x;
	pos.y	+= y;

	if(pos.DoesIntersect(clip))
	{
		uint32 font = GetParentElement()->GetFont();
		RGBA color = GetParentElement()->GetColor("color", true, GetDocument()->GetDefColor());
		
		GetDocument()->GetHtmlCtrl().DrawText(hdc, use_transformed ? transformed_text : text, font, color, pos);
	}
}

int ElText::LineHeight() const
{
	return GetParentElement()->LineHeight();
}

uint32 ElText::GetFont( FontMetrics* fm /*= 0*/ )
{
	return GetParentElement()->GetFont(fm);
}

StyleDisplay ElText::GetDisplay() const
{
	return DisplayInlineText;
}

WhiteSpace ElText::GetWhiteSpace() const
{
	Element* higher = GetParentElement();
	if(higher) return higher->GetWhiteSpace();
	return WhiteSpaceNormal;
}

ElementPosition ElText::GetElementPosition(CssOffsets* offsets) const
{
	Element* p = GetParentElement();
	while(p && p->GetDisplay() == DisplayInline)
	{
		if(p->GetElementPosition() == ElementPositionRelative)
		{
			if(offsets)
			{
				*offsets = p->GetCssOffsets();
			}
			return ElementPositionRelative;
		}
		p = p->GetParentElement();
	}
	return ElementPositionStatic;
}

CssOffsets ElText::GetCssOffsets() const
{
	Element* p = GetParentElement();
	while(p && p->GetDisplay() == DisplayInline)
	{
		if(p->GetElementPosition() == ElementPositionRelative)
		{
			return p->GetCssOffsets();
		}
		p = p->GetParentElement();
	}
	return CssOffsets();
}








ElTitle::ElTitle(  )
{

}

void ElTitle::ParseAttributes()
{
	WString text;
	GetText(text);
	GetDocument()->GetHtmlCtrl().SetCaption(text);
}











ElTr::ElTr()
{

}

void ElTr::ParseAttributes()
{
	String str = GetAttr("align");
	if(str.GetCount())
	{
		style.AddProperty("text-align", str, "", false);
	}
	str = GetAttr("valign");
	if(str.GetCount())
	{
		style.AddProperty("vertical-align", str, "", false);
	}
	str = GetAttr("bgcolor");
	if(str.GetCount())
	{
		style.AddProperty("background-color", str, "", false);
	}
	HtmlTag::ParseAttributes();
}

void ElTr::GetInLineBoxes( Vector<Position>& Boxes )
{
	Position pos;
	for (int i = 0; i < Object::GetCount(); i++) {
		Element* el = At(i).As<Element>();
		if(el && el->GetDisplay() == DisplayTableCell)
		{
			pos.x		= el->Left() + el->MarginLeft();
			pos.y		= el->Top() - padding.top - borders.top;

			pos.width	= el->Right() - pos.x - el->MarginRight() - el->MarginLeft();
			pos.height	= el->Height() + padding.top + padding.bottom + borders.top + borders.bottom;

			Boxes.Add(pos);
		}
	}
}


NAMESPACE_LAYOUT_END
