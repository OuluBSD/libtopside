#include "High.h"
#if USE_HIGH_BYTECODE

namespace UPP {

IrValue::IrValue() {
	type = V_VOID;
}

/*IrValue::IrValue(IrValue&& v) {
	
}*/

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
		case V_STRING:	return s;
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
		case V_LABEL_STR:	return s;
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
		s << ", " << arg[i].ToString();
	}
	return s;
}




void IrVM::OnError(String msg) {
	LOG("IrVM: error: " << msg);
	LOG("	   at " << s->pc);
	SetNotRunning();
	fail = true;
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

void IrVM::Execute(const Vector<IR>& ir) {
	DUMPC(ir);
	int& max_pc		= s->max_pc;
	int& pc			= s->pc;
	auto& r_stack	= s->r_stack;
	fail = 0;
	
	if (!RefreshLabels(ir)) {
		fail = 1;
		return;
	}
	
	max_pc = ir.GetCount();
	if (!max_pc) {
		fail = 1;
		return;
	}
	
	
	const IR* vec = ir.Begin();
	pc = 0;
	flag.Start();
	
	while (IsRunning()) {
		const IR& ins = vec[pc];
		
		Execute(ins);
		
		pc++;
		if (pc >= max_pc)
			SetNotRunning();
	}
	
	flag.SetStopped();
}

void IrVM::Execute(const IR& ir) {
	#undef CHECK
	#define CHECK(x) if (!(x)) {OnError("Instruction " + ir.GetCodeString() + " failed: " #x " == false"); return;}
	HiValue a, b;
	double d;
	int64 i;
	SRVal* val;
	int& max_pc		= s->max_pc;
	int& pc			= s->pc;
	auto& r_stack	= s->r_stack;
	auto& self_stack	= s->self_stack;
	auto& rself_stack	= s->rself_stack;
	auto& var_stack		= s->var_stack;
	auto& argvec_stack	= s->argvec_stack;
	auto& temp_stack	= s->temp_stack;
	auto& regs			= s->regs;
	
	switch (ir.code) {
		
    case IR_LABEL:
        return;
	
	//case IR_SCOPE_PUSH:break;
	
	case IR_PUSH_R_EMPTY:
		r_stack.Add();
		return;
	
	//case IR_PUSH_R_SELF:
	//	CHECK(!self_stack.IsEmpty());
	//	r_stack.Add(self_stack.Top());
	//	return;
	
	case IR_PUSH_R_ARGVEC_ADD:
		CHECK(!argvec_stack.IsEmpty());
		r_stack.Add(argvec_stack.Top().ArrayAdd(HiValue()));
		return;
	
	case IR_PUSH_R_TEMP:
		CHECK(!temp_stack.IsEmpty());
		r_stack.Add(temp_stack.Detach(temp_stack.GetCount()-1));
		return;
	
	case IR_POP_R:
		CHECK(!r_stack.IsEmpty());
		r_stack.Remove(r_stack.GetCount()-1);
		return;
	
	case IR_POP_R_TEMP:
		CHECK(!r_stack.IsEmpty());
		temp_stack.Add(r_stack.Detach(r_stack.GetCount()-1));
		return;
	
	case IR_POP_R_R1:
		CHECK(!r_stack.IsEmpty());
		Get(r_stack.Top(), regs[1]);
		r_stack.Remove(r_stack.GetCount()-1);
		return;
	
	//case IR_PUSH_SELF_EMPTYMAP:
	//	self_stack.Add().SetEmptyMap();
	//	return;
	
	//case IR_POP_SELF:
	//	CHECK(!self_stack.IsEmpty());
	//	self_stack.Remove(self_stack.GetCount()-1);
	//	return;
	
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
		CHECK(r_stack.Top().sbs.IsArray());
		r_stack.Top().sbs.ArrayAdd(HiValue());
		return;
	
	case IR_R_SBS_ARRAYADD_1:
		CHECK(r_stack.Top().sbs.IsArray());
		r_stack.Top().sbs.ArrayAdd(ReadVar(ir.arg[0]));
		return;
	
	case IR_R_SBS_ARRAYADD_1_ARRAY1:
		CHECK(r_stack.Top().sbs.IsArray());
		a.SetEmptyArray();
		a.ArrayAdd(ReadVar(ir.arg[0]));
		r_stack.Top().sbs.ArrayAdd(a);
		return;
	
	case IR_R_SBS_ARRAYADD_1_ARRAY2:
		CHECK(r_stack.Top().sbs.IsArray());
		a.SetEmptyArray();
		a.ArrayAdd(ReadVar(ir.arg[0]));
		a.ArrayAdd(ReadVar(ir.arg[1]));
		r_stack.Top().sbs.ArrayAdd(a);
		return;
	
	case IR_R_SBS_ARRAYADD_1_ARRAY3:
		CHECK(r_stack.Top().sbs.IsArray());
		a.SetEmptyArray();
		a.ArrayAdd(ReadVar(ir.arg[0]));
		a.ArrayAdd(ReadVar(ir.arg[1]));
		a.ArrayAdd(ReadVar(ir.arg[2]));
		r_stack.Top().sbs.ArrayAdd(a);
		return;
	
	
	case IR_ARGVEC_PUSH_NEW:
		argvec_stack.Add();
		return;
	
	case IR_ARGVEC_POP:
		CHECK(!argvec_stack.IsEmpty());
		argvec_stack.SetCount(argvec_stack.GetCount()-1);
		return;
	
	case IR_EXECUTE_LAMBDA: break;
	
	case IR_JUMP:
		Jump(ir.arg[0]);
		return;
	
	case IR_JUMP_IF_FALSE:
		if (!IsTrue(ReadVar(ir.arg[0])))
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
		if(a.IsVoid()) {
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
		r_stack.Top() = (int64)!IsTrue(ReadVar(ir.arg[0]));
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
		r_stack.Top() = Int(r_stack.Top(), ">>") >> Int(regs[1],  ">>");
		return;
	
	case IR_OP_CMP:
		regs[0] = DoCompare(ReadVar(ir.arg[0]), ReadVar(ir.arg[1]), ir.arg[2].str);
		return;
	
	case IR_OP_CMP_RESULT:
		CHECK(!r_stack.IsEmpty())
		CHECK(ir.arg[0].type == IrValue::V_INT32);
		if (regs[0].IsInt()) {
			switch (ir.arg[0].i32) {
				case 0: r_stack.Top() = (int)regs[0] >= 0; return;
				case 1: r_stack.Top() = (int)regs[0] <= 0; return;
				case 2: r_stack.Top() = (int)regs[0] > 0; return;
				case 3: r_stack.Top() = (int)regs[0] < 0; return;
				default: return;
			}
		}
		else {
			switch (ir.arg[0].i32) {
				case 0: r_stack.Top() = (double)regs[0] >= 0; return;
				case 1: r_stack.Top() = (double)regs[0] <= 0; return;
				case 2: r_stack.Top() = (double)regs[0] > 0; return;
				case 3: r_stack.Top() = (double)regs[0] < 0; return;
				default: return;
			}
		}
	
	case IR_OP_ADDASS1:
		CHECK(!r_stack.IsEmpty() && !ir.arg[0].IsVoid() && !ir.arg[1].IsVoid());
		AddAssign1(r_stack.Top(), ReadVar(ir.arg[0]), ReadVar(ir.arg[1]));
		return;
	
	case IR_OP_SUBASS1:
		CHECK(!r_stack.IsEmpty());
		if(a.IsInt64() && b.IsInt64())	r_stack.Top() = Int(a, "-") - Int(b, "-");
		else							r_stack.Top() = Number(a, "-") - Number(b, "-");
		return;
	
	case IR_OP_DIVASS1:
		CHECK(!r_stack.IsEmpty());
		d = Number(b, "/");
		if (d == 0)
			OnError("divide by zero");
		else
			r_stack.Top() = Number(a, "/") / d;
		return;
	
	case IR_OP_MODASS1:
		i = Int(regs[1], "%");
		if (i == 0)
			ThrowError("divide by zero");
		else
			r_stack.Top() = Int(r_stack.Top(), "%") % i;
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
		AddAssign2(r_stack.Top(), ReadVar(ir.arg[0]), ReadVar(ir.arg[1]));
		return;
	
	case IR_OP_SUBASS2:
		CHECK(!r_stack.IsEmpty());
		if(a.IsInt64() && b.IsInt64())
			Assign(r_stack.Top(), Int(a, "-=") - Int(b, "-="));
		else
			Assign(r_stack.Top(), Number(a, "-=") - Number(b, "-="));
		return;
	
	case IR_OP_MULASS2:
		if(a.IsInt64() && b.IsInt64())
			Assign(r_stack.Top(), Int(a, "*=") * Int(b, "*="));
		else
			Assign(r_stack.Top(), Number(a, "*=") * Number(b, "*="));
		return;
	
	case IR_OP_DIVASS2:
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
		
	case IR_ASSIGN_R_LVAL_1:
		CHECK(!r_stack.IsEmpty());
		val = &r_stack.Top();
		val->lval_owned = ReadVar(ir.arg[0]);
		val->lval = &val->lval_owned;
		return;
		
	case IR_ASSIGN_R_LVAL_2:
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
		*val = Int(*val, "&") & Int(regs[1], "&");
		return;
		
	case IR_ASSIGN_R_BWXOR:
		CHECK(!r_stack.IsEmpty());
		val = &r_stack.Top();
		*val = Int(*val, "^") ^ Int(regs[1], "^");
		return;
		
	case IR_ASSIGN_R_BWOR:
		CHECK(!r_stack.IsEmpty());
		val = &r_stack.Top();
		*val = Int(*val, "|") | Int(regs[1], "|");
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
	
	case IR_GLOBAL_GETADD:
		CHECK(!r_stack.IsEmpty());
		CHECK(ir.arg[0].IsAnyString());
		r_stack.Top().lval = &global.GetAdd(ir.arg[0].GetString());
		return;
	
	case IR_VAR_GETADD:
		CHECK(!r_stack.IsEmpty());
		CHECK(ir.arg[0].IsAnyString());
		r_stack.Top().lval = &var.GetAdd(ir.arg[0].GetString());
		return;
	
	case IR_SELF_LAMBDA_CHECK:
		CHECK(!rself_stack.IsEmpty());
		CHECK(!self_stack.IsEmpty());
		CHECK(ir.arg[0].IsAnyString());
		val = &rself_stack.Top();
		if (!val->lval && self_stack.Top().IsMap()) {
			regs[1] = self.MapGet(ir.arg[0].GetString());
			regs[0] = regs[1].IsLambda();
		}
		else regs[0] = false;
		return;
	  
	case IR_GLOBAL_LAMBDA_CHECK:
		CHECK(!rself_stack.IsEmpty());
		CHECK(!self_stack.IsEmpty());
		CHECK(ir.arg[0].IsAnyString());
		val = &rself_stack.Top();
		if (!val->lval && (i = global.Find(ir.arg[0].GetString()) >= 0)) {
			regs[1] = i;
			regs[0] = global[i].IsLambda();
		}
		else regs[0] = false;
		return;
	 
	case IR_ASSIGN_R_GLOBALIDX:
		CHECK(!r_stack.IsEmpty());
		if (!ir.arg[0].IsInt() || i < 0 || i >= global.GetCount())
			OnError("invalid global index");
		else
			r_stack.Top() = global[i];
		return;
	
	case IR_RSELF_LVAL_CHECK:
		CHECK(!rself_stack.IsEmpty());
		regs[0] = rself_stack.Top().lval != 0;
		return;
	
	case IR_PUSH_R_RSELF:
		CHECK(!rself_stack.IsEmpty());
		r_stack.Add(rself_stack.Top());
		return;
	
	case IR_POP_R_RSELF:
		CHECK(!rself_stack.IsEmpty());
		CHECK(!r_stack.IsEmpty());
		rself_stack.Top() = r_stack.Top();
		r_stack.SetCount(r_stack.GetCount()-1);
		return;
	
	case IR_PUSH_RSELF_EMPTY:
		rself_stack.Add();
		return;
	
	case IR_POP_RSELF:
		CHECK(!rself_stack.IsEmpty());
		r_stack.SetCount(r_stack.GetCount()-1);
		return;
	
	case IR_HAS_VAR:
		CHECK(ir.arg[0].IsAnyString());
		regs[0] = var.Find(ir.arg[0].GetString()) >= 0;
		return;
	
	}
	
	DUMP(ir);
	Panic("not implemented");
	
	#if 0
	TODO
	switch (ir.code) {
		case IR_R_SBS_RESET:
			// r.sbs = IrValue();
		case IR_R_SBS_ARRAYADD_EMPTY:
			//r.sbs.ArrayAdd(HiValue());
		
		case IR_R_SBS_ARRAYADD_1:
			//r.sbs.ArrayAdd(x);
		case IR_R_SBS_ARRAYADD_1_ARRAY1:
		case IR_R_SBS_ARRAYADD_1_ARRAY2:
			/*HiValue x;
			x.ArrayAdd(v1);
			x.ArrayAdd(v2);
			r.sbs.ArrayAdd(x);*/
		case IR_R_SBS_ARRAYADD_1_ARRAY3:
		
		case IR_EXECUTE_LAMBDA:
			/*try {
				r = ExecuteLambda(id, v, _self, arg);
			}
			catch(Exc e) {
				throw Error(Get(r).GetTypeName() + "." + id + "(): " + e);
			}*/
			
		//case IR_PUSH_RSELF:
			// _self = IrValue()
			
		case IR_ASSIGN_RSELF_LVAL_SELF:
			// _self.lval = &self;
			
		//case IR_PUSH_SELF_EMPTYMAP_R:
			// _self = r;
		
		case IR_POP_SELF:
			
		case IR_ASSIGN_R:
			// r =
			
		/*
		WROOOOOOOOOONG
		case IR_ASSIGN_R_RSELF:
			// r = self;
		case IR_ASSIGN_R_VOID:
			// r = IrValue()
		case IR_ASSIGN_R_TMPSELF:
			// r = _self;
		case IR_ASSIGN_R_TMPMETHOD:
			//// see: IR_COND_IF_SELFLAMBDA
			// r = method;
		case IR_ASSIGN_R_TMPGLOBALIDX:
			//// see: IR_COND_IF_GLOBALLAMBDA
			// r = global[ii];
		case IR_ASSIGN_R_LVAL:
			// r.lval = &v0;
			
		*/
		case IR_ASSIGN_R_LVAL_1:
			// r.lval = a0
			
		case IR_ASSIGN_R_LVAL_2:
			/*if(!r.lval)
				ThrowError("l-value required");
			if(r.sbs.IsArray() && r.sbs.GetCount())
				Assign(*r.lval, r.sbs.GetArray(), 0, src);
			else
				*r.lval = src;*/
		
		case IR_ASSIGN_SELF_R:
			// self = r
			
		//case IR_PUSH_R_RSELF:
			// r = _self
		
		//case IR_SCOPE_PUSH_EMPTYMAP:
			// IrValue map;
			// map.SetEmptyMap();
			//// be able to reference with stack.top
		
		//case IR_ASSIGN_R_SCOPE_POP:
			// r = scope.Pop();
		
		//case IR_SCOPE_ARRAYADD:
			// stack.Top().ArrayAdd(v);
			
		//case IR_SCOPE_MAPSET:
			//// reference stack.top
			// stack.Top().MapSet(k, v);
			
		//case IR_SCOPE_PUSH_EMPTYARRAY:
			// IrValue array;
			//array.SetEmptyArray();
			//// be able to reference with stack.Top()
		
		case IR_COND_ELSE:
			
		case IR_COND_ENDIF:
			// finishes if or if+else
			
			
		case IR_COND_IF_SELFLAMBDA:
			// if(!_self.lval && !_global && locali < 0 && IsChar('(') &&
			//     self.IsMap() && (method = self.MapGet(id)).IsLambda()) {
		
		case IR_COND_IF_GLOBALLAMBDA:
			// if(!_self.lval && !_global && locali < 0 && IsChar('(') &&
			//    (ii = global.Find(id)) >= 0 && global[ii].IsLambda()) {
		
		case IR_COND_IF_SELF_LVAL:
			// if(_self.lval) {
		
		case IR_COND_IF_GLOBAL:
			// if(_global) {
		
		case IR_ASSERT_SELF_MAP:
			//if(!self.IsMap())
			//	ThrowError("self in non-member code");
			
			
		case IR_OP_PREINC:
			/*if(v.IsInt64())
				Assign(r, Int(v, "++") + 1);
			else
				Assign(r, Number(v, "++") + 1);*/

		case IR_OP_PREDEC:
			/*if(v.IsInt64())
				Assign(r, Int(v, "--") - 1);
			else
				Assign(r, Number(v, "--") - 1);*/
		
		case IR_OP_NEGATIVE:
			/*if(v.IsInt64())
				r = -Int(v, "-");
			else
				r = -Number(v, "-");*/
				
		case IR_OP_POSITIVE:
			/*if(v.IsInt64())
				r = Int(v, "+");
			else
				r = Number(v, "+");*/
		
		case IR_OP_NOT:
			//r = (int64)!IsTrue(v0);
			
		case IR_OP_NEGATE:
			//r = ~Int(Get(r), "~");
		
		case IR_OP_DIVASS1:
			/*
			IrValue b = Number(y, "/");
			if(b == 0)
				ThrowError("divide by zero");
			r = Number(x, "/") / b;*/
		
		case IR_OP_MODASS1:
			// w in R1
			/*
			IrValue b = Int(w, "%");
			if(b == 0)
				ThrowError("divide by zero");
			r = Int(r, "%") % b;*/
			// pop r
		
			// pop r
		
		case IR_OP_ADDASS2:
			/*if(v.IsArray() && b.IsArray()) {
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
			}*/
			
		case IR_OP_LSHF:
			/*if(v.IsArray() && b.IsArray()) {
				if(!v.Replace(v.GetCount(), 0, b))
					OutOfMemory();
				Assign(r, v);
			}
			else
			if(!(v.IsArray() && b.IsVoid()))
				r = Int(v, "<<") << Int(b, "<<");*/
		
		case IR_OP_RSHF:
			// w is in 2nd argument register R1
			//r = Int(r, ">>") >> Int(w,  ">>");
			
		case IR_OP_SUBASS1:
			/*if(v.IsInt64() && b.IsInt64())
				r = Int(v, "-") - Int(b, "-");
			else
				r = Number(v, "-") - Number(b, "-");*/
		
		case IR_OP_SUBASS2:
			/*if(v.IsInt64() && b.IsInt64())
				Assign(r, Int(v, "-=") - Int(b, "-="));
			else
				Assign(r, Number(v, "-=") - Number(b, "-="));*/
		
		case IR_OP_MULASS2:
			/*if(x.IsInt64() && y.IsInt64())
				Assign(r, Int(x, "*=") * Int(y, "*="));
			else
				Assign(r, Number(x, "*=") * Number(y, "*="));*/
			
		case IR_OP_DIVASS2:
			/*double q = Number(v, "/=");
			if(q == 0)
				ThrowError("divide by zero");
			Assign(r, Number(b, "/=") / q);*/
		
		//case IR_OP_MODASS2:
			// w in R1
			/*int64 a = Int(r, "%=");
			int64 b = Int(w, "%=");
			if(b == 0)
				ThrowError("divide by zero");
			Assign(r, a % b);*/
			
		case IR_OP_CMP:
			// DoCompare(a, b, op);
			// store return integer to register A0
		
		case IR_OP_CMP_RESULT:
			/* x = ingeger from IR_OP_CMP register A0
			code 0: r = x >= 0
			code 1: r = x <= 0
			code 2: r = x > 0
			code 3: r = x < 0*/
		
		case IR_OP_EQ:
			// r = a == b
		
		case IR_OP_INEQ_RSELF:
			/*if(!_self.lval || (!g.IsVoid() && !g.IsMap()))
				ThrowError("l-value map or l-value void expected on the right side of !");
			if(g.IsVoid()) {
				IrValue v;
				v.SetEmptyMap();
				Assign(_self, v);
			}*/
			
		case IR_OP_INEQ:
			// r = a != b
		
		case IR_OP_ANDASS1:
			// b = b && IsTrue(v);
		
		case IR_OP_ORASS1:
			// b = b || IsTrue(v);
		
		
		case IR_ASSIGN_R_BWAND:
			// r = Int(r, "&") & Int(R1, "&");
		
		case IR_ASSIGN_R_BWXOR:
			// r = Int(r, "^") ^ Int(R1, "^");
		
		case IR_ASSIGN_R_BWOR:
			// r = Int(r, "|") | Int(R1, "|");
		
		
		
		case IR_OP_POSTINC:
			/*if(v.IsInt64())
				Assign(r, Int(v, "++") + 1);
			else
				Assign(r, Number(v, "++") + 1);
			r = v;*/
		
		case IR_OP_POSTDEC:
			/*if(v.IsInt64())
				Assign(r, Int(v, "--") - 1);
			else
				Assign(r, Number(v, "--") - 1);
			r = v;*/
		
		case IR_PUSH_R_EMPTY:
			// SRVal w;
		
		case IR_POP_R:
			// kuten nimi kertoo
		
		case IR_POP_R_R1:
			// pop r to 2nd argument register
		
		
		case IR_OP_MULARRAY:
			/*if(x.IsArray() && y.IsInt())
				r = MulArray(x, y);
			else
			if(y.IsArray() && x.IsInt())
				r = MulArray(y, x);
			else
			if(x.IsInt64() && y.IsInt64())
				r = Int(x, "*") * Int(y, "*");
			else
				r = Number(x, "*") * Number(y, "*");*/
		case IR_POP_R_TEMP:
			// pop last r to temp register
		case IR_PUSH_R_TEMP:
			// push temp register back to stack
		
		case IR_R_GET:
			Get();
			
			
		default: break;
	}
	#endif
}

void IrVM::Get() {
	SRVal& r = s->r_stack.Top();
	HiValue& v = s->regs[0];
	
	v = r.lval ? *r.lval : r.rval;
	Get(r, v);
}

void IrVM::Get(const SRVal& r, HiValue& v) {
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
						ThrowError("slice out of range");
				}
				else {
					int64 i = (int)Int(ss, "index");
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
}

void IrVM::ThrowError(String msg) {
	THROW(Exc(msg));
}

double IrVM::Number(const HiValue& a, const char *oper)
{
	if(!a.IsNumber())
		ThrowError(String().Cat() << "number expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return a.GetNumber();
}

int64 IrVM::Int(const HiValue& a, const char *oper)
{
	if(!a.IsNumber())
		ThrowError(String().Cat() << "integer expected for '" << oper << "', encountered " << Lims(a.ToString()));
	return a.GetInt64();
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
	ThrowError("IrVM out of memory");
}

HiValue	IrVM::ReadVar(const IrValue& v) {
	HiValue r;
	/*if (v.type == IrValue::V_REG) {
		int i = v.i32;
		if (i < 0 || i >= REG_COUNT)
			OnError("Trying to write out-of-range register");
		else
			r = s->regs[i];
	}
	else*/
		r = v.AsHiValue(*s);
	
	return r;
}

void IrVM::Jump(const IrValue& v) {
	if (v.type == IrValue::V_LABEL_INT) {
		if (v.i32 < 0 || v.i32 >= lbl_pos.GetCount()) {
			OnError("Position label out-of-range");
			return;
		}
		s->pc = lbl_pos[v.i32];
	}
	else if (v.type == IrValue::V_LABEL_STR) {
		int i = lbl_names.Find(v.s);
		if (i < 0) {
			OnError("String label not found");
			return;
		}
		s->pc = lbl_names[i];
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
			//r = (int64)(int)Int(a, "+") + (int64)(int)Int(b, "+");
			int64 ai = (int)Int(a, "+");
			int64 bi = (int)Int(b, "+");
			r = ai + bi;
		}
		else {
			//r = (double)Number(a, "+") + (double)Number(b, "+");
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
		ThrowError("l-value required");
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








}
#endif
