#include "Emu.h"

int Monitor::Init() {
	TODO
	return 0;
}

void Monitor::MoveCursor() {
	TODO
}

void Monitor::Scroll() {
	TODO
}

void Monitor::Put(char c) {
	TODO
}

void Monitor::Clear() {
	TODO
}

Monitor& Monitor::Write(const char *c) {
	TODO
	return *this;
}

Monitor& Monitor::WriteDec(int i) {
	TODO
	return *this;
}

Monitor& Monitor::WriteHex(void* p) {
	TODO
	return *this;
}

Monitor& Monitor::WriteHex(uint32 i) {
	TODO
	return *this;
}

Monitor& Monitor::NewLine() {
	TODO
	return *this;
}

