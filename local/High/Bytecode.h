#ifndef _High_Emitter_h_
#define _High_Emitter_h_


typedef enum {
	#define IR(x) IR_##x,
	#include "IrList.inl"
	#undef IR
} IrCode;



struct IrValue {
	static int total;
	static int GetTotalCount();
	static int GetMaxTotalCount();
	
	typedef enum {
		V_VOID,
		V_REG,
		V_CSTRING,
		V_STRING,
		V_WSTRING,
		V_INT32,
		V_INT64,
		V_UINT64,
		V_DOUBLE,
		V_HIVAL,
		V_MAP,
		V_ARRAY,
		V_LABEL_INT,
		V_LABEL_STR,
	} Type;
	
	typedef enum {
		REG_VOID,
		REG_R0,
		REG_R1,
		REG_R2,
		REG_R3,
		REG_R4,
	} RegType;
	
	Type type;
	const char* str;
	String s;
	WString ws;
	int i32;
	union {
		int64 i64;
		uint64 u64;
		double d;
	};
	HiValue hv;
	ArrayMap<String, IrValue> map;
	Array<IrValue> array;
	RegType reg;
	
	
	IrValue();
	//IrValue(IrValue&& v);
	IrValue(const IrValue& v);
	IrValue(const char* s);
	IrValue(String s);
	IrValue(WString s);
	IrValue(int i);
	IrValue(int64 i);
	IrValue(uint64 i);
	IrValue(double d);
	IrValue(const HiValue& v);
	
	
	IrValue& operator=(const IrValue& v);
	
	
	void Clear();
	void SetEmptyMap();
	void SetEmptyArray();
	void MapSet(const IrValue& key, const IrValue& value);
	void ArrayAdd(const IrValue& value);
	IrValue& SetRegisterValue(RegType r);
	IrValue& SetLabel(int i);
	IrValue& SetLabel(String s);
	bool IsVoid() const;
	bool IsMap() const;
	bool IsArray() const;
	bool IsAnyString() const;
	String GetString() const;
	int GetCount() const;
	String GetTypeString() const;
	String GetTextValue() const;
	String ToString() const;
	HiValue AsHiValue() const;
	
	const VectorMap<IrValue, IrValue>& GetMap() const;
	
};

struct IR : Moveable<IR> {
	IrCode code;
	IrValue arg[3];
	String label;
	
	
	String GetCodeString() const;
	String ToString() const;
	
};

struct HiCompiler : public CParser {
	
protected:
	struct LoopStack : Moveable<LoopStack> {
		IrValue repeat, exit;
		
	};
	
	Vector<IR> ir;
	Vector<LoopStack> loop_stack;
	int lbl_counter = 0;
	
	
	void Emit(IrCode x);
	void Emit1(IrCode x, IrValue a);
	void Emit2(IrCode x, IrValue a, IrValue b);
	void Emit3(IrCode x, IrValue a, IrValue b, IrValue c);
	void EmitLabel(IrValue l);
	
	IrValue CreateLabel();
	void PushLoop(IrValue exit);
	void PushLoop(IrValue exit, IrValue repeat);
	void CreateSwitchDefault();
	void PopLoop();
	
	void ReadGlobalIr();
	
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

	ArrayMap<String, HiValue>& global_hi;
	ArrayMap<String, IrValue>  global;
	IrValue                    self;
	ArrayMap<String, IrValue>  var;

	//int      skipexp;
	int      r_stack_level;
	int      loop;
	
	static int stack_level;
	
	void       OutOfMemory();
	
	void       TestLimit();
	void       DoCompare(const IrValue& a, const IrValue& b, const char *op);
	void       DoCompare(const char *op);
	String     ReadName();
	IrValue    ExecuteLambda(const String& id, IrValue lambda);
	IrValue	   IsTrue(const IrValue& v);
	void       Assign(IrValue& val, const Vector<IrValue>& sbs, int si, const IrValue& src);

	IrValue    Get();
	void       Assign(const IrValue& src);

	IrValue   GetExp();

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
	//void  SkipStatement();
	void  SkipExp();
	IrValue  PCond();
	void  FinishSwitch();
	void  DoStatement();

	void  Run();

	HiCompiler(ArrayMap<String, HiValue>& global, const char *s, int& oplimit,
	    const String& fn, int line = 1)
	: CParser(s, fn, line), global_hi(global)
	{ r_stack_level = stack_level; ReadGlobalIr();}
	~HiCompiler() { stack_level = r_stack_level; }
};



struct IrVM {
	struct SRVal : Moveable<SRVal> {
		HiValue *lval;
		HiValue  rval;
		HiValue  sbs;

		SRVal()                    { lval = NULL; }
		SRVal(const HiValue& v)    { lval = NULL; rval = v; }
		SRVal(double n)            { lval = NULL; rval = n; }
		SRVal(int64 n)             { lval = NULL; rval = n; }
		SRVal(uint64 n)            { lval = NULL; rval = (int64)n; }
		SRVal(bool n)              { lval = NULL; rval = (int64)n; }
		
		void operator=(const HiValue& v)    { lval = NULL; rval = v; }
		void operator=(double n)            { lval = NULL; rval = n; }
		void operator=(int64 n)             { lval = NULL; rval = n; }
		void operator=(uint64 n)            { lval = NULL; rval = (int64)n; }
		void operator=(bool n)              { lval = NULL; rval = (int64)n; }
	};
	static const int REG_COUNT = 5;
	
	Vector<SRVal> r_stack;
	HiValue regs[REG_COUNT];
	
	int pc = 0;
	int max_pc = 0;
	TS::RunningFlagSingle flag;
	int&     op_limit;
	
	
	IrVM(int& op_limit) : op_limit(op_limit) {}
	void Execute(const IR& ir);
	void Execute(const Vector<IR>& ir);
	void Get();
	bool IsRunning() const {return flag.IsRunning();}
	void SetNotRunning() {flag.SetNotRunning();}
	void OnError(String msg);
	void ThrowError(String msg);
	HiValue  Number(const HiValue& a, const char *oper);
	HiValue  Int(const HiValue& a, const char *oper);
	void     TestLimit();
	void     AddAssign1(SRVal& r, const HiValue& a, const HiValue& b);
	void     OutOfMemory();
	
};


struct Hi : public HiCompiler {
	HiValue  self;
	HiValue  return_value;
	bool     no_break, no_return, no_continue;
	IrVM     vm;
	
	
	Hi(ArrayMap<String, HiValue>& global, const char *s, int& oplimit,
	    const String& fn, int line = 1) : HiCompiler(global, s, oplimit, fn, line), vm(oplimit) {}
	
	void     Run();
	HiValue  Number(const HiValue& a, const char *oper);
	HiValue  Int(const HiValue& a, const char *oper);
	
	
};

#endif
