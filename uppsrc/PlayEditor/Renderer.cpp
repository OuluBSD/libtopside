#include "PlayEditor.h"

NAMESPACE_TOPSIDE_BEGIN


PlayRenderer::PlayRenderer(PlayScript& s) : script(s) {
	//frame_sz = Size(1280,720);
	frame_sz = Size(640,360);
	
}

void PlayRenderer::Seek(int i) {
	time = i;
}

Image PlayRenderer::Render() {
	ImageDraw id(frame_sz);
	
	Size bg_size(320, 180);
	Image bg = LiquidBokeh(bg_size, time * 0.001);
	bg = RescaleFilter(bg, frame_sz, FILTER_BSPLINE);
	
	//id.DrawRect(frame_sz, RandomColor(256-64,64));
	
	id.DrawImage(0, 0, bg);
	
	
	const PlayScript::Subtitle* st = script.FindSubtitle(time);
	
	if (st) {
		int font_h = 20;
		Font fnt = SansSerif(font_h);
		Size txt_sz = GetTextSize(st->str, fnt);
		int x = (frame_sz.cx - txt_sz.cx) / 2;
		int y = (frame_sz.cy - txt_sz.cy) / 2;
		id.DrawText(x, y, st->str, fnt, White());
	}
	
	return id;
}


NAMESPACE_TOPSIDE_END
