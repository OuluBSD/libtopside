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

Font ScriptLayout::GetFont(int fnt) const {
	switch (fnt) {
		case LayoutObject::FNT_H1: return h1;
		case LayoutObject::FNT_H2: return h2;
		default:
		case LayoutObject::FNT_REGULAR: return regular;
	}
}

int ScriptLayout::GetOffset(int time) const {
	time = max(time, 0);
	
	if (objects.IsEmpty())
		return 0;
	
	const LayoutObject* prev = 0;
	for (const LayoutObject& o : objects) {
		int begin = o.time;
		int end = begin + o.duration;
		if (o.col == LayoutObject::COL_NAME)
			continue;
		
		ASSERT(begin >= 0);
		if (end < time)
			;
		else if (time >= begin && time < end) {
			double f = (double)(time - begin) / (double)o.duration;
			ASSERT(f >= 0.0 && f <= 1.0);
			int offset = o.y + (int)(o.txt_sz.cy * f);
			ASSERT(o.txt_sz.cy > 0);
			return offset;
		}
		else if (time > begin)
			return o.y + o.txt_sz.cy;
		else if (time < begin && !prev) {
			double f = (double)time / (double)begin;
			ASSERT(f >= 0.0 && f <= 1.0);
			int offset = (int)(o.y * f);
			return offset;
		}
		else if (time < begin && prev) {
			int prev_end = prev->time + prev->duration;
			int duration = begin - prev_end;
			ASSERT(duration > 0);
			double f = (double)(time - prev_end) / (double)duration;
			ASSERT(f >= 0.0 && f <= 1.0);
			int y0 = prev->y + prev->txt_sz.cy;
			int y1 = o.y;
			int h = y1 - y0;
			ASSERT(h >= 0);
			int offset = y0 + (int)(h * f);
			ASSERT(o.txt_sz.cy > 0);
			return offset;
		}
		
		
		prev = &o;
	}
	
	const LayoutObject& last = objects.Top();
	return last.y + last.txt_sz.cy;
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
		int i = script.FindSubtitle(time);
		OnlineAverage clr0[3];
		{
			int a = max(0, i - fps * 2);
			int b = min(script.GetSubtitleCount(), i + fps * 2);
			for(int i = a; i < b; i++) {
				const PlayScript::Subtitle& st = script.Get(i);
				clr0[0].Add(st.clr.GetR());
				clr0[1].Add(st.clr.GetG());
				clr0[2].Add(st.clr.GetB());
			}
		}
		
		Color a = Color(clr0[0].GetMean(), clr0[1].GetMean(), clr0[2].GetMean());
		Color b = TransformHue(a, 90);
		Size bg_size(320, 180);
		Image bg = LiquidBokeh(bg_size, time * 0.001, a, b);
		bg = RescaleFilter(bg, frame_sz, FILTER_BSPLINE);
		CopyImage(ib, Point(0,0), bg);
	}
	else {
		RGBA black = Black();
		for (RGBA& i : ib) i = black;
	}
	
	Image script = RenderScript();
	
	if (!cfg.render_blur && !cfg.render_text_bending) {
		CopyImageTransparent(ib, Point(0,0), script, Black());
	}
	else {
		float bend = 0;
		if (cfg.render_text_bending)
			bend = M_PI / 4.0 * 0.5;
		int max_blur = 0;
		if (cfg.render_blur)
			max_blur = 5;
		CopyImageTransparentBentBlurred(ib, Point(0,0), script, Black(), +bend, -bend, max_blur);
	}
	
	if (cfg.render_notes) {
		Image notes = LoadNotes();
		if (!notes.IsEmpty()) {
			CopyImageSemiTransparentDark(ib, Point(0,0), notes, 256-32);
		}
	}
	
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
	for (int y = pt.y, y0 = 0; y < dsz.cy && y0 < ssz.cy; y++, y0++) {
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* sit = src + y0 * ssz.cx;
		for (int x = pt.x, x0 = 0; x < wlimit && x0 < ssz.cx; x++) {
			RGBA r = *sit++;
			if (r != transparent)
				*dit = r;
			dit++;
		}
	}
}

