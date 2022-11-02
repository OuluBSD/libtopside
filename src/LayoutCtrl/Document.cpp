#include "LayoutCtrl.h"


NAMESPACE_LAYOUT_BEGIN

bool Document::Init(String html, String address) {
	Object::Clear();
	fonts.Clear();
	css.Clear();
	styles.Clear();
	def_color = Black();
	fixed_boxes.Clear();
	media_lists.Clear();
	media_lists.Clear();
	over_element = NULL;
	tabular_elements.Clear();
	//media.Clear();
	
	
	addr = address;
	UrlParser up;
	up.Parse(address);
	base_addr = up.GetFormattedBaseAddr();
	
	HtmlParser p;
	if (!p.Parse(html))
		return false;
	//LOG(NodeTreeString(p.root));
	
	//Element& root = *Object::Add(new Element()).As<Element>();
	CreateNode(p.root, *this);
	Element* root = At(0).As<Element>();
	
	ASSERT(!GetParent());
	
	if (root) {
		GetHtmlCtrl().GetMediaFeatures(this->media);
			
		// apply master CSS
		root->ApplyStylesheet(GetHtmlCtrl().MasterCss());
		
		// parse elements attributes
		root->ParseAttributes();
		
		// parse Style sheets linked in Document
		MediaQueryList* media = NULL;
		for (CssText::vector::Iterator css = this->css.Begin(); css != this->css.End(); css++)
		{
			if (!css->media.IsEmpty())
			{
				media = MediaQueryList::CreateFromString(css->media, this);
			}
			else
			{
				media = 0;
			}
			styles.ParseStylesheet(css->text, css->baseurl, this, media);
		}
		
		// Sort css Selectors using CSS rules.
		styles.SortSelectors();
	
		// get current media features
		if (!media_lists.IsEmpty()) {
			UpdateMediaLists(this->media);
		}
	
		// Apply parsed Styles.
		root->ApplyStylesheet(styles);
	
		// Apply user Styles if any
		if (user_styles) {
			root->ApplyStylesheet(*user_styles);
		}
	
		// Parse applied Styles in the elements
		ASSERT(!GetParent());
		root->ParseStyles();
	
		// Now the m_tabular_elements is filled with tabular elements.
		// We have to check the tabular elements for missing table elements
		// and create the anonymous Boxes in visual table layout
		FixTablesLayout();
	
		// Finally Initialize elements
		root->Init();
	}
	
	return true;
}

void Document::CreateNode(HtmlNode& n, Object& o) {
	if (n.IsType(HTMLNODE_ROOT)) {
		Element* e = new HtmlTag();
		for(int i = 0; i < n.GetCount(); i++)
			CreateNode(n.At(i), *e);
		o.Add(e);
	}
	else if (n.IsType(HTMLNODE_TAG) || n.IsType(HTMLNODE_TAG_SCOPE)) {
		Element* e = CreateElement(n);
		if (e) {
			for(int i = 0; i < n.GetCount(); i++)
				CreateNode(n.At(i), *e);
			o.Add(e);
		}
	}
	else if (n.IsType(HTMLNODE_TEXT)) {
		int mode = -1;
		enum {TEXT, SPACE};
		WString txt = n.GetText();
		WString tmp;
		for(int i = 0; i < txt.GetCount(); i++) {
			int chr = txt[i];
			if (IsSpace(chr)) {
				if (mode == TEXT) {
					o.Add(new ElText(tmp));
					tmp.Clear();
				}
				mode = SPACE;
				tmp.Cat(chr);
			}
			else {
				if (mode == SPACE) {
					o.Add(new ElSpace(tmp));
					tmp.Clear();
				}
				mode = TEXT;
				tmp.Cat(chr);
			}
			if (tmp.GetCount()) {
				if (mode == TEXT) {
					o.Add(new ElText(tmp));
					tmp.Clear();
				}
				else if (mode == SPACE) {
					o.Add(new ElSpace(tmp));
					tmp.Clear();
				}
			}
		}
	}
}

