#include "LayoutCtrl.h"

NAMESPACE_LAYOUT_BEGIN


void CssLength::FromString(const String& str, const String& predefs, int def_value)
{
	
	// TODO: Make support for calc
	if (str.Mid(0, 4) == "calc")
	{
		is_predefined = true;
		predef		= 0;
		return;
	}

	int predef = ValueIndex(str, predefs, -1);
	if (predef >= 0)
	{
		is_predefined		= true;
		this->predef		= predef;
	}
	else {
		is_predefined = false;

		String num;
		String un;
		bool is_unit = false;
		
		for (int i = 0; i < str.GetCount(); i++) {
			int chr = str[i];
			if (!is_unit) {
				if (IsDigit(chr) || chr == '.' || chr == '+' || chr == '-') {
					num.Cat(chr);
				} else {
					is_unit = true;
				}
			}
			if (is_unit) {
				un += chr;
			}
		}
		if (!num.IsEmpty()) {
			value = StrDbl(num);
			units	= (CssUnits) ValueIndex(un, CssUnitsStrings, CssUnitsNone);
		}
		else {
			// not a number so it is predefined
			is_predefined = true;
			predef = def_value;
		}
	}
}













CssElementSelector::CssElementSelector(const CssElementSelector& val)
{
	tag	= val.tag;
	attrs	<<= val.attrs;
}


CssElementSelector& CssElementSelector::operator = (const CssElementSelector& es) {
	tag = es.tag;
	attrs <<= es.attrs;
	return *this;
}
	
