#include "High.h"
#if USE_HIGH_BYTECODE

namespace UPP {


#define EMIT_FLAGS __FILE__, __LINE__
#define Emit(x) Emit_(x, EMIT_FLAGS)
#define Emit1(x, a) Emit1_(x, a, EMIT_FLAGS)
#define Emit2(x, a, b) Emit2_(x, a, b, EMIT_FLAGS)
#define Emit3(x, a, b, c) Emit3_(x, a, b, c, EMIT_FLAGS)
#define EmitLabel(x) EmitLabel_(x, EMIT_FLAGS)
#define EmitPushVar(x) EmitPushVar_(x, EMIT_FLAGS)
#define EmitPopVar(x, y) EmitPopVar_(x, y, EMIT_FLAGS)


#ifdef _MSC_VER
#pragma inline_depth(255)
#pragma optimize("t", on)
#endif

#define LTIMING(x)  // RTIMING(x)



int IrValue::total = 0;
int IrValue::GetTotalCount() {return total;}
int IrValue::GetMaxTotalCount() {return 1000000;}



void IrVM::TestLimit()
{
	LTIMING("TestLimit1");
	if(op_limit < 0)
		ThrowError("out of operations limit - considered frozen");
}

void HiCompiler::OutOfMemory()
{
	ThrowError("Out of memory");
}

void HiCompiler::TestLimit()
{
	LTIMING("TestLimit2");
	if(IrValue::GetTotalCount() >= IrValue::GetMaxTotalCount())
		OutOfMemory();
}

IrValue HiCompiler::Get()
{
	LTIMING("Get");
	Emit(IR_R_GET);
	IrValue v;
	v.SetRegisterValue(0);
	return v;
}

void HiCompiler::Assign(const IrValue& src)
{
	Emit1(IR_ASSIGN_R_LVAL_VALUE, src);
}

void HiCompiler::Subscript(String id)
{
	LTIMING("Subscript");
	
	for(;;) {
		TestLimit();
		if(Char('[')) {
			if(Char(']'))
				Emit(IR_R_SBS_ARRAYADD_EMPTY);
			else {
				IrValue v1, v2;
				if(!IsChar(',') && !IsChar(':'))
					v1 = GetExp();
				
				if(Char(',')) {
					if(!IsChar(']')) {
						v1 = EmitPushVar(v1);
						v2 = GetExp();
						v1 = EmitPopVar(v1, v2);
					}
					Emit2(IR_R_SBS_ARRAYADD_1_ARRAY2, v1, v2);
				}
				else
				if(Char(':')) {
					if(!IsChar(']')) {
						v1 = EmitPushVar(v1);
						v2 = GetExp();
						v1 = EmitPopVar(v1, v2);
					}
					Emit3(IR_R_SBS_ARRAYADD_1_ARRAY3, v1, v2, IrValue());
				}
				else
					Emit1(IR_R_SBS_ARRAYADD_1, v1);
				PassChar(']');
			}
		}
		else
		if(Char('.')) {
			Emit(IR_ASSIGN_RSELF_R);
			id = ReadId();
			Emit1(IR_R_SBS_ARRAYADD_1, id);
		}
		else
		if(Char('(')) {
			LTIMING("call fn");
			Emit(IR_ARGVEC_PUSH_NEW);
			if(!Char(')')) {
				for(;;) {
					LTIMING("make args");
					Emit(IR_PUSH_R_EMPTY);
					Exp();
					Emit(IR_POP_R_ARGVEC_ADD);
					if(Char(')')) break;
					PassChar(',');
				}
			}
			if(!IsChar2('!', '=') && Char('!')) {
				Emit(IR_PUSH_R_RSELF);
				Term();
				IrValue g = Get();
				Emit(IR_POP_R_RSELF);
				Emit1(IR_OP_INEQ_RSELF, g);
			}
			{
				IrValue v = Get();
				Emit2(IR_EXECUTE_LAMBDA, id, v);
			}
			Emit(IR_ARGVEC_POP);
		}
		else
			return;
	}
}

void HiCompiler::Subscript()
{
	Subscript(String());
}

void HiCompiler::Term()
{
	Emit(IR_R_SBS_RESET);

	TestLimit();
	if(IsChar2('0', 'x') || IsChar2('0', 'X')) {
		Emit1(IR_ASSIGN_R, ReadNumber64(16));
		return;
	}
	if(IsChar2('0', 'b') || IsChar2('0', 'B')) {
		Emit1(IR_ASSIGN_R, ReadNumber64(2));
		return;
	}
	if(IsChar2('0', '.')) {
		Emit1(IR_ASSIGN_R, ReadDouble());
		return;
	}
	if(IsChar('0')) {
		Emit1(IR_ASSIGN_R, IsNumber() ? ReadNumber64(8) : 0);
		return;
	}
	if(IsNumber()) {
		// TODO: int64 !
		Emit1(IR_ASSIGN_R, ReadDouble());
		return;
	}
	if(IsString()) {
		Emit1(IR_ASSIGN_R, IrValue(FromUtf8(ReadString())));
		return;
	}
	if(IsChar('\'')) {
		WString s = FromUtf8(ReadString('\'', true));
		if(s.GetLength() != 1)
			ThrowError("invalid character literal");
		Emit1(IR_ASSIGN_R, (int64)s[0]);
		return;
	}
	if(Char('@')) {
		Emit1(IR_ASSIGN_R, ReadLambda(*this));
		Subscript();
		return;
	}
	if(Id("void")) {
		Emit(IR_ASSIGN_R_VOID);
		return;
	}
	if(Char('{')) {
		Emit(IR_ASSIGN_R_EMPTYMAP);
		if(!Char('}')) {
			for(;;) {
				IrValue a = GetExp();
				PassChar(':');
				a = EmitPushVar(a);
				IrValue b = GetExp();
				a = EmitPopVar(a, b);
				Emit2(IR_R_MAPSET, a, b);
				if(Char('}'))
					break;
				PassChar(',');
				TestLimit();
			}
		}
		Subscript();
		return;
	}
	if(Char('[')) {
		Emit(IR_ASSIGN_R_EMPTYARRAY);
		if(!Char(']')) {
			for(;;) {
				Emit1(IR_R_ARRAYADD, GetExp());
				if(Char(']'))
					break;
				PassChar(',');
				TestLimit();
			}
		}
		Subscript();
		return;
	}
	if(Char('(')) {
		Exp();
		PassChar(')');
		Subscript();
		return;
	}
	
	Emit(IR_PUSH_RSELF_EMPTY);
	bool  _global = false;
	if(Char('.')) {
		Emit(IR_ASSERT_SELF_MAP);
		Emit(IR_ASSIGN_RSELF_LVAL_SELF);
	}
	else
	if(Char(':'))
		_global = true;
	if(IsId()) {
		String id = ReadId();
		
		if(id == "self") {
			Emit(IR_ASSERT_SELF_MAP);
			Emit(IR_ASSIGN_RSELF_LVAL_SELF);
		}
		else {
			IrValue lbl_exit = CreateLabel();
			
			// EmitLabel(lbl_a);
			IrValue tmp, b;
			if (!_global && IsChar('(')) {
				//IrValue lbl_a = CreateLabel();
				IrValue lbl_b = CreateLabel();
				IrValue lbl_c = CreateLabel();
				
				Emit1(IR_HAS_VAR, id);
				b.SetRegisterValue(0);
				Emit2(IR_JUMP_IF_TRUE, b, lbl_c);
				
				b = EmitSelfLambdaCheck(id, tmp, EMIT_FLAGS);
				Emit2(IR_JUMP_IF_FALSE, b, lbl_b);
				{
				    Emit(IR_ASSIGN_RSELF_LVAL_SELF);
					Emit1(IR_ASSIGN_R, tmp);
					Emit1(IR_JUMP, lbl_exit);
				}
				
				EmitLabel(lbl_b);
				b = EmitGlobalLambdaCheck(id, tmp, EMIT_FLAGS);
				Emit2(IR_JUMP_IF_FALSE, b, lbl_c);
				{
					Emit1(IR_ASSIGN_R_GLOBALIDX, tmp);
					Emit1(IR_JUMP, lbl_exit);
				}
				EmitLabel(lbl_c);
			}
			
			IrValue lbl_d = CreateLabel();
			
			b = EmitSelfLvalCheck(EMIT_FLAGS);
			Emit2(IR_JUMP_IF_FALSE, b, lbl_d);
			{
				Emit(IR_ASSIGN_R_RSELF);
				Emit1(IR_R_SBS_ARRAYADD_1, id);
				Emit1(IR_JUMP, lbl_exit);
			}
			
			EmitLabel(lbl_d);
			
			ASSERT(id.GetCount());
			if (_global)
				Emit1(IR_ASSIGN_R_LVAL_GLOBAL_GETADD, id);
			else
				Emit1(IR_ASSIGN_R_LVAL_VAR_GETADD, id);
			
			EmitLabel(lbl_exit);
		}
		
		try {
			Subscript(id);
		}
		catch(CParser::Error e) {
			throw CParser::Error(id + ": " + e);
		}
	}
	else
		ThrowError("invalid expression");
	
	Emit(IR_POP_RSELF);
}

String Lims(const String& s)
{
	return s.GetLength() > 80 ? s.Mid(0, 80) : s;
}

void HiCompiler::Unary()
{
	if(Char2('+', '+')) {
		Unary();
		IrValue v = Get();
		Emit1(IR_OP_PREINC, v);
	}
	else
	if(Char2('-', '-')) {
		Unary();
		IrValue v = Get();
		Emit1(IR_OP_PREDEC, v);
	}
	else
	if(Char('-')) {
		Unary();
		IrValue v = Get();
		Emit1(IR_OP_NEGATIVE, v);
	}
	else
	if(Char('+')) {
		Unary();
		IrValue v = Get();
		Emit1(IR_OP_POSITIVE, v);
	}
	else
	if(Char('!')) {
		Unary();
		Emit1(IR_OP_NOT, Get());
	}
	else
	if(Char('~')) {
		Unary();
		Emit1(IR_OP_NEGATE, Get());
	}
	else
		Term();

	if(Char2('+', '+')) {
		Emit1(IR_OP_POSTINC, Get());
	}
	if(Char2('-', '-')) {
		Emit1(IR_OP_POSTDEC, Get());
	}
}

void HiCompiler::Mul()
{
	Unary();
	for(;;) {
		if(!IsChar2('*', '=') && Char('*')) {
			IrValue a = EmitPushVar(Get());
			Emit(IR_PUSH_R_EMPTY);
			Unary();
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_MULARRAY, EmitPopVar(a, b), b);
		}
		else
		if(!IsChar2('/', '=') && Char('/')) {
			Emit(IR_PUSH_R_EMPTY);
			Unary();
			Emit(IR_POP_R_TEMP);
			IrValue a = EmitPushVar(Get());
			Emit(IR_PUSH_R_TEMP);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_DIVASS1, EmitPopVar(a, b), b);
		}
		else
		if(!IsChar2('%', '=') && Char('%')) {
			Emit(IR_PUSH_R_EMPTY);
			Unary();
			Emit(IR_POP_R_R1);
			Emit(IR_OP_MODASS1);
		}
		else
			return;
	}
}

