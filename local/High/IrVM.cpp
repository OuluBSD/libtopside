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
		case V_LABEL_INT:;
		case V_INT32:	i32 = v.i32; break;
		case V_INT64:	i64 = v.i64; break;
		case V_UINT64:	u64 = v.u64; break;
		case V_DOUBLE:	d = v.d; break;
		case V_HIVAL:	hv = v.hv; break;
		case V_MAP:		map <<= v.map; break;
		case V_ARRAY:	array <<= v.array; break;
		case V_REG:		reg = v.reg; break;
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
	reg = REG_VOID;
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

IrValue& IrValue::SetRegisterValue(RegType r) {
	Clear();
	type = V_REG;
	reg = r;
	return *this;
}

IrValue& IrValue::SetLabel(int i) {type = V_LABEL_INT; i32 = i; return *this;}
IrValue& IrValue::SetLabel(String s) {type = V_LABEL_STR; this->s = s; return *this;}

bool IrValue::IsVoid() const {
	return type == V_VOID;
}

bool IrValue::IsMap() const {
	return type == V_MAP;
}

bool IrValue::IsArray() const {
	return type == V_ARRAY;
}

bool IrValue::IsAnyString() const {
	return type == V_STRING || type == V_CSTRING || type == V_WSTRING;
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
		default: return "<invalid type>";
	}
	return String();
}

String IrValue::GetTextValue() const {
	String s;
	switch (type) {
		case V_VOID:	return "<void>";
		case V_REG:		return "R" + IntStr(reg);
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
		default: return "<invalid type>";
	}
	return s;
}

String IrValue::ToString() const {
	return GetTypeString() + ": " + GetTextValue();
}

