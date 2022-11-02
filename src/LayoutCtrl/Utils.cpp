#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN

struct DefColor
{
	String	name;
	String	rgb;
};


DefColor g_DefColors[] = 
{
	{"transhigher","rgba(0, 0, 0, 0)"},
	{"AliceBlue","#F0F8FF"},
	{"AntiqueWhite","#FAEBD7"},
	{"Aqua","#00FFFF"},
	{"Aquamarine","#7FFFD4"},
	{"Azure","#F0FFFF"},
	{"Beige","#F5F5DC"},
	{"Bisque","#FFE4C4"},
	{"Black","#000000"},
	{"BlanchedAlmond","#FFEBCD"},
	{"Blue","#0000FF"},
	{"BlueViolet","#8A2BE2"},
	{"Brown","#A52A2A"},
	{"BurlyWood","#DEB887"},
	{"CadetBlue","#5F9EA0"},
	{"Chartreuse","#7FFF00"},
	{"Chocolate","#D2691E"},
	{"Coral","#FF7F50"},
	{"CornflowerBlue","#6495ED"},
	{"Cornsilk","#FFF8DC"},
	{"Crimson","#DC143C"},
	{"Cyan","#00FFFF"},
	{"DarkBlue","#00008B"},
	{"DarkCyan","#008B8B"},
	{"DarkGoldenRod","#B8860B"},
	{"DarkGray","#A9A9A9"},
	{"DarkGrey","#A9A9A9"},
	{"DarkGreen","#006400"},
	{"DarkKhaki","#BDB76B"},
	{"DarkMagenta","#8B008B"},
	{"DarkOliveGreen","#556B2F"},
	{"Darkorange","#FF8C00"},
	{"DarkOrchid","#9932CC"},
	{"DarkRed","#8B0000"},
	{"DarkSalmon","#E9967A"},
	{"DarkSeaGreen","#8FBC8F"},
	{"DarkSlateBlue","#483D8B"},
	{"DarkSlateGray","#2F4F4F"},
	{"DarkSlateGrey","#2F4F4F"},
	{"DarkTurquoise","#00CED1"},
	{"DarkViolet","#9400D3"},
	{"DeepPink","#FF1493"},
	{"DeepSkyBlue","#00BFFF"},
	{"DimGray","#696969"},
	{"DimGrey","#696969"},
	{"DodgerBlue","#1E90FF"},
	{"FireBrick","#B22222"},
	{"FloralWhite","#FFFAF0"},
	{"ForestGreen","#228B22"},
	{"Fuchsia","#FF00FF"},
	{"Gainsboro","#DCDCDC"},
	{"GhostWhite","#F8F8FF"},
	{"Gold","#FFD700"},
	{"GoldenRod","#DAA520"},
	{"Gray","#808080"},
	{"Grey","#808080"},
	{"Green","#008000"},
	{"GreenYellow","#ADFF2F"},
	{"HoneyDew","#F0FFF0"},
	{"HotPink","#FF69B4"},
	{"Ivory","#FFFFF0"},
	{"Khaki","#F0E68C"},
	{"Lavender","#E6E6FA"},
	{"LavenderBlush","#FFF0F5"},
	{"LawnGreen","#7CFC00"},
	{"LemonChiffon","#FFFACD"},
	{"LightBlue","#ADD8E6"},
	{"LightCoral","#F08080"},
	{"LightCyan","#E0FFFF"},
	{"LightGoldenRodYellow","#FAFAD2"},
	{"LightGray","#D3D3D3"},
	{"LightGrey","#D3D3D3"},
	{"LightGreen","#90EE90"},
	{"LightPink","#FFB6C1"},
	{"LightSalmon","#FFA07A"},
	{"LightSeaGreen","#20B2AA"},
	{"LightSkyBlue","#87CEFA"},
	{"LightSlateGray","#778899"},
	{"LightSlateGrey","#778899"},
	{"LightSteelBlue","#B0C4DE"},
	{"LightYellow","#FFFFE0"},
	{"Lime","#00FF00"},
	{"LimeGreen","#32CD32"},
	{"Linen","#FAF0E6"},
	{"Magenta","#FF00FF"},
	{"Maroon","#800000"},
	{"MediumAquaMarine","#66CDAA"},
	{"MediumBlue","#0000CD"},
	{"MediumOrchid","#BA55D3"},
	{"MediumPurple","#9370D8"},
	{"MediumSeaGreen","#3CB371"},
	{"MediumSlateBlue","#7B68EE"},
	{"MediumSpringGreen","#00FA9A"},
	{"MediumTurquoise","#48D1CC"},
	{"MediumVioletRed","#C71585"},
	{"MidnightBlue","#191970"},
	{"MintCream","#F5FFFA"},
	{"MistyRose","#FFE4E1"},
	{"Moccasin","#FFE4B5"},
	{"NavajoWhite","#FFDEAD"},
	{"Navy","#000080"},
	{"OldLace","#FDF5E6"},
	{"Olive","#808000"},
	{"OliveDrab","#6B8E23"},
	{"Orange","#FFA500"},
	{"OrangeRed","#FF4500"},
	{"Orchid","#DA70D6"},
	{"PaleGoldenRod","#EEE8AA"},
	{"PaleGreen","#98FB98"},
	{"PaleTurquoise","#AFEEEE"},
	{"PaleVioletRed","#D87093"},
	{"PapayaWhip","#FFEFD5"},
	{"PeachPuff","#FFDAB9"},
	{"Peru","#CD853F"},
	{"Pink","#FFC0CB"},
	{"Plum","#DDA0DD"},
	{"PowderBlue","#B0E0E6"},
	{"Purple","#800080"},
	{"Red","#FF0000"},
	{"RosyBrown","#BC8F8F"},
	{"RoyalBlue","#4169E1"},
	{"SaddleBrown","#8B4513"},
	{"Salmon","#FA8072"},
	{"SandyBrown","#F4A460"},
	{"SeaGreen","#2E8B57"},
	{"SeaShell","#FFF5EE"},
	{"Sienna","#A0522D"},
	{"Silver","#C0C0C0"},
	{"SkyBlue","#87CEEB"},
	{"SlateBlue","#6A5ACD"},
	{"SlateGray","#708090"},
	{"SlateGrey","#708090"},
	{"Snow","#FFFAFA"},
	{"SpringGreen","#00FF7F"},
	{"SteelBlue","#4682B4"},
	{"Tan","#D2B48C"},
	{"Teal","#008080"},
	{"Thistle","#D8BFD8"},
	{"Tomato","#FF6347"},
	{"Turquoise","#40E0D0"},
	{"Violet","#EE82EE"},
	{"Wheat","#F5DEB3"},
	{"White","#FFFFFF"},
	{"WhiteSmoke","#F5F5F5"},
	{"Yellow","#FFFF00"},
	{"YellowGreen","#9ACD32"}
};