void CssElementSelector::Parse(const String& txt)
{
	int el_end = FindFirstOf(txt, ".#[:");
	if (el_end >= 0)
		tag = txt.Mid(0, el_end);
	else
		tag = txt;
	LowerCase(tag);
	while(el_end != -1)
	{
		if(txt[el_end] == '.') {
			CssAttributeSelector attribute;

			int pos = FindFirstOf(txt, ".#[:", el_end + 1);
			if (pos != -1)
				attribute.val		= txt.Mid(el_end + 1, pos - el_end - 1);
			else
				attribute.val		= txt.Mid(el_end + 1);
			attribute.condition	= SelectEqual;
			attribute.attribute	= "class";
			attrs.Add(attribute);
			el_end = pos;
		}
		else if (txt[el_end] == ':') {
			CssAttributeSelector attribute;

			if (txt[el_end + 1] == ':') {
				int pos = FindFirstOf(txt, ".#[:", el_end + 2);
				if (pos != -1)
					attribute.val		= txt.Mid(el_end + 2, pos - el_end - 2);
				else
					attribute.val		= txt.Mid(el_end + 2);
				
				attribute.condition	= SelectPseudoElement;
				LowerCase(attribute.val);
				attribute.attribute	= "pseudo-el";
				attrs.Add(attribute);
				el_end = pos;
			}
			else {
				int pos = FindFirstOf(txt, ".#[:(", el_end + 1);
				if (pos != -1 && txt[pos] == '(') {
					pos = FindCloseBracket(txt, pos);
					if(pos != -1) {
						pos++;
					}
					else {
						int iii = 0;
						iii++;
					}
				}
				if(pos != -1) {
					attribute.val		= txt.Mid(el_end + 1, pos - el_end - 1);
				}
				else {
					attribute.val		= txt.Mid(el_end + 1);
				}
				LowerCase(attribute.val);
				if(attribute.val == "after" || attribute.val == "before") {
					attribute.condition	= SelectPseudoElement;
				}
				else {
					attribute.condition	= SelectPseudoClass;
				}
				attribute.attribute	= "pseudo";
				attrs.Add(attribute);
				el_end = pos;
			}
		} else if(txt[el_end] == '#')
		{
			CssAttributeSelector attribute;

			int pos = FindFirstOf(txt, ".#[:", el_end + 1);
			if (pos == -1)		attribute.val		= txt.Mid(el_end + 1);
			else				attribute.val		= txt.Mid(el_end + 1, pos - el_end - 1);
			attribute.condition	= SelectEqual;
			attribute.attribute	= "id";
			attrs.Add(attribute);
			el_end = pos;
		} else if(txt[el_end] == '[')
		{
			CssAttributeSelector attribute;

			int pos = FindFirstOf(txt, "]~=|$*^", el_end + 1);
			String attr;
			if (pos == -1)		attr = txt.Mid(el_end + 1);
			else				attr = txt.Mid(el_end + 1, pos - el_end - 1);
			Trim(attr);
			LowerCase(attr);
			if(pos != -1)
			{
				if(txt[pos] == ']')
				{
					attribute.condition = SelectExists;
				}
				else if(txt[pos] == '=')
				{
					attribute.condition = SelectEqual;
					pos++;
				}
				else if(txt.Mid(pos, 2) == "~=")
				{
					attribute.condition = SelectContainStr;
					pos += 2;
				}
				else if(txt.Mid(pos, 2) == "|=")
				{
					attribute.condition = SelectStartStr;
					pos += 2;
				}
				else if(txt.Mid(pos, 2) == "^=")
				{
					attribute.condition = SelectStartStr;
					pos += 2;
				}
				else if(txt.Mid(pos, 2) == "$=")
				{
					attribute.condition = SelectEndStr;
					pos += 2;
				}
				else if(txt.Mid(pos, 2) == "*=")
				{
					attribute.condition = SelectContainStr;
					pos += 2;
				}
				else
				{
					attribute.condition = SelectExists;
					pos += 1;
				}
				//pos = txt.find_first_not_of(" \t"), pos);
				pos = FindFirstNotOf(txt, " \t", pos);
				if(pos != -1)
				{
					if(txt[pos] == '"')
					{
						int pos2 = FindFirstOf(txt, '\"', pos + 1);
						attribute.val = txt.Mid(pos + 1, pos2 == -1 ? pos2 : (pos2 - pos - 1));
						pos = pos2 == -1 ? pos2 : (pos2 + 1);
					} else if(txt[pos] == ']')
					{
						pos ++;
					} else
					{
						int pos2 = FindFirstOf(txt, "]", pos + 1);
						attribute.val = txt.Mid(pos, pos2 == -1 ? pos2 : (pos2 - pos));
						Trim(attribute.val);
						pos = pos2 == -1 ? pos2 : (pos2 + 1);
					}
				}
			} else
			{
				attribute.condition = SelectExists;
			}
			attribute.attribute	= attr;
			attrs.Add(attribute);
			el_end = pos;
		} else
		{
			el_end++;
		}
		el_end = FindFirstOf(txt, ".#[:", el_end);
	}
}


bool CssSelector::Parse( const String& text )
{
	if (text.IsEmpty())
	{
		return false;
	}
	StringVector tokens;
	SplitString(text, tokens, "", " \t>+~", "([");

	if (tokens.IsEmpty())
	{
		return false;
	}

	String left;
	String right = LAST(tokens);
	wchar combinator = 0;

	REMOVELAST(tokens);
	while(!tokens.IsEmpty() && (LAST(tokens) == " " || LAST(tokens) == "\t" || LAST(tokens) == "+" || LAST(tokens) == "~" || LAST(tokens) == ">"))
	{
		if(combinator == ' ' || combinator == 0) {
			combinator = LAST(tokens)[0];
		}
		REMOVELAST(tokens);
	}

	for(StringVector::Iterator i = tokens.Begin(); i != tokens.End(); i++)
	{
		left += *i;
	}

	Trim(left);
	Trim(right);

	if (right.IsEmpty()) {
		return false;
	}

	this->right.Parse(right);

	switch(combinator)
	{
	case '>':
		combinator	= CombinatorChild;
		break;
	case '+':
		combinator	= CombinatorAdjacentSibling;
		break;
	case '~':
		combinator	= CombinatorGeneralSibling;
		break;
	default:
		combinator	= CombinatorDescendant;
		break;
	}

	left.Clear();

	if (!left.IsEmpty()) {
		this->left = new CssSelector(NULL);
		if (!this->left->Parse(left))
			return false;
	}
	return true;
}

