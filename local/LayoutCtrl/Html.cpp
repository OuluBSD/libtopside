#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN
	
Array<Font> HtmlCtrl::_fonts;


void HtmlRenderer::Paint(Draw& d) {
	int y = -yscroll;
	int x = -xscroll;
	d.DrawRect(GetSize(), bg);
	
	lock.Enter();
	for(int i = 0; i < pieces.GetCount(); i++) {
		Piece& p = pieces[i];
		d.DrawImage(x + p.rect.left, y + p.rect.top, p.img);
	}
	lock.Leave();
}







HtmlCtrl::HtmlCtrl() : doc(this), master_doc(this) {
	hscroll.Horz();
	AddFrame(vscroll);
	AddFrame(hscroll);
	Add(renderer.SizePos());
	
	vscroll.WhenScroll << THISBACK(OnScroll);
	hscroll.WhenScroll << THISBACK(OnScroll);
	vscroll.SetLine(30);
	hscroll.SetLine(30);
	
	String str = GetMasterCss();
	MediaQueryList* m = NULL;
	master_css.ParseStylesheet(str, "", &master_doc, m);
	master_css.SortSelectors();
	media = m;
	
	
}

HtmlCtrl::~HtmlCtrl() {
	doc.Object::Clear();
}

void HtmlCtrl::OnScroll() {
	renderer.xscroll = hscroll;
	renderer.yscroll = vscroll;
	Refresh();
}

void HtmlCtrl::Layout() {
	Size sz(GetSize());
	vscroll.SetPage(sz.cy);
	hscroll.SetPage(sz.cx);
	ParentCtrl::Layout();
	
	if (init_ready == true) {
		ProcessAtLeast(RENDER);
		Thread::Start(THISBACK(Process));
	}
}

void HtmlCtrl::MouseWheel(Point, int zdelta, dword) {
	vscroll.Wheel(zdelta);
}

bool HtmlCtrl::Key(dword key, int) {
	return vscroll.VertKey(key);
}

void HtmlCtrl::Process() {
	process_lock.Enter();
	int this_tread_process = process;
	process = IDLE;
	process_lock.Leave();
	
	if (this_tread_process == IDLE) return;
	
	
	process_lock_run.Enter();
	
	if (this_tread_process >= INIT) {
		init_ready = false;
		doc.Init(html, addr);
	}
	if (this_tread_process >= RENDER) {
		Size sz(GetSize());
		doc.Render(sz.cx);
	}
	if (this_tread_process >= PAINT) {
		Size sz(GetSize());
		int w = doc.Width();
		int h = min(sz.cy*2, doc.Height());
		ImageDraw id(w, h);
		id.DrawRect(Size(w,h), bg_color);
		Position clip(0, 0, w, h);
		doc.Paint(id, 0, 0, clip);
		
		renderer.lock.Enter();
		renderer.pieces.Clear();
		HtmlRenderer::Piece& p = renderer.pieces.Add();
		p.img = id;
		p.rect = RectC(0, 0, w, h);
		renderer.lock.Leave();
		
		
		PostCallback(THISBACK2(SetScrollTotal, h, w));
		PostCallback(THISBACK(OnScroll));
	}
	
	if (this_tread_process >= INIT) {
		//TODO: check that no CSS is pending
		init_ready = true;
	}
	
	process_lock_run.Leave();
}

void HtmlCtrl::SetHtml(String html, String addr) {
	this->html = html;
	this->addr = addr;
	ProcessAtLeast(INIT);
	Thread::Start(THISBACK(Process));
}

Element* HtmlCtrl::CreateElement(HtmlNode& n) {
	return NULL;
}

void HtmlCtrl::AddScript(ElScript* script) {
	scripts.Add(script);
}


