#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN

bool IsClose(double a, double b) {
	if (IsFin(a) && IsFin(b)) {
		double diff = fabs(a - b);
		return diff < 0.001;
	}
	else {
		return *(uint64*)&a == *(uint64*)&b;
	}
}

double FastMultiply(double prev_norm, int64 count, double multiplier) {
	if (count <= 0)
		return multiplier;
	if (prev_norm == 0.0 || multiplier == 0.0)
		return 0.0;
	ASSERT(count < 300);
	return FastPow(FastPow(prev_norm, (double)count) * multiplier, 1.0 / (count + 1));
}

void RenameFile(String oldpath, String newpath) {
	rename(oldpath.Begin(), newpath.Begin());
}

void TouchFile(String path) {
	if (!FileExists(path)) {
		FileOut fout(path);
		fout.Close();
	}
}





String EscapeString(String s) {
	s.Replace("\n", "\\n");
	s.Replace("\t", "\\t");
	s.Replace("\r", "\\r");
	s.Replace("\"", "\\\"");
	s.Replace("\\", "\\\\");
	
	return s;
}

String EscapeCharacter(String s) {
	s.Replace("\n", "\\n");
	s.Replace("\t", "\\t");
	s.Replace("\r", "\\r");
	s.Replace("\"", "\\\"");
	s.Replace("\'", "\\\'");
	s.Replace("\\", "\\\\");
	
	return s;
}

String ReadFileName(String s) {
	String out;
	bool force_add = false;
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		if (force_add)
			out.Cat(chr);
		else {
			if (chr == '\\')
				force_add = true;
			else if (IsSpace(chr))
				break;
			else
				out.Cat(chr);
		}
	}
	return out;
}

String GetLineNumStr(String s, bool from_zero) {
	Vector<String> lines = Split(s, "\n", false);
	String out;
	const int tab_size = 4;
	int begin = from_zero ? 0 : 1;
	for(int i = 0; i < lines.GetCount(); i++) {
		String& l = lines[i];
		String nstr = IntStr(begin + i);
		if (l.IsEmpty()) {
			out << nstr << "\n";
		}
		else {
			nstr.Cat('\t', nstr.GetCount() < tab_size ? 2 : 1);
			out << nstr << l << "\n";
		}
	}
	return out;
}

bool ScanBoolString(const String& s) {
	return ToLower(s) == "true" || s == "1";
}

bool IsConstChar(const WString& n, const char* cmp, int cmp_len) {
	if (n.GetCount() < cmp_len)
		return false;
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	if (cmp_len == n.GetCount())
		return true;
	
	return n[cmp_len] == ',';
}

bool IsConstCharEnd(const WString& n, const char* cmp, int cmp_begin, int cmp_len) {
	for(int i = cmp_begin; i < cmp_len; i++) {
		int chr = n[i];
		if (chr != cmp[i])
			return false;
	}
	return true;
}

bool IsArg(const WString& n, const char* cmp, int cmp_len) {
	int count = n.GetCount();
	if (count < cmp_len)
		return false;
	
	for(int i = 0; i < cmp_len; i++) {
		int chr = n[count-cmp_len+i];
		if (chr != cmp[i])
			return false;
	}
	if (cmp_len == n.GetCount())
		return true;
	
	return n[count-cmp_len-1] == ',';
}

bool IsAllSpace(const String& a) {
	bool is_space = true;
	for(int i = 0; i < a.GetCount() && is_space; i++)
		if (!IsSpace(a[i]))
			is_space = false;
	return is_space;
}

bool IsAllDigit(const String& a) {
	if (a.IsEmpty())
		return false;
	for (char chr : a)
		if (!IsDigit(chr))
			return false;
	return true;
}

String CamelToName(String s) {
	String o;
	bool is_cap = true;
	
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		
		if (chr == '_') {
			is_cap = true;
		}
		else {
			if (is_cap || IsUpper(chr))
				o.Cat(ToUpper(chr));
			else
				o.Cat(ToLower(chr));
			is_cap = false;
		}
	}
	
	return o;
}

String ToVarName(String s) {
	String o;
	
	bool all_upper = true;
	for(int i = 0; i < s.GetCount() && all_upper; i++) {
		int chr = s[i];
		if (IsUpper(chr) || chr == '_')
			;
		else
			all_upper = false;
	}
	if (all_upper)
		return ToLower(s);
	
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		
		if (IsUpper(chr)) {
			if (i > 0)
				o.Cat('_');
			o.Cat(ToLower(chr));
		}
		else {
			o.Cat(chr);
		}
	}
	
	return o;
}