void HiCompiler::Add()
{
	Mul();
	for(;;) {
		if(!IsChar2('+', '=') && Char('+')) {
			IrValue a = EmitPushVar(Get());
			Emit(IR_PUSH_R_EMPTY);
			Mul();
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_ADDASS1, EmitPopVar(a, b), b);
		}
		else
		if(!IsChar2('-', '=') && Char('-')) {
			Emit(IR_PUSH_R_EMPTY);
			Mul();
			Emit(IR_POP_R_TEMP);
			IrValue a = EmitPushVar(Get());
			Emit(IR_PUSH_R_TEMP);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_SUBASS1, EmitPopVar(a, b), b);
		}
		else
			return;
	}
}

void HiCompiler::Shift()
{
	Add();
	for(;;) {
		if(Char2('<', '<')) {
			IrValue a = EmitPushVar(Get());
			Emit(IR_PUSH_R_EMPTY);
			Add();
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_LSHF, EmitPopVar(a, b), b);
		}
		else
		if(Char2('>', '>')) {
			Emit(IR_PUSH_R_EMPTY);
			Add();
			Emit(IR_POP_R_R1);
			Emit(IR_OP_RSHF);
		}
		else
			return;
	}
}

void HiCompiler::DoCompare(const char *op)
{
	Emit(IR_PUSH_R_EMPTY);
	Shift();
	Emit(IR_POP_R_TEMP);
	IrValue a = EmitPushVar(Get());
	Emit(IR_PUSH_R_TEMP);
	IrValue b = Get();
	Emit(IR_POP_R);
	Emit3(IR_OP_CMP, EmitPopVar(a, b), b, op);
}

