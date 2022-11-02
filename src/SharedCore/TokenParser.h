#ifndef _SharedCore_TokenParser_h_
#define _SharedCore_TokenParser_h_

NAMESPACE_UPP


struct IdParser {
	bool is_valid = false;
	const String& input;
	int pos;
	String id;
	
	IdParser(const String& input, int pos) : input(input), pos(pos) {Parse();}
	
	void Parse();
	
};

struct StringParser {
	bool is_valid = false;
	const String& input;
	int pos;
	String str;
	int delim = '\"';
	bool checkend = true;
	
	StringParser(const String& input, int pos, int delim='\"', bool checkend=true) :
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
	const String& input;
	int cursor;
	String str;
	uint32 u32;
	int32 i32;
	int64 i64;
	float f;
	double d;
	
	NumberParser(const String& input, int cursor) : input(input), cursor(cursor) {Parse();}
	
	void Parse();
	
};


END_UPP_NAMESPACE

#endif
