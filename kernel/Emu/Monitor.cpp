#include "Emu.h"

int Monitor::Init() {
	
	return 0;
}

void Monitor::Clear() {
	OnClear();
}

void Monitor::MoveCursor() {
	OnMoveCursor();
}

void Monitor::Scroll() {
	OnScroll();
}

void Monitor::Put(char c) {
	OnPut(c);
}

Monitor& Monitor::Write(const char *c) {
	OnWrite(c);
	return *this;
}

Monitor& Monitor::WriteN(const char *c, int n) {
	OnWriteN(c, n);
	return *this;
}

Monitor& Monitor::WriteDec(int i) {
	OnWriteDec(i);
	return *this;
}

Monitor& Monitor::WriteHexPtr(void* p) {
	OnWriteHexPtr(p);
	return *this;
}

Monitor& Monitor::WriteHexInt(size_t i) {
	OnWriteHexInt(i);
	return *this;
}

Monitor& Monitor::NewLine() {
	OnNewLine();
	return *this;
}