RGBA RGBAFromString( const String& str )
{
	if(!str.GetCount())
	{
		return Black();
	}
	if(str[0] == '#')
	{
		String red		= "";
		String green	= "";
		String blue		= "";
		if (str.GetCount() - 1 == 3)
		{
			red.Cat(str[1]); red.Cat(str[1]);
			green.Cat(str[2]); green.Cat(str[2]);
			blue.Cat(str[3]); blue.Cat(str[3]);
		}
		else if (str.GetCount() - 1 == 6)
		{
			red		+= str[1];
			red		+= str[2];
			green	+= str[3];
			green	+= str[4];
			blue	+= str[5];
			blue	+= str[6];
		}
		RGBA clr;
		clr.r	= HexInt(red);
		clr.g	= HexInt(green);
		clr.b	= HexInt(blue);
		clr.a	= 255;
		return clr;
	} else if(!str.Compare("rgb"))
	{
		String s = str;

		int pos = s.FindFirstOf("(");
		if(pos != -1)
		{
			s.Remove(0, pos+1);
		}
		pos = FindLastOf(s, ")");
		if(pos != -1)
		{
			s.Remove(pos, s.GetCount()-pos);
		}

		Vector<String> tokens;
		SplitString(s, tokens, ", \t");

		RGBA clr;

		if(tokens.GetCount() >= 1)	clr.r	= (byte) StrInt(tokens[0]);
		if(tokens.GetCount() >= 2)	clr.g	= (byte) StrInt(tokens[1]);
		if(tokens.GetCount() >= 3)	clr.b	= (byte) StrInt(tokens[2]);
		if(tokens.GetCount() >= 4)	clr.a	= (byte) (StrDbl(tokens[3]) * 255.0);

		return clr;
	} else
	{
		String rgb = ResolveName(str);
		if(rgb.GetCount())
		{
			return RGBAFromString(rgb);
		}
	}
	return Black();
}

String ResolveName( const String& name )
{
	for(int i=0; g_DefColors[i].name.GetCount(); i++)
	{
		if(!CompareNoCase(name, g_DefColors[i].name))
		{
			return g_DefColors[i].rgb;
		}
	}
	return "";
}

bool IsColor( const String& str )
{
	if(!CompareNoCase(str, "rgb") || str[0] == '#')
	{
		return true;
	}
	if(ResolveName(str).GetCount())
	{
		return true;
	}
	return false;
}