// Checks if font(s) exists and loads them to memory
uint32 HtmlCtrl::CreateFont(const String& faceName, int size, int weight, FontStyle italic, unsigned int decoration, FontMetrics* fm) {
	//LOG("CreateFont: " << faceName << " size=" << size << " weight=" << weight);
	PERFMETER_BEGIN(PERF_CREATEFONT);
	
	
	Vector<String> fonts;
	fonts = Split(faceName.ToString(), ",");
	if (!fonts.GetCount()) {
		PERFMETER_END(PERF_CREATEFONT);
		return -1;
	}
	
	bool found = false;
	int findex;
	int font_count = Font::GetFaceCount();
	for(int i = 0; i < fonts.GetCount(); i++) {
		String f = TrimBoth(fonts[i]);
		if (!f.GetCount()) continue;
		
		for(int j = 0; j < font_count; j++) {
			if (Font::GetFaceName(j) == fonts[i]) {
				findex = j;
				found = true;
				break;
			}
		}
	}
	
	
	Font fnt;
	
	if(!found) {
		if (faceName == "Times New Roman" || faceName == "Serif")
			fnt = Serif();
		else if (faceName == "courier")
			fnt = Monospace();
		else
			fnt = SansSerif();
	}
	else
		fnt.Face(findex);
	
	if(italic == FontStyleItalic ) {
		fnt.Italic(1);
	}
	
	// http://www.w3.org/TR/css3-fonts/#font-weight-prop
	if (weight >= 600) fnt.Bold(1);
	
	if (size)
		fnt.Height(size);
	
	if (decoration & FontDecorationLinethrough)
		fnt.Strikeout(1);
	
	if (decoration & FontDecorationUnderline)
		fnt.Underline(1);
	
	if(fm)
	{
		fm->ascent		= fnt.GetAscent();
		fm->descent		= fnt.GetDescent();
		fm->height		= fnt.GetAscent() + fnt.GetDescent();
		fm->x_height	= fnt.GetHeight();
	}
	
	
	for(int i = 0; i < _fonts.GetCount(); i++) {
		if (_fonts[i] == fnt) {
			PERFMETER_END(PERF_CREATEFONT);
			return i+1;
		}
	}
	
	int i = _fonts.GetCount();
	_fonts.Add(fnt);
	
	PERFMETER_END(PERF_CREATEFONT);
	return i+1;
}

void HtmlCtrl::DeleteFont(uint32 hFont) {
	
}

int HtmlCtrl::TextWidth(const WString& text, uint32 hFont) {
	if (hFont == 0) return 0;
	
	PERFMETER_BEGIN(PERF_TEXTWIDTH);
	
	hFont--;
	
	Size sz(0,0);
	sz = GetTextSize(text, _fonts[hFont]);
	
	PERFMETER_END(PERF_TEXTWIDTH);
	return sz.cx;
}

void HtmlCtrl::DrawText(Draw& hdc, const WString& text, uint32 hFont, RGBA color, const Position& pos, bool centered) {
	if (hFont == 0) return;
	hFont--;
	
	PERFMETER_BEGIN(PERF_DRAWTEXT);
	
	if (!centered) {
		if (color.a == 255) {
			hdc.DrawText(pos.x, pos.y, text, _fonts[hFont], color);
		} else {
			ImageDraw id(pos.width, pos.height);
			id.Alpha().DrawRect(0,0,pos.width,pos.height, GrayColor(color.a));
			id.DrawText(0, 0, text, _fonts[hFont], color);
			hdc.DrawImage(pos.x, pos.y, id);
		}
	} else {
		Font& fnt = _fonts[hFont];
		Size txt = GetTextSize(text, fnt);
		int x = pos.x - txt.cx/2 + 2;
		int y = pos.y - txt.cy/2 + 2;
		
		if (color.a == 255) {
			hdc.DrawText(x, y, text, _fonts[hFont], color);
		} else {
			ImageDraw id(pos.width, pos.height);
			id.Alpha().DrawRect(0,0,pos.width,pos.height, GrayColor(color.a));
			id.DrawText(0, 0, text, _fonts[hFont], color);
			hdc.DrawImage(x, y, id);
		}
	}
	PERFMETER_END(PERF_DRAWTEXT);
}

void HtmlCtrl::FillRect(Draw& hdc, const Position& pos, const RGBA color, const CssBorderRadius& radius)
{
	Panic("FillRect");
	Vector<Point> poly;
	
	
	if(radius.top_left_x.GetValue())
	{
		Arc(poly, pos.Left() + radius.top_left_x.GetValue(), pos.Top() + radius.top_left_x.GetValue(), radius.top_left_x.GetValue(), M_PI, M_PI * 3.0 / 2.0);
	} else
	{
		LineTo(poly, pos.Left(), pos.Top());
	}

	LineTo(poly, pos.Right() - radius.top_right_x.GetValue(), pos.Top());

	if(radius.top_right_x.GetValue())
	{
		Arc(poly, pos.Right() - radius.top_right_x.GetValue(), pos.Top() + radius.top_right_x.GetValue(), radius.top_right_x.GetValue(), M_PI * 3.0 / 2.0, 2.0 * M_PI);
	}

	LineTo(poly, pos.Right(), pos.Bottom() - radius.bottom_right_x.GetValue());

	if(radius.bottom_right_x.GetValue())
	{
		Arc(poly, pos.Right() - radius.bottom_right_x.GetValue(), pos.Bottom() - radius.bottom_right_x.GetValue(), radius.bottom_right_x.GetValue(), 0, M_PI / 2.0);
	}

	LineTo(poly, pos.Left() - radius.bottom_left_x.GetValue(), pos.Bottom());

	if(radius.bottom_left_x.GetValue())
	{
		Arc(poly, pos.Left() + radius.bottom_left_x.GetValue(), pos.Bottom() - radius.bottom_left_x.GetValue(), radius.bottom_left_x.GetValue(), M_PI / 2.0, M_PI);
	}
	
	hdc.DrawPolygon(poly, color);
}

