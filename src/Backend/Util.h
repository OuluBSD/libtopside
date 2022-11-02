#ifndef _Backend_Util_h_
#define _Backend_Util_h_

NAMESPACE_TOPSIDE_BEGIN





struct PathIdentifier {
	enum {
		DIRECT,
		PTR,
		LREF
	};
	
	static const int MAX_PARTS = 32;
	static const int MAX_TAIL_COUNT = 8;
	
	const Token* parts[MAX_PARTS];
	bool is_meta[MAX_PARTS];
	byte head[MAX_TAIL_COUNT];
	byte tail[MAX_TAIL_COUNT];
	int part_count = 0;
	int head_count = 0;
	int tail_count = 0;
	bool is_const = false;
	
	const Token* begin = 0;
	const Token* end = 0;
	
	void Clear();
	String ToString() const;
	bool HasMeta() const;
	bool HasPartialMeta() const;
	bool IsEmpty() const;
	
};

NAMESPACE_TOPSIDE_END

#endif
