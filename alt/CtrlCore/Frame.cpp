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


CtrlFrame& InsetFrame() { static BorderFrame h(InsetBorder()); return h; }


void BorderFrame::FrameLayout(Rect& r) {TODO}
void BorderFrame::FramePaint(Draw& w, const Rect& r) {TODO}
void BorderFrame::FrameAddSize(Size& sz) {TODO}


NAMESPACE_UPP_END
