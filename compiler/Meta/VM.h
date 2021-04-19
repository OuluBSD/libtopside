#ifndef _Meta_VM_h_
#define _Meta_VM_h_

NAMESPACE_OULU_BEGIN


class VM : public ErrorSource {
	Stream* in = NULL;
	Stream* out = NULL;
	const Object* prog = NULL;
	
	enum {
		FLAG_BRANCH,
		FLAG_ZERO,
		FLAG_CARRY,
		FLAG_OVERFLOW,
		FLAG_EXTEND,
		FLAG_NEGATIVE,
		FLAG_MICRO0,
		
		FLAG_COUNT
	};
	
	enum {
		R0,
		R1,
		R2,
		R3,
		R4,
		R5,
		R6,
		R7,
		R8,
		R9,
		R10,
		R11,
		R12,
		R13,
		R14,
		R15,
		PC,   // program counter
		BAS,  // base
		ST,   // stack
		STB,  // stack base
		SRC,  // source
		DST,  // destination
		INPUT,
		INPUT_REMAINING,
		
		MICRO0, // microcode's own
		
		REG_COUNT
	};
	
	String accepted, line;
	byte indent = 0;
	const char* post = NULL;
	Vector<byte> data;
	dword reg32[REG_COUNT];
	bool flag[FLAG_COUNT];
	dword pc;
	
	dword prog_size = 0, input_size = 0, output_size = 0, user_size = 0, stack_size = 0, total_size = 0;
	dword input_begin = 0, output_begin = 0, user_begin = 0, stack_begin = 0;
	int exit_code = 0;
	bool is_halt = false;
	
	Vector<String> dbg_chk_lines;
	int dbg_chk_line = 0;
	
	#define MACH_NAME(x) void Run##x();
	#define MICROCODE_INFO
	#include "machines.h"
	#undef MICROCODE_INFO
	
	
	void InterruptInvalidMemoryAddress();
	void InterruptInvalidInstruction();
	void InterruptStackOverflow();
	void InterruptStackUnderflow();
	
	void Push(dword d);
	dword Pop();
	
	void ReadInput();
	void InputSkipSpace();
	void InputAcceptExact(dword reg_in, dword flag_out);
	void InputAcceptId(dword flag_out);
	void InputAcceptNumber(dword flag_out);
	void InputAcceptCharLiteral(dword flag_out);
	
	void OutputAddress(dword addr);
	void OutputString(const char* s);
	void OutputAccepted();
	void OutputNewline();
	void OutputFlush();
	void SetOutputIndent(int i);
	
	void DbgCheck(String s);
	
public:
	typedef VM CLASSNAME;
	VM();
	
	void SetInput(Stream& s) {in  = &s;}
	void SetOutput(Stream& s) {out = &s;}
	void SetProgram(const Object& obj) {prog = &obj;}
	void Run();
	void Reset();
	void LoadDebugCorrect(String file_path);
	String GetStateString(String title) const;
	String GetRegName(int i) const;
	String GetFlagName(int i) const;
	
	int GetExitCode() const {return exit_code;}
	
};


struct SimpleProgramProcess : public ErrorSourceBuffered {
	
	
	typedef SimpleProgramProcess CLASSNAME;
	
	SimpleProgramProcess() : ErrorSourceBuffered("SimpleProgramProcess") {}
	
	
	void AddMessage(ProcMsg msg) {ErrorSource::AddMessage(msg);}
	bool Process(String mach, String asm_path, String file_in_path, String file_out_path, String dbg_log_path="");
	
};


NAMESPACE_OULU_END

#endif