Element* ElementsIterator::Next(bool ret_higher)
{
	NextIdx();

	while(idx < (int) this->el->GetChildrenCount())
	{
		Element* el = this->el->GetChild(idx);
		if (!el)
			NextIdx();
		else if(el->GetChildrenCount() && go_inside && go_inside->Select(el) )
		{
			stack_item si;
			si.idx		= idx;
			si.el		= el;
			stack.Add(si);
			this->el	= el;
			idx			= -1;
			if(ret_higher)
			{
				return el;
			}
			NextIdx();
		} else
		{
			if(!select || (select && select->Select(el->GetChild(idx))))
			{
				return el->GetChild(idx);
			} else
			{
				NextIdx();
			}
		}
	}

	return 0;
}

void ElementsIterator::NextIdx()
{
	idx++;
	while(idx >= (int) el->GetChildrenCount() && stack.GetCount())
	{
		stack_item si = LAST(stack);
		REMOVELAST(stack);
		idx	= si.idx;
		el	= si.el;
		idx++;
		continue;
	}
}


bool GoInsideInline::Select( Element* el )
{
	if(el->GetDisplay() == DisplayInline || el->GetDisplay() == DisplayInlineText)
	{
		return true;
	}
	return false;
}

bool GoInsideTable::Select( Element* el )
{
	if(	el->GetDisplay() == DisplayTableRowGroup ||
		el->GetDisplay() == DisplayTableHeaderGroup ||
		el->GetDisplay() == DisplayTableFooterGroup)
	{
		return true;
	}
	return false;
}

bool TableRowsSelector::Select( Element* el )
{
	if(	el->GetDisplay() == DisplayTableRow)
	{
		return true;
	}
	return false;
}

bool TableCellsSelector::Select( Element* el )
{
	if(	el->GetDisplay() == DisplayTableCell)
	{
		return true;
	}
	return false;
}




bool ElementZIndexSort::operator()(const Element* l, const Element* r) const
{
	return l->GetZIndex() < r->GetZIndex();
}






















ArrayMap<int, PerformanceMeter> meters;

int GetPerformanceMeterCount() {return meters.GetCount();}
PerformanceMeter& GetPerformanceMeter(int i) {return meters[i];}


PerformanceMeter::PerformanceMeter() {
	total = 0;
	count = 0;
}

void PerformanceMeter::Begin() {
	ts.Reset();
	count++;
}


void PerformanceMeter::End() {
	uint64 el = ts.Elapsed();
	total += el;
}

void PerformanceMeterBegin(int id) {
	int i = meters.Find(id);
	if (i == -1) {
		i = meters.GetCount(); 
		meters.Add(id);
		PerformanceMeter& pm = meters[i];
		switch (id) {
			case PERF_CREATEFONT:		pm.SetTitle("Create font"); break;
			case PERF_TEXTWIDTH:		pm.SetTitle("Text width"); break;
			case PERF_DRAWTEXT:			pm.SetTitle("Draw text"); break;
			case PERF_DRAWLISTMARKER:	pm.SetTitle("Draw Listmarker"); break;
			case PERF_IMAGESIZEGET:		pm.SetTitle("Image Size Get"); break;
			case PERF_IMAGESIZEFIND:	pm.SetTitle("Image Size Find"); break;
			case PERF_DRAWBG:			pm.SetTitle("Draw Background"); break;
			case PERF_DRAWBORDERS:		pm.SetTitle("Draw Borders"); break;
			case PERF_LOADMASTERCSS:	pm.SetTitle("Load Master Css"); break;
			case PERF_CSSELEMENTPARSE:	pm.SetTitle("Css Element Parse"); break;
			case PERF_CSSSELPARSE:		pm.SetTitle("Css Selection Parse"); break;
			case PERF_CSSSELCALCSPEC:	pm.SetTitle("Css Selection Calc Spec."); break;
			case PERF_CSSPARSE:			pm.SetTitle("Css Parse"); break;
			case PERF_CREATEDOC:		pm.SetTitle("Create document"); break;
			case PERF_DOCINIT :			pm.SetTitle("Document Init"); break;
			case PERF_DOCADDFONT:		pm.SetTitle("Document Add Font"); break;
			case PERF_GETFONT:			pm.SetTitle("Get Font"); break;
			case PERF_DOCRENDER:		pm.SetTitle("Document Render"); break;
			case PERF_DOCPAINT:			pm.SetTitle("Document Paint"); break;
			case PERF_MOUSEOVER :		pm.SetTitle("Document Mouse Over"); break;
			case PERF_MOUSELEAVE:		pm.SetTitle("Document Mouse Leave"); break;
			case PERF_MOUSELEFTDOWN:	pm.SetTitle("Document Mouse Left Down"); break;
			case PERF_MOUSELEFTUP:		pm.SetTitle("Document Mouse Left Up"); break;
			case PERF_DRAWBG0:			pm.SetTitle("Draw Background 0"); break;
			case PERF_DRAWBG1:			pm.SetTitle("Draw Background 1"); break;
			case PERF_DRAWBG2:			pm.SetTitle("Draw Background 2"); break;
			
			
			default: Panic("Unknown performance-meter id: " + IntStr(id));
		}
		pm.Begin();
	} else {
		PerformanceMeter& pm = meters[i];
		pm.Begin();
	}
}