int HtmlCtrl::PtPx(int pt) const {
	double dpi = 94; // TODO: get real from Draw::GetNativeDpi
	return (int) ((double) pt * dpi / 72.0);
}

int HtmlCtrl::GetDefaultFontSize() const {
	return 16;
}

String HtmlCtrl::GetDefaultFontName() const {
	//return Serif().GetFaceName();// "Times New Roman";
	//String s = Serif().GetFaceName();
	//LOG("font: " << s);
	//return s;
	return "Serif";
}

void HtmlCtrl::DrawListMarker(Draw& hdc, const ListMarker& marker) {
	PERFMETER_BEGIN(PERF_DRAWLISTMARKER);
	if(!marker.image.IsEmpty())
	{
		String baseurl = marker.baseurl;
		if (baseurl.GetCount() == 0) baseurl = doc.GetBaseUrl();
		ResourceCache& cache = GetResourceCache();
		int i = cache.FindObject(marker.image, marker.baseurl);
		//LOG("DrawListMarker DrawImage cache_id=" << i);
		if (i == -1) {
			PERFMETER_END(PERF_DRAWLISTMARKER);
			return;
		}
		Image img = cache.GetObject(i).GetImage();
		if (img) {
			hdc.DrawImage(marker.pos.x, marker.pos.y, img);
		}
	} else
	{
		String txt;
		switch(marker.marker_type)
		{
		case ListStyleTypeCircle:
			{
				DrawEllipseLine(hdc, marker.pos.x, marker.pos.y, marker.pos.width, marker.pos.height, 1, marker.color);
			}
			break;
		case ListStyleTypeDisc:
			{
				hdc.DrawEllipse(marker.pos.x, marker.pos.y, marker.pos.width, marker.pos.height, marker.color);
			}
			break;
		case ListStyleTypeSquare:
			{
				hdc.DrawRect(marker.pos.x, marker.pos.y, marker.pos.width, marker.pos.height, marker.color);
				/*if (marker.color.a == 255)
					;//hdc.DrawRect(marker.pos.x, marker.pos.y, marker.pos.width, marker.pos.height, marker.color);
				else if (marker.color.a > 0)
					Panic("todo");*/
			}
			break;
		case ListStyleTypeDecimal:
			txt = IntStr(marker.list_id) + ".";
			DrawText(hdc, txt.ToWString(), marker.font, marker.color, marker.pos, true);
			break;
			
		default:
			//do nothing
			break;
		}
	}
	PERFMETER_END(PERF_DRAWLISTMARKER);
}

void HtmlCtrl::LoadImage(const String& src, const String& baseurl, bool render_on_ready) {
	LOG("LoadImage " << src << " " << baseurl);
	int i = GetResourceCache().FindObject(src, baseurl);
	if (i == -1) {
		i = GetResourceCache().AddObject(src, baseurl);
		
		UrlParser bp, up, cp;
		bp.Parse(baseurl);
		up.Parse(src);
		cp.Parse(addr);
		
		ResourceHeader h;
		if (up.IsProtocolDefined()) {
			h.base_addr = up.GetFormattedBaseAddr();
			h.addr = up.GetFormattedAddr();
		} else {
			if (baseurl.IsEmpty()) {
				h.base_addr = cp.GetFormattedBaseAddr();
				h.addr = JoinUrl(cp.GetFormattedDirectory(), src);
			} else {
				h.base_addr = bp.GetFormattedBaseAddr();
				h.addr = JoinUrl(h.base_addr, src);
			}
		}
		GetResources().FillCookies(h.base_addr, h.cookies);
		
		GetResources().Query(h, THISBACK2(ImageReady, i, render_on_ready));
	}
}

void HtmlCtrl::ImageReady(ResourceQuery* res, int cache_id, bool render_on_ready) {
	CacheObject& obj = GetResourceCache().GetObject(cache_id);
	Image img = StreamRaster::LoadStringAny(res->GetData());
	obj.SetImage(img);
	ProcessAtLeast(render_on_ready ? RENDER : PAINT);
	Thread::Start(THISBACK(Process));
}

