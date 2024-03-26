#include "LittleCore.h"

ScreenProxy::ScreenProxy() {
	
}

void ScreenProxy::Clear() {
	if (target) target->Clear();
}

void ScreenProxy::MoveCursor() {
	if (target) target->MoveCursor();
}

void ScreenProxy::Scroll() {
	if (target) target->Scroll();
}

void ScreenProxy::Put(char c) {
	if (target) target->Put(c);
}

void ScreenProxy::Write(const char *c) {
	if (target) target->Write(c);
}

void ScreenProxy::WriteN(const char *c, int n) {
	if (target) target->WriteN(c, n);
}

void ScreenProxy::WriteDec(int i) {
	if (target) target->WriteDec(i);
}

void ScreenProxy::WriteHexPtr(void* p) {
	if (target) target->WriteHexPtr(p);
}

void ScreenProxy::WriteHexInt(size_t i) {
	if (target) target->WriteHexInt(i);
}

void ScreenProxy::NewLine() {
	if (target) target->NewLine();
}
