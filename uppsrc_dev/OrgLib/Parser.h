#ifndef _OrgLib_Parser_h_
#define _OrgLib_Parser_h_


BEGIN_TEXTLIB_NAMESPACE


#define META_INSTRUCTION_LIST \
	INS(IMPORT_VIRTUAL_MODULE) \
	INS(IMPORT_MODULE) \
	INS(BEGIN_MODULE) \
	INS(DECLARE_CLASS) \
	INS(DECLARE_FUNCTION) \
	INS(BEGIN_CLASS) \
	INS(DECLARE_METHOD) \
	INS(DECLARE_FUNCTION_VIRTUAL) \
	INS(DECLARE_FUNCTION_OVERRIDE) \
	INS(END_CLASS) \
	INS(BEGIN_FUNCTION) \
	INS(BEGIN_STATEMENT) \
	INS(INITIALIZE_MODULE) \
	INS(UNINITIALIZE_MODULE) \
	INS(CALL_FUNCTION) \
	INS(END_STATEMENT) \
	INS(END_FUNCTION) \
	INS(BEGIN_METHOD) \
	INS(END_METHOD) \
	INS(DECLARE_META_FUNCTION) \
	INS(BEGIN_META_FUNCTION) \
	INS(DECLARE_META_STATEMENT) \
	INS(END_META_FUNCTION) \
	INS(END_MODULE) \



typedef enum {
	#define INS(x) x,
	META_INSTRUCTION_LIST
	#undef INS
} MetaInstructionType;


struct MetaStatementString {
	struct Param : Moveable<Param> {
		String name, type;
	};
	String meta_instruction;
	Vector<String> class_path;
	String name;
	String ret;
	String comment;
	Vector<Param> params;
	
	void Dump();
	String GetInstruction() const;
};

class Parser {
	
public:
	
	static bool ParseMetaStatementString(const String& in, MetaStatementString& out);
	static bool ParseMetaInstructionType(const String& in, MetaInstructionType& out);
	static bool ParseTypeString(const String& in, Vector<String>& out);
	static bool ParseTypeString(CParser& p, Vector<String>& out);
	
	static String GetMetaInstructionString(MetaInstructionType type);
	
};


END_TEXTLIB_NAMESPACE


#endif
