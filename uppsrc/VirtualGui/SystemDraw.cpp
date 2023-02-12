#if 0

#include "Local.h"

#ifdef VIRTUALGUI

NAMESPACE_UPP


PubSystemDraw::PubSystemDraw() {
	has_alpha = false;
}

PubSystemDraw::PubSystemDraw(Size sz) {
	has_alpha = false;
	Resize(sz);
}

PubSystemDraw::PubSystemDraw(int cx, int cy) {
	has_alpha = false;
	Resize(Size(cx,cy));
}

void PubSystemDraw::Resize(Size sz) {
	if (ib.GetSize() != sz) {
		ib.Create(sz);
		this->Init(Rect(sz));
		if (has_alpha)
			alpha.Create(sz);
	}
}

PubSystemDraw::operator Image() const {
	ImageBuffer b(ib.GetSize());
	memcpy(b, ib.Begin(), sizeof(RGBA) * ib.GetLength());
	RGBA *t = b;
	const RGBA *e = b.End();
	const auto& alpha_buf = this->alpha.GetBuffer();
	if(has_alpha) {
		const RGBA *s = alpha_buf.Begin();
		while(t < e) {
			t->a = s->r;
			t++;
			s++;
		}
		Premultiply(b);
		b.SetKind(IMAGE_ALPHA);
	}
	else {
		while(t < e) {
			t->a = 255;
			t++;
		}
		b.SetKind(IMAGE_OPAQUE);
	}
	return b;
}

Size PubSystemDraw::GetSize() const {
	return this->ib.GetSize();
}


END_UPP_NAMESPACE

#endif

#endif
