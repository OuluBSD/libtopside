#include "Language.h"

NAMESPACE_LANGUAGE_BEGIN

PennTreebankTokenizer::PennTreebankTokenizer() {
	
}
	
bool PennTreebankTokenizer::Tokenize(WString txt) {
	tokens.Clear();
	tokens.Add();
	
	for(int i = 0; i < txt.GetCount(); i++) {
		int chr = txt[i];
		
		if (chr == '\"') {
			/*int chr_1 = i > 0 ? txt[i-1] : 0;
			
			if (chr_1 == 0 || IsSpace(chr_1))
				NewSingle("``");
			else
				NewSingle("''");*/
			NewSingle("").Cat(chr);
		}
		else if (chr == '(') {
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			int chr2 = i+2 < txt.GetCount() ? txt[i+2] : 0;
			int chr3 = i+3 < txt.GetCount() ? txt[i+3] : 0;
			if (chr1 == '`' && chr2 == '`' && chr3 == ')') {
				NewSingle("``");
				i += 3;
			}
			else
				NewSingle("(");
		}
		else if (chr == '[' ||
			chr == '{' ||
			chr == '<' ||
			chr == ':' ||
			chr == ',' ||
			chr == ';' ||
			chr == '@' ||
			chr == '#' ||
			chr == '$' ||
			chr == '%' ||
			chr == '&' ||
			chr == '?' ||
			chr == '!' ||
			chr == '^' ||
			chr == ']' ||
			chr == '}' ||
			chr == '>' ||
			chr == ')'
			) {
			NewSingle("").Cat(chr);
		}
		else if (chr == '.') {
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			int chr2 = i+2 < txt.GetCount() ? txt[i+2] : 0;
			if (chr1 == '.' && chr2 == '.') {
				NewSingle("...");
				i += 2;
			}
		}
		else if (chr == '-') {
			WString s;
			while (i < txt.GetCount() && txt[i] == '-') {
				s.Cat('-');
				i++;
			}
			i--;
			NewSingle(s);
		}
		else if (chr == '\'') {
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			int chr2 = i+2 < txt.GetCount() ? txt[i+2] : 0;
			int chr3 = i+3 < txt.GetCount() ? txt[i+3] : 0;
			
			if ((chr1 == 's' || chr1 == 'S') && (IsSpace(chr2) || chr2 == 0)) {
				NewSingle("").Cat(chr).Cat(chr1);
				i += 2;
			}
			else if ((chr1 == 'm' || chr1 == 'M') && (IsSpace(chr2) || chr2 == 0)) {
				NewSingle("").Cat(chr).Cat(chr1);
				i += 2;
			}
			else if ((chr1 == 'd' || chr1 == 'D') && (IsSpace(chr2) || chr2 == 0)) {
				NewSingle("").Cat(chr).Cat(chr1);
				i += 2;
			}
			else if ((chr1 == 'l' || chr1 == 'L') && (chr2 == 'l' || chr2 == 'L') && (IsSpace(chr3) || chr3 == 0)) {
				NewSingle("").Cat(chr).Cat(chr1).Cat(chr2);
				i += 3;
			}
			else if ((chr1 == 'r' || chr1 == 'R') && (chr2 == 'e' || chr2 == 'E') && (IsSpace(chr3) || chr3 == 0)) {
				NewSingle("").Cat(chr).Cat(chr1).Cat(chr2);
				i += 3;
			}
			else if ((chr1 == 'v' || chr1 == 'V') && (chr2 == 'e' || chr2 == 'E') && (IsSpace(chr3) || chr3 == 0)) {
				NewSingle("").Cat(chr).Cat(chr1).Cat(chr2);
				i += 3;
			}
			else
				NewSingle("'");
		}
		else if (chr == 'n' || chr == 'N') {
			int chr1 = i+1 < txt.GetCount() ? txt[i+1] : 0;
			int chr2 = i+2 < txt.GetCount() ? txt[i+2] : 0;
			int chr3 = i+3 < txt.GetCount() ? txt[i+3] : 0;
			if (chr1 == '\'' && (chr2 == 't' || chr2 == 'T') && (IsSpace(chr3) || chr3 == 0)) {
				NewSingle("").Cat(chr).Cat(chr1).Cat(chr2);
				i += 3;
			}
			else
				Cat(chr);
		}
		else if (IsSpace(chr)) {
			if (!tokens.Top().str_value.IsEmpty())
				tokens.Add();
		}
		else
			Cat(chr);
	}
	
	for(int i = 0; i < tokens.GetCount(); i++) {
		Token& t = tokens[i];
		int c0 = t.str_value.GetCount();
		
		if (c0 == 0) {
			tokens.Remove(i);
			i--;
			continue;
		}
	}
	
	bool skip = false, start_quotes = false;
	Vector<Token> words;
	
	for(int i = 0; i < tokens.GetCount(); i++) {
		Token& t = tokens[i];
		Token* t1 = NULL;
		int c0 = t.str_value.GetCount();
		int c0i = t.str_value[0];
		int c0i2 = c0 >= 2 ? t.str_value[1] : 0;
		int c1 = 0;
		int c1i = 0;
		if (i+1 < tokens.GetCount()) {
			t1 = &tokens[i+1];
			c1 = t1->str_value.GetCount();
			if (c1)
				c1i = t1->str_value[0];
		}
		
		if (skip)
			skip = false;
		
		// Tokenization Exceptions
		else if (c0 == 1 && c0i == '&' && c1 == 1 && t1) {
			if (words.IsEmpty()) words.Add();
			words.Top().str_value += "&" + t1->str_value;
			skip = true;
		}
		else if (c0 == 1 && c0i == '#' && t1) {
			words.Add().str_value = "#" + t1->str_value;
			skip = true;
		}
		else if (c0 == 2 && c0i == '\'' && (c0i2 == 's' || c0i2 == 'S') && words.GetCount() && IsNumberStr(words.Top().str_value)) {
			words.Top().str_value += t.str_value;
		}
		
		// Special Penn symbols: keep track of original in tuple
		else if (c0 == 1 && c0i == '(') {
			words.Add().str_value = "-LRB-";
		}
		else if (c0 == 1 && c0i == ')') {
			words.Add().str_value = "-RRB-";
		}
		else if (c0 == 1 && c0i == '\"') {
			if (start_quotes) {
				start_quotes = false;
				words.Add().str_value = "''";
			} else {
				start_quotes = true;
				words.Add().str_value = "``";
			}
		}
		else
			words.Add().str_value = t.str_value;
	}
	
	return true;
}


NAMESPACE_LANGUAGE_END