Element* Document::CreateElement(HtmlNode& n) {
	ASSERT(n.IsType(HTMLNODE_TAG) || n.IsType(HTMLNODE_TAG_SCOPE));
	Element* new_tag = NULL;
	
	String tag_name = n.GetText().ToString();
	
	if (ctrl)
		new_tag = ctrl->CreateElement(n);
	
	if (!new_tag) {
		if (!tag_name.Compare("br"))
			new_tag = new ElBreak();
		else if(!tag_name.Compare("p"))
			new_tag = new ElPara();
		else if(!tag_name.Compare("img"))
			new_tag = new ElImage();
		else if(!tag_name.Compare("table"))
			new_tag = new ElTable();
		else if(!tag_name.Compare("td") || !tag_name.Compare("th"))
			new_tag = new ElTd();
		else if(!tag_name.Compare("link"))
			new_tag = new ElLink();
		else if(!tag_name.Compare("title"))
			new_tag = new ElTitle();
		else if(!tag_name.Compare("a"))
			new_tag = new ElAnchor();
		else if(!tag_name.Compare("tr"))
			new_tag = new ElTr();
		else if(!tag_name.Compare("style"))
			new_tag = new ElStyle();
		else if(!tag_name.Compare("base"))
			new_tag = new ElBase();
		else if(!tag_name.Compare("body"))
			new_tag = new ElBody();
		else if(!tag_name.Compare("div"))
			new_tag = new ElDiv();
		else if(!tag_name.Compare("script"))
			new_tag = new ElScript();
		else if(!tag_name.Compare("font"))
			new_tag = new ElFont();
		else if (tag_name == "!DOCTYPE html")
			return NULL;
		else
			new_tag = new HtmlTag();
	}

	if (new_tag) {
		new_tag->SetTagName(tag_name);
		for (int i = 0; i < n.GetAttrCount(); i++)
			new_tag->SetAttr(n.GetAttrKey(i), n.GetAttr(i));
	}

	return new_tag;
}



uint32 Document::AddFont( String name, int size, const String& weight, const String& Style, const String& decoration, FontMetrics* fm )
{
	PERFMETER_BEGIN(PERF_DOCADDFONT);
	
	uint32 ret = 0;

	HtmlCtrl* container = &GetHtmlCtrl();
	
	if( !name.GetCount() || (name.GetCount() && !CompareNoCase(name, "inherit")) )
	{
		name = container->GetDefaultFontName();
	}

	if(!size)
	{
		size = GetHtmlCtrl().GetDefaultFontSize();
	}

	String key = name;
	key += ":";
	key += IntStr(size);
	key += ":";
	key += weight;
	key += ":";
	key += Style;
	key += ":";
	key += decoration;

	if(fonts.Find(key) == -1)
	{
		FontStyle fs = (FontStyle) ValueIndex(Style, FontstyleStrings, FontStyleNormal);
		int	fw = ValueIndex(weight, FontWeightStrings, -1);
		if(fw >= 0)
		{
			switch(fw)
			{
			case FontWeightBold:
				fw = 700;
				break;
			case FontWeightBolder:
				fw = 600;
				break;
			case FontWeightLighter:
				fw = 300;
				break;
			default:
				fw = 400;
				break;
			}
		} else
		{
			fw = StrInt(weight);
			if(fw < 100)
			{
				fw = 400;
			}
		}

		unsigned int decor = 0;

		if(decoration.GetCount())
		{
			Vector<String> tokens;
			SplitString(decoration, tokens, " ");
			for(Vector<String>::Iterator i = tokens.Begin(); i != tokens.End(); i++)
			{
				if(!CompareNoCase(*i, "underline"))
				{
					decor |= FontDecorationUnderline;
				}
				else if(!CompareNoCase(*i, "line-through"))
				{
					decor |= FontDecorationLinethrough;
				}
				else if(!CompareNoCase(*i,"overline"))
				{
					decor |= FontDecorationOverline;
				}
			}
		}

		FontItem fi= {0};
		fi.font = container->CreateFont(name, size, fw, fs, decor, &fi.metrics);
		fonts.GetAdd(key) = fi;
		ret = fi.font;
		if(fm)
		{
			*fm = fi.metrics;
		}
	}
	
	PERFMETER_END(PERF_DOCADDFONT);
	return ret;
}

uint32 Document::GetFont( String name, int size, const String& weight, const String& style, const String& decoration, FontMetrics* fm )
{
	PERFMETER_BEGIN(PERF_GETFONT);
	
	if( !name.GetCount() || (name.GetCount() && !CompareNoCase(name, "inherit"))) {
		name = GetHtmlCtrl().GetDefaultFontName();
	}

	if(!size)
	{
		size = GetHtmlCtrl().GetDefaultFontSize();
	}

	String key = name;
	key += ":";
	key += IntStr(size);
	key += ":";
	key += weight;
	key += ":";
	key += style;
	key += ":";
	key += decoration;
	
	
	int i = fonts.Find(key);

	if(i != -1)
	{
		FontItem* el = &fonts[i];
		if (fm) {
			*fm = el->metrics;
		}
		return el->font;
	}
	uint32 f = AddFont(name, size, weight, style, decoration, fm);
	
	PERFMETER_END(PERF_GETFONT);
	return f;
}

