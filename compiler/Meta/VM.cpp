#include "Meta.h"

NAMESPACE_TOPSIDE_BEGIN


VM::VM() : ErrorSource("VM") {
	
}

void VM::Run() {
	Reset();
	
	data <<= prog->bc.data;
	
	prog_size = prog->bc.data.GetCount();
	input_size = 1024*1024;
	output_size = 1024*1024;
	user_size = 1024*1024;
	stack_size = 1024*1024;
	input_begin = prog_size;
	output_begin = input_begin + input_size;
	user_begin = output_begin + output_size;
	stack_begin = user_begin + user_size;
	total_size = stack_begin + stack_size;
	
	
	
	data.SetCount(total_size, 0);
	
	ReadInput();
	
	#define MACH_NAME(x) if (prog->header.mach == #x) {Run##x(); return;}
	#define MICROCODE_INFO
	#include "machines.h"
	#undef MICROCODE_INFO
	
	AddError(FileLocation(), Format(t_("Not a valid machine type: %s"), prog->header.mach));
	exit_code = 1;
}

void VM::Reset() {
	exit_code = 0;
	is_halt = false;
	indent = 1;
	post = NULL;
	
	data.SetCount(0);
	
	dbg_chk_line = 0;
	
	for(int i = 0; i < REG_COUNT; i++)
		reg32[i] = 0;
	
	for(int i = 0; i < FLAG_COUNT; i++)
		flag[i] = 0;
}

void VM::LoadDebugCorrect(String file_path) {
	dbg_chk_lines = Split(LoadFile(file_path), "\n");
	for(String& line : dbg_chk_lines)
		line = line.Mid(line.Find(" ") + 1);
	DUMPC(dbg_chk_lines);
}

void VM::DbgCheck(String s) {
	if (dbg_chk_line < dbg_chk_lines.GetCount()) {
		String correct = dbg_chk_lines[dbg_chk_line].Left(s.GetCount());
		if (correct != s) {
			DUMP(correct);
			DUMP(s);
			Panic("Incorrect instruction: " + s + " != " + correct + " (in line " + IntStr(dbg_chk_line) + ")");
		}
		dbg_chk_line++;
	}
}

String VM::GetStateString(String title) const {
	String s;
	s << "VM State: " << title << "\n";
	Vector<String> keys, values;
	for(int i = 0; i < REG_COUNT; i++) {
		keys.Add(GetRegName(i));
		values.Add(Format("%08X", (int64)reg32[i]));
	}
	for(int i = 0; i < FLAG_COUNT; i++) {
		keys.Add(GetFlagName(i));
		values.Add((flag[i] ? "true" : "false"));
	}
	int max_len = 0;
	for(const String& l : keys)
		max_len = max(max_len, l.GetCount());
	const String* v = values.Begin();
	for(const String& l : keys) {
		s << "\t" << l;
		int pad = max_len - l.GetCount() + 2;
		s.Cat(' ', pad);
		s << *v++ << "\n";
	}
	return s;
}

String VM::GetRegName(int i) const {
	switch(i) {
		case R0: return t_("R0");
		case R1: return t_("R1");
		case R2: return t_("R2");
		case R3: return t_("R3");
		case R4: return t_("R4");
		case R5: return t_("R5");
		case R6: return t_("R6");
		case R7: return t_("R7");
		case R8: return t_("R8");
		case R9: return t_("R9");
		case R10: return t_("R10");
		case R11: return t_("R11");
		case R12: return t_("R12");
		case R13: return t_("R13");
		case R14: return t_("R14");
		case R15: return t_("R15");
		case PC:  return t_("Program Counter");
		case BAS: return t_("Data Base");
		case ST:  return t_("Stack");
		case STB: return t_("Stack Base");
		case SRC: return t_("Source");
		case DST: return t_("Destination");
		case INPUT: return t_("Input Buffer Cursor");
		case INPUT_REMAINING: return t_("Input Buffer Remaining");
		
		case MICRO0: return t_("Microcode's Internal R0");
	}
	return t_("Invalid Register Number");
}

String VM::GetFlagName(int i) const {
	switch(i) {
		case FLAG_BRANCH:	return t_("Branch");
		case FLAG_ZERO:		return t_("Zero");
		case FLAG_CARRY:	return t_("Carry");
		case FLAG_OVERFLOW:	return t_("Overflow");
		case FLAG_EXTEND:	return t_("Extend");
		case FLAG_NEGATIVE:	return t_("Negative");
		case FLAG_MICRO0:	return t_("Microcode's Internal F0");
	}
	return t_("Invalid Flag Number");
}

