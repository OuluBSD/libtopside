#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


Tokenizer::Tokenizer() : ErrorSource("Tokenizer") {
	
}

Token& Tokenizer::Add(int token_id) {
	struct Token& t = tokens.Add();
	t.loc = loc;
	t.end = loc;
	t.end.col++;
	t.type = token_id;
	return t;
}

bool Tokenizer::PassToken(int tk) {
	if (!IsToken(tk)) return ThrowError("Unexpected token");
	pass_cursor++;
	return true;
}

bool Tokenizer::IsToken(int tk) {
	if (pass_cursor >= tokens.GetCount()) return false;
	return tokens[pass_cursor].type == tk;
}

bool Tokenizer::TryPassToken(int tk) {
	if (!IsToken(tk)) return false;
	pass_cursor++;
	return true;
}

bool Tokenizer::ReadString(String& s) {
	if (!IsToken(TK_STRING)) return ThrowError("Unexpected token");
	s = tokens[pass_cursor++].str_value;
	return true;
}

bool Tokenizer::ReadId(String& s) {
	if (!IsToken(TK_ID)) return ThrowError("Unexpected token");
	s = tokens[pass_cursor++].str_value;
	return true;
}

bool Tokenizer::ReadInt(int64& i) {
	if (!IsToken(TK_INTEGER)) return ThrowError("Unexpected token");
	i = StrInt64(tokens[pass_cursor++].str_value);
	return true;
}

bool Tokenizer::ReadDouble(double& d) {
	if (!IsToken(TK_DOUBLE) && !IsToken(TK_FLOAT)) return ThrowError("Unexpected token");
	d = StrDbl(tokens[pass_cursor++].str_value);
	return true;
}

