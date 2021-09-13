#include <SerialLib/SerialLib.h>


NAMESPACE_UPP

TS::Windows* Ctrl::wm;


TS::CoreWindow* Ctrl::GetWindow() {
	TopWindow* tw = GetTopWindow();
	return tw ? tw->GetWindow() : 0;
}


Image Ctrl::OverrideCursor(const Image& m) {
	TODO
}

void Ctrl::CloseTopCtrls() {
	LOG("TODO Ctrl::CloseTopCtrls");
}

#if 0

CoreWindow* Ctrl::GetWindow() {
	Ctrl* c = this;
	while (c) {
		CoreWindow* cw = CastPtr<CoreWindow>(c);
		if (cw)
			return cw;
		c = c->GetParent();
	}
	return NULL;
}

#endif

TS::Windows* Ctrl::GetWindows() {
	ASSERT(wm);
	return wm;
}

END_UPP_NAMESPACE