void HtmlCtrl::CssReady(ResourceQuery* res, int cache_id) {
	CacheObject& obj = GetResourceCache().GetObject(cache_id);
	obj.SetText(res->GetData());
	ProcessAtLeast(INIT);
	Thread::Start(THISBACK(Process));
}

void HtmlCtrl::GetImageSize(int cache_id, Size& sz) {
	PERFMETER_BEGIN(PERF_IMAGESIZEGET);
	
	ASSERT(cache_id != -1);
	ResourceCache& cache = GetResourceCache();
	Image bgbmp = GetResourceCache().GetObject(cache_id).GetImage();
	
	// If image is not downloaded
	if (!bgbmp) {
		sz.cx = 0;
		sz.cy = 0;
	} else {
		sz.cx = bgbmp.GetWidth();
		sz.cy = bgbmp.GetHeight();
	}
	
	PERFMETER_END(PERF_IMAGESIZEGET);
}

void HtmlCtrl::GetImageSize(const String& src, const String& baseurl_, Size& sz) {
	PERFMETER_BEGIN(PERF_IMAGESIZEFIND);
	
	//LOG("GetImageSize " << src << " " << baseurl);
	ResourceCache& cache = GetResourceCache();
	
	
	String baseurl = baseurl_;
	if (baseurl.GetCount() == 0)
		baseurl = doc.GetBaseUrl();
	
	int cache_id = cache.FindObject(src, baseurl);
	
	Image bgbmp = cache_id == -1 ? Image() : cache.GetObject(cache_id).GetImage();
	
	// If image is not downloaded
	if (!bgbmp) {
		sz.cx = 0;
		sz.cy = 0;
	} else {
		sz.cx = bgbmp.GetWidth();
		sz.cy = bgbmp.GetHeight();
	}
	
	
	PERFMETER_END(PERF_IMAGESIZEFIND);
}

void HtmlCtrl::DrawImage(Draw& hdc, const String& src, const String& baseurl, const Position& pos) {
	ResourceCache& cache = GetResourceCache();
	int cache_id = cache.FindObject(src, baseurl);
	Image img = cache_id == -1 ? Image() : cache.GetObject(cache_id).GetImage();
	hdc.DrawImage(pos.x, pos.y, pos.width, pos.height, img);
}

void HtmlCtrl::DrawBackground(Draw& hdc, const BackgroundPaint& bg) {
	PERFMETER_BEGIN(PERF_DRAWBG);
	PERFMETER_BEGIN(PERF_DRAWBG0);
	
	ResourceCache& cache = GetResourceCache();
	
	//LOG("DrawBackground " << bg.baseurl << " " << bg.image << " cache_id=" << bg.cache_id);
	
	
	Rect r0(bg.border_box.GetRect());
	Rect r1(bg.clip_box.GetRect());
	
	ASSERT(	r0.left		<= r1.left &&
			r0.right	>= r1.right &&
			r0.top		<= r1.top &&
			r0.bottom	>= r1.bottom);
	
	Size sz(r0.GetSize());
	ImageDraw id(sz);
	
	int trans_x = bg.position_x - r0.left;
	int trans_y = bg.position_y - r0.top;
	
	Color bg_color = White();
	if(bg.color.a)
		bg_color = bg.color;
	
	if (bg.border_radius.IsZero()) {
		id.DrawRect(sz, bg_color);
		id.Alpha().DrawRect(sz, GrayColor(bg.color.a));
	}
	else {
		id.Alpha().DrawRect(sz, Black());
		id.DrawRect(sz, bg_color);
		DrawRoundedRect(id.Alpha(), bg.border_box, bg.border_radius, White());
	}
	
	Image bgbmp = bg.cache_id == -1 ? Image() : cache.GetObject(bg.cache_id).GetImage();
	
	
	PERFMETER_END(PERF_DRAWBG0);
	PERFMETER_BEGIN(PERF_DRAWBG1);
	
	if (bgbmp) {
		if(bg.image_size.cx != bgbmp.GetWidth() || bg.image_size.cy != bgbmp.GetHeight())
		{
			Size rsz(bg.image_size.cx, bg.image_size.cy);
			bgbmp = CachedRescale(bgbmp, rsz);
		}
		
		int x, y, max_x, max_y, w, h, tmp;
		x = trans_x;
		y = trans_y;
		max_x = trans_x + r1.Width();
		max_y = trans_y + r1.Height();
		w = bgbmp.GetWidth();
		h = bgbmp.GetHeight();
		Rect trans_clip = RectC(r0.left - r1.left, r0.top - r1.top, r1.Width(), r1.Height());
		
		switch(bg.repeat)
		{
		case BackgroundRepeatNoRepeat:
			id.DrawImage(trans_x, trans_y, bgbmp);
			id.Alpha().DrawRect(trans_x, trans_y, w, h, GrayColor(255));
			break;
	
		case BackgroundRepeatRepeatX:
			while (x > 0) x -= w;
			for(; x < max_x; x += w) {
				id.DrawImage(x, y, bgbmp, trans_clip);
				id.Alpha().DrawRect(x, y, w, h, GrayColor(255));
			}
			break;
	
		case BackgroundRepeatRepeatY:
			while (y > 0) y -= h;
			for(; y < max_y; y += h) {
				id.DrawImage(x, y, bgbmp, trans_clip);
				id.Alpha().DrawRect(x, y, w, h, GrayColor(255));
			}
			break;
	
		case BackgroundRepeatRepeat:
			while (x > 0) x -= w;
			while (y > 0) y -= h;
			tmp = y;
			for(; x < max_x; x += w) {
				for(y = tmp; y < max_y; y += h) {
					id.DrawImage(x, y, bgbmp, trans_clip);
					id.Alpha().DrawRect(x, y, w, h, GrayColor(255));
				}
			}
			break;
		}

	}
	
	PERFMETER_END(PERF_DRAWBG1);
	PERFMETER_BEGIN(PERF_DRAWBG2);
	
	hdc.DrawImage(r0.left, r0.top, id);
	
	PERFMETER_END(PERF_DRAWBG2);
	PERFMETER_END(PERF_DRAWBG);
}