String ToCaps(String s) {
	String out;
	
	for(int i = 0; i < s.GetCount(); i++) {
		int chr = s[i];
		
		if (i && IsUpper(chr))
			out << "_";
		out.Cat(ToUpper(chr));
	}
	
	return out;
}



void GetDirectoryFiles(String dir, Index<String>& files) {
	files.Clear();
	FindFile ff;
	if (ff.Search(AppendFileName(dir, "*"))) {
		do {
			String name = ff.GetName();
			if (name == "." || name == "..") continue;
			files.Add(ff.GetPath());
		}
		while (ff.Next());
	}
}

String Join(const Vector<int>& v, String join_str) {
	String s;
	int i = 0;
	for (int val : v) {
		if (i++ > 0)
			s << join_str;
		s << IntStr(val);
	}
	return s;
}


void RunningFlagSingle::Stop() {running = false; while (!stopped) Sleep(100);}

void RunningFlag::Stop() {running = false; while (workers_running > 0) Sleep(sleep_time);}
void RunningFlag::Wait() {while ((int)workers_running != 0) Sleep(100);}













void CommandLineArguments::AddArg(char key, const char* desc, bool has_value, String value_desc) {
	CmdArg& a = args.Add();
	a.key = key;
	a.desc = desc;
	a.has_value = has_value;
	a.value_desc = value_desc;
}

bool CommandLineArguments::Parse() {
	const Vector<String>& args = CommandLine();
	//DUMPC(args);
	
	for(int i = 0; i < args.GetCount(); i++) {
		String arg = args[i];
		
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
				if (!IsAlpha(c) && !IsDigit(c) && c != '_') {
					is_valid_key = false;
					break;
				}
				++key_size;
			}
			if (is_valid_key && is_var) {
				String key = arg.Mid(1, key_size);
				String value = arg.Mid(2+key_size);
				NumberParser p(value, 0);
				if (p.type == NumberParser::FLOAT || p.type == NumberParser::DOUBLE)
					vars.Add(key, p.d);
				else if (p.type != NumberParser::INVALID)
					vars.Add(key, p.i32);
				else
					vars.Add(key, value);
				found = true;
			}
			else {
				char key = arg[1];
				if (key) {
					for(int j = 0; j < this->args.GetCount(); j++) {
						CmdArg& a = this->args[j];
						if (a.key == key) {
							found = true;
							CmdInput& in = inputs.Add();
							in.key = key;
							if (a.has_value) {
								if (i+1 >= args.GetCount()) {
									Cerr() << "No value provided: " << arg << EOL;
									return false;
								}
								in.value = args[i+1];
								i++;
							}
							break;
						}
					}
				}
			}
		}
		
		if (!found) {Cerr() << "Invalid argument: " << arg << EOL; return false;}
	}
	
	return true;
}

void CommandLineArguments::PrintHelp() {
	String exe = GetExeFilePath();
	int i = exe.ReverseFind(DIR_SEPS);
	if (i >= 0)
		exe = exe.Mid(i+1);
	
	Stream& cout = Cout();
	cout << exe << " [-";
	for(int i = 0; i < args.GetCount(); i++)
		if (args[i].has_value)
			cout << args[i].key;
	cout << " value]";
	
	cout << " [-";
	for(int i = 0; i < args.GetCount(); i++)
		if (!args[i].has_value)
			cout << args[i].key;
	cout << "]" << EOL;
	
	for(int i = 0; i < args.GetCount(); i++) {
		CmdArg& a = args[i];
		cout << "\t-" << a.key;
		if (a.has_value)
			cout << " " << (a.value_desc.IsEmpty() ? (String)"value" : a.value_desc);
		cout << ": " << a.desc << EOL;
	}
}