void HiCompiler::Compare()
{
	Shift();
	for(;;) {
		if (Char2('>', '=')) {
			DoCompare(">=");
			Emit1(IR_OP_CMP_RESULT, 0);
		}
		else if (Char2('<', '=')) {
			DoCompare("<=");
			Emit1(IR_OP_CMP_RESULT, 1);
		}
		else if (Char('>')) {
			DoCompare(">");
			Emit1(IR_OP_CMP_RESULT, 2);
		}
		else if (Char('<')) {
			DoCompare("<");
			Emit1(IR_OP_CMP_RESULT, 3);
		}
		else
			return;
	}
}

void HiCompiler::Equal()
{
	Compare();
	for(;;) {
		if(Char2('=', '=')) {
			Emit(IR_PUSH_R_EMPTY);
			Compare();
			Emit(IR_POP_R_TEMP);
			IrValue a = EmitPushVar(Get());
			Emit(IR_PUSH_R_TEMP);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_EQ, EmitPopVar(a, b), b);
		}
		else
		if(Char2('!', '=')) {
			Emit(IR_PUSH_R_EMPTY);
			Compare();
			Emit(IR_POP_R_TEMP);
			IrValue a = EmitPushVar(Get());
			Emit(IR_PUSH_R_TEMP);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_INEQ, EmitPopVar(a, b), b);
		}
		else
			return;
	}
}

