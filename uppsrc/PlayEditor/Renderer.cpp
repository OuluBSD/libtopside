#include "PlayEditor.h"

NAMESPACE_TOPSIDE_BEGIN




ScriptLayout::ScriptLayout() {
	regular_h = 20;
	h1_h = 30;
	h2_h = 40;
	
	regular = SansSerif(regular_h);
	h1 = SansSerif(h1_h);
	h2 = SansSerif(h2_h);
	
}

int ScriptLayout::GetOffset(int time) const {
	time = max(time, 0);
	
	if (objects.IsEmpty())
		return 0;
	
	for (const LayoutObject& o : objects) {
		int begin = o.time;
		int end = begin + o.duration;
		if (o.col == LayoutObject::COL_NAME)
			continue;
		
		if (end < time)
			continue;
		else if (time >= begin && time < end) {
			double f = (double)(time - begin) / (double)o.duration;
			ASSERT(f >= 0.0 && f <= 1.0);
			int offset = o.y + (int)(o.txt_sz.cy * f);
			ASSERT(o.txt_sz.cy > 0);
			return offset;
		}
		else if (time > begin)
			return o.y + o.txt_sz.cy;
		else if (time < begin) {
			double f = (double)time / (double)begin;
			ASSERT(f >= 0.0 && f <= 1.0);
			int offset = (int)(o.txt_sz.cy * f);
			ASSERT(o.txt_sz.cy > 0);
			return offset;
		}
	}
	
	ASSERT(0);
	return 0;
}











PlayRenderer::PlayRenderer(PlayScript& s) : script(s) {
	//frame_sz = Size(1280,720);
	frame_sz = Size(640,360);
	
	
}

void PlayRenderer::Seek(int i) {
	time = i;
}

Image PlayRenderer::Render(PlayRendererConfig& cfg) {
	
	if (layout.objects.IsEmpty())
		RenderScriptLayout();
	
	ImageBuffer ib(frame_sz);
	
	if (cfg.render_bg) {
		Size bg_size(320, 180);
		Image bg = LiquidBokeh(bg_size, time * 0.001);
		bg = RescaleFilter(bg, frame_sz, FILTER_BSPLINE);
		CopyImage(ib, Point(0,0), bg);
	}
	else {
		RGBA black = Black();
		for (RGBA& i : ib) i = black;
	}
	
	Image script = RenderScript();
	
	CopyImageTransparent(ib, Point(0,0), script, Black());
	
	return ib;
}

void PlayRenderer::CopyImage(ImageBuffer& ib, Point pt, Image img) {
	const RGBA* src = img.Begin();
	RGBA* dst = ib.Begin();
	Size dsz = ib.GetSize();
	Size ssz = img.GetSize();
	int wlimit = min(pt.x + img.GetWidth(), dsz.cx);
	for (int y = pt.y, y0 = 0; y < dsz.cy; y++, y0++) {
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* sit = src + y0 * ssz.cx;
		for (int x = pt.x; x < wlimit; x++) {
			*dit++ = *sit++;
		}
	}
}

void PlayRenderer::CopyImageTransparent(ImageBuffer& ib, Point pt, Image img, Color key) {
	RGBA transparent = key;
	const RGBA* src = img.Begin();
	RGBA* dst = ib.Begin();
	Size dsz = ib.GetSize();
	Size ssz = img.GetSize();
	int wlimit = min(pt.x + img.GetWidth(), dsz.cx);
	for (int y = pt.y, y0 = 0; y < dsz.cy; y++, y0++) {
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* sit = src + y0 * ssz.cx;
		for (int x = pt.x; x < wlimit; x++) {
			RGBA r = *sit++;
			if (r != transparent)
				*dit = r;
			dit++;
		}
	}
}