String FindShareDir() {
	String config_share = ConfigFile("share");
	if (DirectoryExists(config_share))
		return config_share;
	
	#if defined flagUWP
	String home_upphub_share = "ms-appx://share";
	#elif defined flagWIN32
	String home_upphub_share = "C:\\git\\libtopside\\share";
	if (!DirectoryExists(home_upphub_share))
		home_upphub_share = "C:\\libtopside\\share";
	#else
	String home_upphub_share = AppendFileName(GetHomeDirFile("libtopside"), "share");
	#endif
	
	if (DirectoryExists(home_upphub_share))
		return home_upphub_share;
	
	#if defined flagLINUX
	return "/usr/share";
	#elif defined flagFREEBSD
	return "/usr/local/share";
	#else
	return config_share;
	#endif
}

String ShareDirFile(String file) {
	return AppendFileName(FindShareDir(), file);
}

String RealizeShareFile(String rel_path) {
	if (rel_path.IsEmpty())
		return String();
	
	#ifdef flagPOSIX
	if (rel_path.Left(2) == "~/") {
		rel_path = AppendFileName(GetHomeDirectory(), rel_path.Mid(2));
	}
	#endif
	
	int tries_count = 8;
	#ifdef flagDEBUG
	tries_count++;
	#endif
	
	for (int tries = 0; tries < tries_count; tries++) {
		String path;
		switch (tries) {
			case 0: path = rel_path; break;
			case 1: path = ShareDirFile(rel_path); break;
			case 2: path = ShareDirFile(AppendFileName("imgs", rel_path)); break;
			case 3: path = ShareDirFile(AppendFileName("videos", rel_path)); break;
			case 4: path = ShareDirFile(AppendFileName("sounds", rel_path)); break;
			case 5: path = ShareDirFile(AppendFileName("models", rel_path)); break;
			case 6: path = ShareDirFile(AppendFileName("sounds", rel_path)); break;
			case 7: path = ShareDirFile(AppendFileName("soundfonts", rel_path)); break;
			#ifdef flagDEBUG
			case 8: path = GetDataDirectoryFile(rel_path); break;
			#endif
		}
		
		//LOG("RealizeShareFile: testing path: " << path);
		
		if (FileExists(path) || DirectoryExists(path))
			return path;
	}
	
	String local_file = FindLocalFile(rel_path);
	if (FileExists(local_file) || DirectoryExists(local_file))
		return local_file;
	
	return rel_path;
}

String TrimTrailingDirSep(String file) {
	while (file.GetCount() && file[file.GetCount()-1] == DIR_SEP)
		file = file.Left(file.GetCount()-1);
	
	return file;
}


void SetCoutLog() {StdLogSetup(LOG_COUT|LOG_FILE);}





bool __enable_opengl_debug;
bool IsGfxAccelDebugMessages() {return __enable_opengl_debug;}
void EnableGfxAccelDebugMessages(bool b) {__enable_opengl_debug = b;}


int HexDigitAny(int c) {
	if (c >= 'a' && c <= 'f') return 10 + c - 'a';
	if (c >= 'A' && c <= 'F') return 10 + c - 'A';
	if (c >= '0' && c <= '9') return c - '0';
	ASSERT(0);
	return -1;
}



String CenteredString(const String& s, int lw) {
	String o;
	Vector<String> lines = Split(s, "\n");
	for(int i = 0; i < lines.GetCount(); i++) {
		if (i) o.Cat('\n');
		String& j = lines[i];
		WString l = j.ToWString();
		int c = l.GetCount();
		int pad = (lw - c) / 2;
		if (pad > 0)
			o.Cat(' ', pad);
		o.Cat(j);
	}
	return o;
}

String FormatScientific(double d) {
	char buffer [100];
	int len = snprintf ( buffer, 100, "%.8g", d);
	return String(buffer, len);
}



float ConvertDipsToPixels(float dips, float dpi) {
    constexpr float dips_per_inch = 96.0f;
    return floorf(dips * dpi / dips_per_inch + 0.5f); // Round to nearest integer.
}

Vector<String> local_file_dirs;

void AddLocalFileDirectory(String dir) {
	local_file_dirs.Add(dir);
}

String FindLocalFile(String filename) {
	String exe_dir_file = GetExeDirFile(filename);
	if (FileExists(exe_dir_file))
		return exe_dir_file;
	
	for(int i = 0; i < local_file_dirs.GetCount(); i++) {
		String dir_file = AppendFileName(local_file_dirs[i], filename);
		if (FileExists(dir_file) || DirectoryExists(dir_file))
			return dir_file;
	}
	
	return ConfigFile(filename);
}



NAMESPACE_TOPSIDE_END