void HiCompiler::BinAnd()
{
	Equal();
	while(!IsChar2('&', '&') && Char('&')) {
		Emit(IR_PUSH_R_EMPTY);
		Equal();
		Emit(IR_POP_R_R1);
		Emit(IR_ASSIGN_R_BWAND);
	}
}

void HiCompiler::BinXor()
{
	BinAnd();
	while(Char('^')) {
		Emit(IR_PUSH_R_EMPTY);
		BinAnd();
		Emit(IR_POP_R_R1);
		Emit(IR_ASSIGN_R_BWXOR);
	}
}

void HiCompiler::BinOr()
{
	BinXor();
	while(!IsChar2('|', '|') && Char('|')) {
		Emit(IR_PUSH_R_EMPTY);
		BinXor();
		Emit(IR_POP_R_R1);
		Emit(IR_ASSIGN_R_BWOR);
	}
}

void HiCompiler::And()
{
	BinOr();
	if(IsChar2('&', '&')) {
		IrValue b = IsTrue(Get());
		IrValue exit = CreateLabel();
		while(Char2('&', '&')) {
			Emit2(IR_JUMP_IF_FALSE, b, exit);
			b = EmitPushVar(b);
			Emit(IR_PUSH_R_EMPTY);
			BinOr();
			IrValue v = IsTrue(Get());
			Emit(IR_POP_R);
			b = EmitPopVar(b, v);
			Emit2(IR_OP_ANDASS1, b, v);
		}
		EmitLabel(exit);
		
		Emit1(IR_ASSIGN_R, b);
	}
}

void HiCompiler::Or()
{
	And();
	if(IsChar2('|', '|')) {
		IrValue b = IsTrue(Get());
		IrValue exit = CreateLabel();
		while(Char2('|', '|')) {
			Emit2(IR_JUMP_IF_TRUE, b, exit);
			b = EmitPushVar(b);
			Emit(IR_PUSH_R_EMPTY);
			And();
			IrValue v = IsTrue(Get());
			Emit(IR_POP_R);
			b = EmitPopVar(b, v);
			Emit2(IR_OP_ORASS1, b, v);
		}
		EmitLabel(exit);
		
		Emit1(IR_ASSIGN_R, b);
	}
}

void HiCompiler::Cond()
{
	Or();
	if(Char('?')) {
		IrValue t = IsTrue(Get());
		IrValue exit = CreateLabel();
		IrValue els = CreateLabel();
		Emit2(IR_JUMP_IF_FALSE, t, els); {
			Cond();
		}
		PassChar(':');
		Emit1(IR_JUMP, exit);
		EmitLabel(els); {
			Cond();
		}
		EmitLabel(exit);
	}
}

