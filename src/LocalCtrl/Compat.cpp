#include "LocalCtrl.h"

NAMESPACE_TOPSIDE_BEGIN

#if 0
CtrlGeomProxy::CtrlGeomProxy() {}
CtrlGeomProxy::CtrlGeomProxy(Ctrl& o) : p(&o) {}

void CtrlGeomProxy::SetTargetCtrl(Ctrl& o) {
	p = &o;
}

void CtrlGeomProxy::OnInvalidate() {
	TODO //SetPendingRedrawDeep();
}

bool CtrlGeomProxy::IsFocusCtrl() const {
	const Ctrl* pc = p;
	const Ctrl* c = Ctrl::GetFocusCtrl();
	while (c) {
		if (pc == c)
			return true;
		c = c->GetParent();
	}
	return false;
}

void CtrlGeomProxy::Layout() {
	TODO
	/*if (!p) return;
	Size sz = GetSize();
	p->SetRect(sz);*/
}

void CtrlGeomProxy::Paint(Draw& d) {
	if (!p) return;
	TODO // deprecated after upp virtual gui integration?
	#if 0
	#if IS_UPP_CORE
	
	#if 1
	Size sz = p->GetRect().GetSize();
	Rect rect = sz;
	Rect orect = rect.Inflated(p->GetOverpaint());
	ImageDraw id(sz);
	id.DrawImage(0,0,img);
	SystemDraw sd;
	sd.SetTarget(&id);
	p->PubCtrlPaint(sd, orect);
	img = id;
	d.DrawImage(0,0,img);
	#elif 1
	Rect rect = p->GetRect().GetSize();
	Rect orect = rect.Inflated(p->GetOverpaint());
	//d.Clipoff(rz);
	p->PubCtrlPaint(d, orect);
	//d.End();
	#elif 1
	Size sz = GetFrameSize();
	d.Clipoff(sz);
	p->Paint(d);
	d.End();
	#else
	Size sz = GetFrameSize();
	ImageDraw id(sz);
	c.Paint(id);
	Image img = id;
	d.DrawImage(0,0,img);
	#endif
	
	#else
	c.Paint(d);
	#endif
	#endif
}

#if IS_UPP_CORE

bool CtrlGeomProxy::DeepMouseMove(const Point& pt, dword keyflags) {
	Rect r = GetContentRect();
	Point cpt = GetContentPoint(pt);
	if (r.Contains(cpt)) {
		p->DispatchMousePub(UPP::Ctrl::MOUSEMOVE, cpt, 0);
		has_mouse = p->HasMouse();
		has_mouse_deep = p->HasMouseDeep();
		return has_mouse_deep;
	}
	has_mouse = false;
	has_mouse_deep = false;
	return false;
}

bool CtrlGeomProxy::Key(dword key, int count) {
	// this is such a hack
	if (p && IsFocusCtrl())
		UPP::Ctrl::DispatchKeyPub(key, count);
	return false;
}

void CtrlGeomProxy::MouseMove(Point pt, dword keyflags) {
	if (p) p->DispatchMousePub(UPP::Ctrl::MOUSEMOVE, pt, 0);
}

void CtrlGeomProxy::MouseWheel(Point pt, int zdelta, dword keyflags) {
	if (p) p->DispatchMousePub(UPP::Ctrl::MOUSEWHEEL, pt, zdelta);
}

void CtrlGeomProxy::MouseLeave() {
	// pass
	has_mouse = false;
	has_mouse_deep = false;
}

void CtrlGeomProxy::LeftDown(Point pt, dword keyflags) {
	if (p) p->DispatchMousePub(UPP::Ctrl::LEFTDOWN, pt, 0);
}

void CtrlGeomProxy::LeftUp(Point pt, dword keyflags) {
	if (p) p->DispatchMousePub(UPP::Ctrl::LEFTUP, pt, 0);
}

void CtrlGeomProxy::RightDown(Point pt, dword keyflags) {
	if (p) p->DispatchMousePub(UPP::Ctrl::RIGHTDOWN, pt, 0);
}

void CtrlGeomProxy::RightUp(Point pt, dword keyflags) {
	if (p) p->DispatchMousePub(UPP::Ctrl::RIGHTUP, pt, 0);
}

#endif

Ctrl* CtrlGeomProxy::operator->() {return p;}
Ctrl& CtrlGeomProxy::operator*() {ASSERT(p); return *p;}

Ctrl* CtrlGeomProxy::GetCtrl() {return p;}
#endif






Image RenderTextBlended(Font font, String s, Color ink) {
	Size sz = GetTextSize(s, font);
	ImageDraw iw(sz);
	iw.Alpha().DrawRect(sz, GrayColor(0));
	iw.DrawText(0, 0, s, font, ink);
	return iw;
}


NAMESPACE_TOPSIDE_END


// PdfDraw is POSIX only package
#ifdef flagWIN32
NAMESPACE_UPP_BEGIN

void __cdecl PdfDraw__initializer() {
	
}

NAMESPACE_UPP_END
#endif
