#ifndef _Meta_Object_h_
#define _Meta_Object_h_

NAMESPACE_OULU_BEGIN

struct ByteCode : Moveable<ByteCode> {
	Vector<byte> data;
	
	
	void Clear() {data.Clear();}
};


enum {
	SEGTYPE_CODE,
	SEGTYPE_DATA,
	SEGTYPE_TEXT,
};

struct ObjectSegment : Moveable<ObjectSegment> {
	byte type = 0;
	dword offset = 0, size = 0;
	
};

enum {
	SYM_FUNCTION,
	SYM_VAR_STATIC,
	SYM_VAR_STACK,
	SYM_VAR_FIELD,
	SYM_CLASS,
};

struct ObjectSymbol : Moveable<ObjectSymbol> {
	byte sym_type = 0;
	dword offset = 0, size = 0;
	dword type_obj = 0;
	String name;
	int file = 0, line = 0, col = 0;
	Vector<ObjectSymbol> fields;
	
};

struct ObjectHeader : Moveable<ObjectHeader> {
	String abi, mach;
	dword entry = 0;
	Vector<ObjectSegment> segments;
	
	// Debug info
	VectorMap<String, int> function_sym, staticvar_sym;
	Vector<ObjectSymbol> syms;
	Index<String> files;
	
	
	void Clear() {
		abi = "";
		mach = "";
		entry = 0;
		segments.SetCount(0);
		function_sym.Clear();
		staticvar_sym.Clear();
		syms.Clear();
		files.Clear();
	}
};

struct Object : Moveable<Object> {
	ObjectHeader header;
	ByteCode bc;
	
	
	void Clear() {header.Clear(); bc.Clear();}
};

NAMESPACE_OULU_END

#endif