void HiCompiler::Assign()
{
	Cond();
	if(Char('=')) {
		Emit(IR_PUSH_R_EMPTY);
		Assign();
		IrValue a = Get();
		Emit(IR_POP_R);
		Assign(a);
	}
	else
	if(Char2('+', '=')) {
		IrValue a = EmitPushVar(Get());
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		IrValue b = Get();
		Emit(IR_POP_R);
		Emit2(IR_OP_ADDASS2, EmitPopVar(a, b), b);
	}
	else
	if(Char2('-', '=')) {
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		Emit(IR_POP_R_TEMP);
		IrValue a = EmitPushVar(Get());
		Emit(IR_PUSH_R_TEMP);
		IrValue b = Get();
		Emit(IR_POP_R);
		Emit2(IR_OP_SUBASS2, EmitPopVar(a, b), b);
	}
	else
	if(Char2('*', '=')) {
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		Emit(IR_POP_R_TEMP);
		IrValue a = EmitPushVar(Get());
		Emit(IR_PUSH_R_TEMP);
		IrValue b = Get();
		Emit(IR_POP_R);
		Emit2(IR_OP_MULASS2, EmitPopVar(a, b), b);
	}
	else
	if(Char2('/', '=')) {
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		Emit(IR_POP_R_TEMP);
		IrValue a = EmitPushVar(Get());
		Emit(IR_PUSH_R_TEMP);
		IrValue b = Get();
		Emit(IR_POP_R);
		Emit2(IR_OP_DIVASS2, EmitPopVar(a, b), b);
	}
	else
	if(Char2('%', '=')) {
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		Emit(IR_POP_R_R1);
	}
}

int HiCompiler::stack_level = 50;

void HiCompiler::Exp()
{
	LTIMING("Exp");
	Spaces();
	stack_level--;
	if(stack_level <= 0)
		ThrowError("stack overflow");
	Assign();
	stack_level++;
}

IrValue HiCompiler::GetExp() {
	Emit(IR_PUSH_R_EMPTY);
	Exp();
	IrValue a = Get();
	Emit(IR_POP_R);
	return a;
}

void HiCompiler::SkipTerm()
{
	if(IsEof())
		ThrowError("unexpected end of file");
	CParser::SkipTerm();
	Spaces();
}

void HiCompiler::SkipExp()
{
	int level = 0;
	for(;;) {
		if(IsChar(';'))
			return;
		if(IsChar(')') && level == 0)
			return;
		if(Char(')'))
			level--;
		else
		if(Char('('))
			level++;
		else
			SkipTerm();
		if(IsEof())
			ThrowError("unexpected end of file");
	}
}

void SkipBlock(CParser& p)
{
	int level = 1;
	while(level > 0 && !p.IsEof()) {
		if(p.Char('{')) level++;
		else
		if(p.Char('}')) level--;
		else
			p.SkipTerm();
	}
}

IrValue  HiCompiler::PCond()
{
	PassChar('(');
	IrValue c = IsTrue(GetExp());
	PassChar(')');
	return c;
}

void HiCompiler::FinishSwitch()
{
	for(;;) {
		if(IsId("case") || IsId("default") || IsChar('}'))
			break;
		DoStatement();
	}
}

