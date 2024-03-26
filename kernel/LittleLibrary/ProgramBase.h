#ifndef _LittleLibrary_ProgramBase_h_
#define _LittleLibrary_ProgramBase_h_



struct CmdArg {
	char key;
	KString desc, value_desc;
	bool has_value;
};

struct CmdInput {
	char key;
	KString value;
};


class CommandLineArguments {
	static const int max_inputs = 30;
	static const int max_args = 30;
	static const int max_vars = 30;
	
	int arg_count = 0;
	int input_count = 0;
	int var_count = 0;
	CmdArg				args[max_args];
	CmdInput			inputs[max_inputs];
	const char*			var_keys[max_vars];
	Object				var_values[max_vars];
	KString				appname;
	
	void AddVar(const KString& key, const Object& val);
	CmdInput& AddInput();
	
public:
	CommandLineArguments() {}
	
	void SetAppName(const KString& c) {appname = c;}
	void AddArg(char key, const char* desc, bool has_value, KString value_desc="value");
	bool Parse(int argc, const char** argv);
	void PrintHelp();
	
	bool IsArg(char c) const;
	KString GetArg(char c) const;
	
	const CmdInput* GetInputs() const {return inputs;}
	const Object* GetVariables() const {return var_values;}
	
	int GetInputCount() const {return input_count;}
	int GetVarCount() const {return var_count;}
	int GetArgCount() const {return arg_count;}
	
};



class ProgramBase {
	int exit_code = 0;
	
protected:
	CommandLineArguments args;
	
public:
	typedef ProgramBase CLASSNAME;
	ProgramBase();
	virtual ~ProgramBase();
	
	virtual bool Init(int argc, const char** argv);
	virtual void Run();
	
	int GetExitCode() const {return exit_code;}
	
	void SetExitCode(int c) {exit_code = c;}
	
	virtual bool Key(dword key, int count) {return false;}
	
};


#endif