void VM::ReadInput() {
	dword& cursor = reg32[INPUT];
	dword& remaining = reg32[INPUT_REMAINING];
	
	if (in) {
		int64 max_read = input_size - remaining;
		Huge huge;
		int64 got = in->Get(huge, max_read);
		byte* dst = data.Begin() + input_begin;
		
		int64 left = (cursor + remaining) % input_size;
		if (left + got <= input_size) {
			dst += left;
			huge.Get(dst, 0, got);
		}
		else {
			byte* left_dst = dst + left;
			int left_read = input_size - left;
			huge.Get(left_dst, 0, left_read);
			byte* right_dst = dst;
			int right_read = got - left_read;
			huge.Get(right_dst, left_read, right_read);
		}
		remaining += got;
		
		if (0) {
			Vector<char> data;
			data.SetCount(remaining + 1);
			huge.Get(data.Begin(), 0, remaining);
			data[remaining] = 0;
			String dbg(data.Begin());
			DUMP(dbg);
		}
	}
}

void VM::InterruptInvalidMemoryAddress() {
	is_halt = true;
	AddError(FileLocation(), t_("Invalid memory address"));
}

void VM::InterruptInvalidInstruction() {
	is_halt = true;
	AddError(FileLocation(), t_("Invalid instruction"));
}

void VM::InterruptStackOverflow() {
	is_halt = true;
	AddError(FileLocation(), t_("Stack overflow"));
}

void VM::InterruptStackUnderflow() {
	is_halt = true;
	AddError(FileLocation(), t_("Stack underflow"));
}

void VM::Push(dword d) {
	dword& stack = reg32[ST];
	dword* ptr = (dword*)(data.Begin() + stack_begin + stack);
	*ptr = d;
	stack += 4;
	if (stack >= stack_size) {
		stack -= 4;
		InterruptStackOverflow();
	}
}

dword VM::Pop() {
	dword& stack = reg32[ST];
	if (stack < 4)
		InterruptStackUnderflow();
	else {
		stack -= 4;
		dword* ptr = (dword*)(data.Begin() + stack_begin + stack);
		return *ptr;
	}
	return 0;
}

void VM::InputSkipSpace() {
	dword& cursor = reg32[INPUT];
	dword& remaining = reg32[INPUT_REMAINING];
	const byte* src = data.Begin() + input_begin + cursor;
	while (remaining) {
		char chr = (char)*src;
		if (!IsSpace(chr))
			break;
		remaining--;
		src++;
		cursor++;
		if (cursor == input_size) {
			src = data.Begin() + input_begin;
			cursor = 0;
		}
	}
}

void VM::InputAcceptExact(dword reg_in, dword flag_out) {
	if (dbg_chk_line == 225) {
		LOG(GetStateString(""));
	}
	ASSERT(reg_in < REG_COUNT);
	dword addr = reg32[reg_in];
	if (addr < total_size) {
		dword cursor = reg32[INPUT];
		dword remaining = reg32[INPUT_REMAINING];
		const char* in_chr = (char*)(data.Begin() + input_begin + cursor);
		byte* chr = (byte*)(data.Begin() + addr);
		byte* end = (byte*)data.End();
		/*if (String(in_chr) == ".,") {
			LOG(GetStateString(".,"));
		}*/
		while (chr != end && remaining) {
			if (*chr == 0) {
				ASSERT(flag_out < FLAG_COUNT);
				flag[flag_out] = true;
				reg32[INPUT] = cursor;
				reg32[INPUT_REMAINING] = remaining;
				return;
			}
			if (*chr != *in_chr)
				break;
			remaining--;
			cursor++;
			in_chr++;
			if (cursor == input_size) {
				cursor = 0;
				in_chr = (char*)(data.Begin() + input_begin);
			}
			chr++;
		}
	}
	flag[flag_out] = false;
}