bool Tokenizer::Process(String str, String path) {
	input = str;
	
	loc.file = path;
	loc.line = 1;
	loc.col = 1;
	loc.cursor = 0;
	
	parse_indent = have_indent_tokens;
	user_spaces = 0;
	indent = 0;
	
	int& cursor = loc.cursor;
	
	bool fail = false;
	while (cursor < input.GetCount()) {
		int chr = input[cursor];
		
		if (parse_indent && chr != '\n') {
			int line_indent = 0;
			fail = false;
			while (cursor < input.GetCount()) {
				chr = input[cursor];
				if (chr == ' ') {
					if (!user_spaces) {
						user_spaces = 1;
						Next();
						while (cursor < input.GetCount() && input[cursor] == ' ') {
							user_spaces++;
							Next();
						}
						line_indent++;
					}
					else {
						int spaces = 1;
						Next();
						while (spaces % user_spaces != 0 && cursor < input.GetCount() && input[cursor] == ' ') {
							spaces++;
							Next();
						}
						int space_mod = spaces % user_spaces;
						if (space_mod != 0) {
							AddError(loc, Format("Invalid amount of spaces in indent: got %d, expected %d", space_mod, user_spaces));
							fail = true;
							break;
						}
						ASSERT(spaces == user_spaces);
						line_indent++;
					}
				}
				else if (chr == '\t') {
					Next();
					line_indent++;
				}
				else break;
			}
			if (fail)
				break;
			
			if (line_indent < indent) {
				int dedents = indent - line_indent;
				for(int i = 0; i < dedents; i++)
					Add(TK_DEDENT);
			}
			else if (line_indent == indent) {
				// do nothing
			}
			else if (line_indent == indent + 1) {
				Add(TK_INDENT);
			}
			else {
				AddError(loc, "Too many indentation levels: " + IntStr(line_indent - indent));
				fail = true;
				break;
			}
			
			indent = line_indent;
			parse_indent = false;
		}
		else if (IsAlpha(chr) || chr == '_') {
			Token& t = Add(TK_ID);
			t.str_value.Cat(chr);
			Next();
			while (cursor < input.GetCount()) {
				int chr = input[cursor];
				if (IsAlpha(chr) || chr == '_' || IsDigit(chr)) {
					t.str_value.Cat(chr);
					Next();
				}
				else
					break;
			}
			t.end = loc;
		}
		else if (IsDigit(chr)) {
			String n;
			if (skip_separateunary && tokens.GetCount()) {
				while (tokens.GetCount() && tokens.Top().IsType(TK_MINUS)) {
					tokens.Pop();
					n.Cat('-');
				}
				while (tokens.GetCount() && tokens.Top().IsType(TK_PLUS)) {
					tokens.Pop();
				}
			}
			Token& tk = Add(TK_INTEGER);
			bool is_double = false, is_float = false;
			n.Cat(chr);
			Next();
			enum {INT, DEC, FRAC, SIGN, EXP, F, END, OCTHEX, OCT, HEX};
			int exp = chr == '0' ? OCTHEX : INT;
			while (cursor < input.GetCount()) {
				int chr = input[cursor];
				bool cat = false;
				
				if (exp == INT) {
					if (IsDigit(chr))
						cat = true;
					else if (chr == '.') {
						exp = FRAC;
						cat = true;
						is_double = true;
					}
					else if (chr == 'e' || chr == 'E') {
						exp = SIGN;
						cat = true;
						is_double = true;
					}
				}
				else if (exp == FRAC) {
					if (IsDigit(chr))
						cat = true;
					else if (chr == 'e' || chr == 'E') {
						exp = SIGN;
						cat = true;
						is_double = true;
					}
				}
				else if (exp == SIGN) {
					if (chr == '+' || chr == '-' || IsDigit(chr)) {
						exp = EXP;
						cat = true;
					}
					else if (chr == 'f' || chr == 'F') {
						exp = END;
						cat = true;
						is_float = true;
					}
				}
				else if (exp == EXP) {
					if (IsDigit(chr))
						cat = true;
					else if (chr == 'f' || chr == 'F') {
						exp = END;
						cat = true;
						is_float = true;
					}
				}
				else if (exp == OCTHEX) {
					if (chr == 'x' || chr == 'X') {
						exp = HEX;
						cat = true;
					}
					else if (chr >= '0' && chr <= '7') {
						exp = OCT;
						cat = true;
					}
					else if (chr == '.') {
						exp = FRAC;
						cat = true;
						is_double = true;
					}
				}
				else if (exp == HEX) {
					if ((chr >= '0' && chr <= '9') ||
						(chr >= 'a' && chr <= 'f') ||
						(chr >= 'A' && chr <= 'F')) {
						cat = true;
					}
				}
				else if (exp == OCT) {
					if (chr >= '0' && chr <= '7') {
						cat = true;
					}
				}
				
				if (cat) {
					Next();
					n.Cat(chr);
					if (exp == END) break;
				}
				else break;
			}
			
			tk.str_value = n;
			
			if (exp == HEX)
				tk.type = TK_HEX;
			else if (exp == OCT)
				tk.type = TK_OCT;
			else if (is_double) {
				if (!is_float)
					tk.type = TK_DOUBLE;
				else
					tk.type = TK_FLOAT;
			}
			
			tk.end = loc;
		}
		else if (chr == '!') {
			Token& tk = Add(TK_EXCLAMATION);
			Next();
			tk.end = loc;
		}
		else if (chr == '\"') {
			Token& tk = Add(TK_STRING);
			Next();
			String str;
			bool success = false;
			while (cursor < input.GetCount()) {
				int chr = input[cursor];
				String tmp;
				tmp.Cat(chr);
				if (chr == '\n') {
					AddError(tk.loc, "no newline allowed in string literal");
					Next();
					parse_indent = have_indent_tokens;
					loc.line++;
					loc.col = 1;
				}
				else if (chr == '\"') {
					Next();
					success = true;
					break;
				}
				else if (chr == '\\') {
					AppendString(str);
				}
				else {
					str.Cat(chr);
					Next();
				}
			}
			tk.end = loc;
			
			if (success) {
				tk.str_value = str;
			}
			else {
				AddError(tk.loc, "no finishing \" in string literal");
				return false;
			}
		}
		else if (chr == '#') {
			Token& tk = Add(TK_NUMBERSIGN);
			Next();
			tk.end = loc;
		}
		else if (chr == '%') {
			Token& tk = Add(TK_PERCENT);
			Next();
			tk.end = loc;
		}
		else if (chr == '&') {
			Token& tk = Add(TK_AMPERSAND);
			Next();
			tk.end = loc;
		}
		else if (chr == '/') {
			//int begin_line = loc.line, begin_col = loc.col;
			int chr1 = cursor+1 < input.GetCount() ? input[cursor+1] : 0;
			if (chr1 == '*') {
				Token* tk = NULL;
				if (!skip_comments)
					tk = &Add(TK_BLOCK_COMMENT);
				Next();
				Next();
				String c;
				bool succ = false;
				while (cursor < input.GetCount()) {
					chr = input[cursor];
					if (chr == '*') {
						chr1 = cursor+1 < input.GetCount() ? input[cursor+1] : 0;
						if (chr1 == '/') {
							Next();
							Next();
							if (tk) tk->str_value = c;
							succ = true;
							break;
						}
						else c.Cat(chr);
					}
					else c.Cat(chr);
					Next();
				}
				if (tk) {
					tk->end = loc;
					if (!succ)
						AddError(tk->loc, "unterminated /* comment");
				}
			}
			else if (chr1 == '/') {
				Token* tk = NULL;
				if (!skip_comments)
					tk = &Add(TK_COMMENT);
				Next();
				Next();
				String c;
				bool add_line = false;
				while (cursor < input.GetCount()) {
					chr = input[cursor];
					if (chr == '\n') {
						if (tk) tk->str_value = c;
						add_line = true;
						break;
					}
					else c.Cat(chr);
					Next();
				}
				if (tk) tk->end = loc;
				if (add_line) {
					parse_indent = have_indent_tokens;
					loc.line++;
					loc.col = 1;
				}
			}
			else {
				Token& tk = Add(TK_DIV);
				Next();
				tk.end = loc;
			}
		}
		else if (chr == '{') {
			Add(TK_BRACKET_BEGIN);
			Next();
		}
		else if (chr == '}') {
			Add(TK_BRACKET_END);
			Next();
		}
		else if (chr == '(') {
			Add(TK_PARENTHESIS_BEGIN);
			Next();
		}
		else if (chr == ')') {
			Add(TK_PARENTHESIS_END);
			Next();
		}
		else if (chr == '[') {
			Add(TK_SQUARE_BEGIN);
			Next();
		}
		else if (chr == ']') {
			Add(TK_SQUARE_END);
			Next();
		}
		else if (chr == '=') {
			Add(TK_ASS);
			Next();
		}
		else if (chr == '+') {
			Add(TK_PLUS);
			Next();
		}
		else if (chr == '?') {
			Add(TK_QUESTION);
			Next();
		}
		else if (chr == '\\') {
			Add(TK_SOLIDUS);
			Next();
		}
		else if (chr == '^') {
			Add(TK_ACCENT);
			Next();
		}
		else if (chr == '~') {
			Add(TK_TILDE);
			Next();
		}
		else if (chr == '*') {
			Add(TK_MUL);
			Next();
		}
		else if (chr == '@') {
			Add(TK_AT);
			Next();
		}
		else if (chr == '\'') {
			Token& tk = Add(TK_CHAR);
			Next();
			String str;
			bool success = false;
			while (cursor < input.GetCount()) {
				int chr = input[cursor];
				if (chr == '\n') {
					AddError(tk.loc, "no newline allowed in char literal");
					Next();
					parse_indent = have_indent_tokens;
					loc.line++;
					loc.col = 1;
				}
				else if (chr == '\'') {
					Next();
					success = true;
					break;
				}
				else if (chr == '\\') {
					AppendString(str);
				}
				else {
					str.Cat(chr);
					Next();
				}
			}
			tk.end = loc;
			
			if (success) {
				tk.str_value = str;
			}
			else {
				AddError(tk.loc, "no finishing \' in char literal");
				return false;
			}
		}
		else if (chr == '-') {
			Add(TK_MINUS);
			Next();
		}
		else if (chr == ';') {
			Add(TK_SEMICOLON);
			Next();
		}
		else if (chr == ',') {
			Add(TK_COMMA);
			Next();
		}
		else if (chr == '.') {
			Add(TK_PUNCT);
			Next();
		}
		else if (chr == ':') {
			Add(TK_COLON);
			Next();
		}
		else if (chr == '<') {
			Add(TK_LESS);
			Next();
		}
		else if (chr == '>') {
			Add(TK_GREATER);
			Next();
		}
		else if (chr == '|') {
			Add(TK_OR);
			Next();
		}
		else if (chr == '\n') {
			if (!skip_newlines) {
				Token& tk = Add(TK_NEWLINE);
				tk.end.col = 1; tk.end.line++;
			}
			Next();
			parse_indent = have_indent_tokens;
			loc.line++;
			loc.col = 1;
		}
		else if (chr == '\t') {
			if (!tokens.IsEmpty())
				tokens.Top().spaces += tab_size;
			Next();
			loc.col += tab_size - 1;
		}
		else if (IsSpace(chr)) {
			if (!tokens.IsEmpty())
				tokens.Top().spaces++;
			Next();
		}
		else if (chr == '$') {
			Add(TK_DOLLARSIGN);
			Next();
		}
		else if (chr == 0)
			break;
		else {
			byte b = chr;
			if (b >= 0x80 && b <= 0xFF) {
				Next();
				while (cursor < input.GetCount()) {
					b = input[cursor];
					if (b >= 0x80 && b <= 0xFF)
						cursor++;
					else
						break;
				}
				//AddWarning("treating Unicode character as whitespace", line, col);
				if (!tokens.IsEmpty())
					tokens.Top().spaces++;
			}
			else {
				String msg = "unexpected character '";
				msg.Cat(chr);
				msg.Cat('\'');
				AddError(loc, msg);
				Next();
			}
		}
	}
	
	for(int i = 0; i < indent; i++)
		Add(TK_DEDENT);
	indent = 0;
	
	Add(TK_EOF);
	
	return !IsFail();
}

