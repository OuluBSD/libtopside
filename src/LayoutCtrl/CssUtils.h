#ifndef _LayoutCtrl_CssUtils_h_
#define _LayoutCtrl_CssUtils_h_


NAMESPACE_LAYOUT_BEGIN


class PropertyValue
{
public:
	String			value;
	bool			important;

	PropertyValue()
	{
		important = false;
	}
	PropertyValue(const String& val, bool imp)
	{
		important = imp;
		value		= val;
	}
	PropertyValue(const PropertyValue& val)
	{
		value		= val.value;
		important	= val.important;
	}

	PropertyValue& operator=(const PropertyValue& val)
	{
		value		= val.value;
		important	= val.important;
		return *this;
	}
	String ToString() const {return value + " (" + IntStr(important) + ")";}
};

typedef ArrayMap<String, PropertyValue>	PropsMap;

class Style : public Object
{
	
private:
	PropsMap			properties;
	static StrMap		valid_values;
	
	void __CheckStyleDefaultValues();
	
public:
	RTTI_DECL1(Style, Object)
	Style();
	Style(const Style& val);

	void operator=(const Style& val);

	void Add(const String& txt, const String& baseurl)
	{
		Parse(txt, baseurl);
	}

	void AddProperty(const String& name, const String& val, const String& baseurl, bool important);
	
	String GetProperty(const String& name) const
	{
		int f = properties.Find(name);
		if (f != -1) {
			return properties[f].value;
		}
		else return "";
	}

	void Combine(const Style& src);
	void Clear()
	{
		properties.Clear();
	}
	
	int GetCount() {return properties.GetCount();}
	String GetKey(int i) {return properties.GetKey(i);}
	String GetValue(int i) {return properties[i].value;}
	

private:
	void ParseProperty(const String& txt, const String& baseurl);
	void Parse(const String& txt, const String& baseurl);
	void ParseShortBorder(const String& prefix, const String& val, bool important);
	void ParseShortBackground(const String& val, const String& baseurl, bool important);
	void ParseShortFont(const String& val, bool important);
	void AddParsedProperty(const String& name, const String& val, bool important);
	void RemoveProperty(const String& name, bool important);
};



#define  CssUnitsStrings	"none;%;in;cm;mm;em;ex;pt;pc;px;dpi;dpcm;vw;vh;vmin;vmax"

enum CssUnits
{
	CssUnitsNone,
	CssUnitsPercentage,
	CssUnitsIn,
	CssUnitsCm,
	CssUnitsMm,
	CssUnitsEm,
	CssUnitsEx,
	CssUnitsPt,
	CssUnitsPc,
	CssUnitsPx,
	CssUnitsDpi,
	CssUnitsDpcm,
	CssUnitsVw,
	CssUnitsVh,
	CssUnitsVmin,
	CssUnitsVmax,
};

class CssLength
{
	union {
		float	value;
		int		predef;
	};
	
	CssUnits	units;
	bool		is_predefined;
	
public:
	CssLength();
	CssLength(const CssLength& val);

	CssLength&	operator=(const CssLength& val);
	//CssLength&	operator=(float val);
	bool		IsPredefined() const;
	void		PreDefine(int val);
	int			PreDefine() const;
	void		SetValue(float val, CssUnits units);
	float		GetValue() const;
	CssUnits	Units() const;
	int			CalcPercent(int width) const;
	void		FromString(const String& str, const String& predefs = "", int def_value = 0);
};

inline CssLength::CssLength()
{
	value			= 0;
	predef			= 0;
	units			= CssUnitsNone;
	is_predefined	= false;
}

inline CssLength::CssLength(const CssLength& val)
{
	if (val.IsPredefined())
	{
		predef	= val.predef;
	} else
	{
		value		= val.value;
	}
	units			= val.units;
	is_predefined	= val.is_predefined;
}

inline CssLength& CssLength::operator=(const CssLength& val)
{
	if (val.IsPredefined()) {
		predef	= val.predef;
	}
	else {
		value		= val.value;
	}
	units			= val.units;
	is_predefined	= val.is_predefined;
	return *this;
}

/*inline CssLength& CssLength::operator=(float val)
{
	value = val;
	units = CssUnitsPx;
	is_predefined = false;
	return *this;
}*/

