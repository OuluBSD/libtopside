#include "Internal.h"

#if HAVE_WINDOWSYSTEM

NAMESPACE_UPP

TS::Ecs::Windows* Ctrl::wm;


TS::Ecs::CoreWindow* Ctrl::GetWindow() {
	TopWindow* tw = GetTopWindow();
	return tw ? tw->GetWindow() : 0;
}


Image Ctrl::OverrideCursor(const Image& m) {
	LOG("TODO Ctrl::OverrideCursor");
	return Image();
}

void Ctrl::CloseTopCtrls() {
	LOG("TODO Ctrl::CloseTopCtrls");
}

#if 0

Ecs::CoreWindow* Ctrl::GetWindow() {
	Ctrl* c = this;
	while (c) {
		Ecs::CoreWindow* cw = CastPtr<Ecs::CoreWindow>(c);
		if (cw)
			return cw;
		c = c->GetParent();
	}
	return NULL;
}

#endif

TS::Ecs::Windows* Ctrl::GetWindows() {
	ASSERT(wm);
	return wm;
}

END_UPP_NAMESPACE

#endif