void VM::InputAcceptId(dword flag_out) {
	dword cursor = reg32[INPUT];
	dword remaining = reg32[INPUT_REMAINING];
	const char* chr = (char*)(data.Begin() + input_begin + cursor);
	bool accept_number = false;
	accepted = "";
	while (remaining) {
		if (!accept_number) {
			if ((*chr >= 'A' && *chr <= 'Z') || (*chr >= 'a' && *chr <= 'z') || (*chr == '_')) {
				accept_number = true;
				accepted.Cat(*chr);
			}
			else break;
		}
		else {
			if ((*chr >= 'A' && *chr <= 'Z') || (*chr >= 'a' && *chr <= 'z') || (*chr == '_') ||
				(*chr >= '0' && *chr <= '9')) {
				accepted.Cat(*chr);
			}
			else break;
		}
		remaining--;
		cursor++;
		chr++;
		if (cursor == input_size) {
			cursor = 0;
			chr = (char*)(data.Begin() + input_begin);
		}
	}
	if (accepted.GetCount()) {
		ASSERT(flag_out < FLAG_COUNT);
		flag[flag_out] = true;
		reg32[INPUT] = cursor;
		reg32[INPUT_REMAINING] = remaining;
	}
	else {
		flag[flag_out] = false;
	}
}

void VM::InputAcceptNumber(dword flag_out) {
	dword cursor = reg32[INPUT];
	dword remaining = reg32[INPUT_REMAINING];
	const char* chr = (char*)(data.Begin() + input_begin + cursor);
	enum {
		INTEGER,
		FRACTION
	};
	int mode = INTEGER;
	accepted = "";
	while (remaining) {
		if (mode == INTEGER) {
			if (*chr == '.') {
				mode = FRACTION;
				accepted.Cat(*chr);
			}
			else if (*chr >= '0' && *chr <= '9') {
				accepted.Cat(*chr);
			}
			else break;
		}
		else if (mode == FRACTION) {
			if (*chr >= '0' && *chr <= '9') {
				accepted.Cat(*chr);
			}
			else break;
		}
		remaining--;
		cursor++;
		chr++;
		if (cursor == input_size) {
			cursor = 0;
			chr = (char*)(data.Begin() + input_begin);
		}
	}
	if (accepted.GetCount()) {
		ASSERT(flag_out < FLAG_COUNT);
		flag[flag_out] = true;
		reg32[INPUT] = cursor;
		reg32[INPUT_REMAINING] = remaining;
	}
	else {
		flag[flag_out] = false;
	}
}

void VM::InputAcceptCharLiteral(dword flag_out) {
	dword cursor = reg32[INPUT];
	dword remaining = reg32[INPUT_REMAINING];
	const char* chr = (char*)(data.Begin() + input_begin + cursor);
	enum {
		LEFT,
		MID,
		FINISH
	};
	int mode = LEFT;
	accepted = "";
	while (remaining && mode != FINISH) {
		if (mode == LEFT) {
			if (*chr == '\'') {
				mode = MID;
			}
			else break;
		}
		else if (mode == MID) {
			if (*chr != '\'') {
				accepted.Cat(*chr);
			}
			else mode = FINISH;
		}
		remaining--;
		cursor++;
		chr++;
		if (cursor == input_size) {
			cursor = 0;
			chr = (char*)(data.Begin() + input_begin);
		}
	}
	if (mode == FINISH) {
		ASSERT(flag_out < FLAG_COUNT);
		flag[flag_out] = true;
		reg32[INPUT] = cursor;
		reg32[INPUT_REMAINING] = remaining;
		accepted = "'" + accepted + "'";
	}
	else {
		flag[flag_out] = false;
	}
}

void VM::OutputAddress(dword addr) {
	if (out && addr < total_size) {
		const char* begin = (const char*)(byte*)(data.Begin() + addr);
		const char* chr = begin;
		const char* end = (const char*)(byte*)data.End();
		while (chr != end) {
			if (!*chr)
				break;
			chr++;
		}
		dword size = chr - begin;
		if (size)
			line.Cat(begin, size);
	}
}

void VM::OutputString(const char* s) {
	if (out) {
		line.Cat(s);
	}
}

void VM::OutputAccepted() {
	if (out) {
		line.Cat(accepted);
		accepted = "";
	}
}

void VM::OutputNewline() {
	if (out) {
		line = TrimRight(line);
		if (line.GetCount()) {
			out->Put('\t', indent);
			out->Put(line);
			line = "";
		}
		if (post)
			out->Put(post);
		out->Put('\n');
		out->Flush();
	}
}

void VM::OutputFlush() {
	if (out) {
		line = TrimRight(line);
		if (line.GetCount()) {
			out->Put('\t', indent);
			out->Put(line);
			if (post)
				out->Put(post);
			out->Put('\n');
			line = "";
		}
		out->Flush();
	}
}

void VM::SetOutputIndent(int i) {
	indent = i;
}


