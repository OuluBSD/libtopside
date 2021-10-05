#include <Local/Local.h>

using namespace TS;
using namespace UPP;

struct IdParser0 {
	bool is_valid = false;
	const String& input;
	int pos;
	String id;
	
	IdParser0(const String& input, int pos) : input(input), pos(pos) {Parse();}
	
	void Parse();
	
};

void IdParser0::Parse() {
	const String& n = input;
	int& cursor = pos;
	
	if (cursor < input.GetCount()) {
		int chr = input[cursor];
		
		if (IsAlpha(chr) || chr == '_') {
			id.Cat(chr);
			cursor++;
			while (cursor < input.GetCount()) {
				int chr = input[cursor];
				if (IsAlpha(chr) || chr == '_' || IsDigit(chr)) {
					id.Cat(chr);
					cursor++;
				}
				else
					break;
			}
			is_valid = true;
		}
	}
}


bool IsUpperString(String s) {
	for(int i = 0; i < s.GetCount(); i++)
		if (IsLower(s[i]))
			return false;
	return true;
}

bool IsLowerString(String s) {
	for(int i = 0; i < s.GetCount(); i++)
		if (IsUpper(s[i]))
			return false;
	return true;
}

bool CamelCase(String s, String& new_id) {
	if (s.Left(3) == "gl_")
		return false;
	if (s.Left(2) == "m_")
		s = s.Mid(2);
	
	Vector<String> parts;
	int b = 0;
	for(int i = 1; i < s.GetCount(); i++) {
		if (IsUpper(s[i])) {
			parts << s.Mid(b, i-b);
			b = i;
		}
	}
	parts << s.Mid(b, s.GetCount()-b);
	if (parts.GetCount() < 2)
		return false;
	if (!IsLowerString(parts[0]))
		return false;
	for(int i = 1; i < parts.GetCount(); i++) {
		String& part = parts[i];
		if (part.GetCount() < 2)
			return false;
		if (!(IsUpperString(part.Left(1)) && IsLowerString(part.Mid(1))))
			return false;
	}
	
	// built in camel case
	if (parts[0] == "gl")
		return false;
	
	new_id = "";
	for (String& part : parts) {
		if (new_id.GetCount())
			new_id.Cat('_');
		new_id += ToLower(part);
	}
	return true;
}

String CleanCamelCase(bool is_header, String src) {
	String out;
	String new_id;
	int prev_end = 0;
	for(int i = 0; i < src.GetCount(); i++) {
		if (!i || src[i-1] == '\n') {
			if (src[i] == '#') {
				int j = src.Find("\n", i);
				if (j < 0) break;
				i = j;
				continue;
			}
		}
		
		IdParser0 ip(src, i);
		if (ip.is_valid) {
			if (CamelCase(ip.id, new_id)) {
				if (ip.id.Left(2) == "m_") {
					if (!is_header)
						new_id = "this->" + new_id;
				}
				LOG(ip.id << " --> " << new_id);
				
				out += src.Mid(prev_end, i - prev_end);
				out += new_id;
				prev_end = ip.pos;
			}
			i = ip.pos - 1;
		}
	}
	out += src.Mid(prev_end, src.GetCount() - prev_end);
	return out;
}

CONSOLE_APP_MAIN {
	SetCoutLog();
	
	if (CommandLine().IsEmpty()) {
		LOG(".upp file required as program argument");
		return;
	}
	
	String upp_file = CommandLine()[0];
	String prj_dir = GetFileDirectory(upp_file);
	String assembly_dir = GetFileDirectory(prj_dir.Left(prj_dir.GetCount()-1));
	String title = GetFileTitle(upp_file);
	
	LOG("Title: " << title);
	LOG("Assembly dir: " << assembly_dir);
	
	// Load packages
	UppAssembly ass;
	ass.AddPath(assembly_dir);
	
	UppAssemblyData ass_data(ass);
	UppAssemblyCache ass_cache(ass_data);
	
	UppProject& main_prj = ass_data.GetProject(title);
	
	for(int i = 0; i < main_prj.GetFileCount(); i++) {
		LOG(i << ": " << main_prj.GetFile(i));
		
		String path = AppendFileName(prj_dir, main_prj.GetFile(i));
		String content = LoadFile(path);
		String new_content = CleanCamelCase(GetFileExt(path) == ".h", content);
		
		if (content != new_content) {
			//LOG(new_content);
			FileOut fout(path);
			fout << new_content;
			fout.Flush();
		}
	}
	
}
