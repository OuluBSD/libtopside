#ifndef _IfaceCore_Package_h_
#define _IfaceCore_Package_h_

NAMESPACE_PLAN_BEGIN

struct Class {
	String name;
	
	Class& SetName(String s) {name = s; return *this;}
	String GetTreeString(int indent);
};

struct EnumValue {
	String name, value;
	
	EnumValue& SetName(String s) {name = s; return *this;}
	EnumValue& Set(String value) {this->value = value; return *this;}
	String GetTreeString(int indent);
	
};

struct Enum {
	ArrayMap<String, EnumValue> keys;
	String name;
	
	
	Enum& SetName(String s) {name = s; return *this;}
	EnumValue& AddKey(String key, String value);
	String GetTreeString(int indent);
	
};

struct Namespace {
	ArrayMap<String, Enum> enums;
	ArrayMap<String, Class> classes;
	
	
	Enum& AddEnum(String name);
	Class& AddClass(String name);
	String GetTreeString(int indent);
	
};

struct Function {
	Vector<String> arg_str;
	String ret_str;
	String name;
	
	
	Function& SetName(String s) {name = s; return *this;}
	Function& Arg(String param);
	Function& Ret(String type);
	String GetTreeString(int indent);
	
};

struct Interface {
	ArrayMap<String, Class> nat_cls, util_cls;
	ArrayMap<String, Function> funcs;
	
	Class& AddNativeClass(String name);
	Class& AddUtilClass(String name);
	Function& AddFunction(String name);
	String GetTreeString(int indent);
};

struct Vendor {
	String name;
	
	
	Vendor& SetName(String s) {name = s; return *this;}
	String GetTreeString(int indent);
};

struct Package {
	Namespace ns;
	Interface iface;
	ArrayMap<String, Vendor> vendors;
	
	Vendor& AddVendor(String name);
	
	virtual const char* GetTitle() const = 0;
	virtual const char* GetAbbreviation() const = 0;
	
	String GetTreeString(int indent);
	void Dump();
	void Export(CompilationUnit& cu);
	
};

NAMESPACE_PLAN_END

#endif