void  HiCompiler::DoStatement()
{
	TestLimit();
	if(Id("if")) {
		IrValue cond = PCond();
		IrValue exit1 = CreateLabel();
		Emit2(IR_JUMP_IF_FALSE, cond, exit1);
		DoStatement();
		if(Id("else")) {
			IrValue exit2 = CreateLabel();
			Emit1(IR_JUMP, exit2);
			EmitLabel(exit1);
			DoStatement();
			EmitLabel(exit2);
		}
		else
			EmitLabel(exit1);
	}
	else
	if(Id("do")) {
		IrValue exit = CreateLabel();
		IrValue cont = CreateLabel();
		PushLoop(exit, cont);
		EmitLabel(cont);
		 {
			DoStatement();
		}
		PassId("while");
		IrValue cond = PCond();
		PassChar(';');
		Emit2(IR_JUMP_IF_TRUE, cond, cont);
		EmitLabel(exit);
		PopLoop();
	}
	else
	if(Id("while")) {
		IrValue exit = CreateLabel();
		IrValue cont = CreateLabel();
		PushLoop(exit, cont);
		{
			EmitLabel(cont);
			Emit2(IR_JUMP_IF_FALSE, PCond(), exit);
			DoStatement();
		}
		EmitLabel(exit);
		PopLoop();
	}
	else
	if(Id("for")) {
		IrValue lbl_exit = CreateLabel();
		IrValue lbl_first = CreateLabel();
		IrValue lbl_post = CreateLabel();
		IrValue lbl_cond = CreateLabel();
		PushLoop(lbl_exit, lbl_post);
		PassChar('(');
		Emit(IR_PUSH_R_EMPTY);
		if(!IsChar(';'))
			Exp();
		{
			Emit1(IR_JUMP, lbl_first);
			PassChar(';');
			
			// for conditional
			EmitLabel(lbl_cond);
			IrValue cond;
			if(!IsChar(';')) {
				cond = IsTrue(GetExp());
				SkipExp();
			}
			PassChar(';');
			Emit2(IR_JUMP_IF_FALSE, cond, lbl_exit);
			Emit1(IR_JUMP, lbl_first);
			
			// for post op
			EmitLabel(lbl_post);
			if(!IsChar(')')) {
				Emit(IR_PUSH_R_EMPTY);
				Exp();
				Emit(IR_POP_R);
			}
			PassChar(')');
			Emit1(IR_JUMP, lbl_cond);
			
			// for block statement
			EmitLabel(lbl_first);
			{
				DoStatement();
			}
			
			Emit1(IR_JUMP, lbl_post);
		}
		EmitLabel(lbl_exit);
		PopLoop();
		Emit(IR_POP_R);
	}
	else
	if(Id("break")) {
		if(!loop)
			ThrowError("misplaced 'break'");
		if (loop_stack.IsEmpty())
			ThrowError("internal error: empty loop stack");
		LoopStack& l = loop_stack.Top();
		if (!l.exit.IsLabel())
			ThrowError("trying to jump non-label");
		Emit1(IR_JUMP, l.exit);
		PassChar(';');
	}
	else
	if(Id("continue")) {
		if(!loop)
			ThrowError("misplaced 'continue'");
		if (loop_stack.IsEmpty())
			ThrowError("internal error: empty loop stack");
		LoopStack& l = loop_stack.Top();
		if (!l.repeat.IsLabel())
			ThrowError("trying to jump non-label");
		Emit1(IR_JUMP, l.repeat);
		PassChar(';');
	}
	else
	if(Id("case"))
		ThrowError("misplaced 'case'");
	else
	if(Id("default"))
		ThrowError("misplaced 'default'");
	else
	if(Id("else"))
		ThrowError("misplaced 'else'");
	else
	if(Id("return")) {
		if(!Char(';')) {
			//already: Emit1(R_ASSIGN_R0, GetExp());
			GetExp();
			PassChar(';');
		}
		else
			Emit1(IR_ASSIGN_R0, IrValue());
		if (loop_stack.IsEmpty())
			ThrowError("internal error: empty loop stack");
		Emit1(IR_JUMP, loop_stack[0].exit);
	}
	else
	if(Id("switch")) {
		PassChar('(');
		IrValue a = GetExp();
		PassChar(')');
		PassChar('{');
		IrValue exit = CreateLabel();
		IrValue next_case = CreateLabel();
		PushLoop(exit);
		while(!Char('}')) {
			if(Id("case")) {
				a = EmitPushVar(a);
				IrValue b = GetExp();
				PassChar(':');
				a = EmitPopVar(a, b);
				Emit3(IR_JUMP_IF_INEQ, a, b, next_case);
				FinishSwitch();
				EmitLabel(next_case);
			}
			else
			if(Id("default")) {
				PassChar(':');
				FinishSwitch();
			}
			else
				ThrowError("Unexpected statement in switch block");
		}
		EmitLabel(exit);
		PopLoop();
	}
	else
	if(Char('#')) {
		TODO
		
	}
	else
	if(Char('{')) {
		while(!Char('}'))
			DoStatement();
	}
	else
	if(!Char(';')) {
		Emit(IR_PUSH_R_EMPTY);
		Exp();
		Emit(IR_POP_R);
		PassChar(';');
	}
}