int Document::Render( int max_width, RenderType rt )
{
	PERFMETER_BEGIN(PERF_DOCRENDER);
	int ret = 0;
	Element* root = GetRoot();
	if (root) {
		if(rt == RenderFixedOnly)
		{
			fixed_boxes.Clear();
			root->RenderPositioned(rt);
		} else
		{
			ret = root->Render(0, 0, max_width);
			if(root->FetchPositioned())
			{
				fixed_boxes.Clear();
				root->RenderPositioned(rt);
			}
			size.cx	= 0;
			size.cy	= 0;
			root->CalcDocumentSize(size);
		}
	}
	
	PERFMETER_END(PERF_DOCRENDER);
	return ret;
}

void Document::Paint( Draw& hdc, int x, int y, const Position& clip )
{
	PERFMETER_BEGIN(PERF_DOCPAINT);
	Element* root = GetRoot();
	if (root) {
		root->Paint(hdc, x, y, clip);
		root->DrawStackingContext(hdc, x, y, clip, true);
	}
	PERFMETER_END(PERF_DOCPAINT);
}

int Document::CvtUnits( const String& str, int fontSize, bool* is_percent/*= 0*/ ) const
{
	if(!str.GetCount())	return 0;
	
	CssLength val;
	val.FromString(str);
	if(is_percent && val.Units() == CssUnitsPercentage && !val.IsPredefined())
	{
		*is_percent = true;
	}
	return CvtUnits(val, fontSize);
}

int Document::CvtUnits( CssLength& val, int fontSize, int size ) const
{
	if(val.IsPredefined())
	{
		return 0;
	}
	int ret = 0;
	switch(val.Units())
	{
	case CssUnitsPercentage:
		ret = val.CalcPercent(size);
		break;
	case CssUnitsEm:
		ret = RoundFlt(val.GetValue() * fontSize);
		val.SetValue((float) ret, CssUnitsPx);
		break;
	case CssUnitsPt:
		ret = GetHtmlCtrl().PtPx((int) val.GetValue());
		val.SetValue((float) ret, CssUnitsPx);
		break;
	case CssUnitsIn:
		ret = GetHtmlCtrl().PtPx((int) (val.GetValue() * 72));
		val.SetValue((float) ret, CssUnitsPx);
		break;
	case CssUnitsCm:
		ret = GetHtmlCtrl().PtPx((int) (val.GetValue() * 0.3937 * 72));
		val.SetValue((float) ret, CssUnitsPx);
		break;
	case CssUnitsMm:
		ret = GetHtmlCtrl().PtPx((int) (val.GetValue() * 0.3937 * 72) / 10);
		val.SetValue((float) ret, CssUnitsPx);
		break;
	case CssUnitsVw:
		ret = (int)((double)media.width * (double)val.GetValue() / 100.0);
		break;
	case CssUnitsVh:
		ret = (int)((double)media.height * (double)val.GetValue() / 100.0);
		break;
	case CssUnitsVmin:
		ret = (int)((double)min(media.height, media.width) * (double)val.GetValue() / 100.0);
		break;
	case CssUnitsVmax:
		ret = (int)((double)max(media.height, media.width) * (double)val.GetValue() / 100.0);
		break;
	default:
		ret = (int) val.GetValue();
		break;
	}
	return ret;
}

int Document::Width() const
{
	return size.cx;
}

int Document::Height() const
{
	return size.cy;
}

void Document::AddStylesheet( const String& str, const String& baseurl, const String& media )
{
	if(str.GetCount())
	{
		css.Add(CssText(str, baseurl, media));
	}
}