void HtmlCtrl::DrawBorders(Draw& hdc, const Borders& borders, const Position& draw_pos, bool root) {
	PERFMETER_BEGIN(PERF_DRAWBORDERS);
	
	Vector<Point> p;

	int bdr_top		= 0;
	int bdr_bottom	= 0;
	int bdr_left	= 0;
	int bdr_right	= 0;

	if(borders.top.width != 0 && borders.top.style > BorderStyleHidden)
	{
		bdr_top = (int) borders.top.width;
	}
	if(borders.bottom.width != 0 && borders.bottom.style > BorderStyleHidden)
	{
		bdr_bottom = (int) borders.bottom.width;
	}
	if(borders.left.width != 0 && borders.left.style > BorderStyleHidden)
	{
		bdr_left = (int) borders.left.width;
	}
	if(borders.right.width != 0 && borders.right.style > BorderStyleHidden)
	{
		bdr_right = (int) borders.right.width;
	}

	// draw right border
	if(bdr_right)
	{
		p.Clear();
		
		double r_top	= borders.radius.top_right_x;
		double r_bottom	= borders.radius.bottom_right_x;
		
		Vector<Point> area;
		if(r_top)
		{
			double end_angle	= 2 * M_PI;
			double start_angle	= end_angle - M_PI / 2.0  / ((double) bdr_top / (double) bdr_right + 1);

			AddPathArc(p,
				draw_pos.Right() - r_top,
				draw_pos.Top() + r_top,
				r_top - bdr_right,
				r_top - bdr_right + (bdr_right - bdr_top),
				end_angle,
				start_angle, true);

			AddPathArc(p,
				draw_pos.Right() - r_top,
				draw_pos.Top() + r_top,
				r_top,
				r_top,
				start_angle,
				end_angle, false);
		} else
		{
			p << Point(draw_pos.Right() - bdr_right, draw_pos.Top() + bdr_top);
			p << Point(draw_pos.Right(), draw_pos.Top());
		}

		if(r_bottom)
		{
			p << Point(draw_pos.Right(),	draw_pos.Bottom() - r_bottom);

			double start_angle	= 0;
			double end_angle	= start_angle + M_PI / 2.0  / ((double) bdr_bottom / (double) bdr_right + 1);

			AddPathArc(p,
				draw_pos.Right() - r_bottom,
				draw_pos.Bottom() - r_bottom,
				r_bottom,
				r_bottom,
				start_angle,
				end_angle, false);

			AddPathArc(p,
				draw_pos.Right() - r_bottom,
				draw_pos.Bottom() - r_bottom,
				r_bottom - bdr_right,
				r_bottom - bdr_right + (bdr_right - bdr_bottom),
				end_angle,
				start_angle, true);
		} else
		{
			p << Point(draw_pos.Right(),	draw_pos.Bottom());
			p << Point(draw_pos.Right() - bdr_right,	draw_pos.Bottom() - bdr_bottom);
		}
		
		hdc.DrawPolyline(p, borders.right.width, borders.right.color);
	}

	// draw bottom border
	if(bdr_bottom)
	{
		//set_color(cr, borders.bottom.color);
		p.Clear();
		
		double r_left	= borders.radius.bottom_left_x;
		double r_right	= borders.radius.bottom_right_x;

		if(r_left)
		{
			double start_angle	= M_PI / 2.0;
			double end_angle	= start_angle + M_PI / 2.0  / ((double) bdr_left / (double) bdr_bottom + 1);

			AddPathArc(p,
				draw_pos.Left() + r_left,
				draw_pos.Bottom() - r_left,
				r_left - bdr_bottom + (bdr_bottom - bdr_left),
				r_left - bdr_bottom,
				start_angle,
				end_angle, false);

			AddPathArc(p,
				draw_pos.Left() + r_left,
				draw_pos.Bottom() - r_left,
				r_left,
				r_left,
				end_angle,
				start_angle, true);
		} else
		{
			p << Point(draw_pos.Left(), draw_pos.Bottom());
			p << Point(draw_pos.Left() + bdr_left, draw_pos.Bottom() - bdr_bottom);
		}

		if(r_right)
		{
			p << Point(draw_pos.Right() - r_right,	draw_pos.Bottom());

			double end_angle	= M_PI / 2.0;
			double start_angle	= end_angle - M_PI / 2.0  / ((double) bdr_right / (double) bdr_bottom + 1);

			AddPathArc(p,
				draw_pos.Right() - r_right,
				draw_pos.Bottom() - r_right,
				r_right,
				r_right,
				end_angle,
				start_angle, true);

			AddPathArc(p,
				draw_pos.Right() - r_right,
				draw_pos.Bottom() - r_right,
				r_right - bdr_bottom + (bdr_bottom - bdr_right),
				r_right - bdr_bottom,
				start_angle,
				end_angle, false);
		} else
		{
			p << Point(draw_pos.Right() - bdr_right,	draw_pos.Bottom() - bdr_bottom);
			p << Point(draw_pos.Right(),	draw_pos.Bottom());
		}

		hdc.DrawPolyline(p, borders.bottom.width, borders.bottom.color);
		
	}

	// draw top border
	if(bdr_top)
	{
		p.Clear();
		
		double r_left	= borders.radius.top_left_x;
		double r_right	= borders.radius.top_right_x;

		if(r_left)
		{
			double end_angle	= M_PI * 3.0 / 2.0;
			double start_angle	= end_angle - M_PI / 2.0  / ((double) bdr_left / (double) bdr_top + 1);

			AddPathArc(p,
				draw_pos.Left() + r_left,
				draw_pos.Top() + r_left,
				r_left,
				r_left,
				end_angle,
				start_angle, true);

			AddPathArc(p,
				draw_pos.Left() + r_left,
				draw_pos.Top() + r_left,
				r_left - bdr_top + (bdr_top - bdr_left),
				r_left - bdr_top,
				start_angle,
				end_angle, false);
		} else
		{
			p << Point(draw_pos.Left(), draw_pos.Top());
			p << Point(draw_pos.Left() + bdr_left, draw_pos.Top() + bdr_top);
		}

		if(r_right)
		{
			p << Point(draw_pos.Right() - r_right,	draw_pos.Top() + bdr_top);

			double start_angle	= M_PI * 3.0 / 2.0;
			double end_angle	= start_angle + M_PI / 2.0  / ((double) bdr_right / (double) bdr_top + 1);

			AddPathArc(p,
				draw_pos.Right() - r_right,
				draw_pos.Top() + r_right,
				r_right - bdr_top + (bdr_top - bdr_right),
				r_right - bdr_top,
				start_angle,
				end_angle, false);

			AddPathArc(p,
				draw_pos.Right() - r_right,
				draw_pos.Top() + r_right,
				r_right,
				r_right,
				end_angle,
				start_angle, true);
		} else
		{
			p << Point(draw_pos.Right() - bdr_right,	draw_pos.Top() + bdr_top);
			p << Point(draw_pos.Right(),	draw_pos.Top());
		}

		hdc.DrawPolyline(p, borders.top.width, borders.top.color);
		
	}

	// draw left border
	if(bdr_left)
	{
		p.Clear();
		
		double r_top	= borders.radius.top_left_x;
		double r_bottom	= borders.radius.bottom_left_x;

		if(r_top)
		{
			double start_angle	= M_PI;
			double end_angle	= start_angle + M_PI / 2.0  / ((double) bdr_top / (double) bdr_left + 1);

			AddPathArc(p,
				draw_pos.Left() + r_top,
				draw_pos.Top() + r_top,
				r_top - bdr_left,
				r_top - bdr_left + (bdr_left - bdr_top),
				start_angle,
				end_angle, false);

			AddPathArc(p,
				draw_pos.Left() + r_top,
				draw_pos.Top() + r_top,
				r_top,
				r_top,
				end_angle,
				start_angle, true);
		} else
		{
			p << Point(draw_pos.Left() + bdr_left, draw_pos.Top() + bdr_top);
			p << Point(draw_pos.Left(), draw_pos.Top());
		}

		if(r_bottom)
		{
			p << Point(draw_pos.Left(),	draw_pos.Bottom() - r_bottom);

			double end_angle	= M_PI;
			double start_angle	= end_angle - M_PI / 2.0  / ((double) bdr_bottom / (double) bdr_left + 1);

			AddPathArc(p,
				draw_pos.Left() + r_bottom,
				draw_pos.Bottom() - r_bottom,
				r_bottom,
				r_bottom,
				end_angle,
				start_angle, true);

			AddPathArc(p,
				draw_pos.Left() + r_bottom,
				draw_pos.Bottom() - r_bottom,
				r_bottom - bdr_left,
				r_bottom - bdr_left + (bdr_left - bdr_bottom),
				start_angle,
				end_angle, false);
		} else
		{
			p << Point(draw_pos.Left(),	draw_pos.Bottom());
			p << Point(draw_pos.Left() + bdr_left,	draw_pos.Bottom() - bdr_bottom);
		}

		hdc.DrawPolyline(p, borders.left.width, borders.left.color);
	}
	
	PERFMETER_END(PERF_DRAWBORDERS);
}