inline bool CssLength::IsPredefined() const
{
	return is_predefined;
}

inline void CssLength::PreDefine(int val)
{
	predef		= val;
	is_predefined = true;
}

inline int CssLength::PreDefine() const
{
	if (is_predefined) {
		return predef;
	}
	return 0;
}

inline void CssLength::SetValue(float val, CssUnits units)
{
	value			= val;
	is_predefined	= false;
	this->units		= units;
}

inline float CssLength::GetValue() const
{
	if (!is_predefined)
	{
		return value;
	}
	return 0;
}

inline CssUnits CssLength::Units() const
{
	return units;
}

inline int CssLength::CalcPercent(int width) const
{
	if(!IsPredefined())
	{
		if(Units() == CssUnitsPercentage)
		{
			return (int) ((double) width * (double) value / 100.0);
		} else
		{
			return (int) GetValue();
		}
	}
	return 0;
}


struct CssMargins
{
	CssLength	left;
	CssLength	right;
	CssLength	top;
	CssLength	bottom;

	CssMargins()
	{

	}

	CssMargins(const CssMargins& val)
	{
		left	= val.left;
		right	= val.right;
		top		= val.top;
		bottom	= val.bottom;
	}

	CssMargins& operator=(const CssMargins& val)
	{
		left	= val.left;
		right	= val.right;
		top		= val.top;
		bottom	= val.bottom;
		return *this;
	}
};

struct CssOffsets
{
	CssLength	left;
	CssLength	top;
	CssLength	right;
	CssLength	bottom;

	CssOffsets()
	{

	}

	CssOffsets(const CssOffsets& val)
	{
		left	= val.left;
		top		= val.top;
		right	= val.right;
		bottom	= val.bottom;
	}

	CssOffsets& operator=(const CssOffsets& val)
	{
		left	= val.left;
		top		= val.top;
		right	= val.right;
		bottom	= val.bottom;
		return *this;
	}
};

struct CssPosition
{
	CssLength	x;
	CssLength	y;
	CssLength	width;
	CssLength	height;

	CssPosition()
	{

	}

	CssPosition(const CssPosition& val)
	{
		x		= val.x;
		y		= val.y;
		width	= val.width;
		height	= val.height;
	}

	CssPosition& operator=(const CssPosition& val)
	{
		x		= val.x;
		y		= val.y;
		width	= val.width;
		height	= val.height;
		return *this;
	}
};


struct SelectorSpecificity
{
	int		a;
	int		b;
	int		c;
	int		d;

	SelectorSpecificity(int va = 0, int vb = 0, int vc = 0, int vd = 0)
	{
		a	= va;
		b	= vb;
		c	= vc;
		d	= vd;
	}

	void operator += (const SelectorSpecificity& val)
	{
		a	+= val.a;
		b	+= val.b;
		c	+= val.c;
		d	+= val.d;
	}

	bool operator==(const SelectorSpecificity& val) const
	{
		if(a == val.a && b == val.b && c == val.c && d == val.d)
		{
			return true;
		}
		return false;
	}

	bool operator!=(const SelectorSpecificity& val) const
	{
		if(a != val.a || b != val.b || c != val.c || d != val.d)
		{
			return true;
		}
		return false;
	}

	bool operator > (const SelectorSpecificity& val) const
	{
		if (a > val.a) {
			return true;
		}
		else if(a < val.a) {
			return false;
		}
		else {
			if(b > val.b)
			{
				return true;
			}
			else if(b < val.b)
			{
				return false;
			}
			else
			{
				if(c > val.c)
				{
					return true;
				}
				else if(c < val.c)
				{
					return false;
				}
				else
				{
					if(d > val.d)
					{
						return true;
					}
					else if(d < val.d)
					{
						return false;
					}
				}
			}
		}
		return false;
	}

	bool operator >= (const SelectorSpecificity& val) const
	{
		if((*this) == val) return true;
		if((*this) > val) return true;
		return false;
	}

	bool operator <= (const SelectorSpecificity& val) const
	{
		if((*this) > val)
		{
			return false;
		}
		return true;
	}

	bool operator < (const SelectorSpecificity& val) const
	{
		if((*this) <= val && (*this) != val)
		{
			return true;
		}
		return false;
	}

};