void Tokenizer::AppendString(String& s) {
	int& cursor = loc.cursor;
	int chr = input[loc.cursor];
	if (chr == '\\') {
		int chr1 = cursor+1 < input.GetCount() ? input[cursor+1] : 0;
		if (chr1 == '\'') {
			Next(); Next();
			s.Cat(0x27);
		}
		else if (chr1 == '\"') {
			Next(); Next();
			s.Cat(0x22);
		}
		else if (chr1 == '?') {
			Next(); Next();
			s.Cat(0x3F);
		}
		else if (chr1 == '\\') {
			Next(); Next();
			s.Cat(0x5c);
		}
		else if (chr1 == 'a') {
			Next(); Next();
			s.Cat(0x07);
		}
		else if (chr1 == 'b') {
			Next(); Next();
			s.Cat(0x08);
		}
		else if (chr1 == 'f') {
			Next(); Next();
			s.Cat(0x0c);
		}
		else if (chr1 == 'n') {
			Next(); Next();
			s.Cat(0x0a);
		}
		else if (chr1 == 'r') {
			Next(); Next();
			s.Cat(0x0d);
		}
		else if (chr1 == 't') {
			Next(); Next();
			s.Cat(0x09);
		}
		else if (chr1 == 'v') {
			Next(); Next();
			s.Cat(0x0b);
		}
		else {
			s.Cat(chr);
			Next();
		}
	}
	else {
		s.Cat(chr);
		Next();
	}
}

