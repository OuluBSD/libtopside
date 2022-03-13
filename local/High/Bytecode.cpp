#include "High.h"
#if USE_HIGH_BYTECODE

namespace UPP {

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
	v.SetRegisterValue(IrValue::REG_R0);
	return v;
}
/*
void HiCompiler::Assign(IrValue& val, const Vector<IrValue>& sbs, int si, const IrValue& src)
{
	LTIMING("Assign");
	const IrValue& ss = sbs[si++];
	if(val.IsVoid())
		val.SetEmptyMap();
	if(val.IsMap()) {
		if(si < sbs.GetCount()) {
			IrValue x = val.MapGet(ss);
			val.MapSet(ss, 0.0);
			Assign(x, sbs, si, src);
			val.MapSet(ss, x);
		}
		else
			val.MapSet(ss, src);
		return;
	}
	else
	if(val.IsArray()) {
		if(si < sbs.GetCount()) {
			if(ss.IsArray())
				ThrowError("slice must be last subscript");
			int64 i = Int(ss, "index");
			if(i >= 0 && i < val.GetCount()) {
				IrValue x = val.ArrayGet((int)i);
				val.ArraySet((int)i, 0.0);
				Assign(x, sbs, si, src);
				if(!val.ArraySet((int)i, x))
					OutOfMemory();
				return;
			}
		}
		else {
			int count = val.GetCount();
			if(ss.IsArray()) {
				if(!src.IsArray() || ss.GetArray().GetCount() < 2)
					ThrowError("only array can be assigned to the slice");
				IrValue v1 = ss.ArrayGet(0);
				IrValue v2 = ss.ArrayGet(1);
				int i = v1.IsInt() ? v1.GetInt() : 0;
				int n = count - i;
				if(ss.GetCount() == 2)
					n = v2.IsInt() ? v2.GetInt() : n;
				else {
					if(v2.IsInt()) {
						n = v2.GetInt();
						if(n < 0)
							n += count;
						n -= i;
					}
				}
				if(i >= 0 && n >= 0 && i + n <= count) {
					val.Replace(i, n, src);
					return;
				}
				else
					ThrowError("slice out of range");
			}
			else {
				int64 i = ss.IsVoid() ? val.GetCount() : Int(ss, "index");
				if(i < 0)
					i = count + i;
				if(i >= 0 && i < INT_MAX) {
					if(!val.ArraySet((int)i, src))
						ThrowError("out of memory");
					return;
				}
			}
		}
	}
	ThrowError("invalid indirection");
}*/

void HiCompiler::Assign(const IrValue& src)
{
	//if(skipexp)
	//	return;
	Emit1(IR_ASSIGN_R_LVAL2, src);
}