enum AttrSelectCondition
{
	SelectExists,
	SelectEqual,
	SelectContainStr,
	SelectStartStr,
	SelectEndStr,
	SelectPseudoClass,
	SelectPseudoElement,
};

struct CssAttributeSelector : Moveable<CssAttributeSelector>
{
	typedef Vector<CssAttributeSelector>	vector;

	String					attribute;
	String					val;
	AttrSelectCondition		condition;

	CssAttributeSelector()
	{
		condition = SelectExists;
	}

	CssAttributeSelector(const CssAttributeSelector& val)
	{
		this->val	= val.val;
		condition	= val.condition;
		attribute	= val.attribute;
	}
};


class CssElementSelector
{
public:
	String							tag;
	CssAttributeSelector::vector	attrs;
public:
	CssElementSelector()
	{

	}

	CssElementSelector(const CssElementSelector& val);

	void Parse(const String& txt);
	CssElementSelector& operator = (const CssElementSelector& es);
};


enum CssCombinator
{
	CombinatorDescendant,
	CombinatorChild,
	CombinatorAdjacentSibling,
	CombinatorGeneralSibling
};


class CssSelector : public Object, public Moveable<CssSelector>
{
	
public:
	typedef Vector<One<CssSelector> > vector;
	
public:
	SelectorSpecificity		specificity;
	CssElementSelector		right;
	One<CssSelector>		left;
	CssCombinator			combinator;
	Style*					style = NULL;
	int						order;
	Ptr<MediaQueryList>		media_query;
	
public:
	RTTI_DECL1(CssSelector, Object)
	CssSelector(MediaQueryList* media)
	{
		media_query	= media;
		combinator	= CombinatorDescendant;
		order		= 0;
	}

	CssSelector(const CssSelector& val)
	{
		right			= val.right;
		if(val.left)
		{
			left			= new CssSelector(*val.left);
		} else
		{
			left = 0;
		}
		combinator	= val.combinator;
		specificity	= val.specificity;
		order		= val.order;
		media_query	= val.media_query;
	}

	bool Parse(const String& text);
	void CalcSpecificity();
	bool IsMediaValid() const;
};

typedef const CssSelector ConstCssSelector;


inline bool CssSelector::IsMediaValid() const
{
	if(!media_query)
	{
		return true;
	}
	return media_query->IsUsed();
}


inline bool operator > (const CssSelector& v1, const CssSelector& v2)
{
	if(v1.specificity == v2.specificity)
	{
		return (v1.order > v2.order);
	}
	return (v1.specificity > v2.specificity);
}

inline bool operator < (const CssSelector& v1, const CssSelector& v2)
{
	if(v1.specificity == v2.specificity)
	{
		return (v1.order < v2.order);
	}
	return (v1.specificity < v2.specificity);
}

/*inline bool operator > (CssSelector* v1, CssSelector* v2)
{
	return (*v1 > *v2);
}

inline bool operator < (CssSelector* v1, CssSelector* v2)
{
	return (*v1 < *v2);
}*/





class UsedSelector : public Object
{
public:
	RTTI_DECL1(UsedSelector, Object)
	typedef Vector<UsedSelector*>	vector;

	ConstCssSelector*	selector;
	bool				used;

	UsedSelector(ConstCssSelector* selector, bool used)
	{
		this->used		= used;
		this->selector	= selector;
	}
};














struct CssBorder
{
	CssLength		width;
	BorderStyle		style;
	RGBA			color;

	CssBorder()
	{
		style = BorderStyleNone;
	}

	CssBorder(const CssBorder& val)
	{
		width	= val.width;
		style	= val.style;
		color	= val.color;
	}

	CssBorder& operator=(const CssBorder& val)
	{
		width	= val.width;
		style	= val.style;
		color	= val.color;
		return *this;
	}
};

struct Border
{
	int				width;
	BorderStyle		style;
	RGBA			color;

