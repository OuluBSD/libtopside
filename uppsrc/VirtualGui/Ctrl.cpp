#include "Local.h"

#ifdef VIRTUALGUI

#define LLOG(x) // DLOG(x)

NAMESPACE_UPP

void Ctrl::GuiPlatformConstruct()
{
	fullrefresh = false;
}

void Ctrl::GuiPlatformRemove()
{
}

void Ctrl::GuiPlatformGetTopRect(Rect& r) const
{
}

bool Ctrl::GuiPlatformRefreshFrameSpecial(const Rect& r)
{
	return false;
}

bool Ctrl::GuiPlatformSetFullRefreshSpecial()
{
	return true;
}

String GuiPlatformGetKeyDesc(dword key)
{
	return Null;
}

void Ctrl::GuiPlatformSelection(PasteClip&)
{
}

void GuiPlatformAdjustDragImage(ImageBuffer&)
{
}

bool GuiPlatformHasSizeGrip()
{
	return true;
}

void GuiPlatformGripResize(TopWindow *q)
{
	q->GripResize();
}

Color GuiPlatformGetScreenPixel(int x, int y)
{
	return Null;
}

void GuiPlatformAfterMenuPopUp()
{
}

String Ctrl::Name() const {
	GuiLock __;
#ifdef CPU_64
	String s = String(typeid(*this).name()) + " : 0x" + FormatIntHex(this);
#else
	String s = String(typeid(*this).name()) + " : " + Format("0x%x", (int) this);
#endif
	Ctrl *parent = GetParent();
	if(parent)
		s << "(parent " << String(typeid(*parent).name()) << ")";
	return s;
}

void  Ctrl::SetMouseCursor(const Image& image)
{
	GuiLock __;
	fbCursorImage = image;
	if(VirtualGuiPtr->GetOptions() & GUI_SETMOUSECURSOR)
		VirtualGuiPtr->SetMouseCursor(image);
}

void Ctrl::Invalidate() {
	invalid = true;
}

void Ctrl::PubCtrlPaint(Draw& w, const Rect& clip) {
	GuiLock __;
	//LEVELCHECK(w, this);
	//LTIMING("CtrlPaint");
	LLOG("=== CtrlPaint " << UPP::Name(this) << ", clip: " << clip << ", rect: " << GetRect() << ", view: " << GetView());
	Rect rect = GetRect().GetSize();
	Rect orect = rect.Inflated(overpaint);
	if(!IsShown() || orect.IsEmpty() || clip.IsEmpty() || !clip.Intersects(orect))
		return;
	Rect view = rect;
	int n = GetFrameCount();
	for(int i = 0; i < n; i++) {
		//LEVELCHECK(w, NULL);
		Frame& f = GetFrame0(i);
		f.frame->FramePaint(w, view);
		view = f.GetView();
	}
	Rect oview = view.Inflated(overpaint);
	bool hasviewctrls = false;
	bool viewexcluded = false;
	bool hiddenbychild = false;
	for(Ctrl& q : *this)
		if(q.IsShown()) {
			if(q.GetRect().Contains(orect) && !q.IsTransparent())
				hiddenbychild = true;
			if(q.InFrame()) {
				if(!viewexcluded && IsTransparent() && q.GetRect().Intersects(view)) {
					w.Begin();
					w.ExcludeClip(view);
					viewexcluded = true;
				}
				//LEVELCHECK(w, &q);
				Point off = q.GetRect().TopLeft();
				w.Offset(off);
				q.PubCtrlPaint(w, clip - off);
				w.End();
			}
			else
				hasviewctrls = true;
		}
	if(viewexcluded)
		w.End();
	//DOLEVELCHECK;
	if(!hiddenbychild && !oview.IsEmpty() && oview.Intersects(clip) && w.IsPainting(oview)) {
		//LEVELCHECK(w, this);
		if(overpaint) {
			w.Clip(oview);
			w.Offset(view.left, view.top);
			Paint(w);
			PubPaintCaret(w);
			w.End();
			w.End();
		}
		else {
			w.Clipoff(view);
			Paint(w);
			PubPaintCaret(w);
			w.End();
		}
	}
	if(hasviewctrls && !view.IsEmpty()) {
		Rect cl = clip & view;
		w.Clip(cl);
		for(Ctrl& q : *this)
			if(q.IsShown() && q.InView()) {
				//LEVELCHECK(w, &q);
				Rect qr = q.GetRect();
				Point off = qr.TopLeft() + view.TopLeft();
				Rect ocl = cl - off;
				if(ocl.Intersects(Rect(qr.GetSize()).Inflated(overpaint))) {
					w.Offset(off);
					q.PubCtrlPaint(w, ocl);
					w.End();
				}
			}
		w.End();
	}
	//DOLEVELCHECK;
}

void Ctrl::PubPaintCaret(Draw& w)
{
	GuiLock __;
	// LLOG("PaintCaret " << Name() << ", caretCtrl: " << caretCtrl << ", WndCaretVisible: " << WndCaretVisible);
	if(this == caretCtrl && WndCaretVisible)
		w.DrawRect(GetCaret(), InvertColor);
}

dword VirtualGui::GetOptions()
{
	return 0;
}

void VirtualGui::SetMouseCursor(const Image& image) {}
void VirtualGui::SetCaret(const Rect& caret) {}

END_UPP_NAMESPACE

#endif
