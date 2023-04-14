#include "High.h"
#if USE_HIGH_BYTECODE

namespace UPP {

void Hi::SleepSpinning(int ms) {
	sleep = true;
	spinning_sleep = true;
	sleep_s = ms * 0.001;
	ts.Reset();
}

void Hi::SleepReleasing(int ms) {
	sleep = true;
	spinning_sleep = false;
	sleep_s = ms * 0.001;
	ts.Reset();
}

void Hi::SleepInfiniteReleasing() {
	sleep = true;
	spinning_sleep = false;
	sleep_s = 0;
}

void Hi::StopSleep() {
	sleep = false;
	spinning_sleep = false;
	ts.Reset();
}

bool Hi::IsRunning() const {
	return !calls.IsEmpty();
}

bool Hi::IsSleepExit() const {
	return !fail && sleep && !spinning_sleep;
}

bool Hi::IsSleepFinished() const {
	return sleep && (sleep_s > 0 && ts.Seconds() >= sleep_s);
}

bool Hi::CheckSleepFinished() {
	bool b = sleep && (sleep_s <= 0 || ts.Seconds() < sleep_s);
	if (!b) {
		sleep = false;
		spinning_sleep = false;
	}
	return !b;
}

void Hi::SetFailed() {
	fail = true;
	for (Call& c : calls)
		if (c.vm)
			c.vm->fail = true;
}

bool Hi::IsFailed() const {
	return fail;
}

void Hi::OnError(String s) {
	LOG("error: " << s);
	fail = true;
}

void Hi::Stop() {
	calls.Clear();
	fail = false;
}

void Hi::Run() {
	return_value = HiValue();
	
	while(!calls.IsEmpty() && !fail) {
		Call& c = calls.Top();
		
		if (c.vm.IsEmpty()) {
			int src = -1;
			
			if (c.type == FN_NAME) {
				int i = global.Find(c.fn);
				if (i < 0) {
					OnError("could not find global function '" + c.fn + "'");
					return;
				}
				
				c.lambda = global[i];
				if (!c.lambda.IsLambda()) {
					OnError("trying to run non-lambda");
					return;
				}
			}
			
			if (c.l ? !c.l->compiled && !c.l->escape : true) {
				String code;
				String filename = c.l ? c.l->filename : (String)"expression";
				int line = c.l ? c.l->line : 0;
				
				if (c.type == EVALX)	code = c.scope_l->def[c.parent_arg_i];
				else if (c.l)			code = c.l->code;
				else					code = c.code;
				ASSERT((c.l != 0 || c.scope_l) == c.code.IsEmpty());
				
				HiCompiler comp(code, filename, line);
				
				if (c.get_exp)
					c.out_var = comp.GetExp();
				else
					comp.Run();
				
				if (comp.fail) {
					LOG("Hi::Run: error: compiling failed");
					return;
				}
				
				if (c.l)
					comp.WriteLambda(*c.l);
				else
					comp.SwapIR(c.tmp_ir);
			}
			
			c.vm = new IrVM(this, global, c.var, oplimit, c.l ? c.l->ir : c.tmp_ir);
			IrVM& vm = *c.vm;
			
			if (calls.GetCount() == 1)
				vm.Self() = self;
			else if (c.get_exp) {
				if (c.type == EVALX)
					vm.SetReturnArg(*c.parent, c.scope_l->arg[c.parent_arg_i]);
			}
			else {
				// TODO: fix, too hacky! use some new class or something
				int evalx_count = vm.InitLambdaExecution(*c.l, *c.parent);
				
				if (evalx_count > 0) {
					Array<IrVM::SRVal>& arg = *vm.parent->call_arg;
					for(int i = 0; i < evalx_count; i++) {
						Call& e = calls.Add();
						e.type = EVALX;
						e.parent = &vm;
						e.scope_l = c.l;
						e.get_exp = true;
						e.parent_arg_i = arg.GetCount() + i - (c.l->arg.GetCount() - c.l->def.GetCount());
					}
					// Jump to newly created evaluatex requests
					continue;
				}
			}
		}
		
		IrVM& vm = *c.vm;
		
		
		bool cont = vm.Execute();
		
		
		if (cont) {
			if (vm.is_calling) {
				Call& e = calls.Add();
				e.type = SUBCALL;
				e.parent = &vm;
				e.l = vm.call_fn;
			}
			else if (sleep && !spinning_sleep) {
				return;
			}
			else {
				OnError("unexpected non-continue signal in IrVM");
			}
		}
		else {
			if (calls.GetCount() == 1) {
				if (c.get_exp)
					return_value = vm.ReadVar(c.out_var);
				else
					return_value = vm.s->regs[0];
				self = vm.Self();
			}
			calls.Remove(calls.GetCount()-1);
		}
	}
	
}

double Hi::Number(const HiValue& a, const char *oper) {
	return calls.Top().vm->Number(a, oper);
}

int64 Hi::Int(const HiValue& a, const char *oper) {
	return calls.Top().vm->Int(a, oper);
}

HiValue& Hi::VarGetAdd(const HiValue& key) {
	return calls.Top().var.GetAdd(key);
}

HiValue Hi::GetExp() {
	Call& c = calls.Top();
	c.get_exp = true;
	Run();
	return return_value;
}

ArrayMap<String, HiValue>& Hi::Var() {
	return calls.Top().var;
}

HiValue& Hi::Self() {
	return self;
}













IrValue::IrValue() {
	type = V_VOID;
}

IrValue::IrValue(const IrValue& v) {
	*this = v;
}

IrValue::IrValue(const char* s) {
	type = V_CSTRING;
	str = s;
}

IrValue::IrValue(String s) {
	type = V_STRING;
	this->s = s;
	ASSERT(s.GetCount());
}

IrValue::IrValue(WString s) {
	type = V_WSTRING;
	ws = s;
}

IrValue::IrValue(int i) {
	type = V_INT32;
	i32 = i;
}

IrValue::IrValue(int64 i) {
	type = V_INT64;
	i64 = i;
}

IrValue::IrValue(uint64 i) {
	type = V_UINT64;
	u64 = i;
}

IrValue::IrValue(double d) {
	type = V_DOUBLE;
	this->d = d;
}

IrValue::IrValue(const HiValue& v) {
	type = V_HIVAL;
	hv = v;
}

IrValue& IrValue::operator=(const IrValue& v) {
	type = v.type;
	switch (type) {
		case V_VOID:	break;
		case V_CSTRING:	str = v.str; break;
		case V_LABEL_STR:
		case V_STRING:	s = v.s; break;
		case V_WSTRING:	ws = v.ws; break;
		case V_LABEL_INT:
		case V_VARSTACK:
		case V_REG:
		case V_INT32:	i32 = v.i32; break;
		case V_INT64:	i64 = v.i64; break;
		case V_UINT64:	u64 = v.u64; break;
		case V_DOUBLE:	d = v.d; break;
		case V_HIVAL:	hv = v.hv; break;
		case V_MAP:		map <<= v.map; break;
		case V_ARRAY:	array <<= v.array; break;
	};
	return *this;
}

void IrValue::SetEmptyMap() {
	Clear();
	type = V_MAP;
}

void IrValue::SetEmptyArray() {
	Clear();
	type = V_ARRAY;
}

void IrValue::Clear() {
	type = V_VOID;
	str = 0;
	s.Clear();
	ws.Clear();
	i32 = 0;
	i64 = 0;
	hv = HiValue();
	map.Clear();
	array.Clear();
}

void IrValue::MapSet(const IrValue& key, const IrValue& value) {
	ASSERT(type == V_MAP);
	ASSERT(key.IsAnyString());
	String ks = key.GetString();
	ASSERT(ks.GetCount());
	map.GetAdd(ks) = value;
}

void IrValue::ArrayAdd(const IrValue& value) {
	TODO
}

IrValue& IrValue::SetRegisterValue(int r) {
	Clear();
	type = V_REG;
	i32 = r;
	return *this;
}

IrValue& IrValue::SetLabel(int i) {
	type = V_LABEL_INT;
	i32 = i;
	return *this;
}

IrValue& IrValue::SetLabel(String s) {
	type = V_LABEL_STR;
	this->s = s;
	return *this;
}

IrValue& IrValue::SetVarStackValue(int offset) {
	type = V_VARSTACK;
	i32 = offset;
	return *this;
}

bool IrValue::IsVoid() const {
	return type == V_VOID;
}

bool IrValue::IsMap() const {
	return type == V_MAP;
}

bool IrValue::IsInt() const {
	return type == V_INT32;
}

bool IrValue::IsArray() const {
	return type == V_ARRAY;
}

bool IrValue::IsAnyString() const {
	return type == V_STRING || type == V_CSTRING || type == V_WSTRING;
}

bool IrValue::IsVarStackValue(int offset) const {
	return type == V_VARSTACK;
}

bool IrValue::IsRegister() const {
	return type == V_REG;
}

bool IrValue::IsRegister(int reg) const {
	return type == V_REG && i32 == reg;
}

bool IrValue::IsLabel() const {
	return type == V_LABEL_INT || type == V_LABEL_STR;
}

String IrValue::GetString() const {
	if (type == V_STRING)  return s;
	if (type == V_CSTRING) return str;
	if (type == V_WSTRING) return ws.ToString();
	ASSERT(0);
	return String();
}

int IrValue::GetCount() const {
	TODO
}

const VectorMap<IrValue, IrValue>& IrValue::GetMap() const {
	TODO
}

String IrValue::GetTypeString() const {
	switch (type) {
		case V_VOID:	return "void";
		case V_REG:		return "register";
		case V_CSTRING:	return "cstring";
		case V_STRING:	return "string";
		case V_WSTRING:	return "wstring";
		case V_INT32:	return "int32";
		case V_INT64:	return "int64";
		case V_UINT64:	return "uint64";
		case V_DOUBLE:	return "double";
		case V_HIVAL:	return "HiValue";
		case V_MAP:		return "map";
		case V_ARRAY:	return "array";
		case V_LABEL_INT:	return "label";
		case V_LABEL_STR:	return "label-str";
		case V_VARSTACK:	return "var-stack";
		default: return "<invalid type>";
	}
	return String();
}

String IrValue::GetTextValue() const {
	String s;
	switch (type) {
		case V_VOID:	return "<void>";
		case V_REG:		return "R" + IntStr(i32);
		case V_CSTRING:	return str;
		case V_STRING:	return this->s;
		case V_WSTRING:	return ws.ToString();
		case V_INT32:	return IntStr(i32);
		case V_INT64:	return IntStr64(i64);
		case V_UINT64:	return IntStr64(i64);
		case V_DOUBLE:	return DblStr(d);
		case V_HIVAL:	return hv.ToString();
		case V_MAP:
			for(int i = 0; i < map.GetCount(); i++)
				s << "[" << i << "] " << map.GetKey(i) << " = " << map[i].ToString() << "\n";
			break;
		case V_ARRAY:
			for(int i = 0; i < array.GetCount(); i++)
				s << "[" << i << "] " << array[i].ToString() << "\n";
			break;
		case V_LABEL_INT:	return IntStr(i32);
		case V_LABEL_STR:	return this->s;
		case V_VARSTACK:	return IntStr(i32);
		default: return "<invalid type>";
	}
	return s;
}

String IrValue::ToString() const {
	return GetTypeString() + ": " + GetTextValue();
}

HiValue IrValue::AsHiValue(VmState& s) const {
	// HIGH_VOID, HIGH_DOUBLE, HIGH_ARRAY, HIGH_MAP, HIGH_LAMBDA, HIGH_INT64
	HiValue h;
	switch (type) {
		case V_VOID:	return HiValue();
		case V_REG:		return i32 >= 0 && i32 < REG_COUNT ? s.regs[i32] : HiValue();
		case V_CSTRING:	return str;
		case V_STRING:	return this->s;
		case V_WSTRING:	return ws;
		case V_INT32:	return i32;
		case V_INT64:	return i64;
		case V_UINT64:	return i64;
		case V_DOUBLE:	return d;
		case V_HIVAL:	return hv;
		case V_MAP:
			h.SetEmptyMap();
			for(int i = 0; i < map.GetCount(); i++)
				h.MapSet(map.GetKey(i), map[i].AsHiValue(s));
			return h;
		case V_ARRAY:
			h.SetEmptyArray();
			for(int i = 0; i < array.GetCount(); i++)
				h.ArrayAdd(array[i].AsHiValue(s));
			return h;
		case V_LABEL_INT:	return i32;
		case V_LABEL_STR:	return this->s;
		case V_VARSTACK:	return i32;
		default: return HiValue();
	}
}

String IR::GetCodeString() const {
	switch (code) {
		#define IR(x) case IR_##x: return #x;
		#include "IrList.inl"
		#undef IR
		default: return "<invalid>";
	}
}

String IR::ToString() const {
	String s = GetCodeString();
	for(int i = 0; i < 3; i++) {
		if (arg[i].IsVoid())
			break;
		String v = arg[i].ToString();
		ASSERT(v.GetCount());
		s << ", " << v;
	}
	if (file)
		s += " (" + GetFileName(String(file)) + ":" + IntStr(line) + ")";
	if (codepos.ptr) {
		int col = (int)(codepos.ptr - codepos.lineptr);
		int line = codepos.line;
		s += " (" + IntStr(line) + ":" + IntStr(col) + ")";
	}
	return s;
}












void IrVM::OnError(String msg) {
	LOG("IrVM: error: " << msg);
	LOG("	   at " << s->pc);
	SetNotRunning();
	fail = true;
	hi.fail = true;
}

bool IrVM::RefreshLabels(const Vector<IR>& ir) {
	lbl_pos.Clear();
	lbl_names.Clear();
	int pos = 0;
	for (const IR& ins : ir) {
		if (ins.code == IR_LABEL) {
			const IrValue& v = ins.arg[0];
			if (v.type == IrValue::V_LABEL_INT) {
				int i = v.i32;
				ASSERT(i >= 0 && i < 10000000);
				if (i >= lbl_pos.GetCount())
					lbl_pos.SetCount(i+1, -1);
				lbl_pos[i] = pos;
			}
			else if (v.type == IrValue::V_LABEL_STR) {
				ASSERT(!v.s.IsEmpty());
				if (lbl_names.Find(v.s) >= 0) {
					LOG("IrVM: error: duplicate label '" + v.s + "'");
					return false;
				}
				lbl_names.Add(v.str, pos);
			}
		}
		pos++;
	}
	return true;
}

void IrVM::ExecuteEscape() {
	ASSERT(fn);
	HiLambda& l			= *fn;
	Array<SRVal>& arg	= *parent->call_arg;
	String& id			=  parent->call_id;
	SRVal& self			= *parent->call_self;
	SRVal& r			=  parent->s->r_stack.Top();
	
	#if LIBTOPSIDE
	var.PickValues(argvar);
	#else
	argvar = var.PickValues();
	#endif
	
	for(int i = l.arg.GetCount(); i < arg.GetCount(); i++) {
		Get(arg[i], argvar.Add());
	}
	
	HiValue v;
	Get(self, v);
	HiEscape e(*this, v, argvar);
	e.id = id;
	l.escape(e);
	
	r = e.ret_val;
	self = e.self;
}

void IrVM::SetReturnArg(IrVM& vm, String arg) {
	ASSERT(!parent);
	ASSERT(arg.GetCount());
	parent = &vm;
	return_argname = arg;
}

void IrVM::InitSubcall() {
	ASSERT(fn);
	HiLambda& l			= *fn;
	Array<SRVal>& arg	= *parent->call_arg;
	
	if(l.varargs) {
		HiValue& argv = var.GetAdd("argv");
		argv.SetEmptyArray();
		for(int i = l.arg.GetCount(); i < arg.GetCount(); i++)
			Get(arg[i], argv.ArrayAdd(HiValue()));
	}
}

void IrVM::FinishSubcall() {
	HiLambda& l			= *fn;
	SRVal& self			= *parent->call_self;
	HiValue& sub_self	=  Self();
	Array<SRVal>& arg	= *parent->call_arg;
	SRVal& r			=  parent->s->r_stack.Top();
	
	#if LIBTOPSIDE
	var.PickValues(argvar);
	#else
	argvar = var.PickValues();
	#endif
	
	for(int i = 0; i < l.inout.GetCount(); i++)
		if(l.inout[i] && i < arg.GetCount() && arg[i].lval)
			Assign(arg[i], argvar[i]);
	if(self.lval)
		Assign(self, sub_self);
	
	r = s->regs[0];
}

void IrVM::FinishArgument() {
	ASSERT(return_argname.GetCount());
	HiValue& v = parent->var.Get(return_argname);
	v = s->regs[0];
}

void IrVM::Yield() {
	run_ins_again = true;
	hi.SleepReleasing(1);
}

bool IrVM::Execute() {
	#define VERBOSE_IRVM 0
	
	#if VERBOSE_IRVM
	DUMPC(ir);
	#endif
	
	int& max_pc		= s->max_pc;
	int& pc			= s->pc;
	auto& r_stack	= s->r_stack;
	
	if (is_sleeping) {
		is_sleeping = false;
	}
	else if (!is_calling) {
		fail = 0;
		argvar.Clear();
		
		if (fn) {
			ASSERT(parent);
			if (fn->escape) {
				ExecuteEscape();
				return false;
			}
			is_subcall = true;
			InitSubcall();
		}
		
		if (!RefreshLabels(ir)) {
			fail = 1;
			return false;
		}
		
		max_pc = ir.GetCount();
		if (!max_pc) {
			fail = 1;
			return false;
		}
		pc = 0;
		flag.Start();
	}
	else {
		pc++;
		is_calling = false;
	}
	
	const IR* vec = ir.Begin();
	
	while (IsRunning()) {
		
		if (hi.sleep) {
			if (hi.spinning_sleep) {
				if (hi.ts.Seconds() >= hi.sleep_s) {
					hi.sleep = false;
					hi.spinning_sleep = false;
				}
				else {
					Sleep(1);
					continue;
				}
			}
			else {
				is_sleeping = true;
				return true; // do continue
			}
		}
		
		const IR& ins = vec[pc];
		
		#if VERBOSE_IRVM
		LOG(pc);
		#endif
		
		ExecuteInstruction(ins);
		
		if (is_calling)
			return true;
		
		if (run_ins_again) {
			run_ins_again = false;
		}
		else {
			pc++;
			if (pc >= max_pc)
				SetNotRunning();
		}
	}
	
	if (is_subcall)
		FinishSubcall();
	
	if (!return_argname.IsEmpty())
		FinishArgument();
	
	#if VERBOSE_IRVM
	DUMP(s->regs[0]);
	#endif
	
	flag.SetStopped();
	return false;
}

void IrVM::ExecuteInstruction(const IR& ir) {
	#undef CHECK
	#define CHECK(x) if (!(x)) {OnError("Instruction " + ir.GetCodeString() + " failed: " #x " == false"); return;}
	HiValue a, b, c;
	double d;
	int64 i;
	SRVal* val;
	String str;
	bool boolean;
	int& max_pc			= s->max_pc;
	int& pc				= s->pc;
	auto& r_stack		= s->r_stack;
	auto& self_stack	= s->self_stack;
	auto& rself_stack	= s->rself_stack;
	auto& var_stack		= s->var_stack;
	auto& argvec_stack	= s->argvec_stack;
	auto& temp_stack	= s->temp_stack;
	auto& regs			= s->regs;
	
	switch (ir.code) {
		
    case IR_LABEL:
        return;
	
	case IR_PUSH_R_EMPTY:
		r_stack.Add();
		return;
	
	case IR_POP_R_ARGVEC_ADD:
		CHECK(!r_stack.IsEmpty());
		CHECK(!argvec_stack.IsEmpty());
		argvec_stack.Top().Add(r_stack.Detach(r_stack.GetCount()-1));
		return;
	
	case IR_PUSH_R_TEMP:
		CHECK(!temp_stack.IsEmpty());
		r_stack.Add(temp_stack.Detach(temp_stack.GetCount()-1));
		return;
	
	case IR_PUSH_R_RSELF:
		CHECK(!rself_stack.IsEmpty());
		r_stack.Add(rself_stack.Top());
		return;
	
	case IR_POP_R:
		CHECK(!r_stack.IsEmpty());
		r_stack.SetCount(r_stack.GetCount()-1);
		return;
	
	case IR_POP_R_TEMP:
		CHECK(!r_stack.IsEmpty());
		temp_stack.Add(r_stack.Detach(r_stack.GetCount()-1));
		return;
	
	case IR_POP_R_R1:
		CHECK(!r_stack.IsEmpty());
		Get(r_stack.Top(), regs[1]);
		r_stack.SetCount(r_stack.GetCount()-1);
		return;
	
	case IR_POP_R_RSELF:
		CHECK(!rself_stack.IsEmpty());
		CHECK(!r_stack.IsEmpty());
		rself_stack.Top() = r_stack.Top();
		r_stack.SetCount(r_stack.GetCount()-1);
		return;
	
	case IR_POP_SELF_R1:
		CHECK(!self_stack.IsEmpty());
		Get(self_stack.Top(), regs[1]);
		self_stack.Remove(self_stack.GetCount()-1);
		return;
	
	case IR_R_GET:
		CHECK(!r_stack.IsEmpty());
		Get();
		return;
	
	case IR_R_MAPSET:
		CHECK(!r_stack.IsEmpty())
		CHECK(r_stack.Top().rval.IsMap());
		r_stack.Top().rval.MapSet(ReadVar(ir.arg[0]), ReadVar(ir.arg[1]));
		return;
	
	case IR_R_ARRAYADD:
		CHECK(!r_stack.IsEmpty())
		CHECK(r_stack.Top().rval.IsArray());
		r_stack.Top().rval.ArrayAdd(ReadVar(ir.arg[0]));
		return;
	
	case IR_R_SBS_RESET:
		CHECK(!r_stack.IsEmpty());
		r_stack.Top().sbs = HiValue();
		return;
	
	case IR_R_SBS_ARRAYADD_EMPTY:
		CHECK(!r_stack.IsEmpty())
		val = &r_stack.Top();
		CHECK(val->sbs.IsArray() || val->sbs.IsVoid());
		val->sbs.ArrayAdd(HiValue());
		return;
	
	case IR_R_SBS_ARRAYADD_1:
		val = &r_stack.Top();
		CHECK(val->sbs.IsArray() || val->sbs.IsVoid());
		val->sbs.ArrayAdd(ReadVar(ir.arg[0]));
		return;
	
	case IR_R_SBS_ARRAYADD_1_ARRAY1:
		val = &r_stack.Top();
		CHECK(val->sbs.IsArray() || val->sbs.IsVoid());
		a.SetEmptyArray();
		a.ArrayAdd(ReadVar(ir.arg[0]));
		val->sbs.ArrayAdd(a);
		return;
	
	case IR_R_SBS_ARRAYADD_1_ARRAY2:
		val = &r_stack.Top();
		CHECK(val->sbs.IsArray() || val->sbs.IsVoid());
		a.SetEmptyArray();
		b = ReadVar(ir.arg[0]);
		c = ReadVar(ir.arg[1]);
		a.ArrayAdd(b);
		a.ArrayAdd(c);
		val->sbs.ArrayAdd(a);
		return;
	
	case IR_R_SBS_ARRAYADD_1_ARRAY3:
		val = &r_stack.Top();
		CHECK(val->sbs.IsArray() || val->sbs.IsVoid());
		a.SetEmptyArray();
		a.ArrayAdd(ReadVar(ir.arg[0]));
		a.ArrayAdd(ReadVar(ir.arg[1]));
		a.ArrayAdd(ReadVar(ir.arg[2]));
		val->sbs.ArrayAdd(a);
		return;
	
	
	case IR_ARGVEC_PUSH_NEW:
		argvec_stack.Add();
		return;
	
	case IR_ARGVEC_POP:
		CHECK(!argvec_stack.IsEmpty());
		argvec_stack.SetCount(argvec_stack.GetCount()-1);
		return;
	
	case IR_JUMP:
		Jump(ir.arg[0]);
		return;
	
	case IR_JUMP_IF_FALSE:
		a = ReadVar(ir.arg[0]);
		if (!IsTrue(a))
			Jump(ir.arg[1]);
		return;
	
	case IR_JUMP_IF_TRUE:
		if (IsTrue(ReadVar(ir.arg[0])))
			Jump(ir.arg[1]);
		return;
	
	case IR_JUMP_IF_EQ:
		if (ReadVar(ir.arg[0]) == ReadVar(ir.arg[1]))
			Jump(ir.arg[2]);
		return;
	
	case IR_JUMP_IF_INEQ:
		if (ReadVar(ir.arg[0]) != ReadVar(ir.arg[1]))
			Jump(ir.arg[2]);
		return;
	
	case IR_OP_EQ:
		CHECK(!r_stack.IsEmpty())
		r_stack.Top() = (ReadVar(ir.arg[0]) == ReadVar(ir.arg[1]));
		return;
	
	case IR_OP_INEQ:
		CHECK(!r_stack.IsEmpty())
		r_stack.Top() = (ReadVar(ir.arg[0]) != ReadVar(ir.arg[1]));
		return;
	
	case IR_OP_INEQ_RSELF:
		CHECK(!rself_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		if(!rself_stack.Top().lval || (!a.IsVoid() && !a.IsMap()))
			OnError("l-value map or l-value void expected on the right side of !");
		else if(a.IsVoid()) {
			b.SetEmptyMap();
			Assign(rself_stack.Top(), b);
		}
		return;
	
	case IR_OP_NEGATIVE:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		if(a.IsInt64())		r_stack.Top() = -Int(a, "-");
		else				r_stack.Top() = -Number(a, "-");
		return;
	
	case IR_OP_POSITIVE:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		if(a.IsInt64())		r_stack.Top() = -Int(a, "-");
		else				r_stack.Top() = -Number(a, "-");
		return;
	
	case IR_OP_NOT:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		val = &r_stack.Top();
		*val = (int64)!IsTrue(a);
		return;
	
	case IR_OP_NEGATE:
		CHECK(!r_stack.IsEmpty())
		r_stack.Top() = ~Int(ReadVar(ir.arg[0]), "~");
		return;
	
	case IR_OP_PREINC:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		if(a.IsInt64())		Assign(r_stack.Top(), Int(a, "++") + 1);
		else				Assign(r_stack.Top(), Number(a, "++") + 1);
		return;
	
	case IR_OP_PREDEC:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		if(a.IsInt64())		Assign(r_stack.Top(), Int(a, "--") - 1);
		else				Assign(r_stack.Top(), Number(a, "--") - 1);
		return;
	
	case IR_OP_POSTINC:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		if(a.IsInt64())		Assign(r_stack.Top(), Int(a, "++") + 1);
		else				Assign(r_stack.Top(), Number(a, "++") + 1);
		r_stack.Top() = a;
		return;
	
	case IR_OP_POSTDEC:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		if(a.IsInt64())		Assign(r_stack.Top(), Int(a, "--") - 1);
		else				Assign(r_stack.Top(), Number(a, "--") - 1);
		r_stack.Top() = a;
		return;
	
	case IR_OP_MULARRAY:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		if(a.IsArray() && b.IsInt())
			r_stack.Top() = MulArray(a, b);
		else
		if(b.IsArray() && a.IsInt())
			r_stack.Top() = MulArray(b, a);
		else
		if(a.IsInt64() && b.IsInt64())
			r_stack.Top() = Int(a, "*") * Int(b, "*");
		else
			r_stack.Top() = Number(a, "*") * Number(b, "*");
		return;
	
	case IR_OP_LSHF:
		CHECK(!r_stack.IsEmpty())
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		if(a.IsArray() && b.IsArray()) {
			if(!a.Replace(a.GetCount(), 0, b))
				OutOfMemory();
			Assign(r_stack.Top(), a);
		}
		else
		if(!(a.IsArray() && b.IsVoid()))
			r_stack.Top() = Int(a, "<<") << Int(b, "<<");
		return;
	
	case IR_OP_RSHF:
		CHECK(!r_stack.IsEmpty())
		b = ReadVar(regs[1]);
		r_stack.Top() = Int(r_stack.Top(), ">>") >> Int(b,  ">>");
		return;
	
	case IR_OP_CMP:
		regs[0] = DoCompare(ReadVar(ir.arg[0]), ReadVar(ir.arg[1]), ir.arg[2].str);
		return;
	
	case IR_OP_CMP_RESULT:
		CHECK(!r_stack.IsEmpty())
		CHECK(ir.arg[0].type == IrValue::V_INT32);
		if (regs[0].GetType() == HIGH_INT64) {
			i = regs[0].GetInt64();
			switch (ir.arg[0].i32) {
				case 0: r_stack.Top() = i >= 0; return;
				case 1: r_stack.Top() = i <= 0; return;
				case 2: r_stack.Top() = i > 0; return;
				case 3: r_stack.Top() = i < 0; return;
				default: return;
			}
		}
		else {
			d = regs[0].GetNumber();
			switch (ir.arg[0].i32) {
				case 0: r_stack.Top() = (double)d >= 0; return;
				case 1: r_stack.Top() = (double)d <= 0; return;
				case 2: r_stack.Top() = (double)d > 0; return;
				case 3: r_stack.Top() = (double)d < 0; return;
				default: return;
			}
		}
	
	case IR_OP_ADDASS1:
		CHECK(!r_stack.IsEmpty() && !ir.arg[0].IsVoid() && !ir.arg[1].IsVoid());
		AddAssign1(r_stack.Top(), ReadVar(ir.arg[0]), ReadVar(ir.arg[1]));
		return;
	
	case IR_OP_SUBASS1:
		CHECK(!r_stack.IsEmpty());
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		if(a.IsInt64() && b.IsInt64())	r_stack.Top() = Int(a, "-") - Int(b, "-");
		else							r_stack.Top() = Number(a, "-") - Number(b, "-");
		return;
	
	case IR_OP_DIVASS1:
		CHECK(!r_stack.IsEmpty());
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		d = Number(b, "/");
		if (d == 0)
			OnError("divide by zero");
		else
			r_stack.Top() = Number(a, "/") / d;
		return;
	
	case IR_OP_MODASS1:
		i = Int(ReadVar(regs[1]), "%");
		val = &r_stack.Top();
		if (i == 0)
			OnError("divide by zero");
		else
			*val = Int(*val, "%") % i;
		return;
	
	case IR_OP_ANDASS1:
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		CHECK(ir.arg[0].IsRegister());
		WriteRegister(ir.arg[0], IsTrue(a) && IsTrue(b));
		return;
	
	case IR_OP_ORASS1:
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		CHECK(ir.arg[0].IsRegister());
		WriteRegister(ir.arg[0], IsTrue(a) || IsTrue(b));
		return;
	
	case IR_OP_ADDASS2:
		CHECK(!r_stack.IsEmpty() && !ir.arg[0].IsVoid() && !ir.arg[1].IsVoid());
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		AddAssign2(r_stack.Top(), a, b);
		return;
	
	case IR_OP_SUBASS2:
		CHECK(!r_stack.IsEmpty());
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		if(a.IsInt64() && b.IsInt64())
			Assign(r_stack.Top(), Int(a, "-=") - Int(b, "-="));
		else
			Assign(r_stack.Top(), Number(a, "-=") - Number(b, "-="));
		return;
	
	case IR_OP_MULASS2:
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		if(a.IsInt64() && b.IsInt64())
			Assign(r_stack.Top(), Int(a, "*=") * Int(b, "*="));
		else
			Assign(r_stack.Top(), Number(a, "*=") * Number(b, "*="));
		return;
	
	case IR_OP_DIVASS2:
		a = ReadVar(ir.arg[0]);
		b = ReadVar(ir.arg[1]);
		if(a.IsInt64() && b.IsInt64())
			Assign(r_stack.Top(), Int(a, "/=") / Int(b, "/="));
		else
			Assign(r_stack.Top(), Number(a, "/=") / Number(b, "/="));
		return;
	
	case IR_PUSH_VAR:
		var_stack.Add(ReadVar(ir.arg[0]));
		return;
	
	case IR_POP_VAR:
		CHECK(!var_stack.IsEmpty());
		WriteRegister(ir.arg[0], var_stack.Top());
		var_stack.SetCount(var_stack.GetCount()-1);
		return;
	
	case IR_ASSIGN_R0:
		regs[0] = ReadVar(ir.arg[0]);
		return;
		
	case IR_ASSIGN_R:
		CHECK(!r_stack.IsEmpty());
		r_stack.Top() = ReadVar(ir.arg[0]);
		return;
		
	case IR_ASSIGN_R_VOID:
		CHECK(!r_stack.IsEmpty());
		r_stack.Top() = HiValue();
		return;
		
	case IR_ASSIGN_R_RSELF:
		CHECK(!r_stack.IsEmpty());
		CHECK(!rself_stack.IsEmpty());
		r_stack.Top() = rself_stack.Top();
		return;
	
	case IR_ASSIGN_R_LVAL_VALUE:
		CHECK(!r_stack.IsEmpty());
		val = &r_stack.Top();
		a = ReadVar(ir.arg[0]);
		if(!val->lval)
			OnError("l-value required");
		else if(val->sbs.IsArray() && val->sbs.GetCount())
			Assign(*val->lval, val->sbs.GetArray(), 0, a);
		else
			*val->lval = a;
		return;
	
	case IR_ASSIGN_R_BWAND:
		CHECK(!r_stack.IsEmpty());
		val = &r_stack.Top();
		b = ReadVar(regs[1]);
		*val = Int(*val, "&") & Int(b, "&");
		return;
		
	case IR_ASSIGN_R_BWXOR:
		CHECK(!r_stack.IsEmpty());
		val = &r_stack.Top();
		b = ReadVar(regs[1]);
		*val = Int(*val, "^") ^ Int(b, "^");
		return;
		
	case IR_ASSIGN_R_BWOR:
		CHECK(!r_stack.IsEmpty());
		val = &r_stack.Top();
		b = ReadVar(regs[1]);
		*val = Int(*val, "|") | Int(b, "|");
		return;
	
	case IR_ASSIGN_R_EMPTYMAP:
		CHECK(!r_stack.IsEmpty());
		r_stack.Top().rval.SetEmptyMap();
		return;
		
	case IR_ASSIGN_R_EMPTYARRAY:
		CHECK(!r_stack.IsEmpty());
		r_stack.Top().rval.SetEmptyArray();
		return;
	
	case IR_ASSIGN_R1_SELF:
		CHECK(!self_stack.IsEmpty());
		regs[1] = self_stack.Top();
		return;
	
	case IR_ASSIGN_RSELF_R:
		CHECK(!rself_stack.IsEmpty());
		CHECK(!r_stack.IsEmpty());
		rself_stack.Top() = r_stack.Top();
		return;
	
	case IR_ASSIGN_RSELF_LVAL_SELF:
		CHECK(!rself_stack.IsEmpty());
		CHECK(!self_stack.IsEmpty());
		rself_stack.Top().lval = &self_stack.Top();
		return;
	
	case IR_ASSIGN_SELF_MAP:
		CHECK(!self_stack.IsEmpty());
		self_stack.Top().MapSet(ReadVar(ir.arg[0]), ReadVar(ir.arg[1]));
		return;
	
	case IR_R_ISTRUE:
		regs[0] = IsTrue(ReadVar(ir.arg[0]));
		return;
	
	case IR_ASSERT_SELF_MAP:
		CHECK(!self_stack.IsEmpty());
		if (!self_stack.Top().IsMap())
			OnError("member-access in non-member code");
		return;
	
	case IR_ASSERT_SELF_NONVOID:
		CHECK(!self_stack.IsEmpty());
		if (!self_stack.Top().IsVoid())
			OnError("no instance");
		return;
	
	case IR_ASSIGN_R_LVAL_GLOBAL_GETADD:
		CHECK(!r_stack.IsEmpty());
		CHECK(ir.arg[0].IsAnyString());
		str = ir.arg[0].GetString();
		CHECK(str.GetCount());
		r_stack.Top().lval = &global.GetAdd(str);
		return;
	
	case IR_ASSIGN_R_LVAL_VAR_GETADD:
		CHECK(!r_stack.IsEmpty());
		CHECK(ir.arg[0].IsAnyString());
		str = ir.arg[0].GetString();
		CHECK(str.GetCount());
		val = &r_stack.Top();
		val->lval = &var.GetAdd(str);
		return;
	
	case IR_SELF_LAMBDA_CHECK:
		if (!rself_stack.IsEmpty() && !self_stack.IsEmpty()) {
			CHECK(!self_stack.IsEmpty());
			CHECK(ir.arg[0].IsAnyString());
			str = ir.arg[0].GetString();
			CHECK(str.GetCount());
			val = &rself_stack.Top();
			if (!val->lval && self_stack.Top().IsMap()) {
				regs[1] = self_stack.Top().MapGet(str);
				regs[0] = regs[1].IsLambda();
				return;
			}
		}
		regs[0] = false;
		return;
	  
	case IR_GLOBAL_LAMBDA_CHECK:
		if (!rself_stack.IsEmpty()) {
			CHECK(ir.arg[0].IsAnyString());
			val = &rself_stack.Top();
			str = ir.arg[0].GetString();
			if (!val->lval && (i = global.Find(str)) >= 0) {
				regs[1] = i;
				regs[0] = global[(int)i].IsLambda();
				return;
			}
		}
		regs[0] = false;
		return;
	 
	case IR_ASSIGN_R_GLOBALIDX:
		CHECK(!r_stack.IsEmpty());
		i = ReadVar(ir.arg[0]).GetInt64();
		if (i < 0 || i >= global.GetCount())
			OnError("invalid global index");
		else
			r_stack.Top() = global[(int)i];
		return;
	
	case IR_RSELF_LVAL_CHECK:
		CHECK(!rself_stack.IsEmpty());
		boolean = rself_stack.Top().lval != 0;
		regs[0] = boolean;
		return;
	
	case IR_PUSH_RSELF_EMPTY:
		rself_stack.Add();
		return;
	
	case IR_POP_RSELF:
		CHECK(!rself_stack.IsEmpty());
		rself_stack.SetCount(rself_stack.GetCount()-1);
		return;
	
	case IR_HAS_VAR:
		CHECK(ir.arg[0].IsAnyString());
		regs[0] = var.Find(ir.arg[0].GetString()) >= 0;
		return;
	
	case IR_EXECUTE_LAMBDA:
		CHECK(!argvec_stack.IsEmpty());
		CHECK(!rself_stack.IsEmpty());
		CHECK(!r_stack.IsEmpty());
		str = ir.arg[0].GetString();
		a = ReadVar(ir.arg[1]);
		val = &rself_stack.Top();
		#if 0
		try {
			r_stack.Top() = ExecuteLambda(str, a, *val, argvec_stack.Top());
		}
		catch(Exc e) {
			throw Exc(a.GetTypeName() + "." + str + "(): " + e);
		}
		#else
		BeginExecutingLambda(str, a, *val, argvec_stack.Top());
		#endif
		return;
		
	}
	
	DUMP(ir);
	Panic("not implemented");
	
}

void IrVM::Get() {
	SRVal& r = s->r_stack.Top();
	HiValue& v = s->regs[0];
	
	v = r.lval ? *r.lval : r.rval;
	GetSbs(r, v);
}

void IrVM::Get(const SRVal& r, HiValue& v) {
	v = r.lval ? *r.lval : r.rval;
	GetSbs(r, v);
}

void IrVM::GetSbs(const SRVal& r, HiValue& v) {
	if(r.sbs.IsArray()) {
		const Vector<HiValue>& sbs = r.sbs.GetArray();
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
						OnError("slice out of range");
				}
				else {
					int64 i = (int)Int(ss, "index");
					if(i < 0)
						i += count;
					if(i >= 0 && i < count)
						v = v.ArrayGet((int)i);
					else
						OnError("index out of range");
				}
			}
			else
				OnError("invalid indirection");
			TestLimit();
		}
	}
}

