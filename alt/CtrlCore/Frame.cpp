#include "CtrlCore.h"

NAMESPACE_UPP_BEGIN


#define SColorEdge Black // for now

const ColorF *InsetBorder()
{
	static ColorF data[] = {
		(ColorF)2,
		&SColorShadow, &SColorShadow, &SColorLight, &SColorLight,
		&SColorEdge, &SColorEdge, &SColorFace, &SColorFace
	};
	return data;
}


CtrlFrame& NullFrame() { return Single<NullFrameClass>(); }
CtrlFrame& InsetFrame() { static BorderFrame h(InsetBorder()); return h; }


void CtrlFrame::FramePaint(Draw& draw, const Rect& r) {}
void CtrlFrame::FrameAdd(Ctrl& ctrl) {}
void CtrlFrame::FrameRemove() {}
int CtrlFrame::OverPaint() const { return 0; }

void NullFrameClass::FrameLayout(Rect& r) {}
void NullFrameClass::FramePaint(Draw& draw, const Rect& r) {}
void NullFrameClass::FrameAddSize(Size& sz) {}

void BorderFrame::FrameLayout(Rect& r) {TODO}
void BorderFrame::FramePaint(Draw& w, const Rect& r) {TODO}
void BorderFrame::FrameAddSize(Size& sz) {TODO}

#if 0
void CtrlFrame::SetCapture() {
	if (!ctrl) return;
	SetCaptured(this);
	ctrl->SetCapture();
}

void CtrlFrame::ReleaseCapture() {
	if (!ctrl) return;
	SetCaptured(NULL);
	ctrl->ReleaseCapture();
}

CtrlFrame* CtrlFrame::GetCaptured() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameCaptured();*/
}

CtrlFrame* CtrlFrame::GetWithMouse() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameWithMouse();*/
}

void CtrlFrame::SetCaptured(CtrlFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameCaptured(c);*/
}

#if 0
void CtrlFrame::SetWithMouse(CtrlFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameWithMouse(c);*/
}
#endif
#endif


NAMESPACE_UPP_END