void PlayRenderer::CopyImageSemiTransparent(ImageBuffer& ib, Point pt, Image img, Color key, int alpha) {
	RGBA transparent = key;
	const RGBA* src = img.Begin();
	RGBA* dst = ib.Begin();
	Size dsz = ib.GetSize();
	Size ssz = img.GetSize();
	int wlimit = min(pt.x + img.GetWidth(), dsz.cx);
	for (int y = pt.y, y0 = 0; y < dsz.cy && y0 < ssz.cy; y++, y0++) {
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* sit = src + y0 * ssz.cx;
		for (int x = pt.x, x0 = 0; x < wlimit && x0 < ssz.cx; x++) {
			RGBA r = *sit++;
			if (r != transparent) {
				*dit = r;
			}
			else {
				dit->r = (((int)dit->r * (255-alpha)) + ((int)sit->r * alpha)) / 255;
				dit->g = (((int)dit->g * (255-alpha)) + ((int)sit->g * alpha)) / 255;
				dit->b = (((int)dit->b * (255-alpha)) + ((int)sit->b * alpha)) / 255;
			}
			dit++;
		}
	}
}

void PlayRenderer::CopyImageSemiTransparent(ImageBuffer& ib, Point pt, Image img, int alpha) {
	const RGBA* src = img.Begin();
	RGBA* dst = ib.Begin();
	Size dsz = ib.GetSize();
	Size ssz = img.GetSize();
	int wlimit = min(pt.x + img.GetWidth(), dsz.cx);
	for (int y = pt.y, y0 = 0; y < dsz.cy && y0 < ssz.cy; y++, y0++) {
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* sit = src + y0 * ssz.cx;
		for (int x = pt.x, x0 = 0; x < wlimit && x0 < ssz.cx; x++) {
			RGBA r = *sit++;
			dit->r = (((int)dit->r * (255-alpha)) + ((int)sit->r * alpha)) / 255;
			dit->g = (((int)dit->g * (255-alpha)) + ((int)sit->g * alpha)) / 255;
			dit->b = (((int)dit->b * (255-alpha)) + ((int)sit->b * alpha)) / 255;
			dit++;
		}
	}
}

void PlayRenderer::CopyImageSemiTransparentDark(ImageBuffer& ib, Point pt, Image img, int base_alpha) {
	const RGBA* src = img.Begin();
	RGBA* dst = ib.Begin();
	Size dsz = ib.GetSize();
	Size ssz = img.GetSize();
	int wlimit = min(pt.x + img.GetWidth(), dsz.cx);
	for (int y = pt.y, y0 = 0; y < dsz.cy && y0 < ssz.cy; y++, y0++) {
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* sit = src + y0 * ssz.cx;
		for (int x = pt.x, x0 = 0; x < wlimit && x0 < ssz.cx; x++) {
			RGBA r = *sit++;
			int alpha = (r.r + r.g + r.b) / 3;
			alpha = base_alpha + (alpha * (255 - base_alpha)) / 255;
			dit->r = (((int)dit->r * (255-alpha)) + ((int)sit->r * alpha)) / 255;
			dit->g = (((int)dit->g * (255-alpha)) + ((int)sit->g * alpha)) / 255;
			dit->b = (((int)dit->b * (255-alpha)) + ((int)sit->b * alpha)) / 255;
			dit++;
		}
	}
}

