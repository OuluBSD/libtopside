#ifndef _Meta_Parser_h_
#define _Meta_Parser_h_

NAMESPACE_OULU_BEGIN

enum {
	IR_INS,
	IR_LBL,
};

struct IR : Moveable<IR> {
	byte type = 0;
	int id = 0;
	
	String str_value;
	double dbl_value = 0;
	int int_value = 0;
	
	
	String ToString() const;
	String GetTypeString() const;
};

enum {
	ARG_NULL,
	ARG_INT,
	ARG_STRING,
	ARG_CHAR,
	ARG_ID,
};

struct MachHeaders {
	struct InsRule : Moveable<InsRule> {
		int type[3] = {0,0,0};
		int arg_count = 0;
		
		void Set(String type) {arg_count = 1; this->type[0] = ParseType(type);}
		int ParseType(String t) {
			if (t == "INT")		return ARG_INT;
			if (t == "STRING")	return ARG_STRING;
			if (t == "CHAR")	return ARG_CHAR;
			if (t == "ID")		return ARG_ID;
			return ARG_NULL;
		}
	};
	
	VectorMap<String, InsRule> rules;
	String mach;
	
	bool Init(String mach);
	void AddInstruction(String key) {rules.Add(key);}
	void AddInstruction(String key, String arg0) {rules.Add(key).Set(arg0);}
};

class Parser : public ErrorSource {
	
	
	MachHeaders mach;
	
	const Tokenizer* tk;
	int cursor;
	
	Vector<IR> ir;
	
	bool CheckEnd();
	bool Is2(int tk0, int tk1);
public:
	typedef Parser CLASSNAME;
	Parser();
	
	bool Init(String mach) {return this->mach.Init(mach);}
	bool Process(const Tokenizer& token);
	void Dump() const;
	String GetIRString(const IR& ir) const;
	
	const Vector<IR>& GetIR() const {return ir;}
	
};

NAMESPACE_OULU_END

#endif
