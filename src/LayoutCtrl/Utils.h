#ifndef _LayoutCtrl_Utils_h_
#define _LayoutCtrl_Utils_h_

NAMESPACE_LAYOUT_BEGIN

class Element;


#define LAST(x) (x.Top())
#define REMOVELAST(x) x.Remove(x.GetCount()-1)





inline int RoundFlt(float val) {
	int int_val = (int) val;
	if(val - int_val >= 0.5)
	{
		int_val++;
	}
	return int_val;
}

inline int RoundDbl(double val) {
	int int_val = (int) val;
	if(val - int_val >= 0.5)
	{
		int_val++;
	}
	return int_val;
}


RGBA		RGBAFromString(const String& str);
String		ResolveName(const String& name);
bool		IsColor(const String& str);




class IteratorSelector
{
public:
	virtual bool Select(Element* el) = 0;
};

class ElementsIterator
{
private:
	struct stack_item : public Moveable<stack_item>
	{
		int			idx;
		Element*	el;
	};

	Vector<stack_item>			stack;
	Element*					el;
	int							idx;
	IteratorSelector*			go_inside;
	IteratorSelector*			select;
public:

	ElementsIterator(Element* el, IteratorSelector* go_inside, IteratorSelector* select)
	{
		this->el		= el;
		idx				= -1;
		this->go_inside	= go_inside;
		this->select	= select;
	}

	~ElementsIterator()
	{

	}

	Element* Next(bool ret_higher = true);

private:
	void NextIdx();
};

class GoInsideInline : public IteratorSelector
{
public:
	virtual bool Select(Element* el);
};

class GoInsideTable : public IteratorSelector
{
public:
	virtual bool Select(Element* el);
};

class TableRowsSelector : public IteratorSelector
{
public:
	virtual bool Select(Element* el);
};

class TableCellsSelector : public IteratorSelector
{
public:
	virtual bool Select(Element* el);
};




class ElementZIndexSort
{
public:
	bool operator()(const Element* l, const Element* r) const;
};









enum {
	PERF_CREATEFONT, PERF_TEXTWIDTH, PERF_DRAWTEXT, PERF_DRAWLISTMARKER, PERF_IMAGESIZEGET,
	PERF_IMAGESIZEFIND, PERF_DRAWBG, PERF_DRAWBORDERS, PERF_LOADMASTERCSS, PERF_CSSELEMENTPARSE,
	PERF_CSSSELPARSE, PERF_CSSSELCALCSPEC, PERF_CSSPARSE, PERF_CREATEDOC, PERF_DOCINIT,
	PERF_DOCADDFONT, PERF_GETFONT, PERF_DOCRENDER, PERF_DOCPAINT, PERF_MOUSEOVER,
	PERF_MOUSELEAVE, PERF_MOUSELEFTDOWN, PERF_MOUSELEFTUP, PERF_DRAWBG0, PERF_DRAWBG1,
	PERF_DRAWBG2
};

	
class PerformanceMeter {
	TimeStop ts;
	
	uint64 total;
	uint64 count;
	String key;
public:
	PerformanceMeter();
	
	void Begin();
	void End();
	
	void SetTitle(const String& s) {key = s;}
	
	String GetTitle() {return key;}
	int Elapsed() {return total;}
	int Count() {return count;}
	int Average() {return total / count;}
};
	
void PerformanceMeterBegin(int id);
void PerformanceMeterEnd(int id);

int GetPerformanceMeterCount();
PerformanceMeter& GetPerformanceMeter(int i);

#define PERFMETER_BEGIN(x)	PerformanceMeterBegin(x)
#define PERFMETER_END(x)	PerformanceMeterEnd(x)








void AddPathArc(Vector<Point>& p, double x, double y, double rx, double ry, double a1, double a2, bool neg);
void Arc(Vector<Point>& poly, int xc, int yc, double radius, double angle1, double angle2);
void LineTo(Vector<Point>& poly, int xc, int yc);
void DrawEllipseLine(Draw& d, int x, int y, int w, int h, int pen, Color c);
void DrawRectLine(Draw& d, int x, int y, int w, int h, int pen, Color c);
//void DrawRoundedRect(Draw& d, const Position& pos, const BorderRadiuses&, Color c);


NAMESPACE_LAYOUT_END

#endif