void PlayRenderer::CopyImageSemiTransparentDark(ImageBuffer& ib, Point pt, Image img, int gray, int alpha) {
	const RGBA* src = img.Begin();
	RGBA* dst = ib.Begin();
	Size dsz = ib.GetSize();
	Size ssz = img.GetSize();
	int wlimit = min(pt.x + img.GetWidth(), dsz.cx);
	for (int y = pt.y, y0 = 0; y < dsz.cy && y0 < ssz.cy; y++, y0++) {
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* sit = src + y0 * ssz.cx;
		for (int x = pt.x, x0 = 0; x < wlimit && x0 < ssz.cx; x++) {
			RGBA r = *sit++;
			int av = (r.r + r.g + r.b) / 3;
			if (av < gray) {
				dit->r = (((int)dit->r * (255-alpha)) + ((int)sit->r * alpha)) / 255;
				dit->g = (((int)dit->g * (255-alpha)) + ((int)sit->g * alpha)) / 255;
				dit->b = (((int)dit->b * (255-alpha)) + ((int)sit->b * alpha)) / 255;
			}
			else {
				*dit = r;
			}
			dit++;
		}
	}
}

void PlayRenderer::CopyImageTransparentBentBlurred(ImageBuffer& ib, Point pt, Image img, Color key, float top_bend, float bottom_bend, int max_blur) {
	RGBA transparent = key;
	const RGBA* src = img.Begin();
	RGBA* dst = ib.Begin();
	Size dsz = ib.GetSize();
	Size ssz = img.GetSize();
	int wlimit = min(pt.x + img.GetWidth(), dsz.cx);
	float bend_range = top_bend - bottom_bend;
	bool use_gauss = true;
	bool is_gauss = use_gauss && max_blur > 0;
	Vector<float> kernel;
	for (int y = pt.y, y0 = 0; y < dsz.cy; y++, y0++) {
		if (y < 0) continue;
		float fy = (float)y0 / (float)ssz.cy;
		float fbend = cos(top_bend - fy * bend_range);
		float fyblur = fabsf(fy - 0.5f) * 2.0f;
		float fyopacity = 1.0f - fyblur * 0.9f ;
		ASSERT(fbend >= 0.0);
		RGBA* dit = dst + y * dsz.cx;
		dit += pt.x;
		const RGBA* srow = src + y0 * ssz.cx;
		int edge;
		float blur = max(0.0f, max_blur * fyblur - 0.2f);
		//float blur = max_blur * fyblur;
		if (is_gauss) {
			float m = fmodf(blur, 1.0);
			
			if (m == 0)
				edge = 1 + (int)blur * 2;
			else
				edge = 3 + (int)blur * 2;
			ASSERT(edge != 0);
			
			int c = gaussians.GetCount();
			if (c <= edge)
				gaussians.SetCount(edge+1);
			for (int g = c; g <= edge; g++) {
				if (g < 3 || g % 2 != 1) continue;
				
				Vector<float>& kernel = gaussians[g];
				int area = g * g;
				kernel.SetCount(area);
				float* k = kernel.Begin();
				for(int i = 0; i < g; i++) {
					float x = (cos((float)i / (float)(g-1) * 2 * M_PI) - 1.0) * -0.5;
					for(int j = 0; j < g; j++) {
						float y = (cos((float)j / (float)(g-1) * 2 * M_PI) - 1.0) * -0.5;
						float v = x * y;
						ASSERT(v >= 0.f && v <= 1.f);
						*k++ = v;
					}
				}
			}
			
			if (edge == 1) {
				kernel.SetCount(1);
				kernel[0] = 1;
			}
			else {
				const Vector<float>& from = gaussians[edge];
				if (m == 0)
					kernel <<= from;
				else {
					kernel.SetCount(from.GetCount());
					const float* f = from.Begin();
					float* t = kernel.Begin();
					int edge_2 = edge / 2;
					float begin = m;
					float step = (1.0f - m) / (float)edge_2;
					float ymul = begin;
					for(int i = 0; i < edge; i++) {
						float xmul = begin;
						for(int j = 0; j < edge; j++) {
							float mul = xmul * ymul;
							float val = *f++ * mul;
							*t++ = val;
							xmul += j < edge_2 ? step : -step;
							ASSERT(xmul > -step && xmul <= 1.0001f);
						}
						ymul += i < edge_2 ? step : -step;
						ASSERT(ymul > -step && ymul <= 1.0001f);
					}
					ASSERT(t == kernel.End());
				}
			}
		}
		
		for (int x = pt.x, x0 = 0; x < wlimit; x++, x0++) {
			if (x < 0) continue;
			float fx = (float)x0 / (float)ssz.cx;
			fx = fx - 0.5f;
			fx /= fbend;
			fx = 0.5f + fx;
			fx *= ssz.cx;
			int x1 = (int)fx;
			
			float pixelf = fmodf(fx, 1.0);
			if (x1 >= 0 && x1 < ssz.cx) {
				RGBA a, b;
				int x2 = x1+1 < ssz.cx ? x1+1 : x1;
				
				if (max_blur == 0) {
					a = *(srow + x1);
					b = *(srow + x2);
				}
				else if (is_gauss) {
					a = GetGaussianBlurTransparent(x1, y0, src, ssz, kernel, edge, transparent);
					b = GetGaussianBlurTransparent(x2, y0, src, ssz, kernel, edge, transparent);
				}
				else {
					a = GetBoxBlurredTransparent(x1, y0, src, ssz, blur, transparent);
					b = GetBoxBlurredTransparent(x2, y0, src, ssz, blur, transparent);
				}
				
				if (a == transparent) a.a = 0;
				if (b == transparent) b.a = 0;
				RGBA r;
				r.r = (1.f - pixelf) * a.r + (pixelf * b.r);
				r.g = (1.f - pixelf) * a.g + (pixelf * b.g);
				r.b = (1.f - pixelf) * a.b + (pixelf * b.b);
				r.a = (1.f - pixelf) * a.a + (pixelf * b.a);
				pixelf = r.a / 255.f * fyopacity;
				if (pixelf == 1.0f)
					*dit = r;
				else if (r.a != 0) {
					a = *dit;
					r.r = (1.f - pixelf) * a.r + (pixelf * r.r);
					r.g = (1.f - pixelf) * a.g + (pixelf * r.g);
					r.b = (1.f - pixelf) * a.b + (pixelf * r.b);
					r.a = (1.f - pixelf) * a.a + (pixelf * r.a);
					*dit = r;
				}
			}
			dit++;
		}
	}
}