	Border()
	{
		width = 0;
	}
	Border(const Border& val)
	{
		width = val.width;
		style = val.style;
		color = val.color;
	}
	Border(const CssBorder& val)
	{
		width = (int) val.width.GetValue();
		style = val.style;
		color = val.color;
	}
	Border& operator=(const Border& val)
	{
		width = val.width;
		style = val.style;
		color = val.color;
		return *this;
	}
	Border& operator=(const CssBorder& val)
	{
		width = (int) val.width.GetValue();
		style = val.style;
		color = val.color;
		return *this;
	}
};

struct BorderRadiuses
{
	int	top_left_x;
	int	top_left_y;

	int	top_right_x;
	int	top_right_y;

	int	bottom_right_x;
	int	bottom_right_y;

	int	bottom_left_x;
	int	bottom_left_y;
	
	BorderRadiuses()
	{
		top_left_x = 0;
		top_left_y = 0;
		top_right_x = 0;
		top_right_y = 0;
		bottom_right_x = 0;
		bottom_right_y = 0;
		bottom_left_x = 0;
		bottom_left_y = 0;
	}
	BorderRadiuses(const BorderRadiuses& val)
	{
		top_left_x = val.top_left_x;
		top_left_y = val.top_left_y;
		top_right_x = val.top_right_x;
		top_right_y = val.top_right_y;
		bottom_right_x = val.bottom_right_x;
		bottom_right_y = val.bottom_right_y;
		bottom_left_x = val.bottom_left_x;
		bottom_left_y = val.bottom_left_y;
	}
	BorderRadiuses& operator = (const BorderRadiuses& val)
	{
		top_left_x = val.top_left_x;
		top_left_y = val.top_left_y;
		top_right_x = val.top_right_x;
		top_right_y = val.top_right_y;
		bottom_right_x = val.bottom_right_x;
		bottom_right_y = val.bottom_right_y;
		bottom_left_x = val.bottom_left_x;
		bottom_left_y = val.bottom_left_y;
		return *this;
	}
	void operator += (const Margins& mg)
	{
		top_left_x += mg.left;
		top_left_y += mg.top;
		top_right_x += mg.right;
		top_right_y += mg.top;
		bottom_right_x += mg.right;
		bottom_right_y += mg.bottom;
		bottom_left_x += mg.left;
		bottom_left_y += mg.bottom;
		fix_values();
	}
	void operator -= (const Margins& mg)
	{
		top_left_x -= mg.left;
		top_left_y -= mg.top;
		top_right_x -= mg.right;
		top_right_y -= mg.top;
		bottom_right_x -= mg.right;
		bottom_right_y -= mg.bottom;
		bottom_left_x -= mg.left;
		bottom_left_y -= mg.bottom;
		fix_values();
	}
	void fix_values()
	{
		if (top_left_x < 0)	top_left_x = 0;
		if (top_left_y < 0)	top_left_y = 0;
		if (top_right_x < 0) top_right_x = 0;
		if (bottom_right_x < 0) bottom_right_x = 0;
		if (bottom_right_y < 0) bottom_right_y = 0;
		if (bottom_left_x < 0) bottom_left_x = 0;
		if (bottom_left_y < 0) bottom_left_y = 0;
	}
	bool IsZero() const {
		return
			(top_left_x == 0 || top_left_y == 0) &&
			(top_right_x == 0 || top_right_y == 0) &&
			(bottom_right_x == 0 || bottom_right_y == 0) &&
			(bottom_left_x == 0 || bottom_left_y == 0);
	}
	
};

struct CssBorderRadius
{
	CssLength	top_left_x;
	CssLength	top_left_y;

	CssLength	top_right_x;
	CssLength	top_right_y;

	CssLength	bottom_right_x;
	CssLength	bottom_right_y;

	CssLength	bottom_left_x;
	CssLength	bottom_left_y;

	CssBorderRadius()
	{

	}

	CssBorderRadius(const CssBorderRadius& val)
	{
		top_left_x		= val.top_left_x;
		top_left_y		= val.top_left_y;
		top_right_x		= val.top_right_x;
		top_right_y		= val.top_right_y;
		bottom_left_x	= val.bottom_left_x;
		bottom_left_y	= val.bottom_left_y;
		bottom_right_x	= val.bottom_right_x;
		bottom_right_y	= val.bottom_right_y;
	}

