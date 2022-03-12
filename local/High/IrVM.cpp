#include "High.h"
#if USE_HIGH_BYTECODE

namespace UPP {


void IrVM::Execute(const IR& ir) {
	
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
			
		case IR_PUSH_TEMPSELF:
			// _self = IrValue()
			
		case IR_ASSIGN_TEMPSELF_LVAL_SELF:
			// _self.lval = &self;
			
		case IR_PUSH_TEMPSELF_R:
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
		case IR_PUSH_R_TEMPSELF:
			// r = _self
		
		case IR_SCOPE_PUSH_EMPTYMAP:
			// IrValue map;
			// map.SetEmptyMap();
			//// be able to reference with stack.top
		
		case IR_ASSIGN_R_SCOPE_POP:
			// r = scope.Pop();
		
		case IR_SCOPE_ARRAYADD:
			// stack.Top().ArrayAdd(v);
			
		case IR_SCOPE_MAPSET:
			//// reference stack.top
			// stack.Top().MapSet(k, v);
			
		case IR_SCOPE_PUSH_EMPTYARRAY:
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
		
		case IR_OP_DIVASS:
			/*
			IrValue b = Number(y, "/");
			if(b == 0)
				ThrowError("divide by zero");
			r = Number(x, "/") / b;*/
		
		case IR_OP_MODASS_R:
			/*
			IrValue b = Int(w, "%");
			if(b == 0)
				ThrowError("divide by zero");
			r = Int(r, "%") % b;*/
			// pop r
		
		case IR_OP_ADDASS:
			/*if(v.IsArray() && b.IsArray()) {
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
			}*/
			// pop r
		
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
			// w is in 2nd argument register A1
			//r = Int(r, ">>") >> Int(w,  ">>");
			
		case IR_OP_SUBASS:
			/*if(v.IsInt64() && b.IsInt64())
				r = Int(v, "-") - Int(b, "-");
			else
				r = Number(v, "-") - Number(b, "-");*/
		
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
		
		case IR_OP_ANDASS:
			// b = b && IsTrue(v);
		
		
		
		case IR_PUSH_BWAND:
			// r = Int(r, "&") & Int(A1, "&");
		
		case IR_PUSH_BWXOR:
			// r = Int(r, "^") ^ Int(A1, "^");
		
		case IR_PUSH_BWOR:
			// r = Int(r, "|") | Int(A1, "|");
		
		
		
		case IR_POSTINC:
			/*if(v.IsInt64())
				Assign(r, Int(v, "++") + 1);
			else
				Assign(r, Number(v, "++") + 1);
			r = v;*/
		
		case IR_POSTDEC:
			/*if(v.IsInt64())
				Assign(r, Int(v, "--") - 1);
			else
				Assign(r, Number(v, "--") - 1);
			r = v;*/
		
		case IR_PUSH_NEW_R:
			// SRVal w;
		
		case IR_POP_R:
			// kuten nimi kertoo
		
		case IR_POP_R_A1:
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
		case IR_POP_TEMP_R:
			// pop last r to temp register
		case IR_PUSH_TEMP_R:
			// push temp register back to stack
		
		case IR_PUSH_R_ARGVEC_ADD:
			//r = arg.Add();
		
	}
}


}
#endif