void IrVM::ThrowError(String msg) {
	THROW(Exc(msg));
}

double IrVM::Number(const HiValue& a, const char *oper)
{
	if(a.IsNumber())
		return a.GetNumber();
	OnError(String().Cat() << "number expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return 0;
}

int64 IrVM::Int(const HiValue& a, const char *oper)
{
	if(a.IsNumber())
		return a.GetInt64();
	OnError(String().Cat() << "integer expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return 0;
}

double IrVM::Number(const SRVal& a, const char *oper)
{
	HiValue v;
	Get(a, v);
	return Number(v, oper);
}

int64 IrVM::Int(const SRVal& a, const char *oper)
{
	HiValue v;
	Get(a, v);
	return Int(v, oper);
}

String IrVM::Lims(const String& s) const {
	if (s.GetCount() < 40)
		return s;
	else
		return s.Left(40);
}

void IrVM::OutOfMemory() {
	OnError("IrVM out of memory");
}

HiValue	IrVM::ReadVar(const IrValue& v) {
	HiValue r;
	r = v.AsHiValue(*s);
	return r;
}

void IrVM::Jump(const IrValue& v) {
	if (v.type == IrValue::V_LABEL_INT) {
		if (v.i32 < 0 || v.i32 >= lbl_pos.GetCount()) {
			OnError("Position label out-of-range");
			return;
		}
		s->pc = lbl_pos[v.i32]; // no " + 1;" because pc++ is after this
	}
	else if (v.type == IrValue::V_LABEL_STR) {
		int i = lbl_names.Find(v.s);
		if (i < 0) {
			OnError("String label not found");
			return;
		}
		s->pc = lbl_names[i]; // no " + 1;" because pc++ is after this
	}
	else {
		OnError("Invalid address value for program counter jump");
	}
}

void IrVM::WriteRegister(const IrValue& reg, const HiValue& v) {
	int i = -1;
	if (reg.type == IrValue::V_INT32 || reg.type == IrValue::V_REG)
		i = reg.i32;
	if (i < 0 || i >= REG_COUNT) {
		OnError("Trying to write out-of-range register");
		return;
	}
	s->regs[i] = v;
}

void IrVM::AddAssign1(SRVal& r, const HiValue& a, const HiValue& b) {
	if (a.IsArray() && b.IsArray()) {
		HiValue aa = a;
		if (!aa.Replace(aa.GetCount(), 0, b))
			OutOfMemory();
		r = aa;
	}
	else if (!(a.IsArray() && b.IsVoid())) {
		if (a.IsInt64() && b.IsInt64()) {
			int64 ai = (int)Int(a, "+");
			int64 bi = (int)Int(b, "+");
			r = ai + bi;
		}
		else {
			double ai = Number(a, "+");
			double bi = Number(b, "+");
			r = ai + bi;
		}
	}
}

void IrVM::AddAssign2(SRVal& r, const HiValue& a, const HiValue& b) {
	if (a.IsArray() && b.IsArray()) {
		HiValue aa = a;
		if (!aa.Replace(aa.GetCount(), 0, b))
			OutOfMemory();
		Assign(r, aa);
	}
	else if (!(a.IsArray() && b.IsVoid())) {
		if (a.IsInt64() && b.IsInt64()) {
			int64 ai = (int)Int(a, "+=");
			int64 bi = (int)Int(b, "+=");
			Assign(r, ai + bi);
		}
		else {
			double ai = Number(a, "+=");
			double bi = Number(b, "+=");
			Assign(r, ai + bi);
		}
	}
}

void IrVM::Assign(const SRVal& val, const HiValue& src)
{
	if(!val.lval)
		OnError("l-value required");
	if(val.sbs.IsArray() && val.sbs.GetCount())
		Assign(*val.lval, val.sbs.GetArray(), 0, src);
	else
		*val.lval = src;
}

void IrVM::Assign(HiValue& val, const Vector<HiValue>& sbs, int si, const HiValue& src)
{
	//LTIMING("Assign");
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
				OnError("slice must be last subscript");
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
					OnError("only array can be assigned to the slice");
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
					OnError("slice out of range");
			}
			else {
				int64 i = ss.IsVoid() ? val.GetCount() : Int(ss, "index");
				if(i < 0)
					i = count + i;
				if(i >= 0 && i < INT_MAX) {
					if(!val.ArraySet((int)i, src))
						OnError("out of memory");
					return;
				}
			}
		}
	}
	OnError("invalid indirection");
}