void Tokenizer::NewlineToEndStatement() {
	int indent = 0;
	
	for(int i = 0; i < tokens.GetCount(); i++) {
		Token& tk = tokens[i];
		
		if (tk.IsType(TK_COLON)) {
			int nl_count = 0;
			for(int j = i+1; j < tokens.GetCount(); j++) {
				Token& tk0 = tokens[j];
				if (tk0.IsType(TK_NEWLINE)) {
					tokens.Remove(j--);
					nl_count++;
				}
				else
					break;
			}
			if (!nl_count) {
				
			}
		}
		else if (tk.IsType(TK_DEDENT)) {
			FileLocation loc = tk.loc;
			Token& end_stmt1 = tokens.Insert(i+1);
			end_stmt1.loc = loc;
			end_stmt1.type = TK_END_STMT;
			Token& end_stmt0 = tokens.Insert(i);
			end_stmt0.loc = loc;
			end_stmt0.type = TK_END_STMT;
			i+=2;
		}
		else if (tk.IsType(TK_NEWLINE)) {
			tk.type = TK_END_STMT;
		}
	}
	
	Vector<int> useless_ends;
	int c = tokens.GetCount()-1;
	for(int i = 0; i < c; i++) {
		Token& tk0 = tokens[i];
		Token& tk1 = tokens[i+1];
		if (tk0.IsType(TK_END_STMT) && tk1.IsType(TK_END_STMT))
			useless_ends.Add(i);
	}
	tokens.Remove(useless_ends);
}

void Tokenizer::Dump() const {
	if (0) {
		DUMPC(tokens);
	}
	else {
		LOG("Dumping tokenizer:");
		String prev_file;
		for(int i = 0; i < tokens.GetCount(); i++) {
			const Token& tk = tokens[i];
			if (tk.loc.file != prev_file) {
				prev_file = tk.loc.file;
				LOG("\tfile: " << prev_file);
			}
			
			LOG("\t[" << i << "] (" << tk.loc.line << ":" << tk.loc.col << ") = " <<
				tk.GetTypeString() << ": " << tk.GetTextValue());
		}
	}
}

