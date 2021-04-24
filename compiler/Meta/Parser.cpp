#include "Meta.h"

NAMESPACE_OULU_BEGIN

String IR::ToString() const {
	String s = GetTypeString();
	if (type == IR_INS)
		s += " " + IntStr(id);
	s += ": ";
	if (str_value.GetCount())
		s += "str='" + str_value + "'";
	else if (int_value)
		s += "int=" + IntStr(int_value);
	else
		s += "dbl=" + DblStr(dbl_value);
	return s;
}

String IR::GetTypeString() const {
	switch (type) {
		case IR_INS: return t_("Instruction");
		case IR_LBL: return t_("Label");
		default: return t_("Invalid type");
	}
}














bool MachHeaders::Init(String mach) {
	if (this->mach == mach)
		return true;
	
	#define MACH_BEGIN(x) if (mach == #x) {
	#define INS(name) AddInstruction(#name);
	#define INS_1(name, type) AddInstruction(#name, #type);
	#define MACH_END \
		this->mach = mach; \
		return true;}
		
	#define MICROCODE_HEADERS
	#include "machines.h"
	#undef MICROCODE_HEADERS
	
	return false;
}












Parser::Parser() : ErrorSource("Parser") {
	
}

bool Parser::Process(const Tokenizer& tk) {
	this->tk = &tk;
	const Vector<Token>& tokens = tk.GetTokens();
	
	ir.SetCount(0);
	ir.Reserve(1000);
	
	cursor = 0;
	while (cursor < tokens.GetCount()) {
		const Token& tk = tokens[cursor];
		bool expect_nl = false;
		bool skip_until_nl = false;
		if (tk.IsType(TK_NEWLINE))
			;
		else if (tk.IsType(TK_EOF))
			break;
		else if (Is2(TK_ID, TK_COLON)) {
			IR& ir = this->ir.Add();
			ir.type = IR_LBL;
			ir.id = -1;
			ir.str_value = tk.str_value;
			cursor += 2;
			expect_nl = true;
		}
		else if (tk.IsType(TK_ID)) {
			int i = mach.rules.Find(tk.str_value);
			if (i < 0) {
				AddError(tk.loc, "Invalid instruction " + tk.str_value);
				skip_until_nl = true;
			}
			else {
				IR& ir = this->ir.Add();
				ir.type = IR_INS;
				ir.id = i;
				
				cursor++;
				const MachHeaders::InsRule& rule = mach.rules[i];
				for(int i = 0; i < rule.arg_count; i++) {
					int type = rule.type[i];
					
					if (CheckEnd())
						break;
					
					const Token& tk = tokens[cursor];
					if (type == ARG_INT) {
						if (tk.IsType(TK_INTEGER))
							ir.int_value = StrInt(tk.str_value);
						else
							AddError(tk.loc, "Expected integer");
					}
					else if (type == ARG_STRING) {
						if (tk.IsType(TK_STRING))
							ir.str_value = tk.str_value;
						else
							AddError(tk.loc, "Expected string");
					}
					else if (type == ARG_CHAR) {
						if (tk.IsType(TK_CHAR))
							ir.str_value = tk.str_value;
						else
							AddError(tk.loc, "Expected char");
					}
					else if (type == ARG_ID) {
						if (tk.IsType(TK_ID))
							ir.str_value = tk.str_value;
						else
							AddError(tk.loc, "Expected char");
					}
					else Panic("Invalid arg type");
					
					cursor++;
				}
				
				expect_nl = true;
			}
		}
		else {
			AddError(tk.loc, "Expected id");
			skip_until_nl = true;
		}
		
		if (expect_nl) {
			const Token& tk = tokens[cursor];
			if (!tk.IsType(TK_NEWLINE) && !tk.IsType(TK_EOF)) {
				AddError(tk.loc, "Expected newline or end-of-file");
				skip_until_nl = true;
			}
		}
		
		if (skip_until_nl) {
			while (cursor < tokens.GetCount() && !tokens[cursor].IsType(TK_NEWLINE)) cursor++;
		}
		
		
		cursor++;
	}
	
	return !IsFail();
}

bool Parser::CheckEnd() {
	const Vector<Token>& tokens = tk->GetTokens();
	if (cursor >= tokens.GetCount()) {
		AddError(tk->GetLocation(), "Unexpected end of file");
		return true;
	}
	return false;
}

bool Parser::Is2(int tk0, int tk1) {
	const Vector<Token>& tokens = tk->GetTokens();
	if (cursor+1 >= tokens.GetCount())
		return false;
	return tokens[cursor].IsType(tk0) && tokens[cursor+1].IsType(tk1);
}

void Parser::Dump() const {
	LOG("ir:");
	for(int i = 0; i < ir.GetCount(); i++) {
		LOG("\t[" << i << "] = " << GetIRString(this->ir[i]));
	}
}

String Parser::GetIRString(const IR& ir) const {
	String s = ir.GetTypeString() + " ";
	if (ir.type == IR_INS) {
		const MachHeaders::InsRule& r = mach.rules[ir.id];
		s += mach.rules.GetKey(ir.id);
		if (r.arg_count) {
			if (r.type[0] == ARG_CHAR || r.type[0] == ARG_ID || r.type[0] == ARG_STRING) {
				s += " '" + ir.str_value + "'";
			}
			else if (r.type[0] == ARG_INT) {
				s += " " + IntStr(ir.int_value);
			}
		}
	}
	else if (ir.type == IR_LBL)
		s += ir.str_value;
	return s;
}


NAMESPACE_OULU_END