#define MACH_BEGIN(x) \
void VM::Run##x() {\
	const byte* begin = prog->bc.data.Begin(); \
	dword limit = prog->bc.data.GetCount(); \
	while (!is_halt) {\
		if (reg32[PC] >= limit) {InterruptInvalidMemoryAddress(); continue;} \
		byte ins = *(begin + reg32[PC]); \
		switch (ins) {
	
#define MACH_END \
			default: InterruptInvalidInstruction(); \
		} \
	}\
	OutputFlush(); \
}

#define BEGIN_INS(id, name) \
	case id: DbgCheck(#name);
#define BEGIN_INS_1(id, name, arg0) \
	case id: DbgCheck(#name);
#define END_INS break;

#define HALT is_halt = true;
#define SET_EXIT(i) exit_code = i;
#define COPY_CODE_U32(reg) reg32[reg] = *(dword*)(data.Begin() + reg32[PC]);
#define DUMP_CODE(str) LOG(GetStateString(str));

#define INPUT_SKIP_SPACE InputSkipSpace();
#define INPUT_ACCEPT_EXACT(reg_in, flag_out) InputAcceptExact(reg_in, FLAG_##flag_out);
#define INPUT_ACCEPT_ID(flag_out) InputAcceptId(FLAG_##flag_out);
#define INPUT_ACCEPT_NUM(flag_out) InputAcceptNumber(FLAG_##flag_out);
#define INPUT_ACCEPT_CHARLIT(flag_out) InputAcceptCharLiteral(FLAG_##flag_out);

#define OUT(reg) OutputAddress(reg32[reg]);
#define OUT_STRING(string) OutputString(string);
#define OUT_INTSTR(reg) OutputString(IntStr64(reg32[reg]));
#define OUT_ACCEPTED OutputAccepted();
#define OUT_INDENT(i) SetOutputIndent(i);
#define OUT_POST(x) post = x;
#define OUT_NL OutputNewline();

#define SET_FLAG(x, value) flag[FLAG_##x] = value;
#define IS_FLAG(x) flag[FLAG_##x]
#define IS_NOT_FLAG(x) (!flag[FLAG_##x])
#define ASSIGN(from, to) reg32[to] = reg32[from];
#define CMP(a, b, flag_out) flag[FLAG_##flag_out] = reg32[a] != reg32[b];
#define INC(x) reg32[x]++;
#define ADD_VALUE(reg_in0, value, reg_out) reg32[reg_out] = reg32[reg_in0] + value;
#define SUB_VALUE(reg_in0, value, reg_out) reg32[reg_out] = reg32[reg_in0] - value;
#define ADD(reg_in0, reg_in1, reg_out) reg32[reg_out] = reg32[reg_in0] + reg32[reg_in1];
#define SUB(reg_in0, reg_in1, reg_out) reg32[reg_out] = reg32[reg_in0] - reg32[reg_in1];

#define PUSH(reg) Push(reg32[reg]);
#define PUSH_VALUE(value) Push(value);
#define POP(reg) reg32[reg] = Pop();
#define IS_STACK_EMPTY (reg32[ST] == 0)

#define IF_BEGIN(x) if (x) {
#define ELSE } else {
#define END_IF }

#define MICROCODE_IMPL
#include "machines.h"
#undef MICROCODE_IMPL

	
	
	


bool SimpleProgramProcess::Process(String mach, String asm_path, String file_in_path, String file_out_path, String dbg_log_path) {
	FileLocation loc;
	loc.file = file_in_path;
	
	String asm_code = LoadFile(asm_path);
	
	CompilationUnit unit;
	unit.WhenMessage << THISBACK(AddMessage);
	if (!unit.CompileString(mach, asm_path, asm_code))
		return false;
	
	Linker link;
	link.WhenMessage << THISBACK(AddMessage);
	link.Add(unit);
	if (!link.Link())
		return false;
	
	const Object& prog = link.GetObject();
	
	FileIn fin(file_in_path);
	FileOut fout(file_out_path);
	
	if (!fin.IsOpen())
		AddError(loc, "Couldn't open \"" + file_in_path + "\" for reading");
	
	if (!fout.IsOpen())
		AddError(loc, "Couldn't open \"" + file_in_path + "\" for writing");
	
	if (!fin.IsOpen() || !fout.IsOpen())
		return false;
	
	VM vm;
	vm.WhenMessage << THISBACK(AddMessage);
	vm.SetInput(fin);
	vm.SetOutput(fout);
	vm.SetProgram(prog);
	if (dbg_log_path.GetCount())
		vm.LoadDebugCorrect(dbg_log_path);
	vm.Run();
	
	return !vm.GetExitCode();
}


NAMESPACE_TOPSIDE_END