void Tokenizer::CombineTokens() {
	int count = tokens.GetCount();
	int limit = count - 1;
	for(int i = 0; i < limit; i++) {
		Token& tk0 = tokens[i];
		
		if (tk0.spaces == 0) {
			Token& tk1 = tokens[i + 1];
			int rem = 0, new_tk;
			bool third = i + 2 < count;
			
			if (tk0.type == '+') {
				if (tk1.type == '+') {
					new_tk = TK_INC;
					rem = 1;
				}
				else if (tk1.type == '=') {
					new_tk = TK_ADDASS;
					rem = 1;
				}
			}
			else if (tk0.type == '-') {
				if (tk1.type == '-') {
					new_tk = TK_DEC;
					rem = 1;
				}
				else if (tk1.type == '=') {
					new_tk = TK_SUBASS;
					rem = 1;
				}
			}
			else if (tk0.type == '<') {
				if (tk1.type == '<') {
					if (tk1.spaces == 0 && third && tokens[i + 2].type == '=') {
						new_tk = TK_LSHIFTASS;
						rem = 2;
					}
					else {
						new_tk = TK_LSHIFT;
						rem = 1;
					}
				}
				else if (tk1.type == '=') {
					new_tk = TK_LSEQ;
					rem = 1;
				}
			}
			else if (tk0.type == '>') {
				if (tk1.type == '>') {
					if (tk1.spaces == 0 && third && tokens[i + 2].type == '=') {
						new_tk = TK_RSHIFTASS;
						rem = 2;
					}
					else {
						new_tk = TK_RSHIFT;
						rem = 1;
					}
				}
				else if (tk1.type == '=') {
					new_tk = TK_GREQ;
					rem = 1;
				}
			}
			else if (tk0.type == '&') {
				if (tk1.type == '&') {
					new_tk = TK_LOGAND;
					rem = 1;
				}
				else if (tk1.type == '=') {
					new_tk = TK_ANDASS;
					rem = 1;
				}
			}
			else if (tk0.type == '|') {
				if (tk1.type == '|') {
					new_tk = TK_LOGOR;
					rem = 1;
				}
				else if (tk1.type == '=') {
					new_tk = TK_ORASS;
					rem = 1;
				}
			}
			#define SINGLETEST(c0, c1, tk) else if (tk0.type == c0 && tk1.type == c1) {new_tk = tk; rem = 1;}
			SINGLETEST('=', '=', TK_EQ)
			SINGLETEST('!', '=', TK_INEQ)
			SINGLETEST('*', '=', TK_MULASS)
			SINGLETEST('/', '=', TK_DIVASS)
			SINGLETEST('%', '=', TK_MODASS)
			SINGLETEST('^', '=', TK_XORASS)
			
			if (rem) {
				tk0.type = new_tk;
				tokens.Remove(i+1, rem);
				limit -= rem;
				count -= rem;
			}
		}
	}
	
}












#ifdef flagSTDEXC

void TokenizerCParser::Load(const Vector<Token>& tokens) {
	this->tokens = &tokens;
	pos = 0;
}

const Token& TokenizerCParser::GetCurrent() const {
	if (!tokens)
		throw Exc("No token vector set");
	if (pos < 0 || pos >= tokens->GetCount())
		throw Exc("Invalid token position");
	return (*tokens)[pos];
}

void TokenizerCParser::IgnoreNewline(bool b) {
	ignore_newline = b;
}

bool TokenizerCParser::IsEnd() const {
	return !tokens || pos >= tokens->GetCount();
}

FileLocation TokenizerCParser::GetLocation() const {
	return GetCurrent().loc;
}

String TokenizerCParser::ReadId() {
	const Token& tk = GetCurrent();
	if (!tk.IsType(TK_ID))
		throw Exc("Token is not id");
	pos++;
	return tk.str_value;
}

int TokenizerCParser::ReadInt() {
	const Token& tk = GetCurrent();
	pos++;
	if (tk.IsType(TK_OCT))
		return OctInt(tk.str_value);
	if (tk.IsType(TK_HEX))
		return HexInt(tk.str_value);
	if (tk.IsType(TK_INTEGER))
		return StrInt(tk.str_value);
	pos--;
	throw Exc("Token is not int");
}

void TokenizerCParser::PassNewline() {
	const Token& tk = GetCurrent();
	if (tk.IsType(TK_NEWLINE))
		throw Exc("Token is not newline");
	pos++;
}

bool TokenizerCParser::Id(String id) {
	const Token& tk = GetCurrent();
	if (tk.IsType(TK_ID) && tk.str_value == id) {
		pos++;
		return true;
	}
	return false;
}

bool TokenizerCParser::Type(int i) {
	const Token& tk = GetCurrent();
	if (tk.IsType(i)) {
		pos++;
		return true;
	}
	return false;
}

bool TokenizerCParser::Newline() {
	const Token& tk = GetCurrent();
	if (tk.IsType(TK_NEWLINE)) {
		pos++;
		return true;
	}
	return false;
}

bool TokenizerCParser::IsId() const {
	return GetCurrent().IsType(TK_ID);
}

bool TokenizerCParser::IsInt() const {
	return GetCurrent().IsType(TK_INTEGER);
}

bool TokenizerCParser::IsType(int i) const {
	return GetCurrent().IsType(i);
}

#endif

NAMESPACE_TOPSIDE_END

