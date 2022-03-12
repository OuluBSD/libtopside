#ifndef _High_Interpreter_h_
#define _High_Interpreter_h_

struct Hi : public CParser {
	struct SRVal : Moveable<SRVal> {
		HiValue *lval;
		HiValue  rval;
		HiValue  sbs;

		SRVal()                    { lval = NULL; }
		SRVal(const HiValue& v)   { lval = NULL; rval = v; }
		SRVal(double n)            { lval = NULL; rval = n; }
		SRVal(int64 n)             { lval = NULL; rval = n; }
		SRVal(uint64 n)            { lval = NULL; rval = (int64)n; }
		SRVal(bool n)              { lval = NULL; rval = (int64)n; }
	};

	ArrayMap<String, HiValue>& global;
	HiValue                    self;
	ArrayMap<String, HiValue>  var;

	int      skipexp;
	int      loop;
	bool     no_break, no_return, no_continue;
	int&     op_limit;
	int      r_stack_level;
	HiValue return_value;

	static int stack_level;

	void       OutOfMemory();

	void       TestLimit();
	double     DoCompare(const HiValue& a, const HiValue& b, const char *op);
	double     DoCompare(const SRVal& a, const char *op);
	String     ReadName();
	HiValue   ExecuteLambda(const String& id, HiValue lambda, SRVal self, Vector<SRVal>& arg);

	void       Assign(HiValue& val, const Vector<HiValue>& sbs, int si, const HiValue& src);

	HiValue   Get(const SRVal& val);
	void       Assign(const SRVal& val, const HiValue& src);

	HiValue   GetExp();

	double Number(const HiValue& a, const char *oper);
	int64  Int(const HiValue& a, const char *oper);
	double Number(const SRVal& a, const char *oper);
	int64  Int(const SRVal& a, const char *oper);

	HiValue   MulArray(HiValue array, HiValue times);

	void  Subscript(SRVal& r, SRVal _self, String id);
	void  Subscript(SRVal& r);
	void  Term(SRVal& r);
	void  Unary(SRVal& r);
	void  Mul(SRVal& r);
	void  Add(SRVal& r);
	void  Shift(SRVal& r);
	void  Compare(SRVal& r);
	void  Equal(SRVal& r);
	void  BinAnd(SRVal& r);
	void  BinXor(SRVal& r);
	void  BinOr(SRVal& r);
	void  And(SRVal& r);
	void  Or(SRVal& r);
	void  Cond(SRVal& r);
	void  Assign(SRVal& r);
	void  Exp(SRVal& r);

	void  SkipTerm();
	void  SkipStatement();
	void  SkipExp();
	bool  PCond();
	void  FinishSwitch();
	void  DoStatement();

	void  Run();

	Hi(ArrayMap<String, HiValue>& global, const char *s, int& oplimit,
	    const String& fn, int line = 1)
	: CParser(s, fn, line), global(global), op_limit(oplimit)
	{ r_stack_level = stack_level;  skipexp = false; }
	~Hi() { stack_level = r_stack_level; }
};

#endif
