#ifndef _LayoutCtrl_Css_h_
#define _LayoutCtrl_Css_h_

NAMESPACE_LAYOUT_BEGIN



class Css : public Object
{
	CssSelector::vector	selectors;
	
public:
	RTTI_DECL1(Css, Object)
	Css() {}
	Css(const Css& src) {
		for (auto& it : src.selectors)
			selectors.Add().Create(*it);
	}
	~Css() {}

	const CssSelector::vector& Selectors() const {
		return selectors;
	}

	void Clear() {
		selectors.Clear();
	}

	void	ParseStylesheet(const String& str, const String& baseurl, Document* doc, MediaQueryList* media);
	void	SortSelectors();
	static void	ParseCssUrl(const String& str, String& url);
	
	//Css& operator = (const Css& css) {
	//	selectors <<= css.selectors; return *this;}
private:
	void	ParseAtRule(const String& text, const String& baseurl, Document* doc, MediaQueryList* media);
	void	AddSelector(CssSelector* Selector);
	bool	ParseSelectors(const String& txt, Style* Styles, MediaQueryList* media);

};

inline void Css::AddSelector( CssSelector* selector )
{
	selector->order = (int) selectors.GetCount();
	selectors.Add() = selector;
}


NAMESPACE_LAYOUT_END

#endif
