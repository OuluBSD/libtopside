#include "AudioCtrl.h"


NAMESPACE_TOPSIDE_BEGIN


AudioSlider::AudioSlider() {
	name = "Unnamed";
	value = 50;
	min = 0;
	max = 100;
	diff = max - min;
	bg = GrayColor(255-32);
}

void AudioSlider::Set(String name, int value, int min, int max) {
	this->name = name;
	this->value = value;
	this->min = min;
	this->max = max;
	diff = max - min;
	ASSERT(diff > 0);
	ASSERT(value >= min && value <= max);
}
	
void AudioSlider::Paint(Draw& w) {
	Size sz(GetSize());
	
	int pad = 15;
	int row = sz.cy / 4;
	Font fnt = Arial(row-4);
	
	w.DrawRect(sz, bg);
	w.DrawText(3, 1, name, fnt, Black());
	
	String value_str = IntStr(value);
	Size txt_sz = GetTextSize(value_str, fnt);
	
	int x = pad + (sz.cx - pad * 2) * (value - min) / diff - txt_sz.cx / 2;
	w.DrawText(x, row + 1, value_str, fnt, Black());
	
	int r2 = row*2;
	int r3 = row*3;
	w.DrawRect(0, r2, sz.cx, row, GrayColor(128));
	
	Size btn_sz(30, row);
	x = pad + (sz.cx - pad * 2) * (value - min) / diff - btn_sz.cx / 2;
	w.DrawRect(x, r2, btn_sz.cx, btn_sz.cy, bg);
	w.DrawLine(x, r2, x+btn_sz.cx, r2, 1, GrayColor(255));
	w.DrawLine(x, r2, x, r3, 1, GrayColor(255));
	w.DrawLine(x, r3, x+btn_sz.cx, r3, 1, GrayColor(64));
	w.DrawLine(x+btn_sz.cx, r2, x+btn_sz.cx, r3+1, 1, GrayColor(64));
	x = pad + (sz.cx - pad * 2) * (value - min) / diff;
	w.DrawLine(x-1, r2+1, x-1, r3-1, 1, GrayColor(64));
	w.DrawLine(x, r2+1, x, r3-1, 1, GrayColor(255));
	
	w.DrawLine(0, r2, sz.cx-1, r2, 1, GrayColor(64));
	w.DrawLine(0, r2, 0, r3, 1, GrayColor(64));
	w.DrawLine(0, r3, sz.cx-1, r3, 1, GrayColor(255));
	w.DrawLine(sz.cx-1, r2, sz.cx-1, r3+1, 1, GrayColor(255));
	
	double value_step = diff / 4.0;
	for(int i = 0; i < 5; i++) {
		int value = min + i * value_step;
		value_str = IntStr(value);
		txt_sz = GetTextSize(value_str, fnt);
		
		int x = pad + (sz.cx - pad * 2) * (value - min) / diff - txt_sz.cx / 2;
		w.DrawText(x, r3 + 1, value_str, fnt, Black());
	}
}


NAMESPACE_TOPSIDE_END