void CssSelector::CalcSpecificity()
{
	if(!right.tag.IsEmpty() && right.tag != "*") {
		specificity.d = 1;
	}
	
	for (CssAttributeSelector::vector::Iterator i = right.attrs.Begin(); i != right.attrs.End(); i++)
	{
		if (i->attribute == "id") {
			specificity.b++;
		}
		else {
			if (i->attribute == "class") {
				StringVector tokens;
				SplitString(i->val, tokens, " ");
				specificity.c += (int) tokens.GetCount();
			}
			else {
				specificity.c++;
			}
		}
	}
	if (left) {
		left->CalcSpecificity();
		specificity += left->specificity;
	}
}










Background::Background()
{
	attachment	= BackgroundAttachmentScroll;
	repeat		= BackgroundRepeatRepeat;
	clip		= BackgroundBoxBorder;
	origin		= BackgroundBoxPadding;
	color		= RGBAZero();
	cache_id	= -1;
}

Background::Background(const Background& val)
{
	image			= val.image;
	baseurl			= val.baseurl;
	color			= val.color;
	attachment		= val.attachment;
	position		= val.position;
	repeat			= val.repeat;
	clip			= val.clip;
	origin			= val.origin;
	cache_id		= -1;
}

Background& Background::operator=( const Background& val )
{
	image			= val.image;
	baseurl			= val.baseurl;
	color			= val.color;
	attachment		= val.attachment;
	position		= val.position;
	repeat			= val.repeat;
	clip			= val.clip;
	origin			= val.origin;
	return *this;
}


BackgroundPaint::BackgroundPaint()
{
	color			= RGBAZero();
	position_x		= 0;
	position_y		= 0;
	attachment		= BackgroundAttachmentScroll;
	repeat			= BackgroundRepeatRepeat;
	is_root			= false;
	cache_id		= -1;
}

BackgroundPaint::BackgroundPaint(const BackgroundPaint& val)
{
	image			= val.image;
	baseurl			= val.baseurl;
	attachment		= val.attachment;
	repeat			= val.repeat;
	color			= val.color;
	clip_box		= val.clip_box;
	origin_box		= val.origin_box;
	border_box		= val.border_box;
	border_radius	= val.border_radius;
	image_size		= val.image_size;
	position_x		= val.position_x;
	position_y		= val.position_y;
	is_root			= val.is_root;
}

void BackgroundPaint::operator=(const Background& val)
{
	attachment	= val.attachment;
	baseurl		= val.baseurl;
	image		= val.image;
	repeat		= val.repeat;
	color		= val.color;
	cache_id	= val.cache_id;
}















StrMap Style::valid_values;



void Style::__CheckStyleDefaultValues() {
	if (valid_values.GetCount() == 0) {
		valid_values.Add("white-space", WhiteSpaceStrings);
	}
}

Style::Style() {
	__CheckStyleDefaultValues();
}

Style::Style( const Style& val )
{
	__CheckStyleDefaultValues();
	
	properties <<= val.properties;
}

void Style::operator=(const Style& val) {
	//LOG("void operator=(const Style& val) {");
	properties <<= val.properties;
}


void Style::Parse( const String& txt, const String& baseurl )
{
	Vector<String> properties;
	SplitString(txt, properties, ";");

	for(Vector<String>::Iterator i = properties.Begin(); i != properties.End(); i++)
	{
		ParseProperty(*i, baseurl);
	}
}

