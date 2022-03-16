#include "High.h"


namespace UPP {

#define LTIMING(x) // RTIMING(x)

void LambdaArgs(CParser& p, HiLambda& l)
{
	p.PassChar('(');
	if(!p.Char(')'))
		for(;;) {
			if(p.Char3('.', '.', '.')) {
				l.varargs = true;
				p.PassChar(')');
				break;
			}
			l.inout.Add(p.Char('&'));
			l.arg.Add(p.ReadId());
			if(p.Char('=')) {
				const char *s = p.GetPtr();
				int level = 0;
				for(;;) {
					if((p.IsChar(')') || p.IsChar(',')) && level == 0)
						break;
					if(p.Char(')'))
						level--;
					else
					if(p.Char('('))
						level++;
					else
						p.SkipTerm();
					if(p.IsEof())
						p.ThrowError("unexpected end of file while reading default value for argument "
						             + l.arg.Top());
				}
				l.def.Add(String(s, p.GetPtr()));
			}
			else
				if(l.def.GetCount())
					p.ThrowError("missing default value for argument " + l.arg.Top());
			if(p.Char(')'))
				break;
			p.PassChar(',');
		}
	l.inout.Shrink();
	l.arg.Shrink();
}

HiValue ReadLambda(CParser& p)
{
	HiValue lambda;
	HiLambda& l = lambda.CreateLambda();
	LambdaArgs(p, l);
	const char *t = p.GetPtr();
	l.filename = p.GetFileName();
	l.line = p.GetLine();
	if(!p.Char('{'))
		p.ThrowError("missing '{'");
	SkipBlock(p);
	l.code = String(t, p.GetPtr());
	return lambda;
}

HiValue ReadLambda(const char *s)
{
	CParser p(s);
	return ReadLambda(p);
}

String HiEscape::InCall()
{
	return id.IsEmpty() ? String() : " in call to '" + id + "'";
}

String HiEscape::DumpType(int i)
{
	if(i < arg.GetCount())
		return String().Cat() << " (" << arg[i].GetTypeName() << " present)";
	else
		return " (not enough arguments)";
}

void  HiEscape::CheckNumber(int i)
{
	if(i < arg.GetCount() && arg[i].IsNumber())
		return;
	ThrowError(String().Cat() << "number expected as parameter " << i + 1 << InCall()
	           << DumpType(i));
}

double HiEscape::Number(int i)
{
	if(i >= arg.GetCount())
		ThrowError("too little parameters" + InCall());
	return esc.Number(arg[i], "parameter" + InCall());
}

int HiEscape::Int(int i)
{
	if(i >= arg.GetCount())
		ThrowError("too little parameters" + InCall());
	return (int)esc.Int(arg[i], "parameter" + InCall());
}

void  HiEscape::CheckArray(int i)
{
	if(i < arg.GetCount() && arg[i].IsArray())
		return;
	ThrowError(String().Cat() << "array expected as parameter " << i + 1 << InCall()
	           << DumpType(i));
}

void  HiEscape::CheckMap(int i)
{
	if(i < arg.GetCount() && arg[i].IsMap())
		return;
	ThrowError(String().Cat() << "map expected as parameter " << i + 1 << InCall());
}

void HighCall(ArrayMap<String, HiValue>& globals, const char *function, Callback1<HiEscape&> escape)
{
	CParser p(function);
	HiValue& v = globals.GetAdd(p.ReadId());
	HiLambda& l = v.CreateLambda();
	l.escape = escape;
	LambdaArgs(p, l);
}

void HighCall(ArrayMap<String, HiValue>& globals, const char *function, void (*escape)(HiEscape& e))
{
	HighCall(globals, function, callback(escape));
}

void  HiValue::HighCall(const char *method, Callback1<HiEscape&> escape)
{
	CParser p(method);
	String id = p.ReadId();
	HiValue v;
	HiLambda& l = v.CreateLambda();
	l.escape = escape;
	LambdaArgs(p, l);
	MapSet(id, v);
}

void  HiValue::HighCall(const char *method, HiHandle *h, Callback1<HiEscape&> escape)
{
	CParser p(method);
	String id = p.ReadId();
	HiValue v;
	HiLambda& l = v.CreateLambda();
	l.escape = escape;
	l.handle = h;
	h->Retain();
	LambdaArgs(p, l);
	if(IsVoid())
		SetEmptyMap();
	MapSet(id, v);
}

void Scan(ArrayMap<String, HiValue>& global, const char *file, const char *filename)
{
	LTIMING("Scan");
	CParser p(file, filename);
	while(!p.IsEof()) {
		HiValue& v = global.GetAdd(p.ReadId());
		v = ReadLambda(p);
	}
}

HiValue Execute(ArrayMap<String, HiValue>& global, HiValue *self,
                 const HiValue& lambda, Vector<HiValue>& arg, int op_limit)
{
	const HiLambda& l = lambda.GetLambda();
	if(arg.GetCount() != l.arg.GetCount()) {
		String argnames;
		for(int i = 0; i < l.arg.GetCount(); i++)
			argnames << (i ? ", " : "") << l.arg[i];
		throw CParser::Error(Format("invalid number of arguments (%d passed, expected: %s)", arg.GetCount(), argnames));
	}
	HiValue ret;
	{
		Hi sub(global, op_limit, lambda.GetLambdaRW());
		HiValue& sub_self = sub.Self();
		if(self)
			sub_self = *self;
		for(int i = 0; i < l.arg.GetCount(); i++)
			sub.VarGetAdd(l.arg[i]) = arg[i];
		for (;;) {
			sub.Run();
			if (!sub.IsSleepExit())
				break;
			while (!sub.CheckSleepFinished())
				Sleep(1);
		}
		if(self)
			*self = sub_self;
		ret = sub.return_value;
	}
	return ret;
}

HiValue Execute(ArrayMap<String, HiValue>& global, HiValue *self,
                 const char *name, Vector<HiValue>& arg, int op_limit)
{
	if(!self->IsMap())
		return HiValue();
	const VectorMap<HiValue, HiValue>& m = self->GetMap();
	int ii = m.Find(String(name));
	if(ii >= 0 && m[ii].IsLambda())
		return Execute(global, self, m[ii], arg, op_limit);
	return HiValue();
}

HiValue Execute(ArrayMap<String, HiValue>& global, const char *name, int op_limit)
{
	int ii = global.Find(String(name));
	Vector<HiValue> arg;
	if(ii >= 0 && global[ii].IsLambda())
		return Execute(global, NULL, global[ii], arg, op_limit);
	return HiValue();
}

HiValue Evaluatex(const char *expression, ArrayMap<String, HiValue>& global, int oplimit)
{
	Hi sub(global, expression, oplimit, "", 0);
	auto& var = sub.Var();
	for(int i = 0; i < global.GetCount(); i++)
		var.Add(global.GetKey(i), global[i]);
	HiValue v;
	v = sub.GetExp();
	for(int i = 0; i < var.GetCount(); i++)
		global.GetAdd(var.GetKey(i)) = var[i];
	return v;
}

#if !USE_HIGH_BYTECODE
HiValue Evaluate(const char *expression, ArrayMap<String, HiValue>& global, int oplimit)
{
	try {
		return Evaluatex(expression, global, oplimit);
	}
	catch(CParser::Error&) {}
	return HiValue();
}

String   Expand(const String& doc, ArrayMap<String, HiValue>& global,
                int oplimit, String (*format)(const Object& v))
{
	String out;
	const char *term = doc;
	bool cond = true;
	while(*term) {
		if(term[0] == '<' && term[1] == ':') {
			term += 2;
			try {
				Hi sub(global, term, oplimit, "", 0);
				for(int i = 0; i < global.GetCount(); i++)
					sub.var.Add(global.GetKey(i), global[i]);
				HiValue v;
				if(*term == '{') {
					sub.Run();
					v = sub.return_value;
				}
				else
				if(sub.Char('!')) {
					HiValue& v = global.GetAdd(sub.ReadId());
					v = ReadLambda(sub);
				}
				else
				if(sub.Char('?'))
					cond = IsTrue(sub.GetExp());
				else
				if(sub.Char('/'))
					cond = !cond;
				else
				if(sub.Char('.'))
					cond = true;
				else
					v = sub.GetExp();
				if(cond)
					out << format(StdValueFromHi(v));
				#if LIBTOPSIDE
				sub.DoSpaces();
				#else
				sub.Spaces();
				#endif
				term = sub.GetPtr();
				if(term[0] != ':' || term[1] != '>')
					throw CParser::Error("missing :>" + String(term));
				term += 2;
			}
			catch(CParser::Error& e) {
				out << "(#ERROR: " << e << "#)";
			}
		}
		else {
			if(cond)
				out.Cat(*term);
			term++;
		}
	}
	return out;
}
#endif

}
