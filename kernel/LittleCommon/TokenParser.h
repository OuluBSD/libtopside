#ifndef _LittleCommon_TokenParser_h_
#define _LittleCommon_TokenParser_h_


struct IdParser {
	bool is_valid = false;
	const KString& input;
	int pos;
	KString id;
	
	IdParser(const KString& input, int pos) : input(input), pos(pos) {Parse();}
	
	void Parse();
	
};

struct StringParser {
	bool is_valid = false;
	const KString& input;
	int pos;
	KString str;
	int delim = '\"';
	bool checkend = true;
	
	StringParser(const KString& input, int pos, int delim='\"', bool checkend=true) :
		input(input), pos(pos), delim(delim), checkend(checkend) {Parse();}
	
	void Parse();
	
};

struct NumberParser {
	enum {
		INVALID,
		OCT,
		HEX,
		INT,
		BIN,
		FLOAT,
		DOUBLE
	};
	
	int type = 0;
	const KString& input;
	int cursor;
	KString str;
	uint32 u32;
	int32 i32;
	int64 i64;
	float f;
	double d;
	
	NumberParser(const KString& input, int cursor) : input(input), cursor(cursor) {Parse();}
	
	void Parse();
	
};



#endif