void PerformanceMeterEnd(int id) {
	int i = meters.Find(id);
	ASSERT(i != -1);
	PerformanceMeter& pm = meters[i];
	
	pm.End();
}
















void AddPathArc(Vector<Point>& poly, double x, double y, double rx, double ry, double a1, double a2, bool neg) {
	if(rx > 0 && ry > 0)
	{
		neg = !neg; // function is counter-clockwise by default
		
		int steps = 12;
		double astep = (a2 - a1) / (steps - 1);
		double asum = 0;
		poly.Reserve(poly.GetCount()+steps);
		for(int i = 0; i < steps; i++) {
			Point& p = poly.Add();
			p.x = x + cos(asum) * rx;
			p.y = y + (neg ? -1 : +1) * sin(asum) * ry;
			asum += astep;
		}
	} else
	{
		poly << Point(x, y);
	}
}

void Arc(Vector<Point>& poly, int xc, int yc, double radius, double angle1, double angle2) {
	AddPathArc(poly, xc, yc, radius, radius, angle1, angle2, false);
}

void LineTo(Vector<Point>& poly, int xc, int yc) {
	Point& p = poly.Add();
	p.x = xc;
	p.y = yc;
}

void DrawEllipseLine(Draw& d, int x, int y, int w, int h, int pen, Color c) {
	double xcenter = x + (double)w*0.5;
	double ycenter = y + (double)h*0.5;
	int steps = 13;
	double astep = 2*M_PI / (steps-1);
	double asum = 0;
	double w2 = w * 0.5;
	double h2 = h * 0.5;
	Vector<Point> poly;
	poly.Reserve(steps);
	for(int i = 0; i < steps; i++) {
		Point& p = poly.Add();
		p.x = xcenter + cos(asum) * w2;
		p.y = ycenter + sin(asum) * h2;
		asum += astep;
	}
	d.DrawPolyline(poly, pen, c);
}

void DrawRectLine(Draw& d, int x, int y, int w, int h, int pen, Color c) {
	d.DrawLine(x, y, x+w, y, pen, c);
	d.DrawLine(x+w, y, x+w, y+h, pen, c);
	d.DrawLine(x, y+h, x+w, y+h, pen, c);
	d.DrawLine(x, y, x, y+h, pen, c);
}

void DrawRoundedRect(Draw& d, const Position& pos, const BorderRadiuses& radius, Color c) {
	Vector<Point> poly;
	if(radius.top_left_x)
	{
		Arc(poly, pos.Left() + radius.top_left_x, pos.Top() + radius.top_left_x, radius.top_left_x, M_PI, M_PI * 3.0 / 2.0);
	} else
	{
		LineTo(poly, pos.Left(), pos.Top());
	}

	LineTo(poly, pos.Right() - radius.top_right_x, pos.Top());

	if(radius.top_right_x)
	{
		Arc(poly, pos.Right() - radius.top_right_x, pos.Top() + radius.top_right_x, radius.top_right_x, M_PI * 3.0 / 2.0, 2.0 * M_PI);
	}

	LineTo(poly, pos.Right(), pos.Bottom() - radius.bottom_right_x);

	if(radius.bottom_right_x)
	{
		Arc(poly, pos.Right() - radius.bottom_right_x, pos.Bottom() - radius.bottom_right_x, radius.bottom_right_x, 0, M_PI / 2.0);
	}

	LineTo(poly, pos.Left() - radius.bottom_left_x, pos.Bottom());

	if(radius.bottom_left_x)
	{
		Arc(poly, pos.Left() + radius.bottom_left_x, pos.Bottom() - radius.bottom_left_x, radius.bottom_left_x, M_PI / 2.0, M_PI);
	}
	
	d.DrawPolygon(poly, c);
}


NAMESPACE_LAYOUT_END