/*IrValue HiCompiler::ExecuteLambda(const String& id, IrValue lambda, SRVal self, Vector<SRVal>& arg)
{
	LTIMING("ExecuteLambda");
	if(!lambda.IsLambda())
		ThrowError(Format("'%s' is not a lambda", id));
	const HiLambda& l = lambda.GetLambda();
	if(!l.varargs && arg.GetCount() > l.arg.GetCount()
	   || arg.GetCount() < l.arg.GetCount() - l.def.GetCount())
		ThrowError("invalid number of arguments in call to '" + id + "'");
	Hi sub(global, l.code, op_limit, l.filename, l.line);
	sub.self = Get(self);
	for(int i = 0; i < l.arg.GetCount(); i++) {
		sub.var.GetAdd(l.arg[i]) =
			i < arg.GetCount() ? Get(arg[i])
		                       : Evaluatex(l.def[i - (l.arg.GetCount() - l.def.GetCount())], global, op_limit);
		TestLimit();
	}
	IrValue retval;
	Array<IrValue> argvar;
	if(l.escape) {
		#if LIBTOPSIDE
		sub.var.PickValues(argvar);
		#else
		argvar = sub.var.PickValues();
		#endif
		
		for(int i = l.arg.GetCount(); i < arg.GetCount(); i++) {
			argvar.Add(Get(arg[i]));
		}
		IrValue v = Get(self);
		HiEscape e(*this, v, argvar);
		e.id = id;
		l.escape(e);
		retval = e.ret_val;
		self = e.self;
	}
	else {
		if(l.varargs) {
			IrValue& argv = sub.var.GetAdd("argv");
			argv.SetEmptyArray();
			for(int i = l.arg.GetCount(); i < arg.GetCount(); i++)
				argv.ArrayAdd(Get(arg[i]));
		}
		sub.Run();
		retval = sub.return_value;
		
		#if LIBTOPSIDE
		sub.var.PickValues(argvar);
		#else
		argvar = sub.var.PickValues();
		#endif
	}
	for(int i = 0; i < l.inout.GetCount(); i++)
		if(l.inout[i] && i < arg.GetCount() && arg[i].lval)
			Assign(arg[i], argvar[i]);
	if(self.lval)
		Assign(self, sub.self);
	return retval;
}*/

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
					if(!IsChar(']'))
						v2 = GetExp();
					Emit2(IR_R_SBS_ARRAYADD_1_ARRAY2, v1, v2);
				}
				else
				if(Char(':')) {
					if(!IsChar(']'))
						v2 = GetExp();
					Emit3(IR_R_SBS_ARRAYADD_1_ARRAY3, v1, v2, IrValue());
				}
				else
					Emit1(IR_R_SBS_ARRAYADD_1, v1);
				PassChar(']');
			}
		}
		else
		if(Char('.')) {
			Emit(IR_ASSIGN_SELF_R);
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
					Emit(IR_PUSH_R_ARGVEC_ADD);
					Exp();
					Emit(IR_POP_R);
					if(Char(')')) break;
					PassChar(',');
				}
			}
			if(!IsChar2('!', '=') && Char('!')) {
				Emit(IR_PUSH_R_POP_SELF);
				Term();
				IrValue g = Get();
				Emit1(IR_OP_INEQ_TEMPSELF, g);
			}
			/*if(!skipexp)*/ {
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

	//op_limit--;
	TestLimit();
	if(Char2('0', 'x') || Char2('0', 'X')) {
		Emit1(IR_ASSIGN_R, ReadNumber64(16));
		return;
	}
	if(Char2('0', 'b') || Char2('0', 'B')) {
		Emit1(IR_ASSIGN_R, ReadNumber64(2));
		return;
	}
	if(IsChar2('0', '.')) {
		Emit1(IR_ASSIGN_R, ReadDouble());
		return;
	}
	if(Char('0')) {
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
				IrValue v = GetExp();
				PassChar(':');
				Emit2(IR_R_MAPSET, v, GetExp());
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
	
	Emit(IR_ASSIGN_R1_SELF);
	Emit(IR_PUSH_SELF);
	bool  _global = false;
	if(Char('.')) {
		Emit(IR_ASSERT_SELF_MAP);
		Emit(IR_ASSIGN_SELF_LVAL_R1); // _self.lval = &self;
		Emit(IR_ASSIGN_R_R1); // r = self;
	}
	else
	if(Char(':'))
		_global = true;
	if(IsId()) {
		String id = ReadId();
		IrValue method;
		int locali = var.Find(id);
		int ii;

		
		if(id == "self") {
			Emit(IR_ASSERT_SELF_MAP);
			Emit(IR_ASSIGN_SELF_LVAL_R1);
			Emit(IR_ASSIGN_R_R1);
		}
		else {
			Emit(IR_COND_IF_SELFLAMBDA);
			{
			    Emit(IR_ASSIGN_SELF_LVAL_R1);
				Emit(IR_ASSIGN_R_TMPMETHOD);
			}
			Emit(IR_COND_ELSE); {
				Emit(IR_COND_IF_GLOBALLAMBDA); {
					Emit(IR_ASSIGN_R_TMPGLOBALIDX);
				}
				Emit(IR_COND_ELSE); {
					Emit(IR_COND_IF_SELF_LVAL); {
						Emit(IR_ASSIGN_R_SELF);
						Emit1(IR_R_SBS_ARRAYADD_1, id);
					}
					Emit(IR_COND_ELSE); {
						Emit(IR_COND_IF_GLOBAL); {
							Emit1(IR_ASSIGN_R_LVAL1, global.GetAdd(id));
						}
						Emit(IR_COND_ELSE); {
							Emit1(IR_ASSIGN_R_LVAL1, var.GetAdd(id));
						}
						Emit(IR_COND_ENDIF);
					}
					Emit(IR_COND_ENDIF);
				}
				Emit(IR_COND_ENDIF);
			}
			Emit(IR_COND_ENDIF);
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
	
	Emit(IR_POP_SELF);
}

String Lims(const String& s)
{
	return s.GetLength() > 80 ? s.Mid(0, 80) : s;
}

/*double HiCompiler::Number(const IrValue& a, const char *oper)
{
	if(!a.IsNumber())
		ThrowError(String().Cat() << "number expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return a.GetNumber();
}

int64 HiCompiler::Int(const IrValue& a, const char *oper)
{
	if(!a.IsNumber())
		ThrowError(String().Cat() << "integer expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return a.GetInt64();
}

double HiCompiler::Number(const HiCompiler::SRVal& a, const char *oper)
{
	return Number(Get(a), oper);
}

int64 HiCompiler::Int(const HiCompiler::SRVal& a, const char *oper)
{
	return Int(Get(a), oper);
}*/

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

/*IrValue HiCompiler::MulArray(IrValue array, IrValue times)
{
	IrValue r;
	r.SetEmptyArray();
	for(int n = times.GetInt(); n > 0; n >>= 1) {
		if(n & 1)
			if(!r.Append(array))
				OutOfMemory();
		if(!array.Append(array))
			OutOfMemory();
		TestLimit();
	}
	return r;
}*/

void HiCompiler::Mul()
{
	Unary();
	for(;;) {
		if(!IsChar2('*', '=') && Char('*')) {
			IrValue x = Get();
			Emit(IR_PUSH_R_EMPTY);
			Unary();
			IrValue y = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_MULARRAY, x, y);
		}
		else
		if(!IsChar2('/', '=') && Char('/')) {
			Emit(IR_PUSH_R_EMPTY);
			Unary();
			Emit(IR_POP_R_TEMP);
			IrValue x = Get();
			Emit(IR_PUSH_R_TEMP);
			IrValue y = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_DIVASS1, x, y);
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
			IrValue v = Get();
			Emit(IR_PUSH_R_EMPTY);
			Mul();
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_ADDASS1, v, b);
		}
		else
		if(!IsChar2('-', '=') && Char('-')) {
			Emit(IR_PUSH_R_EMPTY);
			Mul();
			Emit(IR_POP_R_TEMP);
			IrValue v = Get();
			Emit(IR_PUSH_R_TEMP);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_SUBASS1, v, b);
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
			IrValue v = Get();
			Emit(IR_PUSH_R_EMPTY);
			Add();
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_LSHF, v, b);
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

/*double HiCompiler::DoCompare(const IrValue& a, const IrValue& b, const char *op)
{
	LTIMING("DoCompare");
	if(a.IsInt64() && b.IsInt64())
		return SgnCompare(a.GetInt64(), b.GetInt64());
	if(a.IsNumber() && b.IsNumber())
		return SgnCompare(a.GetNumber(), b.GetNumber());
	if(a.IsArray() && b.IsArray()) {
		const Vector<IrValue>& x = a.GetArray();
		const Vector<IrValue>& y = b.GetArray();
		int i = 0;
		for(;;) {
			if(i >= x.GetCount())
				return i < y.GetCount() ? -1 : 0;
			if(i >= y.GetCount())
				return i < x.GetCount() ? 1 : 0;
			double q = DoCompare(x[i], y[i], op);
			if(q) return q;
			i++;
		}
	}
	if(a.IsVoid() && b.IsVoid())
		return 0;
	if(!a.IsVoid() && b.IsVoid())
		return 1;
	if(a.IsVoid() && !b.IsVoid())
		return -1;
	ThrowError("invalid values for comparison " + a.GetTypeName() + ' ' + String(op) + ' ' + b.GetTypeName());
	return 0;
}*/

void HiCompiler::DoCompare(const char *op)
{
	Emit(IR_PUSH_R_EMPTY);
	Shift();
	Emit(IR_POP_R_TEMP);
	IrValue a = Get();
	Emit(IR_PUSH_R_TEMP);
	IrValue b = Get();
	Emit(IR_POP_R);
	Emit3(IR_OP_CMP, a, b, op);
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
			IrValue a = Get();
			Emit(IR_PUSH_R_TEMP);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_EQ, a, b);
		}
		else
		if(Char2('!', '=')) {
			Emit(IR_PUSH_R_EMPTY);
			Compare();
			Emit(IR_POP_R_TEMP);
			IrValue a = Get();
			Emit(IR_PUSH_R_TEMP);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_INEQ, a, b);
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
			Emit(IR_PUSH_R_EMPTY);
			BinOr();
			IrValue v = IsTrue(Get());
			Emit(IR_POP_R);
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
			Emit(IR_PUSH_R_EMPTY);
			And();
			IrValue v = IsTrue(Get());
			Emit(IR_POP_R);
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
		Emit1(IR_COND_IF, t); {
			Cond();
		}
		PassChar(':');
		Emit(IR_COND_ELSE); {
			Cond();
		}
		Emit(IR_COND_ENDIF);
	}
}