bool Document::OnMouseOver( int x, int y, int client_x, int client_y, Vector<Position>& redraw_boxes, Element** el_sel )
{
	Element* root = GetRoot();
	
	if(!root)
		return false;
	
	PERFMETER_BEGIN(PERF_MOUSEOVER);
	
	bool ret;
	Element* over_el = root->GetElementByPoint(x, y, client_x, client_y);
	if (el_sel)
		*el_sel = over_el;
	
	bool state_was_changed = false;

	if(over_el != over_element)
	{
		if(over_element)
		{
			if(over_element->OnMouseLeave())
			{
				state_was_changed = true;
			}
		}
		over_element = over_el;
	}

	String cursor;

	if(over_element)
	{
		if(over_element->OnMouseOver())
		{
			state_was_changed = true;
		}
		cursor = over_element->GetCursor();
	}
	
	GetHtmlCtrl().SetCursor(cursor.GetCount() ? cursor : "auto");
	
	if(state_was_changed)
	{
		ret = root->FindStylesChanges(redraw_boxes, 0, 0);
	}
	else ret = false;
	
	PERFMETER_END(PERF_MOUSEOVER);
	return ret;
}

bool Document::OnMouseLeave( Vector<Position>& redraw_boxes )
{
	Element* root = GetRoot();
	
	if(!root)
		return false;
	
	PERFMETER_BEGIN(PERF_MOUSELEAVE);
	bool ret;
	if(over_element &&over_element->OnMouseLeave()) {
		ret = root->FindStylesChanges(redraw_boxes, 0, 0);
	}
	else ret = false;
	
	PERFMETER_END(PERF_MOUSELEAVE);
	return ret;
}

bool Document::OnMouseLeftDown( int x, int y, int client_x, int client_y, Vector<Position>& redraw_boxes )
{
	Element* root = GetRoot();
	
	if(!root)
		return false;

	PERFMETER_BEGIN(PERF_MOUSELEFTDOWN);
	bool ret;
	Element* over_el = root->GetElementByPoint(x, y, client_x, client_y);

	bool state_was_changed = false;

	if(over_el != over_element)
	{
		if(over_element)
		{
			if(over_element->OnMouseLeave())
			{
				state_was_changed = true;
			}
		}
		over_element = over_el;
		if(over_element)
		{
			if(over_element->OnMouseOver())
			{
				state_was_changed = true;
			}
		}
	}

	String cursor;

	if(over_element)
	{
		if(over_element->OnMouseLeftDown())
		{
			state_was_changed = true;
		}
		cursor = over_element->GetCursor();
	}

	GetHtmlCtrl().SetCursor(cursor.GetCount() ? cursor : "auto");

	if(state_was_changed)
	{
		ret = root->FindStylesChanges(redraw_boxes, 0, 0);
	}
	else ret = false;
	
	PERFMETER_END(PERF_MOUSELEFTDOWN);
	return ret;
}

bool Document::OnMouseLeftUp( int x, int y, int client_x, int client_y, Vector<Position>& redraw_boxes )
{
	Element* root = GetRoot();
	
	if(!root)
		return false;
	
	PERFMETER_BEGIN(PERF_MOUSELEFTUP);
	bool ret;
	if(over_element&& over_element->OnMouseLeftUp()) {
		ret = root->FindStylesChanges(redraw_boxes, 0, 0);
	}
	else ret = false;
	PERFMETER_BEGIN(PERF_MOUSELEFTUP);
	return ret;
}

void Document::GetFixedBoxes( Vector<Position>& fixed_boxes ) {
	fixed_boxes <<= fixed_boxes;
}

void Document::AddFixedBox( const Position& pos )
{
	fixed_boxes.Add(pos);
}

bool Document::MediaChanged()
{
	Element* root = GetRoot();
	if(root && !media_lists.IsEmpty())
	{
		GetHtmlCtrl().GetMediaFeatures(media);
		if (UpdateMediaLists(media))
		{
			root->RefreshStyles();
			root->ParseStyles();
			return true;
		}
	}
	return false;
}

bool Document::UpdateMediaLists(const MediaFeatures& features)
{
	bool update_styles = false;
	for(Vector<MediaQueryList*>::Iterator iter = media_lists.Begin(); iter != media_lists.End(); iter++)
	{
		if((*iter)->ApplyMediaFeatures(features))
		{
			update_styles = true;
		}
	}
	return update_styles;
}

void Document::AddMediaList(MediaQueryList* list )
{
	if(list)
	{
		if(UPP::Find(media_lists.Begin(), media_lists.End(), list, StdEqual<MediaQueryList*>()) == media_lists.End())
		{
			media_lists.Add(list);
		}
	}
}

