#include "Bootstrap.h"

#ifdef flagMAIN

NAMESPACE_TOPSIDE_BEGIN

enum {
	TYPE_CXX,
	TYPE_PYTHON3,
};

void ProcessGrammar(String title, int type) {
	String dir = GetDataFile("");
	String ass_dir = GetFileDirectory(dir.Left(dir.GetCount()-1));
	String out_dir = AppendFileName(ass_dir, "Grammar") + DIR_SEPS;
	
	
	
	String path = AppendFileName(out_dir, title + ".g");
	String name = GetFileName(path);
	
	AntlrGrammar g;
	if (type == TYPE_CXX) {
		g.tk_indent = "TK_INDENT";
		g.tk_dedent = "TK_DEDENT";
	}
	else if (type == TYPE_PYTHON3) {
		g.tk_indent = "'{'";
		g.tk_dedent = "'}'";
	}
	if (!g.Load(path))
		return;
	g.FixNames();
	g.CountUses();
	//g.Sort();
	
	Time now = GetSysTime();
	String time_header = "// Generated at " + Format("%", now);
	
	FileOut c_out(out_dir + "Generated_" + title + ".cpp");
	c_out << time_header << "\n";
	c_out << "#include \"Grammar.h\"\n";
	c_out << "namespace Topside::" << title << " {\n";
	if (type == TYPE_CXX)
		c_out << g.GetCppParserImplementation();
	else if (type == TYPE_PYTHON3)
		c_out << g.GetPython3ParserImplementation();
	c_out << "}\n\n";
	
	FileOut h_out(out_dir + "Generated_" + title + ".inl");
	h_out << time_header << "\n";
	if (type == TYPE_CXX)
		h_out << g.GetCppParserHeader();
	else if (type == TYPE_PYTHON3)
		h_out << g.GetPython3ParserHeader();
	
	FileOut enum_out(out_dir + "Generated_Enum_" + title + ".inl");
	enum_out << time_header << "\n";
	enum_out << "NODE_GRAMMAR_" + title + "_BEGIN = GRAMMAR_ENUM_BEGIN,\n";
	if (type == TYPE_CXX)
		enum_out << g.GetCppParserEnum();
	else if (type == TYPE_PYTHON3)
		enum_out << g.GetPython3ParserEnum();
	
	FileOut enumtype_out(out_dir + "Generated_EnumType_" + title + ".inl");
	enumtype_out << time_header << "\n";
	if (type == TYPE_CXX)
		enumtype_out << g.GetCppParserEnumType();
	else if (type == TYPE_PYTHON3)
		enumtype_out << g.GetPython3ParserEnumType();
}

NAMESPACE_TOPSIDE_END


using namespace Upp;
using namespace Topside;

CONSOLE_APP_MAIN {
	ParserService().Start();
	
	ProcessGrammar("Grammar", TYPE_CXX);
	ProcessGrammar("Meta", TYPE_CXX);
	
	ParserService().Stop();
}

#endif
