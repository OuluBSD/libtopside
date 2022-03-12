#ifndef _High_Emitter_h_
#define _High_Emitter_h_


typedef enum {
	IR_R_SBS_RESET,
	IR_R_SBS_ARRAYADD_EMPTY,
	IR_R_SBS_ARRAYADD_1,
	IR_R_SBS_ARRAYADD_1_ARRAY1,
	IR_R_SBS_ARRAYADD_1_ARRAY2,
	IR_R_SBS_ARRAYADD_1_ARRAY3,
	IR_ASSIGN_R,
	IR_ASSIGN_R_VOID,
	IR_SCOPE_PUSH,
	
} IrCode;

struct IrValue {
	
};

struct IR {
	
	
	
};

struct IrVM {
	
	
	
	void Execute(const IR& ir);
	
};


struct Hi : public CParser {
	Array<IR> ir;
	
	
	void Emit(IrCode x);
	void Emit1(IrCode x, IrValue a);
	void Emit2(IrCode x, IrValue a, IrValue b);
	void Emit3(IrCode x, IrValue a, IrValue b, IrValue c);
	
public:
	
	/*struct SRVal : Moveable<SRVal> {
		IrValue *lval;
		IrValue  rval;
		IrValue  sbs;

		SRVal()                    { lval = NULL; }
		SRVal(const IrValue& v)    { lval = NULL; rval = v; }
		SRVal(double n)            { lval = NULL; rval = n; }
		SRVal(int64 n)             { lval = NULL; rval = n; }
		SRVal(uint64 n)            { lval = NULL; rval = (int64)n; }
		SRVal(bool n)              { lval = NULL; rval = (int64)n; }
	};*/

	ArrayMap<String, IrValue>& global;
	IrValue                    self;
	ArrayMap<String, IrValue>  var;

	int      skipexp;
	int      loop;
	bool     no_break, no_return, no_continue;
	int&     op_limit;
	int      r_stack_level;
	IrValue return_value;
	
	static int stack_level;
	
	void       OutOfMemory();
	
	void       TestLimit();
	IrValue    DoCompare(const IrValue& a, const IrValue& b, const char *op);
	IrValue    DoCompare(const char *op);
	String     ReadName();
	IrValue    ExecuteLambda(const String& id, IrValue lambda);
	IrValue		IsTrue(IrValue v);
	void       Assign(IrValue& val, const Vector<IrValue>& sbs, int si, const IrValue& src);

	IrValue    Get();
	void       Assign(const IrValue& src);

	IrValue   GetExp();

	IrValue  Number(const IrValue& a, const char *oper);
	IrValue  Int(const IrValue& a, const char *oper);
	//double Number(const SRVal& a, const char *oper);
	//int64  Int(const SRVal& a, const char *oper);

	IrValue   MulArray(IrValue array, IrValue times);

	void  Subscript(String id);
	void  Subscript();
	void  Term();
	void  Unary();
	void  Mul();
	void  Add();
	void  Shift();
	void  Compare();
	void  Equal();
	void  BinAnd();
	void  BinXor();
	void  BinOr();
	void  And();
	void  Or();
	void  Cond();
	void  Assign();
	void  Exp();

	void  SkipTerm();
	void  SkipStatement();
	void  SkipExp();
	bool  PCond();
	void  FinishSwitch();
	void  DoStatement();

	void  Run();

	Hi(ArrayMap<String, IrValue>& global, const char *s, int& oplimit,
	    const String& fn, int line = 1)
	: CParser(s, fn, line), global(global), op_limit(oplimit)
	{ r_stack_level = stack_level;  skipexp = false; }
	~Hi() { stack_level = r_stack_level; }
};

#endif