RGBA PlayRenderer::GetBoxBlurredTransparent(int x0, int y0, const RGBA* src, const Size& ssz, float max_blurf, const RGBA& transparent) {
	int max_blur = max_blurf;
	float edge_factor = fmodf(max_blurf, 1.0);
	if (edge_factor > 0.0f)
		max_blur++;
	else
		edge_factor = 1.0f;
	
	float edge = 1.0f + 2 * max_blurf;
	float area = edge * edge;
	float area_mul = 1.0f / area;
	
	float r = 0, g = 0, b = 0, a = 0;
	int ybegin = max(     0, y0 - max_blur);
	int yend   = min(ssz.cy, y0 + max_blur + 1);
	int xbegin = max(     0, x0 - max_blur);
	int xend   = min(ssz.cx, x0 + max_blur + 1);
	int yedge = y0 + max_blur;
	int xedge = x0 + max_blur;
	const RGBA* row = src + ybegin * ssz.cx + xbegin;
	float alpha_samples = 0.0f;
	for (int y = ybegin; y < yend; y++) {
		const RGBA* it = row;
		for (int x = xbegin; x < xend; x++) {
			if (*it != transparent) {
				float weight = 1.0f;
				if (x == xbegin || x == xedge || y == ybegin || y == yedge)
					weight = edge_factor;
				r += it->r * weight;
				g += it->g * weight;
				b += it->b * weight;
				a += it->a * weight;
				alpha_samples += weight;
			}
			it++;
		}
		row += ssz.cx;
	}
	
	RGBA ret;
	if (alpha_samples == 0) {
		ret.r = ret.g = ret.b = ret.a = 0;
	}
	else {
		float mul = 1.0f / (float)alpha_samples;
		int br = r * mul;
		int bg = g * mul;
		int bb = b * mul;
		int ba = min(255, (int)(a * area_mul)); // small error due to corner case (literally)
		ASSERT(br >= 0 && br <= 255);
		ASSERT(bg >= 0 && bg <= 255);
		ASSERT(bb >= 0 && bb <= 255);
		ASSERT(ba >= 0 && ba <= 255);
		ret.r = br;
		ret.g = bg;
		ret.b = bb;
		ret.a = ba;
	}
	return ret;
}