Image PlayRenderer::RenderScript() {
	int pad = 10;
	Size frame_sz = this->frame_sz;
	frame_sz.cx += 2 * pad;
	frame_sz.cy += 2 * pad;
	
	ImageDraw id(frame_sz);
	
	id.DrawRect(frame_sz, Black());
	
	int y_offset = layout.GetOffset(time);
	int y_begin = y_offset - frame_sz.cy / 2;
	int y_end = y_offset + frame_sz.cy / 2;
	
	for (const LayoutObject& o : layout.objects) {
		int a = o.y;
		int b = o.y + o.txt_sz.cy;
		
		if ((a >= y_begin && a <= y_end) ||
			(b >= y_begin && b <= y_end)) {
			int dst_x = 0;
			int dst_y = o.y - y_begin;
			
			if (o.col == LayoutObject::COL_NAME) {
				
			}
			else if (o.col == LayoutObject::COL_TXT) {
				dst_x += layout.max_name_w;
			}
			else if (o.col == LayoutObject::COL_CENTER) {
				dst_x += layout.max_name_w / 2;
			}
			
			Font fnt;
			if      (o.fnt == 0) fnt = layout.regular;
			else if (o.fnt == 1) fnt = layout.h1;
			else if (o.fnt == 2) fnt = layout.h2;
			
			Color clr = White();
			
			if (y_offset >= a && y_offset < b)
				clr = Red();
			
			id.DrawText(dst_x, dst_y, o.txt, fnt, clr);
		}
	}
	
	return id;
}


void PlayRenderer::RenderScriptLayout() {
	layout.Clear();
	
	
	int y = 0;
	for (const PlayPart& part : script.parts) {
		for (const PlaySection& sect : part.sections) {
			for (const PlayLine& line : sect.dialog.lines) {
				if (line.sents.IsEmpty())
					continue;
				
				if (line.is_narration) {
					LayoutObject& o = layout.objects.Add();
					o.y = y;
					o.col = LayoutObject::COL_CENTER;
					o.txt = line.id.name.ToString();
					o.txt_sz = GetTextSize(o.txt, layout.regular);
				}
				else {
					LayoutObject& name = layout.objects.Add();
					name.y = y;
					name.col = LayoutObject::COL_NAME;
					name.txt = line.id.name.ToString();
					name.txt_sz = GetTextSize(name.txt, layout.regular);
					
					layout.max_name_w = max(layout.max_name_w, name.txt_sz.cx);
					
					for (const PlaySentence& sent : line.sents) {
						LayoutObject& l = layout.objects.Add();
						l.y = y;
						l.col = LayoutObject::COL_TXT;
						l.txt = sent.GetData();
						l.txt_sz = GetTextSize(l.txt, layout.regular);
						l.time = sent.tmp_time;
						l.duration = sent.tmp_duration;
						
						y += layout.regular_h;
					}
				}
			}
		}
	}
	
	
}

/*Image PlayRenderer::RenderText(int& time_y) {
	Size txt_frame_sz(frame_sz.cx + frame_sz.cy + 60);
	ImageDraw id(txt_frame_sz);
	id.DrawRect(txt_frame_sz, Black());
	
	int sti = script.FindSubtitle(time);
	
	if (sti < 0) return id;
	
	const PlayScript::Subtitle& st = script.Get(sti);
	
	int font_h = 20;
	Font fnt = SansSerif(font_h);
	Size txt_sz = GetTextSize(st.str, fnt);
	int x = 100;
	int y = (frame_sz.cy - txt_sz.cy) / 2;
	id.DrawText(x+2, y+2, st.str, fnt, Black());
	id.DrawText(x, y, st.str, fnt, White());
	
	if (sti+1 < script.GetSubtitleCount()) {
		const PlayScript::Subtitle& st1 = script.Get(sti+1);
		int st_len = st1.time - st.time;
		double factor = (double)(time_y - st.time) / (double)st_len;
		time_y = y + factor * txt_sz.cy;
	}
	else
		time_y = y;
	
	for (int i = sti-1; i >= 0; i--) {
		
	}
	
	return id;
}*/


NAMESPACE_TOPSIDE_END