HiValue IrValue::AsHiValue() const {
	// HIGH_VOID, HIGH_DOUBLE, HIGH_ARRAY, HIGH_MAP, HIGH_LAMBDA, HIGH_INT64
	HiValue h;
	switch (type) {
		case V_VOID:	return HiValue();
		case V_REG:		return "R" + IntStr(reg);
		case V_CSTRING:	return str;
		case V_STRING:	return s;
		case V_WSTRING:	return ws;
		case V_INT32:	return i32;
		case V_INT64:	return i64;
		case V_UINT64:	return i64;
		case V_DOUBLE:	return d;
		case V_HIVAL:	return hv;
		case V_MAP:
			h.SetEmptyMap();
			for(int i = 0; i < map.GetCount(); i++)
				h.MapSet(map.GetKey(i), map[i].AsHiValue());
			return h;
		case V_ARRAY:
			h.SetEmptyArray();
			for(int i = 0; i < array.GetCount(); i++)
				h.ArrayAdd(array[i].AsHiValue());
			return h;
		case V_LABEL_INT:	return i32;
		case V_LABEL_STR:	return s;
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
	LOG("	   at " << pc);
}

void IrVM::Execute(const Vector<IR>& ir) {
	DUMPC(ir);
	
	max_pc = ir.GetCount();
	if (!max_pc) return;
	
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
	
	switch (ir.code) {
	    case IR_LABEL: break;
		
		case IR_SCOPE_PUSH: break;
		
		case IR_PUSH_R_EMPTY:
			r_stack.Add();
			return;
		case IR_PUSH_R_POP_SELF: break;
		case IR_PUSH_R_ARGVEC_ADD: break;
		case IR_PUSH_R_TEMP: break;
		
		case IR_POP_R:
			CHECK(!r_stack.IsEmpty());
			r_stack.Remove(r_stack.GetCount()-1);
			return;
		
		case IR_POP_R_TEMP: break;
		case IR_POP_R_R1: break;
		
		case IR_PUSH_SELF: break;
		case IR_POP_SELF: break;
		case IR_POP_SELF_R1: break;
		
		case IR_R_GET:
			CHECK(!r_stack.IsEmpty());
			Get();
			return;
		
		case IR_R_MAPSET: break;
		case IR_R_ARRAYADD: break;
		case IR_R_SBS_RESET:
			CHECK(!r_stack.IsEmpty());
			r_stack.Top().sbs = HiValue();
			return;
		
		case IR_R_SBS_ARRAYADD_EMPTY: break;
		case IR_R_SBS_ARRAYADD_1: break;
		case IR_R_SBS_ARRAYADD_1_ARRAY1: break;
		case IR_R_SBS_ARRAYADD_1_ARRAY2: break;
		case IR_R_SBS_ARRAYADD_1_ARRAY3: break;
		
		case IR_ARGVEC_PUSH_NEW: break;
		case IR_ARGVEC_POP: break;
		
		case IR_EXECUTE_LAMBDA: break;
		
		case IR_JUMP: break;
		case IR_JUMP_IF_FALSE: break;
		case IR_JUMP_IF_TRUE: break;
		case IR_JUMP_IF_EQ: break;
		case IR_JUMP_IF_INEQ: break;
		
		case IR_COND_IF: break;
		case IR_COND_IF_SELFLAMBDA: break;
		case IR_COND_IF_GLOBALLAMBDA: break;
		case IR_COND_IF_SELF_LVAL: break;
		case IR_COND_IF_GLOBAL: break;
		case IR_COND_ELSE: break;
		case IR_COND_ENDIF: break;
		
		case IR_OP_EQ: break;
		case IR_OP_INEQ: break;
		case IR_OP_INEQ_TEMPSELF: break;
		case IR_OP_NEGATIVE: break;
		case IR_OP_POSITIVE: break;
		case IR_OP_NOT: break;
		case IR_OP_NEGATE: break;
		case IR_OP_DIVASS: break;
		case IR_OP_PREINC: break;
		case IR_OP_PREDEC: break;
		case IR_OP_POSTINC: break;
		case IR_OP_POSTDEC: break;
		case IR_OP_MULARRAY: break;
		case IR_OP_LSHF: break;
		case IR_OP_RSHF: break;
		case IR_OP_CMP: break;
		case IR_OP_CMP_RESULT: break;
		
		case IR_OP_ADDASS1:
			CHECK(!r_stack.IsEmpty() && !ir.arg[0].IsVoid() && !ir.arg[1].IsVoid());
			AddAssign1(r_stack.Top(), ir.arg[0].AsHiValue(), ir.arg[1].AsHiValue());
			return;
		
		case IR_OP_SUBASS1: break;
		case IR_OP_DIVASS1: break;
		case IR_OP_MODASS1: break;
		case IR_OP_ANDASS1: break;
		case IR_OP_ORASS1: break;
		case IR_OP_ADDASS2: break;
		case IR_OP_SUBASS2: break;
		case IR_OP_MULASS2: break;
		case IR_OP_DIVASS2: break;
		
		case IR_ASSIGN: break;
		
		case IR_ASSIGN_R0:
			regs[0] = ir.arg[0].AsHiValue();
			return;
			
		case IR_ASSIGN_R:
			CHECK(!r_stack.IsEmpty());
			r_stack.Top() = ir.arg[0].AsHiValue();
			return;
			
		case IR_ASSIGN_R_VOID: break;
		case IR_ASSIGN_R_SELF: break;
		case IR_ASSIGN_R_LVAL1: break;
		case IR_ASSIGN_R_LVAL2: break;
		case IR_ASSIGN_R_TMPMETHOD: break;
		case IR_ASSIGN_R_TMPGLOBALIDX: break;
		case IR_ASSIGN_R_TMPSELF: break;
		case IR_ASSIGN_R_BWAND: break;
		case IR_ASSIGN_R_BWXOR: break;
		case IR_ASSIGN_R_BWOR: break;
		case IR_ASSIGN_R_R1: break;
		case IR_ASSIGN_R_EMPTYMAP: break;
		case IR_ASSIGN_R_EMPTYARRAY: break;
		
		case IR_ASSIGN_R1_SELF: break;
		
		case IR_ASSIGN_SELF_R: break;
		case IR_ASSIGN_SELF_LVAL_R1: break;
		case IR_ASSIGN_SELF_MAP: break;
		
		case IR_R_ISTRUE: break;
		
		case IR_ASSERT_SELF_MAP: break;
		case IR_ASSERT_SELF_NONVOID: break;
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
			
		//case IR_PUSH_TEMPSELF:
			// _self = IrValue()
			
		case IR_ASSIGN_SELF_LVAL_R1:
			// _self.lval = &self;
			
		//case IR_PUSH_SELF_R:
			// _self = r;
		
		case IR_POP_SELF:
			
		case IR_ASSIGN_R:
			// r =
			
		/*
		WROOOOOOOOOONG
		case IR_ASSIGN_R_SELF:
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
		case IR_ASSIGN_R_LVAL1:
			// r.lval = a0
			
		case IR_ASSIGN_R_LVAL2:
			/*if(!r.lval)
				ThrowError("l-value required");
			if(r.sbs.IsArray() && r.sbs.GetCount())
				Assign(*r.lval, r.sbs.GetArray(), 0, src);
			else
				*r.lval = src;*/
		
		case IR_ASSIGN_SELF_R:
			// self = r
			
		//case IR_PUSH_R_TEMPSELF:
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
		
		case IR_OP_INEQ_TEMPSELF:
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
		
		case IR_PUSH_R_ARGVEC_ADD:
			//r = arg.Add();
		
		case IR_R_GET:
			Get();
			
		default: break;
	}
	#endif
}

void IrVM::Get() {
	SRVal& r = r_stack.Top();
	
	HiValue& v = regs[0];
	v = r.lval ? *r.lval : r.rval;
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

HiValue IrVM::Number(const HiValue& a, const char *oper) {
	TODO
}

HiValue IrVM::Int(const HiValue& a, const char *oper) {
	TODO
}

void IrVM::OutOfMemory() {
	ThrowError("IrVM out of memory");
}

void IrVM::AddAssign1(SRVal& r, const HiValue& a, const HiValue& b) {
	if (a.IsArray() && b.IsArray()) {
		HiValue aa = a;
		if (!aa.Replace(aa.GetCount(), 0, b))
			OutOfMemory();
		r = aa;
	}
	else if (!(a.IsArray() && b.IsVoid())) {
		if (a.IsInt64() && b.IsInt64())
			r = (int64)(int)Int(a, "+") + (int64)(int)Int(b, "+");
		else
			r = (double)Number(a, "+") + (double)Number(b, "+");
	}
}












}
#endif
