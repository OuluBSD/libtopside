#include <High/High.h>
#if !USE_HIGH_BYTECODE

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
	if(HiValue::GetTotalCount() >= HiValue::GetMaxTotalCount())
		OutOfMemory();
}

HiValue Hi::Get(const SRVal& val)
{
	LTIMING("Get");
	if(skipexp)
		return (int64)1;
	HiValue v = val.lval ? *val.lval : val.rval;
	if(val.sbs.IsArray()) {
		const Vector<HiValue>& sbs = val.sbs.GetArray();
		for(int i = 0; i < sbs.GetCount(); i++) {
			const HiValue& ss = sbs[i];
			if(v.IsMap()) //!!!! (problem with a[1, 2]
				v = v.MapGet(ss);
			else
			if(v.IsArray()) {
				int count = v.GetCount();
				if(ss.IsArray() && ss.GetArray().GetCount() >= 2) {
					HiValue v1 = ss.ArrayGet(0);
					HiValue v2 = ss.ArrayGet(1);
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
}

void Hi::Assign(HiValue& val, const Vector<HiValue>& sbs, int si, const HiValue& src)
{
	LTIMING("Assign");
	const HiValue& ss = sbs[si++];
	if(val.IsVoid())
		val.SetEmptyMap();
	if(val.IsMap()) {
		if(si < sbs.GetCount()) {
			HiValue x = val.MapGet(ss);
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
				HiValue x = val.ArrayGet((int)i);
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
				HiValue v1 = ss.ArrayGet(0);
				HiValue v2 = ss.ArrayGet(1);
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
}

void Hi::Assign(const SRVal& val, const HiValue& src)
{
	if(skipexp)
		return;
	if(!val.lval)
		ThrowError("l-value required");
	if(val.sbs.IsArray() && val.sbs.GetCount())
		Assign(*val.lval, val.sbs.GetArray(), 0, src);
	else
		*val.lval = src;
}

HiValue Hi::ExecuteLambda(const String& id, HiValue lambda, SRVal self, Vector<SRVal>& arg)
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
	HiValue retval;
	Array<HiValue> argvar;
	if(l.escape) {
		#if LIBTOPSIDE
		sub.var.PickValues(argvar);
		#else
		argvar = sub.var.PickValues();
		#endif
		
		for(int i = l.arg.GetCount(); i < arg.GetCount(); i++) {
			argvar.Add(Get(arg[i]));
		}
		HiValue v = Get(self);
		HiEscape e(*this, v, argvar);
		e.id = id;
		l.escape(e);
		retval = e.ret_val;
		self = e.self;
	}
	else {
		if(l.varargs) {
			HiValue& argv = sub.var.GetAdd("argv");
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
}

void Hi::Subscript(Hi::SRVal& r, Hi::SRVal _self, String id)
{
	LTIMING("Subscript");
	for(;;) {
		TestLimit();
		if(Char('['))
			if(Char(']'))
				r.sbs.ArrayAdd(HiValue());
			else {
				HiValue v1, v2;
				if(!IsChar(',') && !IsChar(':'))
					v1 = GetExp();
				if(Char(',')) {
					if(!IsChar(']'))
						v2 = GetExp();
					HiValue x;
					x.ArrayAdd(v1);
					x.ArrayAdd(v2);
					r.sbs.ArrayAdd(x);
				}
				else
				if(Char(':')) {
					if(!IsChar(']'))
						v2 = GetExp();
					HiValue x;
					x.ArrayAdd(v1);
					x.ArrayAdd(v2);
					x.ArrayAdd(HiValue());
					r.sbs.ArrayAdd(x);
				}
				else
					r.sbs.ArrayAdd(v1);
				PassChar(']');
			}
		else
		if(Char('.')) {
			_self = r;
			r.sbs.ArrayAdd(id = ReadId());
		}
		else
		if(Char('(')) {
			LTIMING("call fn");
			Vector<SRVal> arg;
			if(!Char(')'))
				for(;;) {
					LTIMING("make args");
					Exp(arg.Add());
					if(Char(')')) break;
					PassChar(',');
				}
			if(!IsChar2('!', '=') && Char('!')) {
				Term(_self);
				HiValue g = Get(_self);
				if(!_self.lval || (!g.IsVoid() && !g.IsMap()))
					ThrowError("l-value map or l-value void expected on the right side of !");
				if(g.IsVoid()) {
					HiValue v;
					v.SetEmptyMap();
					Assign(_self, v);
				}
			}
			if(!skipexp)
				try {
					r = ExecuteLambda(id, Get(r), _self, arg);
				}
				catch(Exc e) {
					throw Error(Get(r).GetTypeName() + "." + id + "(): " + e);
				}
		}
		else
			return;
	}
}

void Hi::Subscript(Hi::SRVal& r)
{
	Subscript(r, SRVal(), String());
}

void Hi::Term(SRVal& r)
{
	r.sbs = HiValue();

	op_limit--;
	TestLimit();
	if(Char2('0', 'x') || Char2('0', 'X')) {
		r = ReadNumber64(16);
		return;
	}
	if(Char2('0', 'b') || Char2('0', 'B')) {
		r = ReadNumber64(2);
		return;
	}
	if(IsChar2('0', '.')) {
		r = ReadDouble();
		return;
	}
	if(Char('0')) {
		r = IsNumber() ? ReadNumber64(8) : 0;
		return;
	}
	if(IsNumber()) {
		// TODO: int64 !
		r = ReadDouble();
		return;
	}
	if(IsString()) {
		r = HiValue(FromUtf8(ReadString()));
		return;
	}
	if(IsChar('\'')) {
		WString s = FromUtf8(ReadString('\'', true));
		if(s.GetLength() != 1)
			ThrowError("invalid character literal");
		r = (int64)s[0];
		return;
	}
	if(Char('@')) {
		r = ReadLambda(*this);
		Subscript(r);
		return;
	}
	if(Id("void")) {
		r = HiValue();
		return;
	}
	if(Char('{')) {
		HiValue map;
		map.SetEmptyMap();
		if(!Char('}'))
			for(;;) {
				HiValue v = GetExp();
				PassChar(':');
				map.MapSet(v, GetExp());
				if(Char('}'))
					break;
				PassChar(',');
				TestLimit();
			}
		r = map;
		Subscript(r);
		return;
	}
	if(Char('[')) {
		HiValue array;
		array.SetEmptyArray();
		if(!Char(']'))
			for(;;) {
				array.ArrayAdd(GetExp());
				if(Char(']'))
					break;
				PassChar(',');
				TestLimit();
			}
		r = array;
		Subscript(r);
		return;
	}
	if(Char('(')) {
		Exp(r);
		PassChar(')');
		Subscript(r);
		return;
	}

	SRVal _self;
	bool  _global = false;
	if(Char('.')) {
		if(!self.IsMap())
			ThrowError("member-access in non-member code");
		_self.lval = &self;
	}
	else
	if(Char(':'))
		_global = true;
	if(IsId()) {
		String id = ReadId();
		HiValue method;
		int locali = var.Find(id);
		int ii;

		if(id == "self") {
			if(!self.IsMap())
				ThrowError("self in non-member code");
			_self.lval = &self;
			r = self;
		}
		else
		if(!_self.lval && !_global && locali < 0 && IsChar('(') &&
		   self.IsMap() && (method = self.MapGet(id)).IsLambda()) {
		    _self.lval = &self;
			r = method;
		}
		else
		if(!_self.lval && !_global && locali < 0 && IsChar('(') &&
		   (ii = global.Find(id)) >= 0 && global[ii].IsLambda()) {
			r = global[ii];
		}
		else
		if(_self.lval) {
			r = _self;
			r.sbs.ArrayAdd(id);
		}
		else
		if(_global)
			r.lval = &global.GetAdd(id);
		else
			r.lval = &var.GetAdd(id);

		try {
			Subscript(r, _self, id);
		}
		catch(CParser::Error e) {
			throw CParser::Error(id + ": " + e);
		}
	}
	else
		ThrowError("invalid expression");
}

String Lims(const String& s)
{
	return s.GetLength() > 80 ? s.Mid(0, 80) : s;
}

double Hi::Number(const HiValue& a, const char *oper)
{
	if(!a.IsNumber())
		ThrowError(String().Cat() << "number expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return a.GetNumber();
}

int64 Hi::Int(const HiValue& a, const char *oper)
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
}

void Hi::Unary(Hi::SRVal& r)
{
	if(Char2('+', '+')) {
		Unary(r);
		HiValue v = Get(r);
		if(v.IsInt64())
			Assign(r, Int(v, "++") + 1);
		else
			Assign(r, Number(v, "++") + 1);
	}
	else
	if(Char2('-', '-')) {
		Unary(r);
		HiValue v = Get(r);
		if(v.IsInt64())
			Assign(r, Int(v, "--") - 1);
		else
			Assign(r, Number(v, "--") - 1);
	}
	else
	if(Char('-')) {
		Unary(r);
		HiValue v = Get(r);
		if(v.IsInt64())
			r = -Int(v, "-");
		else
			r = -Number(v, "-");
	}
	else
	if(Char('+')) {
		Unary(r);
		HiValue v = Get(r);
		if(v.IsInt64())
			r = Int(v, "+");
		else
			r = Number(v, "+");
	}
	else
	if(Char('!')) {
		Unary(r);
		r = (int64)!IsTrue(Get(r));
	}
	else
	if(Char('~')) {
		Unary(r);
		r = ~Int(Get(r), "~");
	}
	else
		Term(r);

	if(Char2('+', '+')) {
		HiValue v = Get(r);
		if(v.IsInt64())
			Assign(r, Int(v, "++") + 1);
		else
			Assign(r, Number(v, "++") + 1);
		r = v;
	}
	if(Char2('-', '-')) {
		HiValue v = Get(r);
		if(v.IsInt64())
			Assign(r, Int(v, "--") - 1);
		else
			Assign(r, Number(v, "--") - 1);
		r = v;
	}
}

HiValue Hi::MulArray(HiValue array, HiValue times)
{
	HiValue r;
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
}

void Hi::Mul(Hi::SRVal& r)
{
	Unary(r);
	for(;;)
		if(!IsChar2('*', '=') && Char('*')) {
			HiValue x = Get(r);
			SRVal w;
			Unary(w);
			HiValue y = Get(w);
			if(x.IsArray() && y.IsInt())
				r = MulArray(x, y);
			else
			if(y.IsArray() && x.IsInt())
				r = MulArray(y, x);
			else
			if(x.IsInt64() && y.IsInt64())
				r = Int(x, "*") * Int(y, "*");
			else
				r = Number(x, "*") * Number(y, "*");
		}
		else
		if(!IsChar2('/', '=') && Char('/')) {
			SRVal w;
			Unary(w);
			HiValue x = Get(r);
			HiValue y = Get(w);
			double b = Number(y, "/");
			if(b == 0)
				ThrowError("divide by zero");
			r = Number(x, "/") / b;
		}
		else
		if(!IsChar2('%', '=') && Char('%')) {
			SRVal w;
			Unary(w);
			int64 b = Int(w, "%");
			if(b == 0)
				ThrowError("divide by zero");
			r = Int(r, "%") % b;
		}
		else
			return;
}

void Hi::Add(Hi::SRVal& r)
{
	Mul(r);
	for(;;)
		if(!IsChar2('+', '=') && Char('+')) {
			HiValue v = Get(r);
			SRVal w;
			Mul(w);
			HiValue b = Get(w);
			if(v.IsArray() && b.IsArray()) {
				if(!v.Replace(v.GetCount(), 0, b))
					OutOfMemory();
				r = v;
			}
			else
			if(!(v.IsArray() && b.IsVoid())) {
				if(v.IsInt64() && b.IsInt64())
					r = Int(v, "+") + Int(b, "+");
				else
					r = Number(v, "+") + Number(b, "+");
			}
		}
		else
		if(!IsChar2('-', '=') && Char('-')) {
			SRVal w;
			Mul(w);
			HiValue v = Get(r);
			HiValue b = Get(w);
			if(v.IsInt64() && b.IsInt64())
				r = Int(v, "-") - Int(b, "-");
			else
				r = Number(v, "-") - Number(b, "-");
		}
		else
			return;
}

void Hi::Shift(Hi::SRVal& r)
{
	Add(r);
	for(;;)
		if(Char2('<', '<')) {
			HiValue v = Get(r);
			SRVal w;
			Add(w);
			HiValue b = Get(w);
			if(v.IsArray() && b.IsArray()) {
				if(!v.Replace(v.GetCount(), 0, b))
					OutOfMemory();
				Assign(r, v);
			}
			else
			if(!(v.IsArray() && b.IsVoid()))
				r = Int(v, "<<") << Int(b, "<<");
		}
		else
		if(Char2('>', '>')) {
			SRVal w;
			Add(w);
			r = Int(r, ">>") >> Int(w,  ">>");
		}
		else
			return;
}

double Hi::DoCompare(const HiValue& a, const HiValue& b, const char *op)
{
	LTIMING("DoCompare");
	if(a.IsInt64() && b.IsInt64())
		return SgnCompare(a.GetInt64(), b.GetInt64());
	if(a.IsNumber() && b.IsNumber())
		return SgnCompare(a.GetNumber(), b.GetNumber());
	if(a.IsArray() && b.IsArray()) {
		const Vector<HiValue>& x = a.GetArray();
		const Vector<HiValue>& y = b.GetArray();
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
}

double Hi::DoCompare(const SRVal& a, const char *op)
{
	SRVal w;
	Shift(w);
	return DoCompare(Get(a), Get(w), op);
}

void Hi::Compare(Hi::SRVal& r)
{
	Shift(r);
	for(;;)
		if(Char2('>', '='))
			r = DoCompare(r, ">=") >= 0;
		else
		if(Char2('<', '='))
			r = DoCompare(r, "<=") <= 0;
		else
		if(Char('>'))
			r = DoCompare(r, ">") > 0;
		else
		if(Char('<'))
			r = DoCompare(r, "<") < 0;
		else
			return;
}

void Hi::Equal(Hi::SRVal& r)
{
	Compare(r);
	for(;;)
		if(Char2('=', '=')) {
			SRVal w;
			Compare(w);
			r = Get(r) == Get(w);
		}
		else
		if(Char2('!', '=')) {
			SRVal w;
			Compare(w);
			r = Get(r) != Get(w);
		}
		else
			return;
}

void Hi::BinAnd(Hi::SRVal& r)
{
	Equal(r);
	while(!IsChar2('&', '&') && Char('&')) {
		SRVal w;
		Equal(w);
		r = Int(r, "&") & Int(w, "&");
	}
}

void Hi::BinXor(Hi::SRVal& r)
{
	BinAnd(r);
	while(Char('^')) {
		SRVal w;
		BinAnd(w);
		r = Int(r, "^") ^ Int(w, "^");
	}
}

void Hi::BinOr(Hi::SRVal& r)
{
	BinXor(r);
	while(!IsChar2('|', '|') && Char('|')) {
		SRVal w;
		BinXor(w);
		r = Int(r, "|") | Int(w, "|");
	}
}

void Hi::And(Hi::SRVal& r)
{
	BinOr(r);
	if(IsChar2('&', '&')) {
		bool b = IsTrue(Get(r));
		while(Char2('&', '&')) {
			SRVal w;
			if(b) {
				BinOr(w);
				b = b && IsTrue(Get(w));
			}
			else {
				skipexp++;
				BinOr(w);
				skipexp--;
			}
		}
		r = b;
	}
}

void Hi::Or(Hi::SRVal& r)
{
	And(r);
	if(IsChar2('|', '|')) {
		bool b = IsTrue(Get(r));
		while(Char2('|', '|')) {
			SRVal w;
			if(b) {
				skipexp++;
				And(w);
				skipexp--;
			}
			else {
				And(w);
				b = b || IsTrue(Get(w));
			}
		}
		r = b;
	}
}

void Hi::Cond(Hi::SRVal& r)
{
	Or(r);
	if(Char('?')) {
		bool t = IsTrue(Get(r));
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
		HiValue v = Get(r);
		SRVal w;
		Cond(w);
		HiValue b = Get(w);
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
		HiValue v = Get(r);
		HiValue b = Get(w);
		if(v.IsInt64() && b.IsInt64())
			Assign(r, Int(v, "-=") - Int(b, "-="));
		else
			Assign(r, Number(v, "-=") - Number(b, "-="));
	}
	else
	if(Char2('*', '=')) {
		SRVal w;
		Cond(w);
		HiValue x = Get(r);
		HiValue y = Get(w);
		if(x.IsInt64() && y.IsInt64())
			Assign(r, Int(x, "*=") * Int(y, "*="));
		else
			Assign(r, Number(x, "*=") * Number(y, "*="));
	}
	else
	if(Char2('/', '=')) {
		SRVal w;
		Cond(w);
		HiValue v = Get(r);
		HiValue b = Get(w);
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

HiValue Hi::GetExp() {
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
			HiValue range = GetExp();
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
					const VectorMap<HiValue, HiValue>& map = range.GetMap();
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
			return_value = HiValue();
	}
	else
	if(Id("switch")) {
		loop++;
		PassChar('(');
		HiValue a = GetExp();
		PassChar(')');
		PassChar('{');
		while(!Char('}')) {
			if(Id("case")) {
				HiValue b = GetExp();
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
		HiValue l = ReadLambda(*this);
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
