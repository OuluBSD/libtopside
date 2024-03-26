#include "LittleCore.h"
#include <LittleLibrary/LittleLibrary.h>


VirtualScreen::VirtualScreen() {
	
}

VirtualScreen::~VirtualScreen() {
	Free();
}

void VirtualScreen::Free() {
	if (mem)
		global->kheap.Free(mem);
	mem = 0;
	sz = 0;
	width = 0;
	height = 0;
	stride = 0;
	pitch = 0;
}

bool VirtualScreen::Init(int w, int h) {
	Free();
	
	width = w;
	height = h;
	stride = 1;
	pitch = w * stride;
	sz = pitch * height;
	if (sz < 0)
		return false;
	if (sz >= 1920*1080*3)
		return false;
	
	mem = (byte*)global->kheap.Allocate(sz, 0);
	
	return true;
}

void VirtualScreen::MoveCursor() {
	// does nothing (but updates hardware)
}

void VirtualScreen::Scroll() {
	int scroll = max(0, min(height, cursor_y - height));
	for(int i = 0; i < height-scroll; i++) {
		int j = i+scroll;
		byte* dst = mem + i * pitch;
		byte* frm = mem + j * pitch;
		memcpy(dst, frm, pitch);
	}
	for(int i = height-scroll; i < height; i++) {
		byte* dst = mem + i * pitch;
		memset(dst, 0, pitch);
	}
}

void VirtualScreen::Put(dword d, int count) {
	char c = (char)d;
	for(int i = 0; i < count; i++) {
		// Handle a backspace, by moving the cursor back one space
		if (c == 0x08 && cursor_x) {
			cursor_x--;
		}
		
		// Handle a tab by increasing the cursor's X, but only to a point
		// where it is divisible by 8.
		else if (c == 0x09) {
			cursor_x = (cursor_x + 8) & ~(8 - 1);
		}
		
		// Handle carriage return
		else if (c == '\r') {
			cursor_x = 0;
		}
		
		// Handle newline by moving cursor back to left and increasing the row
		else if (c == '\n') {
			cursor_x = 0;
			cursor_y++;
		}
		// Handle any other printable character.
		else {
			if (mem && cursor_x >= 0 && cursor_x < width &&
				cursor_y >= 0 && cursor_y < height) {
				int pos = cursor_y * pitch + cursor_x;
				mem[pos] = c;
			}
			cursor_x++;
			if (cursor_x >= width) {
				cursor_y++;
			}
		}
	}
	
	// Scroll the screen if needed.
	Scroll();
	// Move the hardware cursor.
	MoveCursor();
}

void VirtualScreen::Clear() {
	if (mem)
		memset(mem, 0, sz);
	
	// Move the hardware cursor back to the start.
	cursor_x = 0;
	cursor_y = 0;
	MoveCursor();
}

void VirtualScreen::Write(const char *c) {
	int i = 0;
	while (c[i]) {
		Put(c[i++]);
	}
}

void VirtualScreen::WriteN(const char *c, int n) {
	int i = 0;
	while (i < n && c[i]) {
		Put(c[i++]);
	}
}

void VirtualScreen::WriteDec(int i) {
	if (i < 0)
		Put('-');
	bool foundfirst = 0;
	for (int j = 9; j >= 0; j--) {
		int pow = Pow10(j);
		int k = i / pow;
		i = i % pow;
		if (k < 0)
			k *= -1;
		if (!foundfirst && k)
			foundfirst = 1;
		if (foundfirst)
			Put('0' + k);
	}
	if (!foundfirst)
		Put('0');
}

void VirtualScreen::WriteHexPtr(void* p) {
	String s = Format("%X", (int64)p);
	Write(s);
}

void VirtualScreen::WriteHexInt(size_t i) {
	String s = Format("%X", (int64)i);
	Write(s);
}

void VirtualScreen::NewLine() {
	Put('\n');
}