void HtmlCtrl::TransformText(WString& text, TextTransform tt) {
	if (tt == TextTransformCapitalize)
		text = ToUpper(text.Left(1)) + ToLower(text.Mid(1));
	else if (tt == TextTransformUppercase)
		text = ToUpper(text);
	else if (tt == TextTransformLowercase)
		text = ToLower(text);
}

void HtmlCtrl::SetClip(Draw& d, const Position& pos, const BorderRadiuses& bdr_radius, bool valid_x, bool valid_y) {
	Position clip_pos = pos;
	Position client_pos;
	GetClientRect(client_pos);
	if(!valid_x)
	{
		clip_pos.x		= client_pos.x;
		clip_pos.width	= client_pos.width;
	}
	if(!valid_y)
	{
		clip_pos.y		= client_pos.y;
		clip_pos.height	= client_pos.height;
	}
	d.ClipOp(clip_pos.GetRect());
}

void HtmlCtrl::DelClip(Draw& d) {
	d.EndOp();
}

// Create GUI-widgets, like Button, EditString, DropList...
Element* HtmlCtrl::CreateElement(const String& tag_name, const StrMap& attributes, Document* doc) {
	LOG(tag_name);
	DUMPM(attributes);
	return NULL;
}

void HtmlCtrl::GetMediaFeatures(MediaFeatures& media) {
	Rect r = GetSize();
	Rect workarea		= GetWorkArea();
	media.type			= MediaTypeScreen;
	media.width			= r.Width();
	media.height		= r.Height();
	media.device_width	= workarea.Width();// Gdk::screen_width();
	media.device_height	= workarea.Height(); //Gdk::screen_height();
	media.color			= 8;
	media.monochrome	= 0;
	media.color_index	= 256;
	media.resolution	= 96; // TODO: dpi
}

