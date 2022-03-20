#include "Adventure.h"

namespace Adventure {
	
Color GetPicoPalette(PaletteColor idx) {
	switch (idx) {
		case 0:  return Color(0x00, 0x00, 0x00);
		case 1:  return Color(0x1D, 0x2B, 0x53);
		case 2:  return Color(0x7E, 0x25, 0x53);
		case 3:  return Color(0x00, 0x87, 0x51);
		
		case 4:  return Color(0xAB, 0x52, 0x36);
		case 5:  return Color(0x5F, 0x57, 0x4F);
		case 6:  return Color(0xC2, 0xC3, 0xC7);
		case 7:  return Color(0xFF, 0xF1, 0xE8);
		
		case 8:  return Color(0xFF, 0x00, 0x4D);
		case 9:  return Color(0xFF, 0xA3, 0x00);
		case 10: return Color(0xFF, 0xEC, 0x27);
		case 11: return Color(0x00, 0xE4, 0x36);
		
		case 12: return Color(0x29, 0xAD, 0xFF);
		case 13: return Color(0x83, 0x76, 0x9C);
		case 14: return Color(0xFF, 0x77, 0xA8);
		case 15: return Color(0xFF, 0xCC, 0xAA);
		
		default: break;
	}
	ASSERT(0);
	return Color(0,0,0);
}




Color ReadColor(const SObj& o, HiValue key, Color def) {
	if (o.IsMap()) {
		const auto& m = o.GetMap();
		int i = m.Find(key);
		if (i >= 0) {
			LOG(o.ToString());
			TODO
		}
	}
	return def;
}

bool TryReadColor(const SObj& o, HiValue key, Color& c) {
	if (o.IsMap()) {
		const auto& m = o.GetMap();
		int i = m.Find(key);
		if (i >= 0) {
			LOG(o.ToString());
			TODO
		}
	}
	return false;
}





void Program::ResetPalette() {
	ui_cursor_cols[0] = GetPicoPalette(7);
	ui_cursor_cols[1] = GetPicoPalette(12);
	ui_cursor_cols[2] = GetPicoPalette(13);
	ui_cursor_cols[3] = GetPicoPalette(13);
	ui_cursor_cols[4] = GetPicoPalette(12);
	ui_cursor_cols[5] = GetPicoPalette(7);
	
}

void Program::PrintLine(String msg, int x, int y, int col, int align, bool use_caps, float duration, bool big_font) {
  // punctuation...
	//  > ":" new line, shown after text prior expires
	//  > ";" new line, shown immediately
	// note: an actor's talk animation is not activated as it is with say-line.
	
	col = col ? col : 7;   // default to white
	align = align ? align : 0; // default to no align
	
	// calc max line width based on x-pos/available space
	int screen_space = 127 - (x - cam.x);
	if (align == 1)
		screen_space = min(x -cam.x, screen_space);
	int max_line_length = max(screen_space / 2, 16);
	
	// search for (";"'s
	String msg_left = "";
	for(int i = 0; i < msg.GetCount(); i++) {
		int curchar = msg[i];
		if (curchar == ':') {
			// show msg up to this point
			// and process the rest as new message

			// next message?
			msg_left = msg.Mid(i+1);
			
			// redefine curr msg
			msg = msg.Left(i);
			break;
		}
	}
	
	Vector<String> lines;
	CreateTextLines(msg, max_line_length, lines);
	
	// find longest line
	int longest_line = GetLongestLineSize(lines);
	
	// center-align text block
	int xpos = x - cam.x;
	if (align == 1)
		xpos -= longest_line * (big_font ? 4 : 2);
	
	// screen bound check
	xpos = max(2, xpos);
	int ypos = max(18, y); // left, top
	xpos = min(xpos, 127 - (longest_line * 4) - 1); // right
	
	TODO
	/*
	talking_curr = {
		msg_lines = lines,
		x = xpos,
		y = ypos,
		col = col,
		align = align,
		time_left = duration || #msg * 8,
		char_width = longest_line,
		use_caps = use_caps,
		big_font = big_font
	};
	// ref point for (skip #####################??????
	//talking_curr.time_orig=talking_curr.time_left


	// if (message was split...
	if (#msg_left > 0) {
	  talking = talking_actor
		WaitForMessage()
		talking_actor = talking
		PrintLine(msg_left, x, y, col, align, use_caps, NULL, big_font)
	}

	// and wait for (message?
	//if (!dont_wait_msg) {
		WaitForMessage();
	//}
	*/
}

}
