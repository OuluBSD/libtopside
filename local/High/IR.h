#ifndef _High_IR_h_
#define _High_IR_h_

namespace UPP {


typedef enum {
	#define IR(x) IR_##x,
	#include "IrList.inl"
	#undef IR
} IrCode;


struct VmState;


struct IrValue {
	static int total;
	static int GetTotalCount();
	static int GetMaxTotalCount();
	
	typedef enum {
		V_VOID,
		V_REG,
		V_CSTRING,
		V_STRING,
		V_WSTRING,
		V_INT32,
		V_INT64,
		V_UINT64,
		V_DOUBLE,
		V_HIVAL,
		V_MAP,
		V_ARRAY,
		V_LABEL_INT,
		V_LABEL_STR,
		V_VARSTACK,
	} Type;
	
	/*typedef enum {
		REG_VOID,
		REG_R0,
		REG_R1,
		REG_R2,
		REG_R3,
		REG_R4,
	} RegType;*/
	static const int REG_COUNT = 5;
	
	Type type;
	const char* str;
	String s;
	WString ws;
	int i32;
	union {
		int64 i64;
		uint64 u64;
		double d;
	};
	HiValue hv;
	ArrayMap<String, IrValue> map;
	Array<IrValue> array;
	
	
	IrValue();
	//IrValue(IrValue&& v);
	IrValue(const IrValue& v);
	IrValue(const char* s);
	IrValue(String s);
	IrValue(WString s);
	IrValue(int i);
	IrValue(int64 i);
	IrValue(uint64 i);
	IrValue(double d);
	IrValue(const HiValue& v);
	
	
	IrValue& operator=(const IrValue& v);
	
	
	void Clear();
	void SetEmptyMap();
	void SetEmptyArray();
	void MapSet(const IrValue& key, const IrValue& value);
	void ArrayAdd(const IrValue& value);
	IrValue& SetRegisterValue(int r);
	IrValue& SetLabel(int i);
	IrValue& SetLabel(String s);
	IrValue& SetVarStackValue(int offset);
	bool IsVoid() const;
	bool IsMap() const;
	bool IsArray() const;
	bool IsInt() const;
	bool IsAnyString() const;
	bool IsVarStackValue(int offset) const;
	bool IsRegister(int reg) const;
	bool IsRegister() const;
	bool IsLabel() const;
	String GetString() const;
	int GetCount() const;
	String GetTypeString() const;
	String GetTextValue() const;
	String ToString() const;
	HiValue AsHiValue(VmState& s) const;
	
	const VectorMap<IrValue, IrValue>& GetMap() const;
	
};

struct IR : Moveable<IR> {
	IrCode code;
	IrValue arg[3];
	String label;
	const char* file;
	int line;
	CParser::Pos codepos;
	
	
	String GetCodeString() const;
	String ToString() const;
	
};


}

#endif
