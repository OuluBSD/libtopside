#ifndef _LayoutCtrl_TemplateUtils_h_
#define _LayoutCtrl_TemplateUtils_h_


NAMESPACE_LAYOUT_BEGIN


// equal to String::Find(), but finds the first position of any character specified
template <class T>
int FindFirstOf(const T& src, const String& match, int startpos=0) {
    if (startpos < 0) return -1;
    for(int i = startpos; i < src.GetCount(); i++) {
        int c = src[i];
        for(int j = 0; j < match.GetCount(); j++) {
            if (c == match[j]) {
                return i;
            }
        }
    }
    return -1;
}

template <class T>
int FindFirstOf(const T& src, char match, int startpos=0) {
    if (startpos < 0) return -1;
    for(int i = startpos; i < src.GetCount(); i++) {
        int c = src[i];
        if (c == match) {
            return i;
        }
    }
    return -1;
}

// equal to FindFirstOf(), but finds the last position of any character specified
template <class T>
int FindLastOf(const T& src, const String& match, int endpos=-1, int count=-1) {
    if (endpos == -1) endpos = src.GetCount() - 1;
    int begin = (count == -1 ? 0 : endpos - count);
    for(int i = endpos; i >= begin; i--) {
        int c = src[i];
        for(int j = 0; j < match.GetCount(); j++) {
            if (c == match[j]) {
                return i;
            }
        }
    }
    return -1;
}

// equal to FindFirstOf(), but returns the position of the first character not of those specified
template <class T>
int FindFirstNotOf(const T& src, const String& match, int startpos=0, int count=-1) {
    if (startpos < 0) return -1;
    int end = (count == -1 ? src.GetCount() : startpos + count);
    for(int i = startpos; i < end; i++) {
        int c = src[i];
        bool is_match = false;
        for(int j = 0; j < match.GetCount(); j++) {
            if (c == match[j]) {
                is_match = true;
                break;
            }
        }
        if (!is_match)
            return i;
    }
    return -1;
}

// equal to FindLastOf(), but returns the last position of any characters not specified
template <class T>
int FindLastNotOf(const T& src, const String& match, int endpos=-1, int count=-1) {
    if (endpos == -1) endpos = src.GetCount() - 1;
    int begin = (count == -1 ? 0 : max(endpos - count, 0));
    for(int i = endpos; i >= begin; i--) {
        int c = src[i];
        bool is_match = false;
        for(int j = 0; j < match.GetCount(); j++) {
            if (c == match[j]) {
                is_match = true;
                break;
            }
        }
        if (!is_match)
            return i;
    }
    return -1;
}


template <class T>
void Trim(T &s)
{
	int pos = FindFirstNotOf(s, " \n\r\t");
	if(pos != -1)
	{
		s.Remove(0, pos);
	}
	pos = FindLastNotOf(s, " \n\r\t");
	if(pos != -1)
	{
		s.Remove(pos+1, s.GetCount()-pos-1);
	}
}

template <class T>
void LowerCase(T &s)
{
	T tmp;
	for (int i = 0; i < s.GetCount(); i++)
	{
		tmp.Cat(ToLower(s[i]));
	}
	s = tmp;
}

template <class T>
int FindCloseBracket(const T &s, int off, wchar open_b='(', wchar close_b=')')
{
	int cnt = 0;
	for(int i = off; i < s.GetCount(); i++)
	{
		if(s[i] == open_b)
		{
			cnt++;
		} else if(s[i] == close_b)
		{
			cnt--;
			if(!cnt)
			{
				return i;
			}
		}
	}
	return -1;
}

template <class T>
int ValueIndex( const T& val, const String& strings, int defValue = -1, wchar delim = ';')
{
	if(val.IsEmpty() || strings.IsEmpty() || !delim)
	{
		return defValue;
	}

	int idx = 0;
	int delim_start	= 0;
	int delim_end	= strings.Find(delim, delim_start);
	int item_len		= 0;
	while(true)
	{
		if(delim_end == -1)
		{
			item_len = strings.GetCount() - delim_start;
		} else
		{
			item_len = delim_end - delim_start;
		}
		if(item_len == val.GetCount())
		{
			if(val == Convert<T>(strings.Mid(delim_start, item_len)))
			{
				return idx;
			}
		}
		idx++;
		delim_start = delim_end;
		if(delim_start == -1) break;
		delim_start++;
		if(delim_start == strings.GetCount()) break;
		delim_end = strings.Find(delim, delim_start);
	}
	return defValue;
}

template <class T>
bool ValueInList( const T& val, const String& strings, wchar delim = ';')
{
	int idx = ValueIndex(val, strings, -1, delim);
	if(idx >= 0)
	{
		return true;
	}
	return false;
}

template <class T>
void SplitString(const T& str, Vector<String>& tokens, const String& delims, const String& delims_preserve = "", const String& quote = "\"")
{
	if(str.IsEmpty() || (delims.IsEmpty() && delims_preserve.IsEmpty()))
	{
		return;
	}

	String all_delims = delims + delims_preserve + quote;

	int token_start	= 0;
	int token_end	= str.FindFirstOf(all_delims, token_start);
	int token_len	= 0;
	String token;
	while(true)
	{
		while( token_end != -1 && FindFirstOf(quote, str[token_end]) != -1 )
		{
			if(str[token_end] == '(')
			{
				token_end = FindCloseBracket(str, token_end, '(', ')');
			} else if(str[token_end] == '[')
			{
				token_end = FindCloseBracket(str, token_end, '[', ']');
			} else if(str[token_end] == '{')
			{
				token_end = FindCloseBracket(str, token_end, '{', '}');
			} else
			{
				token_end = FindFirstOf(str, str[token_end], token_end + 1);
			}
			if(token_end != -1)
			{
				token_end = FindFirstOf(str, all_delims, token_end + 1);
			}
		}

		if(token_end == -1)
		{
			token_len = -1;
			token = str.Mid(token_start);
		} else
		{
			token_len = token_end - token_start;
			token = str.Mid(token_start, token_len);
		}
		
		
		if(!token.IsEmpty())
		{
			tokens.Add( token );
		}
		if(token_end != -1 && !delims_preserve.IsEmpty() && FindFirstOf(delims_preserve, str[token_end]) != -1)
		{
			tokens.Add( str.Mid(token_end, 1) );
		}

		token_start = token_end;
		if(token_start == -1) break;
		token_start++;
		if(token_start == str.GetCount()) break;
		token_end = str.FindFirstOf(all_delims, token_start);
	}
}


NAMESPACE_LAYOUT_END

#endif