void HiCompiler::Run() {
	loop = 0;
	fail = 0;
	
	ASSERT(loop_stack.IsEmpty());
	IrValue exit = CreateLabel();
	PushLoop(exit);
	
	while(!IsEof() && !fail)
		DoStatement();
	
	EmitLabel(exit);
	PopLoop();
}

void HiCompiler::SwapIR(Vector<IR>& ir) {
	Swap(ir, this->ir);
}

void HiCompiler::WriteLambda(HiLambda& l) {
	Swap(l.ir, ir);
	l.compiled = true;
}

void HiCompiler::Emit_(IrCode x, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = x;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
}

void HiCompiler::Emit1_(IrCode x, IrValue a, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = x;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0] = a;
}

void HiCompiler::Emit2_(IrCode x, IrValue a, IrValue b, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = x;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0] = a;
	ir.arg[1] = b;
}

void HiCompiler::Emit3_(IrCode x, IrValue a, IrValue b, IrValue c, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = x;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0] = a;
	ir.arg[1] = b;
	ir.arg[2] = c;
}

void HiCompiler::EmitLabel_(IrValue l, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = IR_LABEL;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0] = l;
}

IrValue HiCompiler::EmitSelfLambdaCheck(String id, IrValue& tmp, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = IR_SELF_LAMBDA_CHECK;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0] = id;
	tmp.SetRegisterValue(1);
	IrValue dst;
	dst.SetRegisterValue(0);
	return dst;
}

IrValue HiCompiler::EmitGlobalLambdaCheck(String id, IrValue& tmp, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = IR_GLOBAL_LAMBDA_CHECK;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0] = id;
	tmp.SetRegisterValue(1);
	IrValue dst;
	dst.SetRegisterValue(0);
	return dst;
}

IrValue HiCompiler::EmitSelfLvalCheck(const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = IR_RSELF_LVAL_CHECK;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	IrValue dst;
	dst.SetRegisterValue(0);
	return dst;
}

IrValue HiCompiler::EmitPushVar_(const IrValue& v, const char* file, int line) {
	IR& ir = this->ir.Add();
	ir.code = IR_PUSH_VAR;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0] = v;
	IrValue dst;
	dst.SetVarStackValue(0);
	return dst;
}

IrValue HiCompiler::EmitPopVar_(const IrValue& v, int reg, const char* file, int line) {
	ASSERT(v.IsVarStackValue(0));
	IR& ir = this->ir.Add();
	ir.code = IR_POP_VAR;
	ir.file = file;
	ir.line = line;
	ir.codepos = GetPos();
	ir.arg[0].SetRegisterValue(reg);
	IrValue dst;
	dst.SetRegisterValue(reg);
	return dst;
}

IrValue HiCompiler::EmitPopVar_(const IrValue& v, const IrValue& avoid0, const char* file, int line) {
	ASSERT(v.IsVarStackValue(0));
	for(int i = 0; i < IrValue::REG_COUNT; i++) {
		if (avoid0.IsRegister(i))
			continue;
		IR& ir = this->ir.Add();
		ir.code = IR_POP_VAR;
		ir.file = file;
		ir.line = line;
		ir.codepos = GetPos();
		ir.arg[0] = i;
		IrValue dst;
		dst.SetRegisterValue(i);
		return dst;
	}
	
	OnError("All registers in use");
	return IrValue();
}

IrValue HiCompiler::CreateLabel() {
	return IrValue().SetLabel(lbl_counter++);
}

void HiCompiler::PushLoop(IrValue exit) {
	LoopStack& l = loop_stack.Add();
	l.exit = exit;
	loop++;
}

void HiCompiler::PushLoop(IrValue exit, IrValue repeat) {
	LoopStack& l = loop_stack.Add();
	l.exit = exit;
	l.repeat = repeat;
	loop++;
}

void HiCompiler::CreateSwitchDefault() {
	TODO
}

void HiCompiler::PopLoop() {
	loop_stack.Remove(loop_stack.GetCount()-1);
	loop--;
}

IrValue HiCompiler::IsTrue(const IrValue& v) {
	Emit1(IR_R_ISTRUE, v);
	IrValue r;
	r.SetRegisterValue(0);
	return r;
}

void HiCompiler::OnError(String msg) {
	fail = true;
	LOG("HiCompiler::OnError: " << msg);
	return;
}



}

#endif