double IrVM::DoCompare(const HiValue& a, const HiValue& b, const char *op)
{
	//LTIMING("DoCompare");
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
	OnError("invalid values for comparison " + a.GetTypeName() + ' ' + String(op) + ' ' + b.GetTypeName());
	return 0;
}

HiValue IrVM::MulArray(HiValue array, HiValue times)
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

void IrVM::BeginExecutingLambda(const String& id, HiValue& lambda, SRVal& self, Array<SRVal>& arg) {
	if(!lambda.IsLambda()) {
		OnError(Format("'%s' is not a lambda", id));
		return;
	}
	HiLambda& l = lambda.GetLambdaRW();
	if(!l.varargs && arg.GetCount() > l.arg.GetCount()
	   || arg.GetCount() < l.arg.GetCount() - l.def.GetCount()) {
		OnError("invalid number of arguments in call to '" + id + "'");
		return;
	}
	call_self = &self;
	call_fn = &l;
	call_arg = &arg;
	call_id = id;
	is_calling = true;
}

int IrVM::InitLambdaExecution(HiLambda& l, IrVM& parent) {
	Array<SRVal>& arg = *parent.call_arg;
	SRVal& self = *parent.call_self;
	HiValue& sub_self = Self();
	
	this->fn = &l;
	this->parent = &parent;
	
	Get(self, sub_self);
	for(int i = 0; i < l.arg.GetCount(); i++) {
		HiValue& v = var.GetAdd(l.arg[i]);
		if (i < arg.GetCount())
			Get(arg[i], v);
		else
		    break;
		TestLimit();
	}
	
	return l.arg.GetCount() - arg.GetCount();
}

