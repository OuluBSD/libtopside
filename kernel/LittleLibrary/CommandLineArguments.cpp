#include "LittleLibrary.h"


bool CommandLineArguments::IsArg(char c) const {
	for (const CmdInput& in : inputs) {
		if (in.key == c)
			return true;
	}
	return false;
}

KString CommandLineArguments::GetArg(char c) const {
	for (const CmdInput& in : inputs) {
		if (in.key == c)
			return in.value;
	}
	return KString();
}

void CommandLineArguments::AddArg(char key, const char* desc, bool has_value, KString value_desc) {
	ASSERT(arg_count < max_args);
	CmdArg& a = args[arg_count++];
	a.key = key;
	a.desc = desc;
	a.has_value = has_value;
	a.value_desc = value_desc;
}

bool CommandLineArguments::Parse(int argc, const char** argv) {
	
	for(int i = 0; i < argc; i++) {
		KString arg = argv[i];
		
		if (arg.GetCount() < 2) return false;
		
		bool found = false;
		
		if (arg[0] == '-') {
			bool is_valid_key = true;
			bool is_var = false;
			int key_size = 0;
			for(int i = 1; i < arg.GetCount(); i++) {
				char c = arg[i];
				if (i > 1 && c == '=') {
					is_var = true;
					break;
				}
				if (!::IsAlpha(c) && !::IsDigit(c) && c != '_') {
					is_valid_key = false;
					break;
				}
				++key_size;
			}
			if (is_valid_key && is_var) {
				KString key = arg.Mid(1, key_size);
				KString value = arg.Mid(2+key_size);
				NumberParser p(value, 0);
				if (p.type == NumberParser::FLOAT || p.type == NumberParser::DOUBLE)
					AddVar(key, p.d);
				else if (p.type != NumberParser::INVALID)
					AddVar(key, p.i32);
				else
					AddVar(key, value);
				found = true;
			}
			else {
				char key = arg[1];
				if (key) {
					for(int j = 0; j < this->arg_count; j++) {
						CmdArg& a = this->args[j];
						if (a.key == key) {
							found = true;
							CmdInput& in = AddInput();
							in.key = key;
							if (a.has_value) {
								if (i+1 >= argc) {
									KCerr() << "No value provided: " << arg << K_EOL;
									return false;
								}
								in.value = argv[i+1];
								i++;
							}
							break;
						}
					}
				}
			}
		}
		
		if (!found) {KCerr() << "Invalid argument: " << arg << K_EOL; return false;}
	}
	
	return true;
}

void CommandLineArguments::PrintHelp() {
	KString exe = appname;
	/*int i = exe.ReverseFind(DIR_SEPS);
	if (i >= 0)
		exe = exe.Mid(i+1);*/
	
	KStream& cout = KCout();
	cout << exe << " [-";
	for(int i = 0; i < arg_count; i++)
		if (args[i].has_value)
			cout << args[i].key;
	cout << " value]";
	
	cout << " [-";
	for(int i = 0; i < arg_count; i++)
		if (!args[i].has_value)
			cout << args[i].key;
	cout << "]" << K_EOL;
	
	for(int i = 0; i < arg_count; i++) {
		CmdArg& a = args[i];
		cout << "\t-" << a.key;
		if (a.has_value)
			cout << " " << (a.value_desc.IsEmpty() ? (KString)"value" : a.value_desc);
		cout << ": " << a.desc << K_EOL;
	}
}

void CommandLineArguments::AddVar(const KString& key, const Object& val) {
	
	TODO
	
}


