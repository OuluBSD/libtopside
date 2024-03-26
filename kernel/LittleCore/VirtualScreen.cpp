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
	for(int i = 0; i < height-1; i++) {
		int j = i+1;
		byte* dst = mem + i * pitch;
		byte* frm = dst + pitch;
		memcpy(dst, frm, pitch);
	}
	byte* dst = mem + (height - 1) * pitch;
	memset(dst, 0, pitch);
}

void VirtualScreen::Put(char c) {
	if (mem &&
		cursor_x >= 0 && cursor_x < width &&
		cursor_y >= 0 && cursor_y < height) {
		int pos = cursor_y * pitch + cursor_x;
		mem[pos] = c;
	}
}

void VirtualScreen::Clear() {
	if (mem)
		memset(mem, 0, sz);
}

void VirtualScreen::Write(const char *c) {
	
	
}

void VirtualScreen::WriteN(const char *c, int n) {
	
	
}

void VirtualScreen::WriteDec(int i) {
	
	
}

void VirtualScreen::WriteHexPtr(void* p) {
	
	
}

void VirtualScreen::WriteHexInt(size_t i) {
	
	
}

void VirtualScreen::NewLine() {
	
	
}