RGBA PlayRenderer::GetGaussianBlurTransparent(int x0, int y0, const RGBA* src, const Size& ssz, const Vector<float>& kernel, int edge, const RGBA& transparent) {
	float r = 0, g = 0, b = 0, a = 0;
	ASSERT(edge % 2 == 1);
	int edge_2 = edge / 2;
	int ybegin = max(     0, y0 - edge_2);
	int yend   = min(ssz.cy, y0 + edge_2 + 1);
	int xbegin = max(     0, x0 - edge_2);
	int xend   = min(ssz.cx, x0 + edge_2 + 1);
	int yedge = y0 + edge_2;
	int xedge = x0 + edge_2;
	int xoff = xbegin - (x0 - edge_2);
	int yoff = ybegin - (y0 - edge_2);
	const float* krow = kernel.Begin() + yoff * edge + xoff;
	const RGBA* row = src + ybegin * ssz.cx + xbegin;
	float alpha_samples = 0.0f;
	for (int y = ybegin; y < yend; y++) {
		const RGBA* it = row;
		const float* kit = krow;
		for (int x = xbegin; x < xend; x++) {
			float weight = *kit;
			if (*it != transparent) {
				r += it->r * weight;
				g += it->g * weight;
				b += it->b * weight;
				a += it->a * weight;
			}
			alpha_samples += weight;
			it++;
			kit++;
		}
		row += ssz.cx;
		krow += edge;
	}
	
	RGBA ret;
	if (alpha_samples == 0) {
		ret.r = ret.g = ret.b = ret.a = 0;
	}
	else {
		float mul = 1.0f / (float)alpha_samples;
		int br = r * mul;
		int bg = g * mul;
		int bb = b * mul;
		int ba = a * mul;
		ASSERT(br >= 0 && br <= 255);
		ASSERT(bg >= 0 && bg <= 255);
		ASSERT(bb >= 0 && bb <= 255);
		ASSERT(ba >= 0 && ba <= 255);
		ret.r = br;
		ret.g = bg;
		ret.b = bb;
		ret.a = ba;
	}
	return ret;
}

Image PlayRenderer::RenderScript() {
	int pad = 10;
	Size frame_sz = this->frame_sz;
	frame_sz.cx += 2 * pad;
	frame_sz.cy += 2 * pad;
	
	ImageDraw id(frame_sz);
	
	id.DrawRect(frame_sz, Black());
	
	//int y_offset = time * 0.020;
	int y_offset = layout.GetOffset(time);
	int y_begin = y_offset - frame_sz.cy / 2;
	int y_end = y_offset + frame_sz.cy / 2;
	
	int indent = layout.max_name_w + 10;
	
	//LOG("time: " << time << ", y-offset: " << y_offset);
	
	for (const LayoutObject& o : layout.objects) {
		int a = o.y;
		int b = o.y + o.txt_sz.cy;
		
		if ((a >= y_begin && a <= y_end) ||
			(b >= y_begin && b <= y_end)) {
			int dst_x = pad;
			int dst_y = o.y - y_begin + o.frame_y;
			
			String txt = o.txt;
			Image img = o.img;
			if (o.col == LayoutObject::COL_NAME) {
				dst_x += layout.max_name_w - o.txt_sz.cx;
				txt += ":";
			}
			else if (o.col == LayoutObject::COL_TXT) {
				dst_x += indent;
				if (txt == "-")
					txt.Clear();
			}
			else if (o.col == LayoutObject::COL_CENTER) {
				dst_x += (frame_sz.cx - o.txt_sz.cx) / 2;
			}
			
			if (txt.GetCount()) {
				Font fnt;
				if      (o.fnt == 0) fnt = layout.regular;
				else if (o.fnt == 1) fnt = layout.h1;
				else if (o.fnt == 2) fnt = layout.h2;
				
				int alpha = 64;
				if (y_offset >= a && y_offset < b) {
					//alpha = 128;
					alpha = 256-64;
					//clr = Color(151, 170, 255);
					//fnt.Bold();
				}
					
				Color clr = Blend(o.clr, White(), alpha);
				
				id.DrawText(dst_x+2, dst_y+2, txt, fnt, GrayColor(1));
				id.DrawText(dst_x+1, dst_y+1, txt, fnt, GrayColor(10));
				id.DrawText(dst_x, dst_y, txt, fnt, clr);
			}
			
			if (!img.IsEmpty()) {
				id.DrawImage(dst_x, dst_y, img);
			}
		}
	}
	
	return id;
}