void HtmlCtrl::SetCaption(const WString& caption) {
	WhenCaption(caption);
}

void HtmlCtrl::SetBaseUrl(const String& base_url) {
	UrlParser p;
	p.Parse(base_url);
	String base_url_parsed = p.GetBaseAddress() + ":" + p.GetPort();
	doc.SetBaseUrl(base_url_parsed);
}

void HtmlCtrl::Link(Document* doc, Element* el) {
	
}

void HtmlCtrl::OnAnchorClick(const String& url, Element* el) {
	WhenLoadAddress(url);
}

void HtmlCtrl::SetCursor(const String& cursor) {
	
}

void HtmlCtrl::ImportCss(String& text, const String& url, String& baseurl) {
	ResourceCache& cache = GetResourceCache();
	int i = cache.FindObject(url, baseurl);
	if (i >= 0) {
		CacheObject& obj = cache.GetObject(i);
		text = obj.GetText();
	}
	else {
		i = GetResourceCache().AddObject(text, baseurl);
		
		UrlParser bp, up, cp;
		bp.Parse(baseurl);
		up.Parse(url);
		cp.Parse(addr);
		
		ResourceHeader h;
		if (up.IsProtocolDefined()) {
			h.base_addr = up.GetFormattedBaseAddr();
			h.addr = up.GetFormattedAddr();
		} else {
			if (baseurl.IsEmpty()) {
				h.base_addr = cp.GetFormattedBaseAddr();
				h.addr = JoinUrl(cp.GetFormattedDirectory(), url);
			} else {
				h.base_addr = bp.GetFormattedBaseAddr();
				h.addr = JoinUrl(h.base_addr, url);
			}
		}
		GetResources().FillCookies(h.base_addr, h.cookies);
		
		GetResources().Query(h, THISBACK1(CssReady, i));
	}
}