void Document::FixTablesLayout()
{
	size_t i = 0;
	while (i < tabular_elements.GetCount())
	{
		Element* el_ptr = tabular_elements[i];

		switch (el_ptr->GetDisplay())
		{
		case DisplayInlineTable:
		case DisplayTable:
			FixTableChildren(el_ptr, DisplayTableRowGroup, "table-row-group");
			break;
		case DisplayTableFooterGroup:
		case DisplayTableRowGroup:
		case DisplayTableHeaderGroup:
			FixTableParent(el_ptr, DisplayTable, "table");
			FixTableChildren(el_ptr, DisplayTableRow, "table-row");
			break;
		case DisplayTableRow:
			FixTableParent(el_ptr, DisplayTableRowGroup, "table-row-group");
			FixTableChildren(el_ptr, DisplayTableCell, "table-cell");
			break;
		case DisplayTableCell:
			FixTableParent(el_ptr, DisplayTableRow, "table-row");
			break;
		// TODO: make table layout fix for table-caption, table-column etc. elements
		case DisplayTableCaption:
		case DisplayTableColumn:
		case DisplayTableColumnGroup:
		default:
			break;
		}
		i++;
	}
}

void Document::FixTableChildren(Element* el_ptr, StyleDisplay disp, const String& disp_str)
{
	ElementsVector tmp;
	int first = 0, cur = 0;

	auto flush_elements = [&]()
	{
		Element* annon_tag = new HtmlTag();
		Style* st = new Style();
		st->AddProperty("display", disp_str, "", false);
		annon_tag->AddStyle(st);
		annon_tag->MoveTo(*el_ptr);
		annon_tag->ParseStyles();
		
		ElementsVector::Iterator it  = tmp.Begin();
		ElementsVector::Iterator end = tmp.End();
		for (; it != end; it++) {
			annon_tag->AppendChild(*it);
		}
		el_ptr->Object::Insert(first, annon_tag);
		cur = first + 1;
		
		while (cur < el_ptr->Object::GetCount()) {
			Element* el = el_ptr->At(cur).As<Element>();
			if (!el) {cur++; continue;}
			
			if (el->GetParentElement() == el_ptr) break;
			el_ptr->Object::Remove(cur);
		}
		
		first = cur;
		tmp.Clear();
	};

	while (cur < el_ptr->Object::GetCount()) {
		Element* cur_iter = el_ptr->At(cur).As<Element>();
		
		if (cur_iter && cur_iter->GetDisplay() != disp) {
			if (!cur_iter->IsWhiteSpace() || (cur_iter->IsWhiteSpace() && !tmp.IsEmpty()))
			{
				if (tmp.IsEmpty())
				{
					first = cur;
				}
				tmp.Add(cur_iter);
			}
			cur++;
		}
		else if (!tmp.IsEmpty()) {
			flush_elements();
		}
		else {
			cur++;
		}
	}
	if (!tmp.IsEmpty()) {
		flush_elements();
	}
}

void Document::FixTableParent(Element* el_ptr, StyleDisplay disp, const String& disp_str)
{
	Element* higher = el_ptr->GetParentElement();

	if (higher->GetDisplay() != disp) {
		int pos = higher->FindPos(el_ptr);
		if (pos != -1) {
			StyleDisplay el_disp = el_ptr->GetDisplay();
			
			int first = pos;
			int last = pos;
			int cur = pos;

			// find first element with same display
			while (true) {
				if (cur == 0) break;
				cur--;
				
				Element* el = higher->At(cur).As<Element>();
				if (el && el->IsWhiteSpace() || el->GetDisplay() == el_disp) {
					first = cur;
				}
				else {
					break;
				}
			}

			// find last element with same display
			cur = pos;
			while (true)
			{
				cur++;
				if (cur == higher->Object::GetCount()) break;

				Element* el = higher->At(cur).As<Element>();
				if (el && el->IsWhiteSpace() || el->GetDisplay() == el_disp) {
					last = cur;
				}
				else {
					break;
				}
			}

			// extract elements with the same display and wrap them with anonymous Object
			Element* annon_tag = new HtmlTag();
			Style* st = new Style();
			st->AddProperty("display", disp_str, "", false);
			annon_tag->AddStyle(st);
			annon_tag->MoveTo(*higher);
			annon_tag->ParseStyles();
			for (int j = first; j < last + 1; j++) {
				Element* el = higher->At(j).As<Element>();
				if (el)
					annon_tag->AppendChild(el);
			}
			higher->Object::Remove(first, last+1-first);
			higher->Object::Insert(first, annon_tag);
		}
	}
}

NAMESPACE_LAYOUT_END
