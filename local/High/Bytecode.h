#ifndef _High_Emitter_h_
#define _High_Emitter_h_

namespace UPP {

typedef enum {
	#define IR(x) IR_##x,
	#include "IrList.inl"
	#undef IR
} IrCode;



struct VmState {
	static const int REG_COUNT = 5;
	
	
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
		
		void operator=(const HiValue& v)    { lval = NULL; rval = v; sbs = HiValue();}
		void operator=(double n)            { lval = NULL; rval = n; sbs = HiValue();}
		void operator=(int64 n)             { lval = NULL; rval = n; sbs = HiValue();}
		void operator=(uint64 n)            { lval = NULL; rval = (int64)n; sbs = HiValue();}
		void operator=(bool n)              { lval = NULL; rval = (int64)n; sbs = HiValue();}
		void operator=(const SRVal& v)		{ lval = v.lval; rval = v.rval; sbs = v.sbs; }
	};
	
	Array<SRVal> r_stack;
	Array<SRVal> temp_stack;
	Vector<SRVal> rself_stack;
	Array<HiValue> var_stack;
	Array<HiValue> self_stack;
	Array<Array<SRVal>> argvec_stack;
	HiValue regs[REG_COUNT];
	int pc = 0;
	int max_pc = 0;
	
};

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
		V_VARSTACK,
	} Type;
	
	/*typedef enum {
		REG_VOID,
		REG_R0,
		REG_R1,
		REG_R2,
		REG_R3,
		REG_R4,
	} RegType;*/
	static const int REG_COUNT = VmState::REG_COUNT;
	
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
	IrValue& SetRegisterValue(int r);
	IrValue& SetLabel(int i);
	IrValue& SetLabel(String s);
	IrValue& SetVarStackValue(int offset);
	bool IsVoid() const;
	bool IsMap() const;
	bool IsArray() const;
	bool IsInt() const;
	bool IsAnyString() const;
	bool IsVarStackValue(int offset) const;
	bool IsRegister(int reg) const;
	bool IsRegister() const;
	bool IsLabel() const;
	String GetString() const;
	int GetCount() const;
	String GetTypeString() const;
	String GetTextValue() const;
	String ToString() const;
	HiValue AsHiValue(VmState& s) const;
	
	const VectorMap<IrValue, IrValue>& GetMap() const;
	
};

struct IR : Moveable<IR> {
	IrCode code;
	IrValue arg[3];
	String label;
	const char* file;
	int line;
	CParser::Pos codepos;
	
	
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
	
	
	void Emit_(IrCode x, const char* file, int line);
	void Emit1_(IrCode x, IrValue a, const char* file, int line);
	void Emit2_(IrCode x, IrValue a, IrValue b, const char* file, int line);
	void Emit3_(IrCode x, IrValue a, IrValue b, IrValue c, const char* file, int line);
	void EmitLabel_(IrValue l, const char* file, int line);
	//IrValue	EmitMovReg(const IrValue& v, int reg);
	IrValue		EmitPushVar_(const IrValue& v, const char* file, int line);
	IrValue		EmitPopVar_(const IrValue& v, int reg, const char* file, int line);
	IrValue		EmitPopVar_(const IrValue& v, const IrValue& avoid0, const char* file, int line);
	IrValue		EmitSelfLambdaCheck(String id, IrValue& tmp, const char* file, int line);
	IrValue		EmitGlobalLambdaCheck(String id, IrValue& tmp, const char* file, int line);
	IrValue		EmitSelfLvalCheck(const char* file, int line);
	
	IrValue CreateLabel();
	void PushLoop(IrValue exit);
	void PushLoop(IrValue exit, IrValue repeat);
	void CreateSwitchDefault();
	void PopLoop();
	
	void ReadGlobalIr();
	
	void OnError(String msg);
	
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

	

	//int		skipexp;
	int			r_stack_level;
	int			loop;
	bool		fail = false;
	
	static int stack_level;
	
	void		OutOfMemory();
	
	void		TestLimit();
	void		DoCompare(const IrValue& a, const IrValue& b, const char *op);
	void		DoCompare(const char *op);
	String		ReadName();
	IrValue		IsTrue(const IrValue& v);
	
	IrValue		Get();
	void		Assign(const IrValue& src);

	IrValue		GetExp();
	

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

	HiCompiler(/*ArrayMap<String, HiValue>& global,*/ const char *s, int& oplimit,
	    const String& fn, int line = 1)
	: CParser(s, fn, line)/*, global_hi(global)*/
	{ r_stack_level = stack_level; ReadGlobalIr();}
	~HiCompiler() { stack_level = r_stack_level; }
};



struct IrVM {
	static const int REG_COUNT = 5;
	using SRVal = VmState::SRVal;
	
	VmState*				s;
	VmState					state;
	TS::RunningFlagSingle	flag;
	int&					op_limit;
	Vector<int>				lbl_pos;
	VectorMap<String, int>	lbl_names;
	bool					fail = 0;
	
	ArrayMap<String, HiValue>&	global;
	//HiValue						self;
	ArrayMap<String, HiValue>	var;
	
	
	IrVM(ArrayMap<String, HiValue>& g, int& op_limit) : global(g), op_limit(op_limit) {s = &state;}
	void	Execute(const IR& ir);
	void	Execute(const Vector<IR>& ir);
	bool	RefreshLabels(const Vector<IR>& ir);
	void	Get();
	void    Get(const SRVal& r, HiValue& v);
	void    Get0(SRVal& r, HiValue& v);
	bool	IsRunning() const {return flag.IsRunning();}
	void	SetNotRunning() {flag.SetNotRunning();}
	void	OnError(String msg);
	void	ThrowError(String msg);
	void	TestLimit();
	void	AddAssign1(SRVal& r, const HiValue& a, const HiValue& b);
	void	AddAssign2(SRVal& r, const HiValue& a, const HiValue& b);
	void	OutOfMemory();
	void	WriteRegister(const IrValue& reg, const HiValue& v);
	HiValue	ReadVar(const IrValue& v);
	void	Jump(const IrValue& v);
	void	Assign(const SRVal& val, const HiValue& src);
	void	Assign(HiValue& val, const Vector<HiValue>& sbs, int si, const HiValue& src);
	double	DoCompare(const HiValue& a, const HiValue& b, const char *op);
	HiValue	MulArray(HiValue array, HiValue times);
	HiValue	ExecuteLambda(const String& id, HiValue& lambda, SRVal& self, Array<SRVal>& arg);
	
	double	Number(const HiValue& a, const char *oper);
	int64	Int(const HiValue& a, const char *oper);
	double	Number(const SRVal& a, const char *oper);
	int64	Int(const SRVal& a, const char *oper);
	String	Lims(const String& s) const;
	
	HiValue&	Self();
	
};


struct Hi : public HiCompiler {
	//HiValue  self;
	HiValue  return_value;
	IrVM     vm;
	
	
	Hi(ArrayMap<String, HiValue>& global, const char *s, int& oplimit,
	    const String& fn, int line = 1) : HiCompiler(s, oplimit, fn, line), vm(global, oplimit) {}
	
	void	Run();
	double	Number(const HiValue& a, const char *oper);
	int64	Int(const HiValue& a, const char *oper);
	
	HiValue&	VarGetAdd(const HiValue& key) {return vm.var.GetAdd(key);}
	HiValue		GetExp();
	
	ArrayMap<String, HiValue>& Var() {return vm.var;}
	HiValue& Self() {return vm.Self();}
	
};


}

#endif