	CssBorderRadius& operator=(const CssBorderRadius& val)
	{
		top_left_x		= val.top_left_x;
		top_left_y		= val.top_left_y;
		top_right_x		= val.top_right_x;
		top_right_y		= val.top_right_y;
		bottom_left_x	= val.bottom_left_x;
		bottom_left_y	= val.bottom_left_y;
		bottom_right_x	= val.bottom_right_x;
		bottom_right_y	= val.bottom_right_y;
		return *this;
	}
	BorderRadiuses CalcPercents(int width, int height)
	{
		BorderRadiuses ret;
		ret.bottom_left_x = bottom_left_x.CalcPercent(width);
		ret.bottom_left_y = bottom_left_y.CalcPercent(height);
		ret.top_left_x = top_left_x.CalcPercent(width);
		ret.top_left_y = top_left_y.CalcPercent(height);
		ret.top_right_x = top_right_x.CalcPercent(width);
		ret.top_right_y = top_right_y.CalcPercent(height);
		ret.bottom_right_x = bottom_right_x.CalcPercent(width);
		ret.bottom_right_y = bottom_right_y.CalcPercent(height);
		return ret;
	}
};

struct CssBorders
{
	CssBorder			left;
	CssBorder			top;
	CssBorder			right;
	CssBorder			bottom;
	CssBorderRadius		radius;

	CssBorders()
	{

	}

	CssBorders(const CssBorders& val)
	{
		left	= val.left;
		right	= val.right;
		top		= val.top;
		bottom	= val.bottom;
		radius	= val.radius;
	}

	CssBorders& operator=(const CssBorders& val)
	{
		left	= val.left;
		right	= val.right;
		top		= val.top;
		bottom	= val.bottom;
		radius	= val.radius;
		return *this;
	}
};

struct Borders
{
	Border			left;
	Border			top;
	Border			right;
	Border			bottom;
	BorderRadiuses	radius;

	Borders()
	{

	}

	Borders(const Borders& val)
	{
		left = val.left;
		right = val.right;
		top = val.top;
		bottom = val.bottom;
		radius = val.radius;
	}

	Borders(const CssBorders& val)
	{
		left = val.left;
		right = val.right;
		top = val.top;
		bottom = val.bottom;
	}

	Borders& operator=(const Borders& val)
	{
		left = val.left;
		right = val.right;
		top = val.top;
		bottom = val.bottom;
		radius = val.radius;
		return *this;
	}

	Borders& operator=(const CssBorders& val)
	{
		left = val.left;
		right = val.right;
		top = val.top;
		bottom = val.bottom;
		return *this;
	}
};













class Background
{
public:
	int						cache_id;
	String					image;
	String					baseurl;
	RGBA					color;
	BackgroundAttachment	attachment;
	CssPosition				position;
	BackgroundRepeat		repeat;
	BackgroundBox			clip;
	BackgroundBox			origin;
	CssBorderRadius			radius;

public:
	Background();
	Background(const Background& val);
	
	Background& operator=(const Background& val);
};

class BackgroundPaint
{
public:
	int						cache_id;
	String					image;
	String					baseurl;
	BackgroundAttachment	attachment;
	BackgroundRepeat		repeat;
	RGBA					color;
	Position				clip_box;
	Position				origin_box;
	Position				border_box;
	BorderRadiuses			border_radius;
	Size					image_size;
	int						position_x;
	int						position_y;
	bool					is_root;
public:
	BackgroundPaint();
	BackgroundPaint(const BackgroundPaint& val);
	void operator=(const Background& val);
};










struct CssText : public Moveable<CssText>
{
	typedef Vector<CssText>	vector;

	String	text;
	String	baseurl;
	String	media;
	
	CssText() {baseurl = ""; baseurl = ""; media = "";}
	CssText(const String& txt) : text(txt) {baseurl	= ""; media	= "";}
	CssText(const String& txt, const String& url) : text(txt), baseurl(url) {media	= "";}
	CssText(const String& txt, const String& url, const String& media_str)
		 : text(txt), baseurl(url), media(media_str) {}

	CssText(const CssText& val)
	{
		text	= val.text;
		baseurl	= val.baseurl;
		media	= val.media;
	}
};








void DrawRoundedRect(Draw& d, const Position& pos, const BorderRadiuses& radius, Color c);


NAMESPACE_LAYOUT_END

#endif