void PlayRenderer::RenderScriptLayout() {
	layout.Clear();
	
	layout.regular_h = frame_sz.cy * 0.040;
	layout.h1_h = frame_sz.cy * 0.055;
	layout.h2_h = frame_sz.cy * 0.070;
	
	layout.regular = SansSerif(layout.regular_h);
	layout.h1 = SansSerif(layout.h1_h);
	layout.h2 = SansSerif(layout.h2_h);
	
	
	int narrator_padding = frame_sz.cy * 0.040;
	int metatext_padding = frame_sz.cy * 0.08;
	int max_width = frame_sz.cx;
	int max_img_width = max_width * 0.333;
	
	
	int y = 0;
	
	Vector<MetaText*> intro_metatext;
	intro_metatext << &script.title << &script.description << &script.disclaimer << &script.author;
	
	LayoutObject* prev = 0;
	
	const PlayScript::Actor& meta_actor = script.tmp_actors.Get("Meta");
	
	for (const MetaText* t : intro_metatext) {
		const MetaText& mt = *t;
		
		int i = 0;
		for (const PlaySentence& sent : mt.sents) {
			if (i == 0) {
				Image img;
				if (t == &script.title)
					img = script.logo;
				else if (t == &script.disclaimer)
					img = script.subscribe;
				else if (t == &script.author)
					img = script.author_img;
				
				if (!img.IsEmpty()) {
					Size sz = img.GetSize();
					
					if (sz.cx > max_img_width) {
						double ratio = (double)max_img_width / (double)sz.cx;
						sz.cx = max_img_width;
						sz.cy = sz.cy * ratio;
					}
					
					LayoutObject& p = layout.objects.Add();
					p.y = y;
					p.col = LayoutObject::COL_CENTER;
					p.img = RescaleFilter(img, sz, FILTER_BSPLINE);
					p.txt_sz = Size(sz.cx, sz.cy + metatext_padding);
					p.img_sz = sz;
					
					if (prev) {
						int stolen_time = prev->duration / 2;
						prev->duration -= stolen_time;
						p.time = prev->time + prev->duration;
						p.duration = stolen_time;
					}
					else {
						p.time = 0;
						p.duration = sent.tmp_time;
					}
					y += p.txt_sz.cy;
					
					prev = &p;
				}
			}
			
			
			LayoutObject& o = layout.objects.Add();
			
			if (t == &script.title) o.fnt = LayoutObject::FNT_H1;
			if (t == &script.author) o.fnt = LayoutObject::FNT_H2;
			
			o.y = y;
			o.col = LayoutObject::COL_CENTER;
			o.txt = sent.GetData();
			o.txt_sz = GetTextSize(o.txt, layout.GetFont(o.fnt));
			o.time = sent.tmp_time;
			o.duration = sent.tmp_duration;
			o.clr = meta_actor.normal_paper;
			if (++i == mt.sents.GetCount())
				o.txt_sz.cy += metatext_padding;
			y += o.txt_sz.cy;
			
			prev = &o;
		}
	}
	
	
	for (const PlayPart& part : script.parts) {
		for (const PlaySection& sect : part.sections) {
			for (const PlayLine& line : sect.dialog.lines) {
				if (line.sents.IsEmpty())
					continue;
				
				String id = line.GetId();
				const PlayScript::Actor& actor = script.tmp_actors.Get(id);
				
				if (line.is_comment || line.is_meta) {
					// skip
				}
				else if (line.is_narration) {
					int i = 0;
					for (const PlaySentence& sent : line.sents) {
						LayoutObject& o = layout.objects.Add();
						o.y = y;
						o.frame_y = i == 0 ? narrator_padding : 0;
						o.col = LayoutObject::COL_CENTER;
						o.txt = sent.GetData();
						o.txt_sz = GetTextSize(o.txt, layout.regular);
						o.time = sent.tmp_time;
						o.duration = sent.tmp_duration;
						o.clr = actor.normal_paper;
						
						if (line.sents.GetCount() == 1)
							o.txt_sz.cy += narrator_padding * 2;
						else if (i == 0 || i == line.sents.GetCount())
							o.txt_sz.cy += narrator_padding;
						i++;
						y += o.txt_sz.cy;
					}
				}
				else {
					LayoutObject& name = layout.objects.Add();
					name.y = y;
					name.col = LayoutObject::COL_NAME;
					name.txt = line.id.name.ToString();
					name.txt_sz = GetTextSize(name.txt, layout.regular);
					name.time = -1;
					name.duration = 0;
					name.clr = actor.normal_paper;
					
					layout.max_name_w = max(layout.max_name_w, name.txt_sz.cx);
					
					for (const PlaySentence& sent : line.sents) {
						LayoutObject& l = layout.objects.Add();
						l.y = y;
						l.col = LayoutObject::COL_TXT;
						l.txt = sent.GetData();
						l.txt_sz = GetTextSize(l.txt, layout.regular);
						l.time = sent.tmp_time;
						l.duration = sent.tmp_duration;
						l.clr = actor.normal_paper;
						
						//y += layout.regular_h;
						y += l.txt_sz.cy;// + 5;
					}
				}
			}
		}
	}
	
	//DUMPC(script.subtitles); DUMPC(layout.objects);
	//LOG("");
	
}

