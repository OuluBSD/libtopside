#include "High.h"
#if USE_HIGH_BYTECODE

namespace UPP {

#ifdef _MSC_VER
#pragma inline_depth(255)
#pragma optimize("t", on)
#endif

#define LTIMING(x)  // RTIMING(x)

void Hi::OutOfMemory()
{
	ThrowError("Out of memory");
}

void Hi::TestLimit()
{
	LTIMING("TestLimit");
	if(op_limit < 0)
		ThrowError("out of operations limit - considered frozen");
	if(IrValue::GetTotalCount() >= IrValue::GetMaxTotalCount())
		OutOfMemory();
}
/*
IrValue Hi::Get(const SRVal& val)
{
	LTIMING("Get");
	if(skipexp)
		return (int64)1;
	IrValue v = val.lval ? *val.lval : val.rval;
	if(val.sbs.IsArray()) {
		const Vector<IrValue>& sbs = val.sbs.GetArray();
		for(int i = 0; i < sbs.GetCount(); i++) {
			const IrValue& ss = sbs[i];
			if(v.IsMap()) //!!!! (problem with a[1, 2]
				v = v.MapGet(ss);
			else
			if(v.IsArray()) {
				int count = v.GetCount();
				if(ss.IsArray() && ss.GetArray().GetCount() >= 2) {
					IrValue v1 = ss.ArrayGet(0);
					IrValue v2 = ss.ArrayGet(1);
					int i = v1.GetInt();
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
					if(i >= 0 && n >= 0 && i + n <= count)
						v = v.ArrayGetMid(i, n);
					else
						ThrowError("slice out of range");
				}
				else {
					int64 i = Int(ss, "index");
					if(i < 0)
						i += count;
					if(i >= 0 && i < count)
						v = v.ArrayGet((int)i);
					else
						ThrowError("index out of range");
				}
			}
			else
				ThrowError("invalid indirection");
			TestLimit();
		}
	}
	return v;
}*/
/*
void Hi::Assign(IrValue& val, const Vector<IrValue>& sbs, int si, const IrValue& src)
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

/*void Hi::Assign(const SRVal& val, const IrValue& src)
{
	if(skipexp)
		return;
	if(!val.lval)
		ThrowError("l-value required");
	if(val.sbs.IsArray() && val.sbs.GetCount())
		Assign(*val.lval, val.sbs.GetArray(), 0, src);
	else
		*val.lval = src;
}*/

/*IrValue Hi::ExecuteLambda(const String& id, IrValue lambda, SRVal self, Vector<SRVal>& arg)
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

void Hi::Subscript(String id)
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
			Emit(IR_PUSH_TEMPSELF_R);
			id = ReadId()
			Emit(IR_POP_SELF);
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
				Emit(IR_PUSH_R_TEMPSELF);
				Term();
				IrValue g = Get();
				Emit1(IR_OP_INEQ_TEMPSELF, g);
			}
			if(!skipexp) {
				IrValue v = Get();
				Emit2(IR_EXECUTE_LAMBDA, id, v)
			}
			Emit(IR_ARGVEC_POP);
		}
		else
			return;
	}
}

void Hi::Subscript()
{
	Subscript(String());
}

void Hi::Term()
{
	Emit(IR_R_SBS_RESET);

	op_limit--;
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
		Emit(IR_SCOPE_PUSH_EMPTYMAP);
		if(!Char('}')) {
			for(;;) {
				IrValue v = GetExp();
				PassChar(':');
				Emit2(IR_SCOPE_MAPSET, v, GetExp());
				if(Char('}'))
					break;
				PassChar(',');
				TestLimit();
			}
		}
		Emit(IR_ASSIGN_R_SCOPE_POP);
		Subscript();
		return;
	}
	if(Char('[')) {
		Emit(IR_SCOPE_PUSH_EMPTYARRAY);
		if(!Char(']'))
			for(;;) {
				Emit2(IR_SCOPE_ARRAYADD, GetExp());
				if(Char(']'))
					break;
				PassChar(',');
				TestLimit();
			}
		Emit(IR_ASSIGN_R_SCOPE_POP);
		Subscript();
		return;
	}
	if(Char('(')) {
		Exp();
		PassChar(')');
		Subscript();
		return;
	}
	
	Emit(IR_PUSH_TEMPSELF);
	bool  _global = false;
	if(Char('.')) {
		if(!self.IsMap())
			ThrowError("member-access in non-member code");
		Emit(IR_ASSIGN_TEMPSELF_LVAL_SELF);
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
			Emit(IR_ASSIGN_TEMPSELF_LVAL_SELF);
			Emit(IR_ASSIGN_R_SELF);
		}
		else {
			Emit(IR_COND_IF_SELFLAMBDA);
			{
			    Emit(IR_ASSIGN_TEMPSELF_LVAL_SELF);
				Emit(IR_ASSIGN_R_TMPMETHOD);
			}
			Emit(IR_COND_ELSE); {
				Emit(IR_COND_IF_GLOBALLAMBDA) {
					Emit(IR_ASSIGN_R_TMPGLOBALIDX);
				}
				Emit(IR_COND_ELSE); {
					Emit(IR_COND_IF_SELF_LVAL) {
						Emit(IR_ASSIGN_R_TMPSELF);
						Emit1(IR_R_SBS_ARRAYADD_1, id);
					}
					Emit(IR_COND_ELSE); {
						Emit(IR_COND_IF_GLOBAL); {
							Emit1(IR_ASSIGN_R_LVAL, &global.GetAdd(id));
						}
						Emit(IR_COND_ELSE); {
							Emit1(IR_ASSIGN_R_LVAL, &var.GetAdd(id));
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
	
	Emit(IR_POP_TEMPSELF);
}

String Lims(const String& s)
{
	return s.GetLength() > 80 ? s.Mid(0, 80) : s;
}

/*double Hi::Number(const IrValue& a, const char *oper)
{
	if(!a.IsNumber())
		ThrowError(String().Cat() << "number expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return a.GetNumber();
}

int64 Hi::Int(const IrValue& a, const char *oper)
{
	if(!a.IsNumber())
		ThrowError(String().Cat() << "integer expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return a.GetInt64();
}

double Hi::Number(const Hi::SRVal& a, const char *oper)
{
	return Number(Get(a), oper);
}

int64 Hi::Int(const Hi::SRVal& a, const char *oper)
{
	return Int(Get(a), oper);
}*/

void Hi::Unary()
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
		Emit1(IR_POSTINC, Get());
	}
	if(Char2('-', '-')) {
		Emit1(IR_POSTDEC, Get());
	}
}