void HiCompiler::Assign()
{
	Cond();
	if(Char('=')) {
		Emit(IR_PUSH_R_EMPTY);
		Assign();
		IrValue v = Get();
		Emit(IR_POP_R);
		Assign(v);
	}
	else
	if(Char2('+', '=')) {
		IrValue v = Get();
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		IrValue b = Get();
		Emit(IR_POP_R);
		Emit(IR_OP_ADDASS2);
	}
	else
	if(Char2('-', '=')) {
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		Emit(IR_POP_R_TEMP);
		IrValue v = Get();
		Emit(IR_PUSH_R_TEMP);
		IrValue b = Get();
		Emit(IR_POP_R);
		Emit(IR_OP_SUBASS2);
	}
	else
	if(Char2('*', '=')) {
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		Emit(IR_POP_R_TEMP);
		IrValue x = Get();
		Emit(IR_PUSH_R_TEMP);
		IrValue y = Get();
		Emit(IR_POP_R);
		Emit(IR_OP_MULASS2);
	}
	else
	if(Char2('/', '=')) {
		Emit(IR_PUSH_R_EMPTY);
		Cond();
		Emit(IR_POP_R_TEMP);
		IrValue v = Get();
		Emit(IR_PUSH_R_TEMP);
		IrValue b = Get();
		Emit(IR_POP_R);
		Emit(IR_OP_DIVASS2);
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
	IrValue v = Get();
	Emit(IR_POP_R);
	return v;
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
/*
void HiCompiler::SkipStatement()
{
	stack_level--;
	if(stack_level <= 0)
		ThrowError("stack overflow");
	if(Id("if")) {
		PassChar('(');
		SkipExp();
		PassChar(')');
		SkipStatement();
		if(Id("else"))
			SkipStatement();
	}
	else
	if(Id("for")) {
		PassChar('(');
		if(!IsChar(';'))
			SkipExp();
		PassChar(';');
		if(!IsChar(';'))
			SkipExp();
		PassChar(';');
		if(!IsChar(')'))
			SkipExp();
		PassChar(')');
		SkipStatement();
	}
	else
	if(Id("while") || Id("switch")) {
		PassChar('(');
		SkipExp();
		PassChar(')');
		SkipStatement();
	}
	else
	if(Id("do")) {
		SkipBlock(*this);
		PassId("while");
		PassChar('(');
		SkipExp();
		PassChar(')');
		PassChar(';');
	}
	else
	if(Char('{'))
		SkipBlock(*this);
	else {
		SkipExp();
		PassChar(';');
	}
	stack_level++;
}*/

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
	//op_limit--;
	TestLimit();
	if(Id("if")) {
		IrValue cond = PCond();
		Emit1(IR_COND_IF, cond);
		DoStatement();
		if(Id("else")) {
			Emit(IR_COND_ELSE);
			DoStatement();
		}
		Emit(IR_COND_ENDIF);
	}
	else
	if(Id("do")) {
		//Pos pos = GetPos();
		IrValue exit = CreateLabel();
		IrValue cont = CreateLabel();
		PushLoop(exit, cont);
		/*do*/ {
			EmitLabel(cont);
			//SetPos(pos);
			DoStatement();
			PassId("while");
			//no_continue = true;
		}
		PassChar(';');
		Emit2(IR_JUMP_IF_TRUE, PCond(), cont);
		EmitLabel(exit);
		PopLoop();
		//no_break = true;
	}
	else
	if(Id("while")) {
		//Pos pos = GetPos();
		IrValue exit = CreateLabel();
		IrValue cont = CreateLabel();
		PushLoop(exit, cont);
		/*for(;;)*/ {
			//SetPos(pos);
			EmitLabel(cont);
			Emit2(IR_JUMP_IF_FALSE, PCond(), exit);
			DoStatement();
			//no_continue = true;
		}
		EmitLabel(exit);
		PopLoop();
		//no_break = true;
	}
	else
	if(Id("for")) {
		IrValue lbl_exit = CreateLabel();
		IrValue lbl_first = CreateLabel();
		IrValue lbl_post = CreateLabel();
		IrValue lbl_cond = CreateLabel();
		PushLoop(lbl_exit, lbl_cond);
		PassChar('(');
		Emit(IR_PUSH_R_EMPTY);
		if(!IsChar(';'))
			Exp();
		/* TODO
		if(Id("in") || Char(':')) {
			IrValue range = GetExp();
			PassChar(')');
			Pos stmt = GetPos();
			int i = 0;
			for(;;) {
				SetPos(stmt);
				// TODO iterator in vm
				// TODO emit if
				if(range.IsArray()) {
					if(i >= range.GetCount())
						break;
					Emit1(IR_ASSIGN_R, (int64)i);
				}
				else
				if(range.IsMap()) {
					const VectorMap<IrValue, IrValue>& map = range.GetMap();
					if(i >= map.GetCount())
						break;
					if(map.IsUnlinked(i)) {
						i++;
						continue;
					}
					Emit1(IR_ASSIGN_R, map.GetKey(i));
				}
				DoStatement();
				no_continue = true;
				i++;
			}
			SkipStatement();
		}
		else*/ {
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
				//no_continue = true;
			}
			
			Emit1(IR_JUMP, lbl_post);
		}
		EmitLabel(lbl_exit);
		PopLoop();
		Emit(IR_POP_R);
		//no_break = true;
	}
	else
	if(Id("break")) {
		if(!loop)
			ThrowError("misplaced 'break'");
		//no_break = false;
		PassChar(';');
	}
	else
	if(Id("continue")) {
		if(!loop)
			ThrowError("misplaced 'continue'");
		//no_continue = false;
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
		//no_return = false;
		if(!Char(';')) {
			//already: Emit1(R_ASSIGN_R0, GetExp());
			GetExp();
			PassChar(';');
		}
		else
			Emit1(IR_ASSIGN_R0, IrValue());
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
				IrValue b = GetExp();
				PassChar(':');
				Emit3(IR_JUMP_IF_INEQ, a, b, next_case);
				FinishSwitch();
				EmitLabel(next_case);
			}
			else
			if(Id("default")) {
				PassChar(':');
				FinishSwitch();
				break;
			}
			else
				ThrowError("Unexpected statement in switch block");
		}
		EmitLabel(exit);
		PopLoop();
		//no_break = true;
	}
	else
	if(Char('#')) {
		int type = 0;
		if(Char('.'))
			type = 1;
		else
		if(Char(':'))
			type = 2;
		String id = ReadId();
		IrValue l = ReadLambda(*this);
		if(type == 1) {
			Emit(IR_ASSERT_SELF_NONVOID);
			Emit2(IR_ASSIGN_SELF_MAP, id, l);
		}
		else
		if(type == 2)
			global.GetAdd(id) = l;
		else
			var.GetAdd(id) = l;
	}
	else
	if(Char('{')) {
		while(!Char('}') /*&& no_break && no_return && no_continue*/)
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

void HiCompiler::Run()
{
	//no_return = no_break = no_continue = true;
	loop = 0;
	//skipexp = 0;
	while(!IsEof() /*&& no_return && no_break && no_continue*/)
		DoStatement();
}

void Hi::Run() {
	HiCompiler::Run();
	
	vm.Execute(ir);
	
	return_value = vm.regs[0];
}

HiValue Hi::Number(const HiValue& a, const char *oper) {
	return vm.Number(a, oper);
}

HiValue Hi::Int(const HiValue& a, const char *oper) {
	return vm.Int(a, oper);
}







void HiCompiler::Emit(IrCode x) {
	IR& ir = this->ir.Add();
	ir.code = x;
}

void HiCompiler::Emit1(IrCode x, IrValue a) {
	IR& ir = this->ir.Add();
	ir.code = x;
	ir.arg[0] = a;
}

void HiCompiler::Emit2(IrCode x, IrValue a, IrValue b) {
	IR& ir = this->ir.Add();
	ir.code = x;
	ir.arg[0] = a;
	ir.arg[1] = b;
}

void HiCompiler::Emit3(IrCode x, IrValue a, IrValue b, IrValue c) {
	IR& ir = this->ir.Add();
	ir.code = x;
	ir.arg[0] = a;
	ir.arg[1] = b;
	ir.arg[2] = c;
}

void HiCompiler::EmitLabel(IrValue l) {
	IR& ir = this->ir.Add();
	ir.code = IR_LABEL;
	ir.arg[0] = l;
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

void HiCompiler::ReadGlobalIr() {
	for(int i = 0; i < global_hi.GetCount(); i++) {
		String key = global_hi.GetKey(i);
		HiValue& val = global_hi[i];
		
		IrValue& ir = global.GetAdd(key);
		
		
	}
}

IrValue HiCompiler::IsTrue(const IrValue& v) {
	Emit1(IR_R_ISTRUE, v);
	IrValue r;
	r.SetRegisterValue(IrValue::REG_R0);
	return r;
}




}

#endif
