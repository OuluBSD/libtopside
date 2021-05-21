#include "Bootstrap.h"

NAMESPACE_TOPSIDE_BEGIN


MacroInterpreter::MacroInterpreter() : ErrorSource("MacroInterpreter") {
	
}

/*bool MacroInterpreter::Process() {
	InputStage* stage = GetUnit().GetPreviousStage();
	tk = stage ? CastPtr<Tokenizer>(stage) : 0;
	if (!tk) {
		AddError(FileLocation(), t_("Tokenizer stage should be before MacroInterpreter"));
		return false;
	}
}*/

bool MacroInterpreter::ProcessTokenizer() {
	this->file_path = "";
	error_file = "";
	cond_stack.Clear();
	root.Clear();
	root.SetType(NODE_PREPROCESSOR_ROOT);
	int line = 0;
	bool succ = true;
	cursor = 0;
	
	int expecting_macroline = true;
	while (!IsEnd()) {
		bool cat_token = false;
		
		if (expecting_macroline) {
			if (have_cpp && Get().IsType(TK_NUMBERSIGN)) {
				try {
					const Token& directive = Next().Get();
					if (directive.IsType(TK_ID)) {
						String directive_str = directive.GetString();
						if (directive_str == "line") {
							Next();
							Assert(TK_INTEGER, t_("#line directive requires a positive integer argument"));
							line = ScanInt(Get().str_value);
							if (line < 0)
								Error(t_("#line directive requires a positive integer argument"));
							
							Next();
							Assert(TK_STRING, t_("invalid filename for #line directive"));
							
							line_diff = line - directive.loc.line;
							error_file = directive.loc.file;
							
							Next();
							
							if (!IsEnd() && !Get().IsType(TK_NEWLINE))
								Warning(t_("extra tokens at end of #line directive"));
						}
						else {
							Error(t_("unsupported preprocessor directive"), directive.loc.line, directive.loc.col);
						}
					}
					
				}
				catch (Exc e) {
					const auto& tokens = *this->tk;
					const Token& tk = tokens[min(tokens.GetCount()-1, cursor)];
					Error(e, tk.loc.line, tk.loc.col);
				}
				while (!IsEnd() && !Get().IsType(TK_NEWLINE))
					Next();
			}
			else {
				expecting_macroline = false;
				cat_token = true;
			}
		}
		else {
			cat_token = true;
		}
		
		if (Get().IsType(TK_EOF)) {
			Next();
		}
		else if (have_cpp && Get().IsType(TK_NEWLINE)) {
			expecting_macroline = true;
			line++;
			Next();
		}
		else if (cat_token) {
			Node& n = Add(NODE_TOKEN);
			n.FromToken(ProcessNonMacroId(Get()));
			Token& dst = n.GetToken();
			const auto& tokens = *this->tk;
			if (cursor < tokens.GetCount()) {
				const Token& src = tokens[cursor];
				dst = src;
			}
			else {
				dst.loc.file = error_file;
				dst.loc.line = line;
			}
			Next();
		}
		
	}
	return succ;
}

void MacroInterpreter::LoadSubExpr(Vector<Token>& subexpr) {
	while (!IsEnd() && !Get().IsType(TK_NEWLINE)) {
		subexpr.Add(Get());
		Next();
	}
}

bool MacroInterpreter::GetSubExprValue(Vector<Token>& subexpr) {
	bool value = false;
	
	if (subexpr.GetCount() == 1) {
		const Token& tk = subexpr[0];
		if (tk.IsType(TK_INTEGER)) {
			int i = ScanInt(tk.str_value);
			value = i;
		}
		else if (tk.IsType(TK_DOUBLE) || tk.IsType(TK_FLOAT)) {
			Error(t_("floating point literal in preprocessor expression"), tk.loc.line, tk.loc.col);
		}
		else if (tk.IsType(TK_ID)) {
			;
		}
		else {
			Warning(t_("invalid token at start of a preprocessor expression"), tk.loc.line, tk.loc.col);
		}
	}
	else if (subexpr.GetCount() == 0) {
		const auto& loc = Get().loc;
		Error(t_("no macro subexpression"), loc.line, loc.col);
	}
	else {
		const auto& loc = subexpr[1].loc;
		Warning(t_("token is not a valid binary operator in a preprocessor subexpression"), loc.line, loc.col);
	}
	
	return value;
}

void MacroInterpreter::AssertPathToken(String msg) {
	int type = Get().type;
	if (type == TK_ID || type == TK_INTEGER || type == TK_FLOAT ||
		type == TK_DOUBLE || type == TK_DIV || type == TK_PLUS || type == TK_SOLIDUS ||
		type == TK_MINUS || type == TK_PUNCT)
		return;
	
	throw Exc(msg);
}