/*IrValue Hi::MulArray(IrValue array, IrValue times)
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

void Hi::Mul()
{
	Unary();
	for(;;) {
		if(!IsChar2('*', '=') && Char('*')) {
			IrValue x = Get();
			Emit(IR_PUSH_NEW_R);
			Unary();
			IrValue y = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_MULARRAY, x, y);
		}
		else
		if(!IsChar2('/', '=') && Char('/')) {
			Emit(IR_PUSH_NEW_R);
			Unary();
			Emit(IR_POP_TEMP_R);
			IrValue x = Get();
			Emit(IR_PUSH_TEMP_R);
			IrValue y = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_DIVASS, x, b);
		}
		else
		if(!IsChar2('%', '=') && Char('%')) {
			Emit(IR_PUSH_NEW_R);
			Unary();
			Emit(IR_POP_R);
			Emit1(IR_OP_MODASS_R, b);
		}
		else
			return;
	}
}

void Hi::Add()
{
	Mul();
	for(;;) {
		if(!IsChar2('+', '=') && Char('+')) {
			IrValue v = Get();
			Emit(IR_PUSH_NEW_R);
			Mul();
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit1(IR_OP_ADDASS, b);
		}
		else
		if(!IsChar2('-', '=') && Char('-')) {
			Emit(IR_PUSH_NEW_R);
			Mul();
			Emit(IR_POP_TEMP_R);
			IrValue v = Get();
			Emit(IR_PUSH_TEMP_R);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_SUBASS, v, b);
		}
		else
			return;
	}
}

void Hi::Shift()
{
	Add();
	for(;;) {
		if(Char2('<', '<')) {
			IrValue v = Get();
			Emit(IR_PUSH_NEW_R);
			Add();
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_LSHF, v, b);
		}
		else
		if(Char2('>', '>')) {
			Emit(IR_PUSH_NEW_R);
			Add();
			Emit(IR_POP_R_A1);
			Emit(IR_OP_RSHF);
		}
		else
			return;
	}
}

/*double Hi::DoCompare(const IrValue& a, const IrValue& b, const char *op)
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

void Hi::DoCompare(const char *op)
{
	Emit(IR_PUSH_NEW_R);
	Shift();
	Emit(IR_POP_TEMP_R);
	HiValue a = Get();
	Emit(IR_PUSH_TEMP_R);
	HiValue b = Get();
	Emit(IR_POP_R);
	Emit3(IR_OP_CMP, a, b, op);
}

void Hi::Compare(Hi::SRVal& r)
{
	Shift(r);
	for(;;) {
		if (Char2('>', '=')) {
			DoCompare(r, ">=");
			Emit1(IR_OP_CMP_RESULT, 0);
		}
		else if (Char2('<', '=')) {
			DoCompare(r, "<=") <= 0;
			Emit1(IR_OP_CMP_RESULT, 1);
		}
		else if (Char('>')) {
			DoCompare(r, ">") > 0;
			Emit1(IR_OP_CMP_RESULT, 2);
		}
		else if (Char('<')) {
			DoCompare(r, "<") < 0;
			Emit1(IR_OP_CMP_RESULT, 3);
		}
		else
			return;
	}
}

void Hi::Equal(Hi::SRVal& r)
{
	Compare(r);
	for(;;) {
		if(Char2('=', '=')) {
			Emit(IR_PUSH_NEW_R);
			Compare();
			Emit(IR_POP_TEMP_R);
			IrValue a = Get();
			Emit(IR_PUSH_TEMP_R);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_EQ, a, b);
		}
		else
		if(Char2('!', '=')) {
			Emit(IR_PUSH_NEW_R);
			Compare();
			Emit(IR_POP_TEMP_R);
			IrValue a = Get();
			Emit(IR_PUSH_TEMP_R);
			IrValue b = Get();
			Emit(IR_POP_R);
			Emit2(IR_OP_INEQ, a, b);
		}
		else
			return;
	}
}

void Hi::BinAnd()
{
	Equal();
	while(!IsChar2('&', '&') && Char('&')) {
		Emit(IR_PUSH_NEW_R);
		Equal();
		Emit(IR_POP_R_A1);
		Emit(IR_PUSH_BWAND);
	}
}

void Hi::BinXor()
{
	BinAnd();
	while(Char('^')) {
		Emit(IR_PUSH_NEW_R);
		BinAnd();
		Emit(IR_POP_R_A1);
		Emit(IR_PUSH_BWXOR);
	}
}

void Hi::BinOr()
{
	BinXor();
	while(!IsChar2('|', '|') && Char('|')) {
		Emit(IR_PUSH_NEW_R);
		BinXor();
		Emit(IR_POP_R_A1);
		Emit(IR_PUSH_BWOR);
	}
}

void Hi::And()
{
	BinOr();
	if(IsChar2('&', '&')) {
		IrValue b = IsTrue(Get());
		IrValue exit = CreateLocalLabel();
		while(Char2('&', '&')) {
			Emit2(IR_JUMP_IF_FALSE, b, exit);
			Emit(IR_PUSH_NEW_R);
			BinOr();
			IrValue v = IsTrue(Get());
			Emit(IR_POP_R);
			Emit2(IR_OP_ANDASS, b, v);
		}
		EmitLabel(exit);
		
		Emit1(IR_ASSIGN_R, b);
	}
}

void Hi::Or()
{
	And();
	if(IsChar2('|', '|')) {
		IrValue b = IsTrue(Get());
		IrValue exit = CreateLocalLabel();
		while(Char2('|', '|')) {
			Emit2(IR_JUMP_IF_TRUE, b, exit);
			Emit(IR_PUSH_NEW_R);
			And();
			IrValue v = IsTrue(Get());
			Emit(IR_POP_R);
			Emit2(IR_OP_ORASS, b, v);
		}
		EmitLabel(exit);
		
		Emit1(IR_ASSIGN_R, b);
	}
}

void Hi::Cond()
{
	Or();
	if(Char('?')) {
		IrValue t = IsTrue(Get(r));
		SRVal dummy;
		if(t) {
			Cond(r);
			PassChar(':');
			skipexp++;
			Cond(dummy);
			skipexp--;
		}
		else {
			skipexp++;
			Cond(dummy);
			skipexp--;
			PassChar(':');
			Cond(r);
		}
	}
}

void Hi::Assign(Hi::SRVal& r)
{
	Cond(r);
	if(Char('=')) {
		SRVal w;
		Assign(w);
		Assign(r, Get(w));
	}
	else
	if(Char2('+', '=')) {
		IrValue v = Get(r);
		SRVal w;
		Cond(w);
		IrValue b = Get(w);
		if(v.IsArray() && b.IsArray()) {
			if(!v.Replace(v.GetCount(), 0, b))
				OutOfMemory();
			Assign(r, v);
		}
		else
		if(!(v.IsArray() && b.IsVoid())) {
			if(v.IsInt64() && b.IsInt64())
				Assign(r, Int(v, "+=") + Int(b, "+="));
			else
				Assign(r, Number(v, "+=") + Number(b, "+="));
		}
	}
	else
	if(Char2('-', '=')) {
		SRVal w;
		Cond(w);
		IrValue v = Get(r);
		IrValue b = Get(w);
		if(v.IsInt64() && b.IsInt64())
			Assign(r, Int(v, "-=") - Int(b, "-="));
		else
			Assign(r, Number(v, "-=") - Number(b, "-="));
	}
	else
	if(Char2('*', '=')) {
		SRVal w;
		Cond(w);
		IrValue x = Get(r);
		IrValue y = Get(w);
		if(x.IsInt64() && y.IsInt64())
			Assign(r, Int(x, "*=") * Int(y, "*="));
		else
			Assign(r, Number(x, "*=") * Number(y, "*="));
	}
	else
	if(Char2('/', '=')) {
		SRVal w;
		Cond(w);
		IrValue v = Get(r);
		IrValue b = Get(w);
		double q = Number(v, "/=");
		if(q == 0)
			ThrowError("divide by zero");
		Assign(r, Number(b, "/=") / q);
	}
	else
	if(Char2('%', '=')) {
		SRVal w;
		Cond(w);
		int64 a = Int(r, "%=");
		int64 b = Int(w, "%=");
		if(b == 0)
			ThrowError("divide by zero");
		Assign(r, a % b);
	}
}

int Hi::stack_level = 50;

void Hi::Exp(Hi::SRVal& r)
{
	LTIMING("Exp");
	Spaces();
	stack_level--;
	if(stack_level <= 0)
		ThrowError("stack overflow");
	Assign(r);
	stack_level++;
}

IrValue Hi::GetExp() {
	SRVal r;
	Exp(r);
	return Get(r);
}

void Hi::SkipTerm()
{
	if(IsEof())
		ThrowError("unexpected end of file");
	CParser::SkipTerm();
	Spaces();
}

void Hi::SkipExp()
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

void Hi::SkipStatement()
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
}

bool  Hi::PCond()
{
	PassChar('(');
	bool c = IsTrue(GetExp());
	PassChar(')');
	return c;
}

void Hi::FinishSwitch()
{
	while(no_break && no_return && no_continue) {
		if(Id("case")) {
			SRVal r;
			Exp(r);
			PassChar(':');
		}
		else
		if(Id("default"))
			PassChar(':');
		else
			if(Char('}'))
				return;
		DoStatement();
	}
	while(!Char('}'))
		SkipStatement();
}

void  Hi::DoStatement()
{
	op_limit--;
	TestLimit();
	if(Id("if"))
		if(PCond()) {
			DoStatement();
			if(Id("else"))
				SkipStatement();
		}
		else {
			SkipStatement();
			if(Id("else"))
				DoStatement();
		}
	else
	if(Id("do")) {
		loop++;
		Pos pos = GetPos();
		do {
			SetPos(pos);
			DoStatement();
			PassId("while");
			no_continue = true;
		}
		while(PCond() && no_break && no_return);
		PassChar(';');
		no_break = true;
		loop--;
	}
	else
	if(Id("while")) {
		loop++;
		Pos pos = GetPos();
		for(;;) {
			SetPos(pos);
			if(!PCond() || !no_break || !no_return || !no_continue) {
				SkipStatement();
				break;
			}
			DoStatement();
			no_continue = true;
		}
		no_break = true;
		loop--;
	}
	else
	if(Id("for")) {
		loop++;
		PassChar('(');
		SRVal var;
		if(!IsChar(';'))
			Exp(var);
		if(Id("in") || Char(':')) {
			IrValue range = GetExp();
			PassChar(')');
			Pos stmt = GetPos();
			int i = 0;
			for(;;) {
				SetPos(stmt);
				if(range.IsArray()) {
					if(i >= range.GetCount())
						break;
					Assign(var, (int64)i);
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
					Assign(var, map.GetKey(i));
				}
				if(!no_break || !no_return || !no_continue) {
					SkipStatement();
					break;
				}
				DoStatement();
				no_continue = true;
				i++;
			}
			SkipStatement();
		}
		else {
			PassChar(';');
			Pos cond;
			if(!IsChar(';')) {
				cond = GetPos();
				SkipExp();
			}
			PassChar(';');
			Pos after;
			if(!IsChar(')')) {
				after = GetPos();
				SkipExp();
			}
			PassChar(')');
			Pos stmt = GetPos();
			for(;;) {
				bool c = true;
				if(cond.ptr) {
					SetPos(cond);
					c = IsTrue(GetExp());
				}
				SetPos(stmt);
				if(!c || !no_break || !no_return || !no_continue) {
					SkipStatement();
					break;
				}
				DoStatement();
				no_continue = true;
				if(after.ptr) {
					SetPos(after);
					SRVal r;
					Exp(r);
				}
			}
		}
		no_break = true;
		loop--;
	}
	else
	if(Id("break")) {
		if(!loop)
			ThrowError("misplaced 'break'");
		no_break = false;
		PassChar(';');
	}
	else
	if(Id("continue")) {
		if(!loop)
			ThrowError("misplaced 'continue'");
		no_continue = false;
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
		no_return = false;
		if(!Char(';')) {
			return_value = GetExp();
			PassChar(';');
		}
		else
			return_value = IrValue();
	}
	else
	if(Id("switch")) {
		loop++;
		PassChar('(');
		IrValue a = GetExp();
		PassChar(')');
		PassChar('{');
		while(!Char('}')) {
			if(Id("case")) {
				IrValue b = GetExp();
				PassChar(':');
				if(a == b) {
					FinishSwitch();
					break;
				}
			}
			else
			if(Id("default")) {
				PassChar(':');
				FinishSwitch();
				break;
			}
			else
				SkipStatement();
		}
		loop--;
		no_break = true;
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
			if(self.IsVoid())
				ThrowError("no instance");
			self.MapSet(id, l);
		}
		else
		if(type == 2)
			global.GetAdd(id) = l;
		else
			var.GetAdd(id) = l;
	}
	else
	if(Char('{')) {
		while(!Char('}') && no_break && no_return && no_continue)
			DoStatement();
	}
	else
	if(!Char(';')) {
		SRVal v;
		Exp(v);
		PassChar(';');
	}
}

void  Hi::Run()
{
	no_return = no_break = no_continue = true;
	loop = 0;
	skipexp = 0;
	while(!IsEof() && no_return && no_break && no_continue)
		DoStatement();
}


}

#endif