Image PlayRenderer::LoadNotes() {
	const PlaySection* sect = script.FindSection(time, true);
	
	if (!sect || sect->musical_idx < 0)
		return Image();
	
	int song_begin = sect->musical_time >= 0 ? sect->musical_time : sect->dialog.GetFirstActorTime();
	int song_time = time - song_begin;
	if (song_time < 0)
		return Image();
	
	double notes_fps = sect->musical_fps > 0 ? sect->musical_fps : this->notes_fps;
	
	int song_frame = (int)((double)song_time * 0.001 * notes_fps);
	ASSERT(song_frame >= 0);
	int note_idx = sect->notes_min + song_frame;
	if (note_idx > sect->notes_max)
		return Image();
	
	String idxstr = IntStr(note_idx);
	String path = sect->musical_dir + DIR_SEPS + "notes ";
	int zeros = sect->notes_idx_digits - idxstr.GetCount();
	path.Cat('0', zeros);
	path << idxstr << ".png";
	
	if (!FileExists(path)) {
		//DUMP(path);
		return Image();
	}
	
	Image img = png.LoadFile(path);
	
	if (1) {
		ImageBuffer inv(img.GetSize());
		RGBA* dst = inv.Begin();
		const RGBA* src = img.Begin();
		const RGBA* end = img.End();
		while (src != end) {
			*dst = InvertRGBA_InvertHue(*src);
			src++;
			dst++;
		}
		img = inv;
	}
	
	double ratio = (double)frame_sz.cx / (double)img.GetWidth();
	if (ratio < 1.0) {
		Size new_sz = img.GetSize() * ratio;
		new_sz.cx = min(new_sz.cx, frame_sz.cx);
		img = RescaleFilter(img, new_sz, FILTER_BILINEAR);
	}
	
	return img;
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