void HtmlCtrl::GetClientRect(Position& client) const {
	Rect rcClient;
	rcClient		= Rect(GetSize());
	client.x		= rcClient.left;
	client.y		= rcClient.top;
	client.width	= rcClient.right - rcClient.left;
	client.height	= rcClient.bottom - rcClient.top;
}

		
	
void HtmlCtrl::DrawEllipse(Draw& hdc, int x, int y, int width, int height, const RGBA& color, double line_width) {
	DrawEllipseLine(hdc, x, y, width, height, line_width, color);
}

void HtmlCtrl::FillEllipse(Draw& hdc, int x, int y, int width, int height, const RGBA& color) {
	hdc.DrawEllipse(x, y, width, height, color);
}

void HtmlCtrl::RoundedRectangle(Draw& hdc, const Position &pos, const BorderRadiuses &radius, RGBA color) {
	Vector<Point> poly;
	if(radius.top_left_x)
	{
		Arc(poly, pos.Left() + radius.top_left_x, pos.Top() + radius.top_left_x, radius.top_left_x, M_PI, M_PI * 3.0 / 2.0);
	} else
	{
		LineTo(poly, pos.Left(), pos.Top());
	}

	LineTo(poly, pos.Right() - radius.top_right_x, pos.Top());

	if(radius.top_right_x)
	{
		Arc(poly, pos.Right() - radius.top_right_x, pos.Top() + radius.top_right_x, radius.top_right_x, M_PI * 3.0 / 2.0, 2.0 * M_PI);
	}

	LineTo(poly, pos.Right(), pos.Bottom() - radius.bottom_right_x);

	if(radius.bottom_right_x)
	{
		Arc(poly, pos.Right() - radius.bottom_right_x, pos.Bottom() - radius.bottom_right_x, radius.bottom_right_x, 0, M_PI / 2.0);
	}

	LineTo(poly, pos.Left() - radius.bottom_left_x, pos.Bottom());

	if(radius.bottom_left_x)
	{
		Arc(poly, pos.Left() + radius.bottom_left_x, pos.Bottom() - radius.bottom_left_x, radius.bottom_left_x, M_PI / 2.0, M_PI);
	}
	
	hdc.DrawPolygon(poly, color);
}






























BrowserCtrl::BrowserCtrl() {
	/*AddButton(prev, Images::previous(), THISBACK(Previous));
	AddButton(next, Images::next(), THISBACK(Next));
	AddButton(home, Images::home(), THISBACK(Home));
	AddButton(refresh, Images::refresh(), THISBACK(Refresh));
	AddButton(stop, Images::stop(), THISBACK(Stop));*/
	
	Add(addr.HSizePos(button_count * button_h, 0).TopPos(0, button_h));
	addr.WhenEnter << THISBACK(Go);
	
	Add(html.HSizePos().VSizePos(button_h));
	html.WhenLoadAddress << THISBACK(SetAddress);
}

void BrowserCtrl::AddButton(Button& b, Image img, Callback cb) {
	int x = button_count++ * button_h;
	Add(b.LeftPos(x, button_h).TopPos(0, button_h));
	b.SetImage(img);
	b <<= cb;
}

void BrowserCtrl::Previous() {
	
}

void BrowserCtrl::Next() {
	
}

void BrowserCtrl::Home() {
	
}

void BrowserCtrl::Refresh() {
	
}

void BrowserCtrl::Stop() {
	
}

void BrowserCtrl::Go() {
	String addr = this->addr.GetData();
	if (addr.IsEmpty()) return;
	
	UrlParser p;
	p.Parse(addr);
	
	ResourceHeader h;
	h.base_addr = p.GetFormattedBaseAddr();
	h.addr = p.GetFormattedAddr();
	GetResources().FillCookies(h.base_addr, h.cookies);
	
	GetResources().Query(h, THISBACK(SetResourcePage));
}

void BrowserCtrl::SetResourcePage(ResourceQuery* res) {
	if (res->GetStatusCode() == 200) {
		if (res->IsRedirect())
			PostCallback(THISBACK1(SetAddressText, res->GetRedirection()));
		html.SetHtml(res->GetData(), res->GetAddr());
	}
	else {
		String response = "Error code: " + IntStr(res->GetStatusCode());
		html.SetHtml(response, res->GetAddr());
	}
}

NAMESPACE_LAYOUT_END