void MacroInterpreter::Push(bool value, const Token& directive) {
	cond_stack.Add(value);
	cond_directive_stack.Add(&directive);
}

void MacroInterpreter::Pop() {
	if (cond_stack.IsEmpty()) {
		throw Exc(t_("#endif without #if"));
	}
	cond_stack.Pop();
	cond_directive_stack.Pop();
}

int& MacroInterpreter::Top() {
	if (cond_stack.IsEmpty()) {
		throw Exc(t_("#elif without #if"));
	}
	return cond_stack.Top();
}

void MacroInterpreter::SeekElseElifEndif() {
	while (!IsEnd()) {
		if (Get().IsType(TK_NEWLINE)) {
			Next();
			if (!IsEnd() && Get().IsType(TK_NUMBERSIGN)) {
				Next();
				const Token& directive = Get();
				if (directive.IsType(TK_ID)) {
					String directive_str = directive.GetString();
					if (directive_str == "elif" ||
						directive_str == "else" ||
						directive_str == "endif") {
						cursor--;
						cursor--;
						return;
					}
				}
			}
		}
		else
			Next();
	}
	if (!cond_directive_stack.IsEmpty()) {
		const auto& loc = cond_directive_stack.Top()->loc;
		Error(t_("unterminated conditional directive"), loc.line, loc.col);
	}
}

void MacroInterpreter::Error(String msg, int line, int col) {
	ProcMsg pm;
	pm.file = error_file;
	pm.line = line;
	pm.col = col;
	pm.severity = PROCMSG_ERROR;
	pm.src = "MacroInterpreter";
	pm.msg = msg;
	WhenMessage(pm);
}

void MacroInterpreter::Warning(String msg, int line, int col) {
	ProcMsg pm;
	pm.file = error_file;
	pm.line = line;
	pm.col = col;
	pm.severity = PROCMSG_WARNING;
	pm.src = "MacroInterpreter";
	pm.msg = msg;
	WhenMessage(pm);
}

bool MacroInterpreter::ReadMacroArgument(const Vector<Token>& src, int& cursor, Vector<Token>& dst) {
	bool succ = false;
	int depth = 0;
	while (cursor < src.GetCount()) {
		const Token& tk = src[cursor];
		if (tk.IsType(TK_PARENTHESIS_END)) {
			if (!depth) {
				succ = true;
				break;
			}
			else {
				dst.Add(src[cursor]);
				depth--;
				cursor++;
			}
		}
		else if (tk.IsType(TK_COMMA)) {
			if (!depth) {
				succ = true;
				break;
			}
			else {
				dst.Add(src[cursor]);
				cursor++;
			}
		}
		else if (tk.IsType(TK_PARENTHESIS_BEGIN)) {
			dst.Add(src[cursor]);
			depth++;
			cursor++;
		}
		else {
			dst.Add(src[cursor]);
			cursor++;
		}
	}
	return succ;
}

void MacroInterpreter::ReplaceIds(Vector<Token>& replaced, const VectorMap<String, Vector<Token> >& replacing) {
	for(int i = 0; i < replaced.GetCount(); i++) {
		Token& tk = replaced[i];
		if (tk.IsType(TK_ID)) {
			String id = tk.GetString();
			int j = replacing.Find(id);
			if (j >= 0) {
				const Vector<Token>& tokens = replacing[j];
				replaced.Remove(i);
				for(int k = 0; k < tokens.GetCount(); k++)
					replaced.Insert(i+k, tokens[k]);
				i += tokens.GetCount() - 1;
			}
		}
	}
}

Token MacroInterpreter::ProcessNonMacroId(const Token& tk) {
	if (tk.IsType(TK_ID)) {
		String id = tk.GetString();
		
		if (id == "__LINE__") {
			Token t;
			t.type = TK_INTEGER;
			t.str_value = IntStr(tk.loc.line);
			return t;
		}
		else if (id == "__FILE__") {
			Token t;
			t.type = TK_STRING;
			t.str_value = file_path;
			return t;
		}
		else if (id == "__DATE__") {
			Time now = GetSysTime();
			Token t;
			t.type = TK_STRING;
			t.str_value = Format("%Mon %02d %04d", (int)now.month, (int)now.day, (int)now.year);
			return t;
		}
		else if (id == "__TIME__") {
			Time now = GetSysTime();
			Token t;
			t.type = TK_STRING;
			t.str_value = Format("%02d:%02d:%02d", (int)now.hour, (int)now.min, (int)now.sec);
			return t;
		}
		else
			return tk;
	}
	else
		return tk;
}


NAMESPACE_TOPSIDE_END
