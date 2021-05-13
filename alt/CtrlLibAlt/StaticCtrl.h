#ifndef _CtrlLibAlt_StaticCtrl_h_
#define _CtrlLibAlt_StaticCtrl_h_


NAMESPACE_UPP


class SeparatorCtrl : public Ctrl {
public:
	virtual Size GetMinSize() const;
	virtual void Paint(Draw& w);

	struct Style : ChStyle<Style> {
		Object l1, l2;
	};
};


class StaticRect : public Ctrl {
	Color clr;
	
public:
	virtual Size GetMinSize() const;
	virtual void Paint(Draw& w);
	
	StaticRect& SetColor(Color c) {clr = c; return *this;}
	
	struct Style : ChStyle<Style> {
		Object def_clr;
	};
};


END_UPP_NAMESPACE


#endif