HiValue IrVM::ExecuteLambda(const String& id, HiValue& lambda, SRVal& self, Array<SRVal>& arg) {
	//LTIMING("ExecuteLambda");
	if(!lambda.IsLambda()) {
		OnError(Format("'%s' is not a lambda", id));
		return HiValue();
	}
	const HiLambda& l = lambda.GetLambda();
	if(!l.varargs && arg.GetCount() > l.arg.GetCount()
	   || arg.GetCount() < l.arg.GetCount() - l.def.GetCount()) {
		OnError("invalid number of arguments in call to '" + id + "'");
		return HiValue();
	}
	HiValue retval;
	Hi sub(global, l.code, op_limit, l.filename, l.line);
	HiValue& sub_self = sub.Self();
	
	Get(self, sub_self);
	for(int i = 0; i < l.arg.GetCount(); i++) {
		HiValue& v = sub.Var().GetAdd(l.arg[i]);
		if (i < arg.GetCount())
			Get(arg[i], v);
		else
		    v = Evaluatex(l.def[i - (l.arg.GetCount() - l.def.GetCount())], global, op_limit);
		TestLimit();
	}
	Array<HiValue> argvar;
	if(l.escape) {
		#if LIBTOPSIDE
		sub.Var().PickValues(argvar);
		#else
		argvar = sub.Var().PickValues();
		#endif
		
		for(int i = l.arg.GetCount(); i < arg.GetCount(); i++) {
			Get(arg[i], argvar.Add());
		}
		HiValue v;
		Get(self, v);
		HiEscape e(*this, v, argvar);
		e.id = id;
		l.escape(e);
		retval = e.ret_val;
		self = e.self;
	}
	else {
		if(l.varargs) {
			HiValue& argv = sub.Var().GetAdd("argv");
			argv.SetEmptyArray();
			for(int i = l.arg.GetCount(); i < arg.GetCount(); i++)
				Get(arg[i], argv.ArrayAdd(HiValue()));
		}
		sub.Run();
		retval = sub.return_value;
		
		#if LIBTOPSIDE
		sub.Var().PickValues(argvar);
		#else
		argvar = sub.Var().PickValues();
		#endif
	}
	for(int i = 0; i < l.inout.GetCount(); i++)
		if(l.inout[i] && i < arg.GetCount() && arg[i].lval)
			Assign(arg[i], argvar[i]);
	if(self.lval)
		Assign(self, sub_self);
	return retval;
}

HiValue& IrVM::Self() {
	return state.self_stack.IsEmpty() ? state.self_stack.Add() : state.self_stack.Top();
}
	








}
#endif
