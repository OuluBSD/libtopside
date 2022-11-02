#include "LayoutCtrl.h"


NAMESPACE_LAYOUT_BEGIN


void Css::ParseStylesheet( const String& str, const String& baseurl, Document* doc, MediaQueryList* media )
{
	
	String text = str;

	// remove comments
	int c_start = text.Find("/*");
	while(c_start != -1)
	{
		int c_end = text.Find("*/", c_start + 2);
		if (c_end == -1)
			Panic("c_end == -1");
		else
			text.Remove(c_start, c_end - c_start + 2);
		c_start = text.Find("/*");
	}

	int pos = FindFirstNotOf(text, " \n\r\t");
	while(pos != -1)
	{
		while(pos != -1 && text[pos] == '@')
		{
			int sPos = pos;
			pos = text.FindFirstOf("{", pos);
			if(pos != -1 && text[pos] == '{')
			{
				pos = FindCloseBracket(text, pos, '{', '}');
			}
			if(pos != -1)
			{
				ParseAtRule(text.Mid(sPos, pos - sPos + 1), baseurl, doc, media);
			} else
			{
				ParseAtRule(text.Mid(sPos), baseurl, doc, media);
			}

			if(pos != -1)
			{
				//pos = text.find_first_not_of(" \n\r\t"), pos + 1);
				pos = FindFirstNotOf(text, " \n\r\t", pos + 1);
			}
		}

		if(pos == -1)
		{
			break;
		}

		int style_start = text.Find("{", pos);
		int style_end	= text.Find("}", pos);
		if(style_start != -1 && style_end != -1)
		{
			Style* st = new Style();
			doc->Add(st);
			
			st->Add(text.Mid(style_start + 1, style_end - style_start - 1), baseurl);

			ParseSelectors(text.Mid(pos, style_start - pos), st, media);

			if (media && doc)
			{
				doc->AddMediaList(media);
			}

			pos = style_end + 1;
		} else
		{
			pos = -1;
		}

		if(pos != -1)
		{
			pos = FindFirstNotOf(text, " \n\r\t", pos);
		}
	}
	
}

void Css::ParseCssUrl( const String& str, String& url )
{
	url = "";
	int pos1 = str.Find('(');
	int pos2 = str.Find(')');
	if(pos1 != -1 && pos2 != -1)
	{
		url = str.Mid(pos1 + 1, pos2 - pos1 - 1);
		if(url.GetCount())
		{
			if(url[0] == '\'' || url[0] == '"')
			{
				url.Remove(0, 1);
			}
		}
		if(url.GetCount())
		{
			if(url[url.GetCount() - 1] == '\'' || url[url.GetCount() - 1] == '"')
			{
				url.Remove(url.GetCount() - 1, 1);
			}
		}
	}
}


bool Css::ParseSelectors( const String& txt, Style* styles, MediaQueryList* media )
{
	ASSERT(styles);
	String Selector = txt;
	Trim(Selector);
	StringVector tokens;
	SplitString(Selector, tokens, ",");

	bool added_something = false;

	for(StringVector::Iterator tok = tokens.Begin(); tok != tokens.End(); tok++)
	{
		CssSelector* selector = new CssSelector(media);
		selector->style = styles;
		Trim(*tok);
		if(selector->Parse(*tok))
		{
			selector->CalcSpecificity();
			AddSelector(selector);
			added_something = true;
		}
		else
			delete selector;
	}

	return added_something;
}

void Css::SortSelectors()
{
	Sort(selectors, StdLess<One<CssSelector> >( ));
}

void Css::ParseAtRule( const String& text, const String& baseurl, Document* doc, MediaQueryList* media )
{
	if(text.Mid(0, 7) == "@import")
	{
		int sPos = 7;
		String iStr;
		iStr = text.Mid(sPos);
		if(iStr[iStr.GetCount() - 1] == ';')
		{
			iStr.Remove(iStr.GetCount() - 1);
		}
		Trim(iStr);
		StringVector tokens;
		SplitString(iStr, tokens, " ", "", "(\"");
		if(!tokens.IsEmpty())
		{
			String url;
			ParseCssUrl(tokens[0], url);
			if(url.IsEmpty())
			{
				url = tokens[0];
			}
			
			tokens.Remove(0);
			if(doc)
			{
				HtmlCtrl* doc_cont = &doc->GetHtmlCtrl();
				if(doc_cont)
				{
					String css_text;
					String css_baseurl;
					//if(baseurl)
					if(baseurl.GetCount())
					{
						css_baseurl = baseurl;
					}
					doc_cont->ImportCss(css_text, url, css_baseurl);
					if(!css_text.IsEmpty())
					{
						MediaQueryList* new_media = &*media;
						if(!tokens.IsEmpty())
						{
							String media_str;
							for(StringVector::Iterator iter = tokens.Begin(); iter != tokens.End(); iter++)
							{
								if(iter != tokens.Begin())
								{
									media_str += " ";
								}
								media_str += (*iter);
							}
							new_media = MediaQueryList::CreateFromString(media_str, doc);
							if(!new_media)
							{
								new_media = media;
							}
						}
						ParseStylesheet(css_text, css_baseurl, doc, new_media);
					}
				}
			}
		}
	} else if(text.Mid(0, 6) == "@media")
	{
		int b1 = FindFirstOf(text, '{');
		
		int b2 = FindLastOf(text, "}");
		if(b1 != -1)
		{
			String MediaType = text.Mid(6, b1 - 6);
			Trim(MediaType);
			MediaQueryList* new_media = MediaQueryList::CreateFromString(MediaType, doc);

			String media_style;
			if(b2 != -1)
			{
				media_style = text.Mid(b1 + 1, b2 - b1 - 1);
			} else
			{
				media_style = text.Mid(b1 + 1);
			}

			ParseStylesheet(media_style, baseurl, doc, new_media);
		}
	}
}


NAMESPACE_LAYOUT_END
