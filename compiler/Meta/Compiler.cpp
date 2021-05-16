#include "Meta.h"

NAMESPACE_TOPSIDE_BEGIN


Compiler::Compiler() : ErrorSource("Compiler") {
	
}



bool Compiler::Process(const Parser& p) {
	const Vector<IR>& irv = p.GetIR();
	obj.Clear();
	tmp_text.Clear();
	tmp_data.Clear();
	
	obj.header.abi = "none";
	obj.header.mach = mach.mach;
	obj.header.entry = 0;
	obj.bc.data.Reserve(1024);
	
	if (mach.rules.GetCount() >= 0x100)
		Panic("Too many rules");
	
	for(const IR& ir : irv) {
		if (ir.type == IR_INS) {
			const MachHeaders::InsRule& rule = mach.rules[ir.id];
			Cat8(ir.id);
			for(int i = 0; i < rule.arg_count; i++) {
				int type = rule.type[i];
				switch (type) {
					case ARG_INT:		CatInt(ir.int_value); break;
					case ARG_STRING:	CatString(ir.str_value); break;
					case ARG_CHAR:		CatChar(ir.str_value); break;
					case ARG_ID:		CatId(ir.str_value); break;
					default: Panic("Invalid type");
				}
			}
		}
		else if (ir.type == IR_LBL) {
			dword addr = obj.bc.data.GetCount();
			if (labels.Find(ir.str_value) >= 0) {
				AddError(FileLocation(), "Label exists already: " + ir.str_value);
			}
			else {
				labels.Add(ir.str_value, addr);
			}
		}
		else Panic("Unexpected IR type");
	}
	
	dword text_addr = obj.bc.data.GetCount();
	obj.bc.data.Append(tmp_text);
	
	for(const Placeholder& pl : placeholder) {
		if (pl.type == PH_LBL) {
			int i = labels.Find(pl.id);
			if (i < 0) {
				AddError(FileLocation(), "Label not found: " + pl.id);
			}
			else {
				dword addr = labels[i];
				Set(pl.addr, addr);
			}
		}
		else if (pl.type == PH_TEXT) {
			dword* d = (dword*)(obj.bc.data.Begin() + pl.addr);
			*d += text_addr;
		}
		else Panic("Invalid label");
	}
	
	return !IsFail();
}

void Compiler::Cat8(byte b) {
	obj.bc.data.Add(b);
}

void Compiler::CatInt(dword d) {
	dword addr = obj.bc.data.GetCount();
	obj.bc.data.SetCount(obj.bc.data.GetCount() + 4);
	Set(addr, d);
}

void Compiler::CatString(String s) {
	int c = s.GetCount() + 1;
	dword addr = tmp_text.GetCount();
	tmp_text.SetCount(addr + c);
	byte* b = tmp_text.Begin() + addr;
	for(int i = 0; i < s.GetCount(); i++)
		*b++ = s[i];
	*b = 0;
	Placeholder& pl = placeholder.Add();
	pl.type = PH_TEXT;
	pl.addr = obj.bc.data.GetCount();
	pl.id = 0;
	CatInt(addr);
}

void Compiler::CatChar(String s) {
	CatString(s);
}

void Compiler::CatId(String s) {
	dword addr = obj.bc.data.GetCount();
	Placeholder& pl = placeholder.Add();
	pl.type = PH_LBL;
	pl.addr = addr;
	pl.id = s;
	CatInt(0);
}

void Compiler::Set(dword addr, dword value) {
	ASSERT(addr <= (dword)(obj.bc.data.GetCount() - 4));
	dword* ptr = (dword*)(obj.bc.data.Begin() + addr);
	*ptr = value;
}

NAMESPACE_TOPSIDE_END
