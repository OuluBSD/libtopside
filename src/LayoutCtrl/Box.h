#ifndef _LayoutCtrl_Box_h_
#define _LayoutCtrl_Box_h_

NAMESPACE_LAYOUT_BEGIN

class Element;

enum BoxType {
	BOX_BLOCK,
	BOX_LINE
};

class Box {
protected:
	int		box_top;
	int		box_left;
	int		box_right;
	
public:
	Box(int top, int left, int right) {
		box_top	= top;
		box_left	= left;
		box_right	= right;
	}
	virtual ~Box() {}

	int		Bottom()	{ return box_top + Height();	}
	int		Top()		{ return box_top;				}
	int		Right()		{ return box_left + Width();	}
	int		Left()		{ return box_left;				}

	virtual BoxType				GetType() = 0;
	virtual int					Height() = 0;
	virtual int					Width() = 0;
	virtual void				AddElement(Element* el) = 0;
	virtual bool				CanHold(Element* el, WhiteSpace ws) = 0;
	virtual void				Finish(bool last_box = false) = 0;
	virtual bool				IsEmpty() = 0;
	virtual int					Baseline() = 0;
	virtual void				GetElements(ElementsVector& els) = 0;
	virtual int					TopMargin() = 0;
	virtual int					BottomMargin() = 0;
	virtual void				SetYShift(int shift) = 0;
	virtual void				NewWidth(int left, int right, ElementsVector& els) = 0;
};


class BlockBox : public Box {
	Ptr<Element>	element;
public:
	BlockBox(int top, int left, int right) : Box(top, left, right) {
		element = NULL;
	}

	virtual BoxType	GetType();
	virtual int					Height();
	virtual int					Width();
	virtual void				AddElement(Element* el);
	virtual bool				CanHold(Element* el, WhiteSpace ws);
	virtual void				Finish(bool last_box = false);
	virtual bool				IsEmpty();
	virtual int					Baseline();
	virtual void				GetElements(ElementsVector& els);
	virtual int					TopMargin();
	virtual int					BottomMargin();
	virtual void				SetYShift(int shift);
	virtual void				NewWidth(int left, int right, ElementsVector& els);
};


class LineBox : public Box {
	Vector<Ptr<Element> >	items;
	int						height;
	int						width;
	int						line_height;
	FontMetrics				font_metrics;
	int						baseline;
	TextAlign				text_align;
public:
	LineBox(int top, int left, int right, int line_height, FontMetrics& fm, TextAlign align) : Box(top, left, right)
	{
		height					= 0;
		width					= 0;
		font_metrics			= fm;
		this->line_height		= line_height;
		baseline				= 0;
		text_align				= align;
	}

	virtual BoxType				GetType();
	virtual int					Height();
	virtual int					Width();
	virtual void				AddElement(Element* el);
	virtual bool				CanHold(Element* el, WhiteSpace ws);
	virtual void				Finish(bool last_box = false);
	virtual bool				IsEmpty();
	virtual int					Baseline();
	virtual void				GetElements(ElementsVector& els);
	virtual int					TopMargin();
	virtual int					BottomMargin();
	virtual void				SetYShift(int shift);
	virtual void				NewWidth(int left, int right, ElementsVector& els);

private:
	Element*					GetLastSpace();
	bool						IsBreakOnly();
};


NAMESPACE_LAYOUT_END

#endif