void Style::ParseProperty( const String& txt, const String& baseurl )
{
	int pos = txt.FindFirstOf(":");
	if(pos != -1)
	{
		String name	= txt.Mid(0, pos);
		String val		= txt.Mid(pos + 1);

		Trim(name);
		Trim(val);

		LowerCase(name);

		if(!name.IsEmpty() && !val.IsEmpty())
		{
			StringVector vals;
			SplitString(val, vals, "!");
			if(vals.GetCount() == 1)
			{
				AddProperty(name, val, baseurl, false);
			} else if(vals.GetCount() > 1)
			{
				Trim(vals[0]);
				LowerCase(vals[1]);
				if(vals[1] == "important")
				{
					AddProperty(name, vals[0], baseurl, true);
				} else
				{
					AddProperty(name, vals[0], baseurl, false);
				}
			}
		}
	}
}

void Style::Combine( const Style& src )
{
	for (int i = 0; i < src.properties.GetCount(); i++)
	{
		String str = src.properties.GetKey(i);
		if (str.IsEmpty())
			continue;
		const PropertyValue& pv = src.properties[i];
		AddParsedProperty(str, pv.value, pv.important);
	}
}

void Style::AddProperty( const String& name, const String& val, const String& baseurl, bool important )
{
	//LOG("Style::AddProperty: " << name << " = " << val);
	if(!name.GetCount() || !val.GetCount())
	{
		return;
	}

	// Add baseurl for background image 
	if(	!name.Compare("background-image"))
	{
		AddParsedProperty(name, val, important);
		if(baseurl.GetCount())
		{
			AddParsedProperty("background-image-baseurl", baseurl, important);
		}
	} else

	// Parse Border spacing properties 
	if(	!name.Compare("border-spacing"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() == 1)
		{
			AddProperty("-litehtml-border-spacing-x", tokens[0], baseurl, important);
			AddProperty("-litehtml-border-spacing-y", tokens[0], baseurl, important);
		} else if(tokens.GetCount() == 2)
		{
			AddProperty("-litehtml-border-spacing-x", tokens[0], baseurl, important);
			AddProperty("-litehtml-border-spacing-y", tokens[1], baseurl, important);
		}
	} else

	// Parse Borders shorthand properties 

	if(	!name.Compare("border"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ", "", "(");
		int idx;
		String str;
		for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
		{
			idx = ValueIndex(*tok, BorderStyleStrings, -1);
			if(idx >= 0)
			{
				AddProperty("border-left-style", *tok, baseurl, important);
				AddProperty("border-right-style", *tok, baseurl, important);
				AddProperty("border-top-style", *tok, baseurl, important);
				AddProperty("border-bottom-style", *tok, baseurl, important);
			} else
			{
				if(IsColor(*tok))
				{
					AddProperty("border-left-color", *tok, baseurl, important);
					AddProperty("border-right-color", *tok, baseurl, important);
					AddProperty("border-top-color", *tok, baseurl, important);
					AddProperty("border-bottom-color", *tok, baseurl, important);
				} else
				{
					AddProperty("border-left-width", *tok, baseurl, important);
					AddProperty("border-right-width", *tok, baseurl, important);
					AddProperty("border-top-width", *tok, baseurl, important);
					AddProperty("border-bottom-width", *tok, baseurl, important);
				}
			}
		}
	} else if(	!name.Compare("border-left")	||
		!name.Compare("border-right")	||
		!name.Compare("border-top")	||
		!name.Compare("border-bottom") )
	{
		StringVector tokens;
		SplitString(val, tokens, " ", "", "(");
		int idx;
		String str;
		for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
		{
			idx = ValueIndex(*tok, BorderStyleStrings, -1);
			if(idx >= 0)
			{
				str = name;
				str += "-style";
				AddProperty(str, *tok, baseurl, important);
			} else
			{
				if(IsColor(*tok))
				{
					str = name;
					str += "-color";
					AddProperty(str, *tok, baseurl, important);
				} else
				{
					str = name;
					str += "-width";
					AddProperty(str, *tok, baseurl, important);
				}
			}
		}
	} else 

	// Parse Border radius shorthand properties 
	if(!name.Compare("border-bottom-left-radius"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() >= 2)
		{
			AddProperty("border-bottom-left-radius-x", tokens[0], baseurl, important);
			AddProperty("border-bottom-left-radius-y", tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 1)
		{
			AddProperty("border-bottom-left-radius-x", tokens[0], baseurl, important);
			AddProperty("border-bottom-left-radius-y", tokens[0], baseurl, important);
		}

	} else if(!name.Compare("border-bottom-right-radius"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() >= 2)
		{
			AddProperty("border-bottom-right-radius-x", tokens[0], baseurl, important);
			AddProperty("border-bottom-right-radius-y", tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 1)
		{
			AddProperty("border-bottom-right-radius-x", tokens[0], baseurl, important);
			AddProperty("border-bottom-right-radius-y", tokens[0], baseurl, important);
		}

	} else if(!name.Compare("border-top-right-radius"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() >= 2)
		{
			AddProperty("border-top-right-radius-x", tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-y", tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 1)
		{
			AddProperty("border-top-right-radius-x", tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-y", tokens[0], baseurl, important);
		}

	} else if(!name.Compare("border-top-left-radius"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() >= 2)
		{
			AddProperty("border-top-left-radius-x", tokens[0], baseurl, important);
			AddProperty("border-top-left-radius-y", tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 1)
		{
			AddProperty("border-top-left-radius-x", tokens[0], baseurl, important);
			AddProperty("border-top-left-radius-y", tokens[0], baseurl, important);
		}

	} else 

	// Parse border-radius shorthand properties 
	if(!name.Compare("border-radius"))
	{
		StringVector tokens;
		SplitString(val, tokens, "/");
		if(tokens.GetCount() == 1)
		{
			AddProperty("border-radius-x", tokens[0], baseurl, important);
			AddProperty("border-radius-y", tokens[0], baseurl, important);
		} else if(tokens.GetCount() >= 2)
		{
			AddProperty("border-radius-x", tokens[0], baseurl, important);
			AddProperty("border-radius-y", tokens[1], baseurl, important);
		}
	} else if(!name.Compare("border-radius-x"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() == 1)
		{
			AddProperty("border-top-left-radius-x",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-x",		tokens[0], baseurl, important);
			AddProperty("border-bottom-right-radius-x",	tokens[0], baseurl, important);
			AddProperty("border-bottom-left-radius-x",	tokens[0], baseurl, important);
		} else if(tokens.GetCount() == 2)
		{
			AddProperty("border-top-left-radius-x",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-x",		tokens[1], baseurl, important);
			AddProperty("border-bottom-right-radius-x",	tokens[0], baseurl, important);
			AddProperty("border-bottom-left-radius-x",	tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 3)
		{
			AddProperty("border-top-left-radius-x",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-x",		tokens[1], baseurl, important);
			AddProperty("border-bottom-right-radius-x",	tokens[2], baseurl, important);
			AddProperty("border-bottom-left-radius-x",	tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 4)
		{
			AddProperty("border-top-left-radius-x",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-x",		tokens[1], baseurl, important);
			AddProperty("border-bottom-right-radius-x",	tokens[2], baseurl, important);
			AddProperty("border-bottom-left-radius-x",	tokens[3], baseurl, important);
		}
	} else if(!name.Compare("border-radius-y"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() == 1)
		{
			AddProperty("border-top-left-radius-y",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-y",		tokens[0], baseurl, important);
			AddProperty("border-bottom-right-radius-y",	tokens[0], baseurl, important);
			AddProperty("border-bottom-left-radius-y",	tokens[0], baseurl, important);
		} else if(tokens.GetCount() == 2)
		{
			AddProperty("border-top-left-radius-y",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-y",		tokens[1], baseurl, important);
			AddProperty("border-bottom-right-radius-y",	tokens[0], baseurl, important);
			AddProperty("border-bottom-left-radius-y",	tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 3)
		{
			AddProperty("border-top-left-radius-y",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-y",		tokens[1], baseurl, important);
			AddProperty("border-bottom-right-radius-y",	tokens[2], baseurl, important);
			AddProperty("border-bottom-left-radius-y",	tokens[1], baseurl, important);
		} else if(tokens.GetCount() == 4)
		{
			AddProperty("border-top-left-radius-y",		tokens[0], baseurl, important);
			AddProperty("border-top-right-radius-y",		tokens[1], baseurl, important);
			AddProperty("border-bottom-right-radius-y",	tokens[2], baseurl, important);
			AddProperty("border-bottom-left-radius-y",	tokens[3], baseurl, important);
		}
	}
	

	// Parse list-style shorthand properties 
	if(!name.Compare("list-style"))
	{
		AddParsedProperty("list-style-type",			"disc",		important);
		AddParsedProperty("list-style-position",		"outside",	important);
		AddParsedProperty("list-style-image",			"",			important);
		AddParsedProperty("list-style-image-baseurl",	"",			important);

		StringVector tokens;
		SplitString(val, tokens, " ", "", "(");
		for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
		{
			int idx = ValueIndex(*tok, ListStyleTypeStrings, -1);
			if(idx >= 0)
			{
				AddParsedProperty("list-style-type", *tok, important);
			} else
			{
				idx = ValueIndex(*tok, ListStylepositionStrings, -1);
				if(idx >= 0)
				{
					AddParsedProperty("list-style-position", *tok, important);
				} else if(!val.Compare("url"))
				{
					AddParsedProperty("list-style-image", *tok, important);
					if(baseurl.GetCount())
					{
						AddParsedProperty("list-style-image-baseurl", baseurl, important);
					}
				}
			}
		}
	} else 

	// Add baseurl for background image 
	if(	!name.Compare("list-style-image"))
	{
		AddParsedProperty(name, val, important);
		if(baseurl.GetCount())
		{
			AddParsedProperty("list-style-image-baseurl", baseurl, important);
		}
	} else
		
	// Parse background shorthand properties 
	if(!name.Compare("background"))
	{
		ParseShortBackground(val, baseurl, important);

	} else 
		
	// Parse margin and padding shorthand properties 
	if(!name.Compare("margin") || !name.Compare("padding"))
	{
		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() >= 4)
		{
			AddParsedProperty(name + "-top",		tokens[0], important);
			AddParsedProperty(name + "-right",		tokens[1], important);
			AddParsedProperty(name + "-bottom",	tokens[2], important);
			AddParsedProperty(name + "-left",		tokens[3], important);
		} else if(tokens.GetCount() == 3)
		{
			AddParsedProperty(name + "-top",		tokens[0], important);
			AddParsedProperty(name + "-right",		tokens[1], important);
			AddParsedProperty(name + "-left",		tokens[1], important);
			AddParsedProperty(name + "-bottom",	tokens[2], important);
		} else if(tokens.GetCount() == 2)
		{
			AddParsedProperty(name + "-top",		tokens[0], important);
			AddParsedProperty(name + "-bottom",	tokens[0], important);
			AddParsedProperty(name + "-right",		tokens[1], important);
			AddParsedProperty(name + "-left",		tokens[1], important);
		} else if(tokens.GetCount() == 1)
		{
			AddParsedProperty(name + "-top",		tokens[0], important);
			AddParsedProperty(name + "-bottom",	tokens[0], important);
			AddParsedProperty(name + "-right",		tokens[0], important);
			AddParsedProperty(name + "-left",		tokens[0], important);
		}
	} else 
		
		
	// Parse border-* shorthand properties 
	if(	!name.Compare("border-left") || 
		!name.Compare("border-right") ||
		!name.Compare("border-top")  || 
		!name.Compare("border-bottom"))
	{
		ParseShortBorder(name, val, important);
	} else 
		
	// Parse border-width/Style/color shorthand properties 
	if(	!name.Compare("border-width") ||
		!name.Compare("border-style")  ||
		!name.Compare("border-color"))
	{
		StringVector nametokens;
		SplitString(name, nametokens, "-");

		StringVector tokens;
		SplitString(val, tokens, " ");
		if(tokens.GetCount() >= 4)
		{
			AddParsedProperty(nametokens[0] + "-top-"		+ nametokens[1],	tokens[0], important);
			AddParsedProperty(nametokens[0] + "-right-"	+ nametokens[1],	tokens[1], important);
			AddParsedProperty(nametokens[0] + "-bottom-"	+ nametokens[1],	tokens[2], important);
			AddParsedProperty(nametokens[0] + "-left-"	+ nametokens[1],	tokens[3], important);
		} else if(tokens.GetCount() == 3)
		{
			AddParsedProperty(nametokens[0] + "-top-"		+ nametokens[1],	tokens[0], important);
			AddParsedProperty(nametokens[0] + "-right-"	+ nametokens[1],	tokens[1], important);
			AddParsedProperty(nametokens[0] + "-left-"	+ nametokens[1],	tokens[1], important);
			AddParsedProperty(nametokens[0] + "-bottom-"	+ nametokens[1],	tokens[2], important);
		} else if(tokens.GetCount() == 2)
		{
			AddParsedProperty(nametokens[0] + "-top-"		+ nametokens[1],	tokens[0], important);
			AddParsedProperty(nametokens[0] + "-bottom-"	+ nametokens[1],	tokens[0], important);
			AddParsedProperty(nametokens[0] + "-right-"	+ nametokens[1],	tokens[1], important);
			AddParsedProperty(nametokens[0] + "-left-"	+ nametokens[1],	tokens[1], important);
		} else if(tokens.GetCount() == 1)
		{
			AddParsedProperty(nametokens[0] + "-top-"		+ nametokens[1],	tokens[0], important);
			AddParsedProperty(nametokens[0] + "-bottom-"	+ nametokens[1],	tokens[0], important);
			AddParsedProperty(nametokens[0] + "-right-"	+ nametokens[1],	tokens[0], important);
			AddParsedProperty(nametokens[0] + "-left-"	+ nametokens[1],	tokens[0], important);
		}
	} else 
		
	// Parse font shorthand properties 
	if(!name.Compare("font"))
	{
		ParseShortFont(val, important);
	} else 
	{
		AddParsedProperty(name, val, important);
	}
}

void Style::ParseShortBorder( const String& prefix, const String& val, bool important )
{
	StringVector tokens;
	SplitString(val, tokens, " ", "", "(");
	if(tokens.GetCount() >= 3)
	{
		AddParsedProperty(prefix + "-width",	tokens[0], important);
		AddParsedProperty(prefix + "-style",	tokens[1], important);
		AddParsedProperty(prefix + "-color",	tokens[2], important);
	} else if(tokens.GetCount() == 2)
	{
		if(iswdigit(tokens[0][0]) || ValueIndex(val, BorderWidthStrings) >= 0)
		{
			AddParsedProperty(prefix + "-width",	tokens[0], important);
			AddParsedProperty(prefix + "-style",	tokens[1], important);
		} else
		{
			AddParsedProperty(prefix + "-style",	tokens[0], important);
			AddParsedProperty(prefix + "-color",	tokens[1], important);
		}
	}
}

void Style::ParseShortBackground( const String& val, const String& baseurl, bool important )
{
	AddParsedProperty("background-color",			"transhigher",	important);
	AddParsedProperty("background-image",			"",				important);
	AddParsedProperty("background-image-baseurl", "",				important);
	AddParsedProperty("background-repeat",		"repeat",		important);
	AddParsedProperty("background-origin",		"padding-box",	important);
	AddParsedProperty("background-clip",			"border-box",	important);
	AddParsedProperty("background-attachment",	"scroll",		important);

	if(val == "none")
	{
		return;
	}

	StringVector tokens;
	SplitString(val, tokens, " ", "", "(");
	bool origin_found = false;
	for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
	{
		if(IsColor(*tok))
		{
			AddParsedProperty("background-color", *tok, important);
		}
		else if(tok->Mid(0, 3) == "url")
		{
			AddParsedProperty("background-image", *tok, important);
			//if(baseurl)
			if(baseurl.GetCount())
			{
				AddParsedProperty("background-image-baseurl", baseurl, important);
			}

		} else if( ValueInList(*tok, BackgroundRepeatStrings) )
		{
			AddParsedProperty("background-repeat", *tok, important);
		} else if( ValueInList(*tok, BackgroundAttachmentStrings) )
		{
			AddParsedProperty("background-attachment", *tok, important);
		} else if( ValueInList(*tok, BackgroundBoxStrings) )
		{
			if(!origin_found)
			{
				AddParsedProperty("background-origin", *tok, important);
				origin_found = true;
			} else
			{
				AddParsedProperty("background-clip",*tok, important);
			}
		} else if(	ValueInList(*tok, "left;right;top;bottom;center") ||
					iswdigit((*tok)[0]) ||
					(*tok)[0] == '-'	||
					(*tok)[0] == '.'	||
					(*tok)[0] == '+')
		{
			if(properties.Find("background-position") != -1)
			{
				properties.Get("background-position").value = 
					properties.Get("background-position").value + " " + *tok;
			} else
			{
				AddParsedProperty("background-position", *tok, important);
			}
		}
	}
}

void Style::ParseShortFont( const String& val, bool important )
{
	AddParsedProperty("font-style",	"normal",	important);
	AddParsedProperty("font-variant",	"normal",	important);
	AddParsedProperty("font-weight",	"normal",	important);
	AddParsedProperty("font-size",		"medium",	important);
	AddParsedProperty("line-height",	"normal",	important);

	StringVector tokens;
	SplitString(val, tokens, " ", "", "\"");

	int idx = 0;
	bool was_normal = false;
	bool is_family = false;
	String font_family;
	for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
	{
		idx = ValueIndex(*tok, FontstyleStrings);
		if(!is_family)
		{
			if(idx >= 0)
			{
				if(idx == 0 && !was_normal)
				{
					AddParsedProperty("font-weight",		*tok, important);
					AddParsedProperty("font-variant",		*tok, important);
					AddParsedProperty("font-style",		*tok, important);
				} else
				{
					AddParsedProperty("font-style",		*tok, important);
				}
			} else
			{
				if(ValueInList(*tok, FontWeightStrings))
				{
					AddParsedProperty("font-weight",		*tok, important);
				} else
				{
					if(ValueInList(*tok, FontVariantStrings))
					{
						AddParsedProperty("font-variant",	*tok, important);
					} else if( iswdigit((*tok)[0]) )
					{
						StringVector szlh;
						SplitString(*tok, szlh, "/");

						if(szlh.GetCount() == 1)
						{
							AddParsedProperty("font-size",	szlh[0], important);
						} else	if(szlh.GetCount() >= 2)
						{
							AddParsedProperty("font-size",	szlh[0], important);
							AddParsedProperty("line-height",	szlh[1], important);
						}
					} else
					{
						is_family = true;
						font_family += *tok;
					}
				}
			}
		} else
		{
			font_family += *tok;
		}
	}
	AddParsedProperty("font-family", font_family, important);
}

void Style::AddParsedProperty( const String& name, const String& val, bool important )
{
	bool is_valid = true;
	int i = valid_values.Find(name);
	
	if (i != -1)
	{
		if (!ValueInList(val, valid_values[i]))
		{
			is_valid = false;
		}
	}

	if (is_valid)
	{
		i = properties.Find(name);
		if (i != -1)
		{
			PropertyValue& prop = properties[i];
			if (!prop.important || (important && prop.important))
			{
				prop.value = val;
				prop.important = important;
			}
		}
		else
		{
			PropertyValue& v = properties.GetAdd(name);
			v.value = val;
			v.important = important;
		}
	}
}

void Style::RemoveProperty( const String& name, bool important )
{
	int i = properties.Find(name);
	if (i != -1)
	{
		PropertyValue& prop = properties[i];
		if (!prop.important || (important && prop.important))
		{
			properties.Remove(i);
		}
	}
}


NAMESPACE_LAYOUT_END
