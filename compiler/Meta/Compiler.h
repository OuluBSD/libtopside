#ifndef _Meta_Compiler_h_
#define _Meta_Compiler_h_

NAMESPACE_OULU_BEGIN

class Compiler : public ErrorSource {
	enum {
		PH_LBL,
		PH_TEXT,
	};
	struct Placeholder : Moveable<Placeholder> {
		byte type;
		dword addr;
		String id;
	};
	
	Object obj;
	Vector<byte> tmp_text, tmp_data;
	Vector<Placeholder> placeholder;
	VectorMap<String, dword> labels;
	
	MachHeaders mach;
	
	void Cat8(byte b);
	void CatInt(dword d);
	void CatString(String s);
	void CatChar(String s);
	void CatId(String s);
	void Set(dword addr, dword value);
	
public:
	typedef Compiler CLASSNAME;
	Compiler();
	
	bool Init(String mach) {return this->mach.Init(mach);}
	bool Process(const Parser& parser);
	
	const Object& GetObject() const {return obj;}
	
};


NAMESPACE_OULU_END

#endif
